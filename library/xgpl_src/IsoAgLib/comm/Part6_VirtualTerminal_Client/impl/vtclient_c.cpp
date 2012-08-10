/*
  vtclient_c.cpp: central VT Client management

  (C) Copyright 2009 - 2012 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/

#include "vtclient_c.h"

#include <IsoAgLib/scheduler/impl/scheduler_c.h>
#include <IsoAgLib/comm/impl/isobus_c.h>
#include <IsoAgLib/comm/Part6_VirtualTerminal_Client/impl/vtclientconnection_c.h>
#include <IsoAgLib/util/iassert.h>
#include "../ivtclientobjectpool_c.h"

#if defined(_MSC_VER)
#pragma warning( disable : 4355 )
#endif

namespace __IsoAgLib {
  /** C-style function, to get access to the unique VtClient_c singleton instance
    * if more than one CAN BUS is used for IsoAgLib, an index must be given to select the wanted BUS
    */
  VtClient_c &getVtClientInstance(uint8_t aui8_instance)
  { // if > 1 singleton instance is used, no static reference can be used
    MACRO_MULTITON_GET_INSTANCE_BODY(VtClient_c, PRT_INSTANCE_CNT, aui8_instance);
  }



/** default constructor
 */
VtClient_c::VtClient_c() :
  ml_vtServerInst(),
  mvec_vtClientServerComm(),
  mt_handler(*this),
  mt_customer(*this)
{
  /// all variable initialization moved to singletonInit!
}


void
VtClient_c::init()
{
  isoaglib_assert (!initialized());

  getSchedulerInstance().registerClient(this);
  getIsoMonitorInstance4Comm().registerControlFunctionStateHandler(mt_handler);

  // register ISO Filters
  bool b_atLeastOneFilterAdded = NULL != getIsoBusInstance4Comm().insertFilter( mt_customer, IsoAgLib::iMaskFilter_c( 0x3FFFF00UL, (VT_TO_GLOBAL_PGN<<8) ), 8, false);
  bool const cb_set1 = NULL != getIsoBusInstance4Comm().insertFilter( mt_customer, IsoAgLib::iMaskFilter_c( 0x3FFFF00UL, (LANGUAGE_PGN<<8) ), 8, false);
  bool const cb_set2 = NULL != getIsoBusInstance4Comm().insertFilter( mt_customer, IsoAgLib::iMaskFilter_c( 0x3FFFF00UL, (ECU_TO_GLOBAL_PGN<<8) ), 8, false);

  if (cb_set1 || cb_set2)
    b_atLeastOneFilterAdded = true;

  if (b_atLeastOneFilterAdded)
    getIsoBusInstance4Comm().reconfigureMsgObj();

  setInitialized();
}


void
VtClient_c::close()
{
  isoaglib_assert (initialized());

  // Detect still registered IsoObjectPools at least in DEBUG mode!
  isoaglib_assert (getClientCount() == 0);

  while (!ml_vtServerInst.empty())
  {
    delete ml_vtServerInst.back();
    ml_vtServerInst.pop_back();
  }
  getIsoBusInstance4Comm().deleteFilter(mt_customer, IsoAgLib::iMaskFilter_c( (0x3FFFF00UL), (VT_TO_GLOBAL_PGN << 8)));
  getIsoBusInstance4Comm().deleteFilter(mt_customer, IsoAgLib::iMaskFilter_c( (0x3FFFF00UL), (LANGUAGE_PGN << 8)));
  getIsoMonitorInstance4Comm().deregisterControlFunctionStateHandler(mt_handler);
  getSchedulerInstance().unregisterClient(this);

  setClosed();
}


VtClientConnection_c*
VtClient_c::initAndRegisterIsoObjectPool(
  IdentItem_c& arc_identItem,
  IsoAgLib::iVtClientObjectPool_c& arc_pool, 
  const char* apc_versionLabel, 
  IsoAgLib::iVtClientDataStorage_c& apc_claimDataStorage, 
  IsoAgLib::iVtClientObjectPool_c::RegisterPoolMode_en aen_mode)
{
  switch (aen_mode)
  {
    case IsoAgLib::iVtClientObjectPool_c::RegisterPoolMode_MasterToPrimaryVt:
    case IsoAgLib::iVtClientObjectPool_c::RegisterPoolMode_MasterToAnyVt:
      if (!arc_identItem.isMaster())
      {
        /// IdentItem must be a Master
        return NULL;
      }
      break;  
    case IsoAgLib::iVtClientObjectPool_c::RegisterPoolMode_Slave:
      break;
  }

  return initAndRegisterIsoObjectPoolCommon(arc_identItem, arc_pool, apc_versionLabel, apc_claimDataStorage, aen_mode);
}

/** Register the given object pool
  It will automatically be uploaded as soon as ISO_Terminal_c is connected to the VT
  and all initialization stuff has been done (Get VT Capabilities, Memory, etc.)
  @return NULL if new vtClientServerCommunication_c instance could be created.
          This could be the case because you have passed a versionLabel
          - longer than 7 characters for a non-multilanguage object-pool
          - longer than 5 characters for a multilanguage object-pool
          or if you already registered an object-pool for this IdentItem
 */
VtClientConnection_c*
VtClient_c::initAndRegisterIsoObjectPoolCommon (IdentItem_c& rc_identItem, IsoAgLib::iVtClientObjectPool_c& arc_pool, const char* apc_versionLabel, IsoAgLib::iVtClientDataStorage_c& apc_claimDataStorage, IsoAgLib::iVtClientObjectPool_c::RegisterPoolMode_en aen_mode)
{
  uint8_t ui8_index = 0;
  // add new instance of VtClientServerCommunication
  for (; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
  {
    if (mvec_vtClientServerComm[ui8_index] == NULL)
    { // found one emtpy entry
      break;
    }
    else
    {
      if (mvec_vtClientServerComm[ui8_index]->getIdentItem() == rc_identItem)
      { // this IdentItem has already one pool registered - use multiple
        // IdentItems if you want to use multiple pools!
        return NULL;
      }
    }
  }
  // create new instance
  VtClientConnection_c* pc_vtCSC = new VtClientConnection_c (rc_identItem, *this, arc_pool, apc_versionLabel, apc_claimDataStorage, ui8_index,
                                                                               aen_mode MULTITON_INST_WITH_COMMA);
  if (pc_vtCSC->men_objectPoolState == VtClientConnection_c::OPCannotBeUploaded) // meaning here is: OPCannotBeInitialized (due to versionLabel problems)
  { // most likely due to wrong version label
    /// Error already registered in the VtClientConnection_c(..) constructor!
    delete pc_vtCSC;
    return NULL;
  }

  // add new instance to vector
  if (ui8_index < mvec_vtClientServerComm.size())
    mvec_vtClientServerComm[ui8_index] = pc_vtCSC;
  else
    mvec_vtClientServerComm.push_back(pc_vtCSC);

  return pc_vtCSC;
}

bool
VtClient_c::deregisterIsoObjectPool (IdentItem_c& r_identItem)
{
  /* what states the IdentItem could have we have to interrupt???
  * - IState_c::ClaimedAddress -> that item is Active and Member on ISOBUS
  * - !UploadType::UploadIdle -> interrupt any upload
  */
  uint8_t ui8_index = 0;
  for (; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
  {
    if (mvec_vtClientServerComm[ui8_index])
    {
      if (&r_identItem == &mvec_vtClientServerComm[ui8_index]->getIdentItem())
      {
        delete mvec_vtClientServerComm[ui8_index];
        mvec_vtClientServerComm[ui8_index] = NULL;
        break;
      }
    }
  }

  if (ui8_index == mvec_vtClientServerComm.size())
    return false; // appropriate IdentItem could not be found, so nothing was deleted
  else
    return true; // IdentItem was found and deleted
}

VtServerInstance_c* VtClient_c::getFirstActiveVtServer( bool mustBePrimary ) const
{
  STL_NAMESPACE::vector<VtServerInstance_c*>::const_iterator lit_vtServerInst;
  if( mustBePrimary )
  {
    for (lit_vtServerInst = ml_vtServerInst.begin(); lit_vtServerInst != ml_vtServerInst.end(); lit_vtServerInst++)
      if ( (*lit_vtServerInst)->isVtActive() && (*lit_vtServerInst)->isPrimaryVt() )
        return (*lit_vtServerInst);
  }
  else
  {
    for (lit_vtServerInst = ml_vtServerInst.begin(); lit_vtServerInst != ml_vtServerInst.end(); lit_vtServerInst++)
      if ( (*lit_vtServerInst)->isVtActive() )
        return (*lit_vtServerInst);
  }
  return NULL;
}

VtServerInstance_c* VtClient_c::getPreferredVtServer(const IsoName_c& aref_prefferedVTIsoName) const
{
  STL_NAMESPACE::vector<VtServerInstance_c*>::const_iterator lit_vtServerInst;
  for (lit_vtServerInst = ml_vtServerInst.begin(); lit_vtServerInst != ml_vtServerInst.end(); lit_vtServerInst++)
  {
    if (((*lit_vtServerInst)->getIsoName() == aref_prefferedVTIsoName) && (*lit_vtServerInst)->isVtActive())
      return (*lit_vtServerInst);
  }
  return NULL;
}

uint16_t
VtClient_c::getClientCount() const
{
  uint16_t ui16_count = 0;
  for (uint8_t ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ++ui8_index)
  {
    if (mvec_vtClientServerComm[ui8_index])
      ++ui16_count;
  }
  return ui16_count;
}


/** periodically event
  @return true -> all planned activities from all vtClientServerCommuniactions were performed in allowed time
 */
bool
VtClient_c::timeEvent(void)
{
  bool b_allActivitiesPerformed = true;

  for (uint8_t ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
  {
    bool const cb_clear = mvec_vtClientServerComm[ui8_index] &&
      !mvec_vtClientServerComm[ui8_index]->timeEvent();
    if (cb_clear)
        b_allActivitiesPerformed = false;
  }
  /** @todo SOON-241: maybe store the one that was out of time if not all could perform their actions? - by member variable of VtClient_c
                      Update: They all need to be scheduled on their own, so then it's okay with this point. */

  // set back the scheduler period to 100msec, as any waiting command has been set
  if (getTimePeriod() != 100) setTimePeriod( 100 );

  return b_allActivitiesPerformed;
}


/** process received can messages
  @return true -> message was processed; else the received CAN message will be served to other matching CanCustomer_c
 */
bool
VtClient_c::processMsg( const CanPkg_c& arc_data )
{

  CanPkgExt_c c_data( arc_data, getMultitonInst() );

  // VT_TO_GLOBAL is the only PGN we accept without VT being active, because it marks the VT active!!
  STL_NAMESPACE::vector<VtServerInstance_c*>::iterator lit_vtServerInst;
  uint8_t ui8_index;

  /// -->VT_TO_GLOBAL_PGN<-- ///
  if ((c_data.isoPgn() & 0x3FFFFLU) == VT_TO_GLOBAL_PGN)
  { // iterate through all registered VtServerInstances and process msg if vtSourceAddress == isoSa
    uint8_t const cui8_cmdByte = c_data.getUint8Data (1-1);

    if (cui8_cmdByte == 0xFE) // Command: "Status", Parameter: "VT Status Message"
    {
      for (lit_vtServerInst = ml_vtServerInst.begin(); lit_vtServerInst != ml_vtServerInst.end(); lit_vtServerInst++)
      {
        if ((*lit_vtServerInst)->getVtSourceAddress() == c_data.isoSa()) // getVtSourceAddress gets the SA from the IsoItem, so it's the current one...
        {
          (*lit_vtServerInst)->setLatestVtStatusData( c_data );

          // iterate through all registered VtClientServerCommunication and notify their pools with "eventVtStatusMsg"
          for (ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
          {
            if (mvec_vtClientServerComm[ui8_index])
            {
              if (mvec_vtClientServerComm[ui8_index]->getVtServerInstPtr() == (*lit_vtServerInst))
              { // this vtClientServerComm is connected to this VT, so notify the objectpool!!
                mvec_vtClientServerComm[ui8_index]->notifyOnVtStatusMessage();
              }
            }
          }
          return true; // VT Status Message is NOT of interest for anyone else!
        }
      }
    }
    else if (cui8_cmdByte == 0x21) // Command: "Auxiliary Control", Parameter: "Auxiliary Input Status"
    { // iterate through all registered VtClientServerCommunication and notify them, maybe they have functions that need that input status!
      for (ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
      {
        if (mvec_vtClientServerComm[ui8_index])
        {
          mvec_vtClientServerComm[ui8_index]->notifyOnAuxInputStatus( c_data );
        }
      }
    }
    else if (cui8_cmdByte == 0x26) // Command: "Auxiliary Control Type 2", Parameter: "Auxiliary Input Status"
    { 
      // iterate through all registered VtClientServerCommunication and notify them, maybe they have functions that need that input status!
      notifyAllVtClientsOnAux2InputStatus( c_data );
    }
    return true;
  }

  if ((c_data.isoPgn() & 0x3FFFFLU) == ECU_TO_GLOBAL_PGN)
  {
    uint8_t const cui8_cmdByte = c_data.getUint8Data (1-1);
    if (cui8_cmdByte == 0x23) // Command: "Auxiliary Control", Parameter: "input maintenance message"
    { // iterate through all registered VtClientServerCommunication and notify them
      notifyAllVtClientsOnAux2InputMaintenance(c_data);
    }
  }


  /// -->LANGUAGE_PGN<-- ///
  if ((c_data.isoPgn() & 0x3FFFFLU) == LANGUAGE_PGN)
  {
    VtServerInstance_c* pc_server = NULL;
    // first process LANGUAGE_PGN for all VtServerInstances BEFORE processing for the VtClientServerCommunications
    for (lit_vtServerInst = ml_vtServerInst.begin(); lit_vtServerInst != ml_vtServerInst.end(); lit_vtServerInst++)
    {
      if ((*lit_vtServerInst)->getVtSourceAddress() == c_data.isoSa())
      {
        pc_server = *lit_vtServerInst;
        break;
      }
    }

    if (pc_server != NULL)
    {
      pc_server->setLocalSettings( c_data );

      // notify all connected vtCSCs
      for (ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
      {
        if (mvec_vtClientServerComm[ui8_index]
            &&
            mvec_vtClientServerComm[ui8_index]->connectedToVtServer()
            &&
            (mvec_vtClientServerComm[ui8_index]->getVtServerInstPtr() == pc_server)
          )
          mvec_vtClientServerComm[ui8_index]->notifyOnVtsLanguagePgn();
      }
    }
    // else: Language PGN from non-VtServerInstance - ignore
    return true;
  }

  return false; /** shouldn't reach here as all filters are handled and returned above */
}


bool
VtClient_c::sendCommandForDEBUG(IsoAgLib::iIdentItem_c& mrc_wsMasterIdentItem, uint8_t* apui8_buffer, uint32_t ui32_size)
{
  for (uint8_t ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
  {
    if (static_cast<__IsoAgLib::IdentItem_c&>(mrc_wsMasterIdentItem) == mvec_vtClientServerComm[ui8_index]->getIdentItem())
      return mvec_vtClientServerComm[ui8_index]->sendCommand(apui8_buffer, ui32_size);
  }
  return false;
}


void
VtClient_c::reactOnIsoItemModification (ControlFunctionStateHandler_c::iIsoItemAction_e at_action, IsoItem_c const& acrc_isoItem)
{
  // we only care for the VTs
  if (acrc_isoItem.isoName().getEcuType() != IsoName_c::ecuTypeVirtualTerminal) return;

  STL_NAMESPACE::vector<VtServerInstance_c*>::iterator lit_vtServerInst;

  switch (at_action)
  {
    case ControlFunctionStateHandler_c::AddToMonitorList:
      { ///! Attention: This function is also called from "init()", not only from ISOMonitor!
        for (lit_vtServerInst = ml_vtServerInst.begin(); lit_vtServerInst != ml_vtServerInst.end(); lit_vtServerInst++)
        { // check if newly added VtServerInstance is already in our list
          if ((*lit_vtServerInst)->getIsoItem())
          {
            if (acrc_isoItem.isoName() == (*lit_vtServerInst)->getIsoItem()->isoName())
            { // the VtServerInstance is already known and in our list, so update the source address in case it has changed now
              return;
            }
          }
        }

        // VtServerInstance not yet in list, so add it ...
        /// @todo SOON-79: It should be enough if we store the IsoItem*, we don't need both the IsoItem AND IsoName...
        VtServerInstance_c* vtserver = new VtServerInstance_c(acrc_isoItem, acrc_isoItem.isoName(), *this MULTITON_INST_WITH_COMMA);
        ml_vtServerInst.push_back (vtserver);

      } break;

    case ControlFunctionStateHandler_c::RemoveFromMonitorList:
      for (lit_vtServerInst = ml_vtServerInst.begin(); lit_vtServerInst != ml_vtServerInst.end(); lit_vtServerInst++)
      { // check if lost VtServerInstance is in our list
        if ((*lit_vtServerInst)->getIsoItem())
        {
          if (acrc_isoItem.isoName() == (*lit_vtServerInst)->getIsoItem()->isoName())
          { // the VtServerInstance is already known and in our list, so it could be deleted
            // notify all clients on early loss of that VtServerInstance
            for (uint8_t ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
            {
              if (mvec_vtClientServerComm[ui8_index])
              {
                mvec_vtClientServerComm[ui8_index]->notifyOnVtServerInstanceLoss(*(*lit_vtServerInst));
              }
            }

            delete (*lit_vtServerInst);
            (void)ml_vtServerInst.erase (lit_vtServerInst);
            break;
          }
        }
      }
      break;

    default:
      // for right now, don't care if VT changes its SourceAddress.
      break;
  }
}


void
VtClient_c::notifyAllVtClientsOnAux2InputStatus( const CanPkgExt_c& refc_data ) const
{
  for (uint8_t ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
  {
    if (mvec_vtClientServerComm[ui8_index])
    {
      mvec_vtClientServerComm[ui8_index]->notifyOnAux2InputStatus( refc_data );
    }
  }
}

void
VtClient_c::notifyAllVtClientsOnAux2InputMaintenance( const CanPkgExt_c& refc_data ) const
{
  for (uint8_t ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
  {
    if (mvec_vtClientServerComm[ui8_index])
    {
      mvec_vtClientServerComm[ui8_index]->notifyOnAux2InputMaintenance( refc_data );
    }
  }
}

/// INTERFACE FUNTIONS ///
// the following define should be globally defined in the project settings...
#ifdef USE_IOP_GENERATOR_FAKE_VT_PROPERTIES
void
VtClient_c::fakeVtProperties (uint16_t aui16_dimension, uint16_t aui16_skWidth, uint16_t aui16_skHeight, uint8_t aui16_colorDepth, uint16_t aui16_fontSizes)
{
  const IsoItem_c c_dummyIsoItem;
  // casting NULL to a reference is okay here, as the reference isn't used for any FAKE_VT case (iop_generator, etc.)
  ml_vtServerInst.push_back (VtServerInstance_c (c_dummyIsoItem, IsoName_c::IsoNameUnspecified(), (*this) MULTITON_INST_WITH_COMMA));
  VtServerInstance_c& r_vtServerInst = ml_vtServerInst.back();
  r_vtServerInst.fakeVtProperties (aui16_dimension, aui16_skWidth, aui16_skHeight, aui16_colorDepth, aui16_fontSizes);
    // ... and notify all vtClientServerComm instances
  for (uint8_t ui8_index = 0; ui8_index < mvec_vtClientServerComm.size(); ui8_index++)
  {
    if (mvec_vtClientServerComm[ui8_index])
      mvec_vtClientServerComm[ui8_index]->notifyOnNewVtServerInstance(r_vtServerInst);
  }
}
#endif

#if DEBUG_SCHEDULER
const char*
VtClient_c::getTaskName() const
{ return "VtClient_c()"; }
#endif


} // end namespace __IsoAgLib