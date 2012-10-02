/*
  multisend_c.cpp: transfer of multi message data

  (C) Copyright 2009 - 2012 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#include "multisend_c.h"

#include <IsoAgLib/driver/system/impl/system_c.h>
#include <IsoAgLib/scheduler/impl/scheduler_c.h>
#include <IsoAgLib/comm/impl/isobus_c.h>
#include <IsoAgLib/comm/Part5_NetworkManagement/impl/isofiltermanager_c.h>
#include <IsoAgLib/util/iassert.h>

#include "../imultisendstreamer_c.h"

#if DEBUG_MULTISEND
  #ifdef SYSTEM_PC
    #include <iostream>
  #else
    #include <supplementary_driver/driver/rs232/impl/rs232io_c.h>
  #endif
#endif

#if defined(_MSC_VER)
#pragma warning( disable : 4355 )
#endif

/** @todo SOON-178 figure that one out... new ISO says we can put out head2head messages! */
static const uint8_t scui8_isoCanPkgDelay = 4;



namespace __IsoAgLib {
/** C-style function, to get access to the unique MultiSend_c singleton instance
  * if more than one CAN BUS is used for IsoAgLib, an index must be given to select the wanted BUS
  */
MultiSend_c &getMultiSendInstance( uint8_t aui8_instance )
{
  MACRO_MULTITON_GET_INSTANCE_BODY(MultiSend_c, PRT_INSTANCE_CNT, aui8_instance);
}

/** This is mostly used for debugging now... */
void SendUploadBase_c::set (uint8_t* apui8_buffer, uint32_t aui32_bufferSize)
{
  /// Use BUFFER - NOT MultiSendStreamer!
  vec_uploadBuffer.clear();
  vec_uploadBuffer.reserve (aui32_bufferSize);

  uint32_t i=0;
  for (; i < aui32_bufferSize; i++) {
    vec_uploadBuffer.push_back (*apui8_buffer);
    apui8_buffer++;
  }
  for (; i < 8; i++) {
    vec_uploadBuffer.push_back (0xFF);
  }
}


void
SendUploadBase_c::set (uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7, uint8_t byte8)
{
  vec_uploadBuffer.clear();
  vec_uploadBuffer.reserve (8);

  vec_uploadBuffer.push_back (byte1);
  vec_uploadBuffer.push_back (byte2);
  vec_uploadBuffer.push_back (byte3);
  vec_uploadBuffer.push_back (byte4);
  vec_uploadBuffer.push_back (byte5);
  vec_uploadBuffer.push_back (byte6);
  vec_uploadBuffer.push_back (byte7);
  vec_uploadBuffer.push_back (byte8);
}


void
SendUploadBase_c::set (uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7, uint8_t byte8, uint8_t byte9)
{
  /// Use BUFFER - NOT MultiSendStreamer!
  vec_uploadBuffer.clear();
  vec_uploadBuffer.reserve (9);

  vec_uploadBuffer.push_back (byte1);
  vec_uploadBuffer.push_back (byte2);
  vec_uploadBuffer.push_back (byte3);
  vec_uploadBuffer.push_back (byte4);
  vec_uploadBuffer.push_back (byte5);
  vec_uploadBuffer.push_back (byte6);
  vec_uploadBuffer.push_back (byte7);
  vec_uploadBuffer.push_back (byte8);
  vec_uploadBuffer.push_back (byte9);
}


const
SendUploadBase_c& SendUploadBase_c::operator= (const SendUploadBase_c& r_source)
{
  vec_uploadBuffer = r_source.vec_uploadBuffer;
  return r_source;
}


SendUploadBase_c::SendUploadBase_c (const SendUploadBase_c& r_source)
  : vec_uploadBuffer (r_source.vec_uploadBuffer)
{
}




  /************************************/
 /**** MultiSend_c Implementation ****/
/************************************/


MultiSend_c::MultiSend_c()
  : SchedulerTask_c( 100, true )
  #if defined(ENABLE_MULTIPACKET_VARIANT_FAST_PACKET)
  , mui8_nextFpSequenceCounter(0)
  #endif
  , mlist_sendStream()
  , mt_handler(*this)
  , mt_customer(*this)
{
}


void
MultiSend_c::init()
{
  isoaglib_assert (!initialized());

  getSchedulerInstance().registerTask( *this, false );
  getIsoMonitorInstance4Comm().registerControlFunctionStateHandler( mt_handler );

  #if defined(ENABLE_MULTIPACKET_VARIANT_FAST_PACKET)
  mui8_nextFpSequenceCounter = 0;
  #endif

  // Receive filters for ISO 11783 are created selectively in the SA claim handler,
  // so that only messages that are directed to a local SA are received

  setInitialized();
}


void
MultiSend_c::close()
{
  isoaglib_assert (initialized());

  getIsoMonitorInstance4Comm().deregisterControlFunctionStateHandler( mt_handler );
  getSchedulerInstance().deregisterTask( *this );

  /// For right now, we do gracefully kill all interrupted stream,
  /// but normally the modules should abort thier own sending when they
  /// get stopped... @todo Check that some day, for now it's okay though.
  mlist_sendStream.clear();

  // if not empty, some modules have not properly closed down its send-streams!
  isoaglib_assert (mlist_sendStream.empty());

  setClosed();
}


SendStream_c*
MultiSend_c::getRunningStream(const IsoName_c& acrc_isoNameSender, const IsoName_c& acrc_isoNameReceiver)
{
  for (STL_NAMESPACE::list<SendStream_c>::iterator pc_iter=mlist_sendStream.begin(); pc_iter != mlist_sendStream.end(); pc_iter++)
  {
    if (pc_iter->isFinished())
      continue;
    if (pc_iter->matchSaDa(acrc_isoNameSender, acrc_isoNameReceiver))
      return &*pc_iter;
  }
  return NULL;
}


SendStream_c*
MultiSend_c::addSendStream(const IsoName_c& acrc_isoNameSender, const IsoName_c& acrc_isoNameReceiver)
{
  SendStream_c* const pc_foundStream = getRunningStream(acrc_isoNameSender, acrc_isoNameReceiver);
  if (pc_foundStream)
    return NULL; // can't start a sendStream, one already active for this one..

  mlist_sendStream.push_back (SendStream_c(*this MULTITON_INST_WITH_COMMA ));
  return &mlist_sendStream.back();
}


bool
MultiSend_c::sendIntern (const IsoName_c& isoNameSender, const IsoName_c& isoNameReceiver, const HUGE_MEM uint8_t* rhpb_data, uint32_t aui32_dataSize, int32_t ai32_pgn, IsoAgLib::iMultiSendStreamer_c* apc_mss, SendStream_c::msgType_t ren_msgType, MultiSendEventHandler_c* apc_multiSendEventHandler)
{
  isoaglib_assert( aui32_dataSize >= endSinglePacketSize );
  isoaglib_assert( (ren_msgType != SendStream_c::NmeaFastPacket) || (aui32_dataSize < endNmeaFastPacketSize) );
  isoaglib_assert( (ren_msgType != SendStream_c::IsoTPbroadcast) || (aui32_dataSize < beginEtpPacketSize) );
  isoaglib_assert( (ren_msgType != SendStream_c::IsoTP) || (aui32_dataSize < endTpPacketSize) );
  isoaglib_assert( (ren_msgType != SendStream_c::IsoETP) || (aui32_dataSize >= beginEtpPacketSize) );
  // end of preconditions.

  /// first check if new transfer can be started
  /// - is the sender correct?
  if( !getIsoMonitorInstance4Comm().existIsoMemberISOName( isoNameSender ) )
    return false;

  // - is the receiver correct?:
  switch (ren_msgType) {
  case SendStream_c::IsoTPbroadcast:
  case SendStream_c::NmeaFastPacket:
    // Destination must be "Unspecified"
    isoaglib_assert( isoNameReceiver.isUnspecified() );
    if( isoNameReceiver.isSpecified() )
      return false;
    break;
  default:
    // destination specific - so the receiver must be registered!
    if( !getIsoMonitorInstance4Comm().existIsoMemberISOName( isoNameReceiver ) )
      return false;
  }
  
  SendStream_c * const cpc_newSendStream = addSendStream( isoNameSender, isoNameReceiver );
  if (!cpc_newSendStream)
  { // couldn't create one, because one still running...
    return false;
  }

  cpc_newSendStream->init( isoNameSender, isoNameReceiver, rhpb_data, aui32_dataSize, ai32_pgn, apc_mss, ren_msgType, apc_multiSendEventHandler );

  // let this SendStream get sorted in now...
  calcAndSetNextTriggerTime();
  return true;
}


void 
MultiSend_c::timeEvent()
{
  if (mlist_sendStream.empty())
  { // nothing to do if no transfer is Running
    setPeriod( 5000, false ); // actually we could use "infinite here"
    return;
  }

  /** @todo SOON-178 Check how we want to calculate the max nr. of packets to send
            ==> Best would be to know when the next comes.
            clip that value as we may expect incoming can-pkgs, too - so be a little polite!
  */
  const int32_t ci32_time = System_c::getTime();
  // store time of last call, to get time interval between execution
  static int32_t si32_lastCall = 0;
  // only send max 1 package for first call, when execution period can't be derived
  uint8_t ui8_pkgCnt = (si32_lastCall > 0 ) ? ((ci32_time - si32_lastCall)/scui8_isoCanPkgDelay) : 1;
  // update last call time
  si32_lastCall = ci32_time;

  const uint8_t cui8_pkgCntForEach = ui8_pkgCnt / mlist_sendStream.size(); // in case it gets 0 after division, it is set to 1 inside of SendStream's timeEvent().

  int32_t i32_nextRetriggerNeeded = -1; // default to: "no retriggering needed"

  // Call each SendStream_c's timeEvent()
  for (STL_NAMESPACE::list<SendStream_c>::iterator pc_iter=mlist_sendStream.begin(); pc_iter != mlist_sendStream.end();)
  { // only call a SendStream when its time has come!
    if ( pc_iter->isFinished () ||
        (pc_iter->timeHasCome() && (pc_iter->timeEvent (cui8_pkgCntForEach))) )
    { // SendStream finished
      pc_iter = mlist_sendStream.erase (pc_iter);
      #if DEBUG_MULTISEND
      INTERNAL_DEBUG_DEVICE << "Kicked SendStream because it finished (abort or success)!" << INTERNAL_DEBUG_DEVICE_ENDL;
      #endif
    }
    else
    { // SendStream not yet finished
      const int32_t ci32_nextTriggerTime = pc_iter->getNextTriggerTime();
      // needs to be triggered at the following time
      if ((i32_nextRetriggerNeeded == -1) || (ci32_nextTriggerTime < i32_nextRetriggerNeeded))
      { // no trigger yet set or this SendStream needs to come earlier!
        i32_nextRetriggerNeeded = ci32_nextTriggerTime;
      }
      pc_iter++;
    }
  }

  // ALWAYS calculate when we want to be triggered again!
  int32_t newTimePeriod = 5000; // default: no SendStream running, idle around with 10 secs.. (actually "unlimited" would be correct - we can sleep!

  if (i32_nextRetriggerNeeded > -1) // "!= -1"
  { // HARD-timing, we need to come to action then!
    int32_t i32_delta = i32_nextRetriggerNeeded-System_c::getTime();
    if (i32_delta < 0) i32_delta = 0;
    newTimePeriod = i32_delta;
  }
  setPeriod( newTimePeriod, false );
};


/**
  start processing of a process msg
  ignore all invalid messages where SEND is not of a member with claimed address,
  or where EMPF isn't valid

  possible errors:
    * Err_c::elNonexistent on SEND/EMPF not registered in Monitor-List
  @return true -> message was processed; else the received CAN message will be served to other matching CanCustomer_c
*/
bool
MultiSend_c::processMsg( const CanPkg_c& arc_data )
{
  CanPkgExt_c pkg( arc_data, getMultitonInst() );
  if( !pkg.isValid() || (pkg.getMonitorItemForSA() == NULL) )
    return true;

  SendStream_c* runningStream = getRunningStream (pkg.getISONameForDA(), pkg.getISONameForSA()); // sa/da swapped, of course ;-) !
  if( runningStream )
  {
    const bool cb_success = runningStream->processMsg( pkg );
    calcAndSetNextTriggerTime();
    return cb_success;
  }
  else
  { // keep next trigger time
    return false;
  }
}

/** this function should NOT be called from INSIDE of timeEvent !
    ==> Only call it from OUTSIDE functions like init(), processMsg(), addSendStream, etc.
  */
void
MultiSend_c::calcAndSetNextTriggerTime()
{
  int32_t i32_nextRetriggerNeeded = -1;
  for (STL_NAMESPACE::list<SendStream_c>::iterator pc_iter=mlist_sendStream.begin(); pc_iter != mlist_sendStream.end();)
  {
    const int32_t ci32_nextTriggerTime = pc_iter->getNextTriggerTime();

    if ((i32_nextRetriggerNeeded == -1) || (ci32_nextTriggerTime < i32_nextRetriggerNeeded))
    { // no trigger yet set or this SendStream needs to come earlier!
      i32_nextRetriggerNeeded = ci32_nextTriggerTime;
    }
    pc_iter++;
  }

  if (i32_nextRetriggerNeeded == -1)
  { // no SendStreams needs to come to action, so idle around
    i32_nextRetriggerNeeded = System_c::getTime() + 5000;
  }
  setNextTriggerTime( i32_nextRetriggerNeeded );
}


void
MultiSend_c::reactOnIsoItemModification (ControlFunctionStateHandler_c::iIsoItemAction_e at_action, IsoItem_c const& acrc_isoItem)
{
  switch (at_action)
  {
    case ControlFunctionStateHandler_c::AddToMonitorList:
      if (acrc_isoItem.itemState (IState_c::Local))
      { // local IsoItem_c has finished adr claim
        getIsoFilterManagerInstance4Comm().insertIsoFilter (IsoFilter_s (mt_customer, IsoAgLib::iMaskFilter_c( (0x3FFFF00UL),  (TP_CONN_MANAGE_PGN << 8) ), &acrc_isoItem.isoName(), NULL, 8), false);
        getIsoFilterManagerInstance4Comm().insertIsoFilter (IsoFilter_s (mt_customer, IsoAgLib::iMaskFilter_c( (0x3FFFF00UL), (ETP_CONN_MANAGE_PGN << 8) ), &acrc_isoItem.isoName(), NULL, 8), true);
      }
      break;

    case ControlFunctionStateHandler_c::RemoveFromMonitorList:
      if (acrc_isoItem.itemState (IState_c::Local))
      { // local IsoItem_c has gone (i.e. IdentItem has gone, too.
        /// @todo SOON-178 activate the reconfiguration when the second parameter in removeIsoFilter is there finally...
        getIsoFilterManagerInstance4Comm().removeIsoFilter (IsoFilter_s (mt_customer, IsoAgLib::iMaskFilter_c( (0x3FFFF00UL),  (TP_CONN_MANAGE_PGN << 8) ), &acrc_isoItem.isoName(), NULL, 8));
        getIsoFilterManagerInstance4Comm().removeIsoFilter (IsoFilter_s (mt_customer, IsoAgLib::iMaskFilter_c( (0x3FFFF00UL), (ETP_CONN_MANAGE_PGN << 8) ), &acrc_isoItem.isoName(), NULL, 8));
        /// @todo SOON-178 Maybe clean up some streams and clients?
        /// Shouldn't appear normally anyway, so don't care for right now...
      }
      break;

    default:
      break;
  }
}


void
MultiSend_c::abortSend (const IsoName_c& acrc_isoNameSender, const IsoName_c& acrc_isoNameReceiver)
{
  SendStream_c* runningStream = getRunningStream (acrc_isoNameSender, acrc_isoNameReceiver);
  if( runningStream )
    runningStream->abortSend();

  // let timeEvent do the erasing from the list, keep it marked finished/aborted
}


void
MultiSend_c::abortSend (const MultiSendEventHandler_c& apc_multiSendEventHandler)
{
  for (STL_NAMESPACE::list<SendStream_c>::iterator pc_iter=mlist_sendStream.begin(); pc_iter != mlist_sendStream.end(); pc_iter++)
  {
    if (pc_iter->getMultiSendEventHandler() == &apc_multiSendEventHandler)
    {
      if (!pc_iter->isFinished())
        pc_iter->abortSend();
    }
  }
}


} // __IsoAgLib
