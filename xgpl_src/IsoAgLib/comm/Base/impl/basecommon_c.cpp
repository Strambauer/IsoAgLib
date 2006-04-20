/***************************************************************************
                          basecommon_c.h  -  base class for basa data types
                             -------------------
    begin                : Fri Apr 07 2000
    copyright            : (C) 2000 - 2004 by Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
    type                 : Header
    $LastChangedDate: 2005-01-11 10:55:57 +0100 (Di, 11 Jan 2005) $
    $LastChangedRevision: 805 $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 * This file is part of the "IsoAgLib", an object oriented program library *
 * to serve as a software layer between application specific program and   *
 * communication protocol details. By providing simple function calls for  *
 * jobs like starting a measuring program for a process data value on a    *
 * remote ECU, the main program has not to deal with single CAN telegram   *
 * formatting. This way communication problems between ECU's which use     *
 * this library should be prevented.                                       *
 * Everybody and every company is invited to use this library to make a    *
 * working plug and play standard out of the printed protocol standard.    *
 *                                                                         *
 * Copyright (C) 2000 - 2004 Dipl.-Inform. Achim Spangler                  *
 *                                                                         *
 * The IsoAgLib is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published          *
 * by the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * General Public License for more details.                                *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with IsoAgLib; if not, write to the Free Software Foundation,     *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA           *
 *                                                                         *
 * As a special exception, if other files instantiate templates or use     *
 * macros or inline functions from this file, or you compile this file and *
 * link it with other works to produce a work based on this file, this file*
 * does not by itself cause the resulting work to be covered by the GNU    *
 * General Public License. However the source code for this file must still*
 * be made available in accordance with section (3) of the                 *
 * GNU General Public License.                                             *
 *                                                                         *
 * This exception does not invalidate any other reasons why a work based on*
 * this file might be covered by the GNU General Public License.           *
 *                                                                         *
 * Alternative licenses for IsoAgLib may be arranged by contacting         *
 * the main author Achim Spangler by a.spangler@osb-ag:de                  *
 ***************************************************************************/

 /**************************************************************************
 *                                                                         *
 *     ###    !!!    ---    ===    IMPORTANT    ===    ---    !!!    ###   *
 * Each software module, which accesses directly elements of this file,    *
 * is considered to be an extension of IsoAgLib and is thus covered by the *
 * GPL license. Applications must use only the interface definition out-   *
 * side :impl: subdirectories. Never access direct elements of __IsoAgLib  *
 * and __HAL namespaces from applications which shouldnt be affected by    *
 * the license. Only access their interface counterparts in the IsoAgLib   *
 * and HAL namespaces. Contact a.spangler@osb-ag:de in case your applicat- *
 * ion really needs access to a part of an internal namespace, so that the *
 * interface might be extended if your request is accepted.                *
 *                                                                         *
 * Definition of direct access:                                            *
 * - Instantiation of a variable with a datatype from internal namespace   *
 * - Call of a (member-) function                                          *
 * Allowed is:                                                             *
 * - Instatiation of a variable with a datatype from interface namespace,  *
 *   even if this is derived from a base class inside an internal namespace*
 * - Call of member functions which are defined in the interface class     *
 *   definition ( header )                                                 *
 *                                                                         *
 * Pairing of internal and interface classes:                              *
 * - Internal implementation in an :impl: subdirectory                     *
 * - Interface in the parent directory of the corresponding internal class *
 * - Interface class name IsoAgLib::iFoo_c maps to the internal class      *
 *   __IsoAgLib::Foo_c                                                     *
 *                                                                         *
 * AS A RULE: Use only classes with names beginning with small letter :i:  *
 ***************************************************************************/
#include "basecommon_c.h"

// Begin Namespace __IsoAgLib
namespace __IsoAgLib {

/** initialize directly after the singleton instance is created.
    this is called from singleton.h and should NOT be called from the user again.
    users please use init(...) instead.
  */
void BaseCommon_c::singletonInit()
{
  setAlreadyClosed();
  init(NULL);
}

/**
  virtual function which delivers a pointer to the CANCustomer
  specific CANPkgExt_c instance
*/
CANPkgExt_c& BaseCommon_c::dataBase()
{
  return c_data;
}

/** every subsystem of IsoAgLib has explicit function for controlled shutdown */
void BaseCommon_c::close( )
{
  if ( ! checkAlreadyClosed() ) {
    // avoid another call
    setAlreadyClosed();
    // unregister from timeEvent() call by Scheduler_c
    getSchedulerInstance4Comm().unregisterClient( this );
  }
};

/** initialise element which can't be done during construct;
    above all create the needed FilterBox_c instances
    possible errors:
      * dependant error in CANIO_c problems during insertion of new FilterBox_c entries for IsoAgLibBase
    @param rpc_devKey optional pointer to the DEV_KEY variable of the responsible member instance (pointer enables automatic value update if var val is changed)
    @param rt_identMode either IsoAgLib::IdentModeImplement or IsoAgLib::IdentModeTractor

  */
void BaseCommon_c::init(const DevKey_c* rpc_devKey, IsoAgLib::IdentMode_t rt_identMode)
{
  // first register in Scheduler_c
  getSchedulerInstance4Comm().registerClient( this );
  c_data.setSingletonKey( c_data.getSingletonVecKey() );

  #ifdef USE_DIN_9684
  if (checkAlreadyClosed())
  {
    b_dinFilterCreated = false;
  }
  #endif

  #ifdef USE_ISO_11783
  if (checkAlreadyClosed())
  {
    b_isoFilterCreated = false;
  }
  #endif

  // set configure values with call for config
  config(rpc_devKey, rt_identMode);

  // clear state of b_alreadyClosed, so that close() is called one time
  clearAlreadyClosed();
};

/** config tractor object after init --> store devKey and mode
    @param rpc_devKey pointer to the DEV_KEY variable of the responsible member instance (pointer enables automatic value update if var val is changed)
    @param rt_identMode either IsoAgLib::IdentModeImplement or IsoAgLib::IdentModeTractor
  */
void BaseCommon_c::config(const DevKey_c* rpc_devKey, IsoAgLib::IdentMode_t rt_identMode)
{
  // set configure values
  pc_devKey = rpc_devKey; // store the pointer in any case
  setMode(rt_identMode);

  // set the timestamps to 0
  i32_lastMsgReceived = 0;

  //setSelectedDataSourceDevKey is only used in tractor mode
  if (rt_identMode == IsoAgLib::IdentModeTractor)
  {
    if ((rpc_devKey != NULL) )
      c_selectedDataSourceDevKey = *rpc_devKey;
    else
      c_selectedDataSourceDevKey.setUnspecified();
  }
}

/** check if a received message should be parsed */
bool BaseCommon_c::checkParseReceived(const DevKey_c& rrefc_currentSender) const
{
  return ( checkMode(IsoAgLib::IdentModeImplement) // I'm not the sender
            && ( // one of the following conditions must be true
                   (c_selectedDataSourceDevKey == rrefc_currentSender  ) // actual sender equivalent to last
                || (c_selectedDataSourceDevKey.isUnspecified()         ) // last sender has not correctly claimed address member
               )
          )?true:false;
}

/** process received moving msg and store updated value for later reading access;
    called by FilterBox_c::processMsg after receiving a msg
    possible errors:
      * LibErr_c::LbsBaseSenderConflict moving msg recevied from different member than before
    @see FilterBox_c::processMsg
    @see CANIO_c::processMsg
    @return true -> message was processed; else the received CAN message will be served to other matching CANCustomer_c
  */
bool BaseCommon_c::processMsg()
{
  #if defined(USE_ISO_11783) && defined(USE_DIN_9684)
  if (c_data.identType() == Ident_c::ExtendedIdent)
  #endif // USE_DIN_9684 && USE_ISO_11783
  #ifdef USE_ISO_11783
  { // an ISO11783 base information msg received
    return isoProcessMsg();
  }
  #endif // USE_ISO_11783
  #if defined(USE_ISO_11783) && defined(USE_DIN_9684)
  else
  #endif
  #ifdef USE_DIN_9684
  return dinProcessMsg();
  #endif
  return false;
}

  /** functions with actions, which must be performed periodically
    -> called periodically by Scheduler_c
    ==> sends base data msg if configured in the needed rates
    possible errors:
      * dependant error in CANIO_c on CAN send problems
    @see CANPkg_c::getData
    @see CANPkgExt_c::getData
    @see CANIO_c::operator<<
    @return true -> all planned activities performed in allowed time
  */
bool BaseCommon_c::timeEvent()
{
  if (Scheduler_c::getAvailableExecTime() == 0) return false;

  checkCreateReceiveFilter();
  if (Scheduler_c::getAvailableExecTime() == 0) return false;

  // check for different base data types whether the previously
  // sending node stopped sending -> other nodes can now step in
  if (  checkMode(IsoAgLib::IdentModeTractor)
        &&(lastedTimeSinceUpdate() >= 3000 )
        && (c_selectedDataSourceDevKey.isSpecified())    )
  { // the previously sending node didn't send the information for 3 seconds -> give other items a chance
    c_selectedDataSourceDevKey.setUnspecified();
  }

  // check if we are in tractor mode and have a pointer to the sending device key
  if ( checkMode(IsoAgLib::IdentModeTractor) )
  {
    if (  (pc_devKey != NULL                                                   )
    #ifdef USE_ISO_11783
          && getIsoMonitorInstance4Comm().existIsoMemberDevKey(*pc_devKey, true)
    #endif
    #ifdef USE_DIN_9684
          && getDinMonitorInstance4Comm().existDinMemberDevKey(*pc_devKey, true)
    #endif
        )
    { // stored base data information sending ISO member or DIN member has claimed address
      #ifdef USE_ISO_11783
        if ( !isoTimeEventTracMode()) return false;
      #endif
      #if defined(USE_ISO_11783) && defined(USE_DIN_9684)
        if (Scheduler_c::getAvailableExecTime() == 0) return false;
      #endif
      #ifdef USE_DIN_9684
        return dinTimeEventTracMode();
      #endif
    }
  }
  #ifdef USE_ISO_11783
  else
  { // we are in implement mode; check if we have a pointer to the sending device key
    if (   (pc_devKey != NULL                                                 )
         && getIsoMonitorInstance4Comm().existIsoMemberDevKey(*pc_devKey, true)
       )
    {
      if ( !isoTimeEventImplMode()) return false;
      if (Scheduler_c::getAvailableExecTime() == 0) return false;
    }
  }
  #endif
  return true;
}

}// end namespace __IsoAgLib
