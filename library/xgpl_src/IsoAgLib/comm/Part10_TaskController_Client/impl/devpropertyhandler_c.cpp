/***************************************************************************
                           devpropertyhandler_c.cpp
                             -------------------
    begin                : Tue Jun 23 2005
    copyright            : (C) 2000 - 2004 by Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
    type                 : Source
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
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/devpropertyhandler_c.h>

#include <IsoAgLib/comm/Scheduler/impl/scheduler_c.h>
#include <IsoAgLib/driver/can/impl/canio_c.h>
#include <IsoAgLib/comm/Part3_DataLink/impl/multisend_c.h>
#include <IsoAgLib/comm/Part3_DataLink/impl/multireceive_c.h>
#include <IsoAgLib/comm/Part3_DataLink/istream_c.h>
#include <IsoAgLib/comm/Part3_DataLink/impl/multisendpkg_c.h>
#include <IsoAgLib/util/impl/singleton.h>
#include <supplementary_driver/driver/rs232/irs232io_c.h>
#include <IsoAgLib/comm/Part5_NetworkManagement//impl/isoitem_c.h>
#include <IsoAgLib/comm/Part5_NetworkManagement//impl/isomonitor_c.h>

#ifdef USE_ISO_TERMINAL
  #include <IsoAgLib/comm/Part6_VirtualTerminal_Client/impl/isoterminal_c.h>
  #include <IsoAgLib/comm/Part6_VirtualTerminal_Client/impl/vtclientservercommunication_c.h>
#endif

//define length of every attribute in deviceObject
#define DEF_Transfer_Code 1
#define DEF_TableID 3
#define DEF_ObjectID 2
#define DEF_Designator_Length 1
#define DEF_Software_Version_Length 1
#define DEF_Workingset_MasterNAME 8
#define DEF_Serialnumber_Length 1
#define DEF_Structurelabel 7


/** This function delivers the offset to the structurelabel in every device description*/
uint8_t getLabelOffset (const HUGE_MEM uint8_t* pc_Array)
{
  uint8_t ui8_designatorLength =      pc_Array[DEF_Transfer_Code + DEF_TableID + DEF_ObjectID];
  uint8_t ui8_softwareVersionLength = pc_Array[DEF_Transfer_Code + DEF_TableID + DEF_ObjectID + DEF_Designator_Length + ui8_designatorLength];
  uint8_t ui8_serialNumberLength =    pc_Array[DEF_Transfer_Code + DEF_TableID + DEF_ObjectID + DEF_Designator_Length + ui8_designatorLength + DEF_Workingset_MasterNAME + DEF_Software_Version_Length + ui8_softwareVersionLength];
  uint8_t ui8_offsetLabel = ( DEF_Transfer_Code
                            + DEF_TableID
                            + DEF_ObjectID
                            + DEF_Designator_Length
                            + ui8_designatorLength
                            + DEF_Software_Version_Length
                            + ui8_softwareVersionLength //pc_Array[(DEF_Transfer_Code + DEF_TableID + DEF_ObjectID + DEF_Designator_Length + pc_Array[DEF_Transfer_Code + DEF_TableID + DEF_ObjectID + DEF_Designator_LengthDEF_TableID+DEF_ObjectID] + DEF_Designator_Length)]
                            + DEF_Workingset_MasterNAME
                            + DEF_Serialnumber_Length
                            + ui8_serialNumberLength
                            );
  return ui8_offsetLabel;
}

namespace __IsoAgLib {

#define DEF_TimeOut_GetVersion 5000
#define DEF_TimeOut_OPTransfer 10000
#define DEF_TimeOut_EndOfDevicePool 10000
#define DEF_WaitFor_Reupload 5000
#define DEF_TimeOut_ChangeDesignatorValue 1500
#define DEF_TimeOut_NormalCommand 1500

//define helper class LanguageLabel_c
//===================================================================
/** class to stored the language label from a device description */
LanguageLabel_c::LanguageLabel_c (const HUGE_MEM char* label)
{
  str[0] = label[0];
  str[1] = label[1];
};

LanguageLabel_c::LanguageLabel_c (const LanguageLabel_c& c_langLabel)
{
  CNAMESPACE::memcpy(str, c_langLabel.str, 2);
};

const LanguageLabel_c& LanguageLabel_c::operator=(const LanguageLabel_c& c_langLabel)
{
  CNAMESPACE::memcpy(str, c_langLabel.str, 2);
  return c_langLabel;
};

const LanguageLabel_c& LanguageLabel_c::operator=(const HUGE_MEM uint8_t* ui8_str)
{
  str[0] = ui8_str[0];
  str[1] = ui8_str[1];
  return *this;
};

bool LanguageLabel_c::operator<(const LanguageLabel_c& c_langLabel) const
{
  return CNAMESPACE::strcmp(str, c_langLabel.str);
};

bool LanguageLabel_c::operator==(const LanguageLabel_c& c_langLabel)
{
  return (CNAMESPACE::strcmp(str, c_langLabel.str)==0)?true:false;
};
//end of definition LanguageLabel_c
//===================================================================


//define helper class DevicePool_c
//===================================================================
/** class to stored the device description byte stream and its length */
DevicePool_c::DevicePool_c (const HUGE_MEM uint8_t* pcui8_bytestream, const uint32_t ui32_length)
{
  p_DevicePool = pcui8_bytestream;
  devicePoolLength = ui32_length;
}

const DevicePool_c& DevicePool_c::operator=(const DevicePool_c& c_devicePool)
{
  p_DevicePool = c_devicePool.p_DevicePool;
  devicePoolLength = c_devicePool.devicePoolLength;
  return *this;
}
//end of definition DevicePool_c
//===================================================================


DevPropertyHandler_c::DevPropertyHandler_c()
   : ui16_currentSendPosition(0), ui16_storedSendPosition(0), mi32_tcStateLastReceived(0), mui8_lastTcState(0), mi32_timeStartWaitAfterAddrClaim(0), mb_initDone(0), mi32_timeWsTaskMsgSent(0),
     mb_setToDefault(false), mb_tcAliveNew(false), mb_receivedStructureLabel(false), mb_receivedLocalizationLabel(false),
     mpc_data(NULL), mui8_tcSourceAddress(0), mui8_versionLabel(0), mpc_devDefaultDeviceDescription(NULL), mpc_devPoolForUpload(NULL),
     mpc_wsMasterIdentItem(NULL), men_poolState(OPNotRegistered), men_uploadState(StateIdle), men_uploadStep(UploadStart),
     men_uploadCommand(UploadCommandWaitingForCommandResponse), mui32_uploadTimestamp(0), mui32_uploadTimeout(0), mui8_uploadRetry(0),
     mui8_commandParameter(0), men_sendSuccess(__IsoAgLib::MultiSend_c::SendSuccess), mi32_timeWsAnnounceKey(-1)
{}


/** process received can messages
    @return true -> message was processed; else the received CAN message will be served to other matching CanCustomer_c
  */
bool
DevPropertyHandler_c::processMsg()
{
  if ((data().isoPgn() & 0x3FF00) != PROCESS_DATA_PGN)
    //should never be the case
    return FALSE;

  // set FALSE if "default" is selected in switch case
  bool b_rc = TRUE;

  //handling of nack
  //-> means that no device description is uploaded before
  //-> so extract all necessary information from the byte-stream (structure and localization label)
  //-> add the stream to the map
  if ((data().getUint8Data(0) & 0xF) == 0xD)
  {
    //here starts nack handling
    // these two cmds could be answered with a NACK
    switch ((data().getUint8Data(0) >> 4) & 0xF)
    {
      case 0x0: //NACK Request StructureLabel
        if (men_uploadState == StatePresettings && men_uploadStep == UploadWaitForStructureLabelResponse)
        {
          men_uploadStep = UploadWaitForUploadInit;
          mb_receivedStructureLabel = false;
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Received NACK for structure label..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
        break;
      case 0x2: //NACK Request LocalizationLabel
        if (men_uploadState == StatePresettings && men_uploadStep == UploadWaitForLocalizationLabelResponse)
        {
          men_uploadStep = UploadWaitForUploadInit;
          mb_receivedLocalizationLabel = false;
          #ifdef DEBUG
            INTERNAL_DEBUG_DEVICE << "Received NACK for localization label..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
        break;
      default:
        b_rc = FALSE;
    }
  }

  uint8_t i;
  switch (data().getUint8Data (0))
  {
    case procCmdPar_VersionMsg:
      if (men_uploadState == StateUploadInit && men_uploadStep == UploadWaitForVersionResponse)
      {
        mui8_versionLabel = data().getUint8Data(1);
        #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Received version response..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
        startUpload();
      }
      break;
    case procCmdPar_StructureLabelMsg:
      if (men_uploadState == StatePresettings && men_uploadStep == UploadWaitForStructureLabelResponse)
      {
        //store structureLabel for later compare in StateUploadInit
        for (i=1; i<8; i++) marrpch_structureLabel[i-1] = char(data().getUint8Data(i));
        mb_receivedStructureLabel = true;

        // send Request Localization Label message
        mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                          procCmdPar_RequestLocalizationLabelMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
        getCanInstance4Comm() << *mpc_data;
        mui32_uploadTimestamp = HAL::getTime();
        mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
        men_uploadStep = UploadWaitForLocalizationLabelResponse;
        #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Received structure label response..." << INTERNAL_DEBUG_DEVICE_ENDL;
          INTERNAL_DEBUG_DEVICE << "Wait for localization label (in processMsg)..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case procCmdPar_LocalizationLabelMsg:
      if (men_uploadState == StatePresettings && men_uploadStep == UploadWaitForLocalizationLabelResponse)
      {
        //store localizationLabel for later compare in StateUploadInit
        for (i=1; i<8; i++) marrpch_localizationLabel[i-1] = char(data().getUint8Data(i));
        mb_receivedLocalizationLabel = true;
        men_uploadStep = UploadWaitForUploadInit;
        #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Received localization response..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case procCmdPar_RequestOPTransferRespMsg:
      if (men_uploadState == StateUploadPool && men_uploadStep == UploadWaitForRequestOPTransferResponse)
      {
        if (data().getUint8Data(1) == 0)
        {
          men_uploadStep = UploadUploading;
          getMultiSendInstance().sendIsoTarget(mpc_wsMasterIdentItem->isoName(),
            getIsoMonitorInstance4Comm().isoMemberNr(mui8_tcSourceAddress).isoName(),
            this, PROCESS_DATA_PGN, men_sendSuccess);
        }
        else
        {
          mui8_commandParameter = procCmdPar_RequestOPTransferRespMsg;
          outOfMemory();
        }
        #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Received response for request OP transfer..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case procCmdPar_OPTransferRespMsg:
      // if timeEvent not yet called => set uploadStep right here
      men_uploadStep = UploadWaitForOPTransferResponse;
      if (men_uploadState == StateUploadPool)
      {
        if (data().getUint8Data(1) == 0)
        {
          men_uploadStep = UploadWaitForOPActivateResponse;
          mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                          procCmdPar_OPActivateMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
          getCanInstance4Comm() << *mpc_data;
          mui32_uploadTimestamp = HAL::getTime();
          mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
          #ifdef DEBUG
            INTERNAL_DEBUG_DEVICE << "Received positive response for OP transfer..." << INTERNAL_DEBUG_DEVICE_ENDL;
            INTERNAL_DEBUG_DEVICE << "OPActivateMsg..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
        else
        {
          mui8_commandParameter = procCmdPar_OPTransferRespMsg;
          outOfMemory();
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Received negative response for OP transfer..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
      }
      break;
    case procCmdPar_OPActivateRespMsg:
      #ifdef DEBUG
      INTERNAL_DEBUG_DEVICE << "Received activate response..." << INTERNAL_DEBUG_DEVICE_ENDL;
      #endif
      if (men_uploadState == StateUploadPool && men_uploadStep == UploadWaitForOPActivateResponse)
      {
        if (data().getUint8Data(1) == 0)
        {
          men_uploadState = StateIdle;
          men_uploadStep = UploadNone;
          men_poolState = OPSuccessfullyUploaded;
        }
        else
        {
          /** @todo SOON: further output for user to locate the error which caused the upload fail -> interprete TC-Response to get more detailed debug output*/
          men_uploadStep = UploadFailed;
          men_poolState = OPCannotBeUploaded;
          mui8_commandParameter = procCmdPar_OPActivateRespMsg;
          #if defined(DEBUG)
          INTERNAL_DEBUG_DEVICE << (uint16_t) data().getUint8Data(1) << INTERNAL_DEBUG_DEVICE_ENDL;
          INTERNAL_DEBUG_DEVICE << "upload failed, activate with error..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
      }
      break;
    case procCmdPar_OPDeleteRespMsg:
      if (men_uploadState == StateUploadInit && men_uploadStep == UploadWaitForDeleteResponse)
      {
        if (data().getUint8Data(1) == 0)
        {
          mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                            procCmdPar_RequestVersionMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
          getCanInstance4Comm() << *mpc_data;
          mui32_uploadTimestamp = HAL::getTime();
          mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
          men_uploadStep = UploadWaitForVersionResponse;
        }
        else
        {
          /** @todo SOON: if the pool couldn't be deleted: fail upload or just ignore it??? */
          mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                            procCmdPar_RequestVersionMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
          getCanInstance4Comm() << *mpc_data;
          mui32_uploadTimestamp = HAL::getTime();
          mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
          men_uploadStep = UploadWaitForVersionResponse;
        }
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Received delete response..." << INTERNAL_DEBUG_DEVICE_ENDL;
        INTERNAL_DEBUG_DEVICE << "Wait for version response (in processMsg)..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    /* UploadCommandWaitingForCommandResponse and UploadMultiSendCommandWaitingForCommandResponse
     * are states for the same cmd but different ways of sending (via CAN pkg and via mss)
     */
    case procCmdPar_ChangeDesignatorRespMsg:
      if (men_uploadState == StateUploadCommand &&
         ((men_uploadCommand == UploadCommandWaitingForCommandResponse) || (men_uploadCommand == UploadMultiSendCommandWaitingForCommandResponse)))
      {
        //no matter if successful or faulty, finish upload command
        finishUploadCommandChangeDesignator();
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "ChangeDesignatorRespMsg..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    default:
      b_rc = FALSE;
  }

  return b_rc;
}


/** initialise element which can't be done during construct
  */
void
DevPropertyHandler_c::init(ProcessPkg_c *apc_data)
{
  static bool b_basicInit = false;
  mpc_data = apc_data;

  if (!b_basicInit)
  {
    mi32_tcStateLastReceived = mi32_timeStartWaitAfterAddrClaim = mi32_timeWsTaskMsgSent = mi32_timeWsAnnounceKey = -1;
    mui8_lastTcState = 0;
    mb_initDone = FALSE;
    mui8_tcSourceAddress = 0x7F;

    men_poolState = OPNotRegistered;
    men_uploadState = StateIdle;
    men_uploadStep = UploadStart;
    mpc_devPoolForUpload = NULL;
  }

  b_basicInit = true;
}

/** periodically event -> call timeEvent for all  identities and parent objects
    @return true -> all planned activities performed in allowed time
  */
bool
DevPropertyHandler_c::timeEvent( void )
{
  if (!mb_initDone)
  { /// Handling 6.4.2.b) here: Wait 6s after successful Address-Claimed
    checkInitState();
    return TRUE;
  }

  // Just getting sure that we really do always have a valid pointer
  if (mpc_wsMasterIdentItem == NULL) return true;

  /// Address is initially claimed successfully. Check now if we're still "online"
  /// This could be a problem is someone stole our SA and we're currently not having one...
  if (!mpc_wsMasterIdentItem->isClaimedAddress()) return true;

  const int32_t i32_currentTime = HAL::getTime();

  // get new TC alive state
  bool tcAliveOld = mb_tcAliveNew;
  mb_tcAliveNew = isTcAlive(i32_currentTime);

  if ((tcAliveOld == true) && (mb_tcAliveNew == false))
  { // TC going offline
    // no need to set the mi32_timeWsAnnounceKey to -1 on "true->false".
    // -> if false, TC is not active, so it's gettinged "return"ed.
    // -> if true again, the rising edge (false->true) was detected above and mi32_timeWsAnnounceKey was set using "startWsAnnounce".
    // actually not needed to be reset here, because if TC not active it's not checked and if TC gets active we restart the sending.
    mi32_timeWsAnnounceKey = -1;
  }

  /// Handling 6.4.2.c) here: Wait until TC transmits the TC Status Message
  if (!mb_tcAliveNew) return true;

  if ((tcAliveOld == false) && (mb_tcAliveNew == true))
  { // TC coming online
    if (men_poolState != OPNotRegistered) {
      men_poolState = OPRegistered;
    }
    men_uploadState = StatePresettings;
    men_uploadStep = UploadStart;
    /// Handling 6.4.2.d) here: Identify itself and its members
    #ifndef USE_WORKING_SET
    #error "Need to define USE_WORKING_SET when utilizing a TaskController-Client."
    #endif
    mi32_timeWsAnnounceKey = mpc_wsMasterIdentItem->getIsoItem()->startWsAnnounce();
  }

  /// Wait until 6.4.2.d) has finished (WS is completely announced)
  if (!mpc_wsMasterIdentItem->getIsoItem()->isWsAnnounced (mi32_timeWsAnnounceKey)) return true;

  /// Handling 6.4.2.e) here: Begin transmission of the working-set task message
  sendWorkingSetTaskMsg(i32_currentTime);

  if ((men_poolState == OPNotRegistered) || (men_poolState == OPCannotBeUploaded)) return true;

  //now TC is active, so send your msgs to TC
  switch(men_uploadStep)
  {
    case UploadStart:
      //first of all: get the structure label (if available)
      mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                            procCmdPar_RequestStructureLabelMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
      getCanInstance4Comm() << *mpc_data;
      mui32_uploadTimestamp = HAL::getTime();
      mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
      men_uploadStep = UploadWaitForStructureLabelResponse;
      #ifdef DEBUG
      INTERNAL_DEBUG_DEVICE << "Wait for structure label..." << INTERNAL_DEBUG_DEVICE_ENDL;
      #endif
      break;
    case UploadWaitForVersionResponse:
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        /** @todo SOON: check when the responses could not be received, and whether simple sending of new pool could cause harm */
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "No version available..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
        startUpload();
      }
      //else INTERNAL_DEBUG_DEVICE << "still waiting for timeout or response..." << INTERNAL_DEBUG_DEVICE_ENDL;
      break;
    case UploadWaitForStructureLabelResponse:
      //Timed out???
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        mb_receivedStructureLabel = false;
        men_uploadStep = UploadWaitForUploadInit;
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Wait for structure label timed out, go to wait for upload init..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case UploadWaitForLocalizationLabelResponse:
      //Timed out???
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        mb_receivedLocalizationLabel = false;
        men_uploadStep = UploadWaitForUploadInit;
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Wait for localization label timed out, go to wait for upload init..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case UploadWaitForUploadInit:
      if (mpc_devDefaultDeviceDescription == NULL) {/*wait*/}
      if (mpc_devDefaultDeviceDescription != NULL)
      {
        men_uploadState = StateUploadInit;
        if (!mb_receivedStructureLabel)
        {
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "get pool from taskcontroller or via default..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
          getPoolForUpload();
        }
        else
        {
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "init upload..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
          initUploading();
        }

        // we received structure and localization label, checks were successful, so no pool uploading necessary
        if (men_uploadState == StateIdle) break;

        if (mb_receivedStructureLabel)
        {
          mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                                  procCmdPar_OPDeleteMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
          getCanInstance4Comm() << *mpc_data;
          mui32_uploadTimestamp = HAL::getTime();
          mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
          men_uploadStep = UploadWaitForDeleteResponse;
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Wait for delete response..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
        else
        {
          mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                                procCmdPar_RequestVersionMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
          getCanInstance4Comm() << *mpc_data;
          mui32_uploadTimestamp = HAL::getTime();
          mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
          men_uploadStep = UploadWaitForVersionResponse;
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Wait for version response..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
      }
      break;
    case UploadWaitForDeleteResponse:
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        men_uploadState = StateIdle;
        men_uploadStep = UploadFailed;
        mui8_commandParameter = procCmdPar_OPDeleteRespMsg;
        mui32_uploadTimestamp = HAL::getTime();
        mui32_uploadTimeout = DEF_WaitFor_Reupload;
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Upload timed out when deleting old pool, wait for re-upload..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case UploadWaitForRequestOPTransferResponse:
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        men_uploadState = StateIdle;
        men_uploadStep = UploadFailed;
        mui8_commandParameter = procCmdPar_RequestOPTransferRespMsg;
        mui32_uploadTimestamp = HAL::getTime();
        mui32_uploadTimeout = DEF_WaitFor_Reupload;
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Upload timed out, wait for re-upload..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case UploadRetryUpload:
      startUpload();
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "UploadRetryUpload..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      break;
    case UploadUploading:
      switch (men_sendSuccess) {
        case __IsoAgLib::MultiSend_c::Running: {
          // wait
        } break;
        case __IsoAgLib::MultiSend_c::SendAborted: {
          // aborted sending
          men_uploadState = StateIdle;
          men_uploadStep = UploadFailed;
          mui8_commandParameter = procCmdPar_OPTransferMsg;
          mui32_uploadTimestamp = HAL::getTime();
          mui32_uploadTimeout = DEF_WaitFor_Reupload;
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Upload failed, send aborted..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        } break;
        case __IsoAgLib::MultiSend_c::SendSuccess: {
          men_uploadStep = UploadWaitForOPTransferResponse;
          mui32_uploadTimestamp = HAL::getTime();
          mui32_uploadTimeout = DEF_TimeOut_EndOfDevicePool;
          #ifdef DEBUG
          INTERNAL_DEBUG_DEVICE << "Upload successful, wait for transfer response..." << INTERNAL_DEBUG_DEVICE_ENDL;
          #endif
        }
      }
      break;
    case UploadWaitForOPTransferResponse:
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        men_uploadState = StateIdle;
        men_uploadStep = UploadFailed;
        mui8_commandParameter = procCmdPar_OPTransferRespMsg;
        mui32_uploadTimestamp = HAL::getTime();
        mui32_uploadTimeout = DEF_WaitFor_Reupload;
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Upload failed, timeout when waiting for transfer response,wait for re-upload..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case UploadWaitForOPActivateResponse:
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        men_uploadState = StateIdle;
        men_uploadStep = UploadFailed;
        mui8_commandParameter = procCmdPar_OPActivateMsg;
        mui32_uploadTimestamp = HAL::getTime();
        mui32_uploadTimeout = DEF_WaitFor_Reupload;
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Upload failed when waiting for activating pool, wait for re-upload..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      break;
    case UploadFailed:
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Upload failed..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
        switch (mui8_commandParameter)
        {
          case procCmdPar_OPActivateRespMsg:
          case procCmdPar_OPActivateMsg:
          case procCmdPar_OPTransferMsg:
          case procCmdPar_OPTransferRespMsg:
          case procCmdPar_RequestOPTransferRespMsg:
          case procCmdPar_RequestOPTransferMsg:
            men_uploadState = StateUploadPool;
            men_uploadStep = UploadRetryUpload;
            break;
          case procCmdPar_OPDeleteRespMsg:
            mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                                  procCmdPar_OPDeleteMsg, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
            getCanInstance4Comm() << *mpc_data;
            mui32_uploadTimestamp = HAL::getTime();
            mui32_uploadTimeout = DEF_TimeOut_NormalCommand;
            men_uploadStep = UploadWaitForDeleteResponse;
            break;
          default:
            men_uploadState = StatePresettings;
            men_uploadStep = UploadStart;
            break;
        }
      }
      break;
    case UploadNone:
      //do nothing
      break;
  }

  /////////////////////////////
  /// UPLOADING --> COMMAND <--
  // Can only be done if the Object-Pool is successfully uploaded!
  if (men_poolState != OPSuccessfullyUploaded) return true;

  /// FROM HERE THE OBJECT-POOL >>IS<< UPLOADED SUCCESSFULLY
  /// NOW HERE THE RUNTIME COMMANDS ARE BEING HANDLED

  if (men_uploadState == StateUploadCommand)
  {
    if (men_uploadCommand == UploadCommandWaitingForCommandResponse)
    {
      // Waiting for an answer - Did it time out?
      if (((uint32_t) HAL::getTime()) > (mui32_uploadTimeout + mui32_uploadTimestamp)) {
        men_uploadCommand = UploadCommandTimedOut;
      }
    }
    else if (men_uploadCommand == UploadMultiSendCommandWaitingForCommandResponse){
      if (((uint32_t) HAL::getTime()) < (mui32_uploadTimeout + mui32_uploadTimestamp))
      {
        switch (men_sendSuccess) {
        case __IsoAgLib::MultiSend_c::Running: {
          // wait
          } break;
        case __IsoAgLib::MultiSend_c::SendAborted: {
          // aborted sending
          men_uploadState = StateIdle;
          men_uploadCommand = UploadCommandTimedOut;
          } break;
        case __IsoAgLib::MultiSend_c::SendSuccess: {
          men_uploadState = StateIdle;
          }
        }
      }
    }
    // last Upload failed?
    if (men_uploadCommand == UploadCommandTimedOut)
    {
      if (mui8_uploadRetry > 0) {
        mui8_uploadRetry--;
        startUploadCommandChangeDesignator();
      } else {
        // No more retries, simply finish this job and go Idle!
        //finishUploadCommandChangeDesignator(); // will pop the SendUpload, as it can't be correctly sent after <retry> times. too bad.
      }
    }
  } // UploadCommand

  // ### Is a) no Upload running and b) some Upload to do?
  if ((men_uploadState == StateIdle) && !ml_sendUpload.empty()) {
    // Set Retry & Start Uploading
    mui8_uploadRetry = (*(ml_sendUpload.begin())).ui8_retryCount;
    startUploadCommandChangeDesignator ();
  }

  return true;
}


/** store every device description with its length in the map with its lanuage label
    @return true => device description successfully stored
  */
bool
DevPropertyHandler_c::queuePoolInMap (const HUGE_MEM uint8_t* apc_devicePoolByteArray, uint32_t aui32_bytestreamlength, bool ab_setToDefault)
{
  /** @todo SOON: add test for minimum size of the pool (1 DeviceObject + 1 DeviceElementObject)*/

  LanguageLabel_c langLabel;
  DevicePool_c devicePool (apc_devicePoolByteArray, aui32_bytestreamlength);

  langLabel = &(apc_devicePoolByteArray[getLabelOffset(apc_devicePoolByteArray)]);
  STL_NAMESPACE::map<LanguageLabel_c, DevicePool_c>::iterator c_iterNew = mmap_deviceDescription.insert(mmap_deviceDescription.begin(), STL_NAMESPACE::pair<LanguageLabel_c, DevicePool_c>(langLabel, devicePool));

  //set DeviceDescription to default
  //if nothing is default, take the first mapped pointer
  if ((mpc_devDefaultDeviceDescription == NULL) || (ab_setToDefault) )
  {
    mpc_devDefaultDeviceDescription = &(c_iterNew->second);
    #if 0
    STL_NAMESPACE::map<LanguageLabel_c, DevicePool_c>::iterator it_default;
    it_default = mmap_deviceDescription.begin();
    mpc_devDefaultDeviceDescription = &it_default->second;
    #endif
  }
  return true;
}


/** every possible device description is stored in a maps
    @param apc_wsMasterIdentItem (of type const IdentItem_c*) must be a WorkingSetMASTER!
    @return true => if pool was successfully stored
  */
bool
DevPropertyHandler_c::registerDevicePool(const IdentItem_c* apc_wsMasterIdentItem, const HUGE_MEM uint8_t* apc_devicePoolByteArray, const uint32_t aui32_bytestreamlength, bool ab_setToDefault)
{
  if (apc_wsMasterIdentItem == NULL) return false;

  if (!apc_wsMasterIdentItem->isMaster()) return false;

  //no double registration for one device description
  if (men_poolState != OPNotRegistered) return false;

  mpc_wsMasterIdentItem = apc_wsMasterIdentItem;

  if (!(queuePoolInMap(apc_devicePoolByteArray, aui32_bytestreamlength, ab_setToDefault)))
  {
    return false;
  }

  men_poolState = OPRegistered;      // try to upload until state == UploadedSuccessfully || CannotBeUploaded
  return true;
}


/**
  call to check if at least one tc_statusMessage has arrived so we know if the terminal is there.
  @return true -> >= 1 tc_statusMessages have arrived -> task controller is there.
*/
bool
DevPropertyHandler_c::isTcAlive (int32_t i32_currentTime)
{
  if ((-1 != mi32_tcStateLastReceived) && ( i32_currentTime - mi32_tcStateLastReceived <= 6000))
    return true;
  else
    return false;
}

void
DevPropertyHandler_c::sendWorkingSetTaskMsg(int32_t i32_currentTime)
{
  if (mpc_wsMasterIdentItem == 0 || !mpc_wsMasterIdentItem->isClaimedAddress())
    return;

  if (i32_currentTime - mi32_timeWsTaskMsgSent >= 2000)
  {
    mi32_timeWsTaskMsgSent = i32_currentTime;
    mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                            0x0F, 0x00, 0x00, 0x00, mui8_lastTcState, 0x00, 0x00, 0x00);

    getCanInstance4Comm() << *mpc_data;
  }
}

/**
  local instances: call to check
  - address claim completed at least 6sec in the past
  - TC status message received
*/
void
DevPropertyHandler_c::checkInitState()
{
  if (mpc_wsMasterIdentItem == 0)
    return;

  if ( (NULL != mpc_wsMasterIdentItem) && mpc_wsMasterIdentItem->isClaimedAddress()
       && (-1 == mi32_timeStartWaitAfterAddrClaim))
  {
    mi32_timeStartWaitAfterAddrClaim = HAL::getTime();
  }

  if ( (mi32_timeStartWaitAfterAddrClaim >= 0) && (HAL::getTime() - mi32_timeStartWaitAfterAddrClaim >= 6000) && (-1 != mi32_tcStateLastReceived))
  { // init is finished when more then 6sec after addr claim and at least one TC status message was received
    mb_initDone = TRUE;
  }
}

/** compare the received structure label from TC with that from the pool which should be uploaded
    if they are different, try a match via the local settings from the ISOTerminal
  */
void
DevPropertyHandler_c::initUploading()
{
  //compare received structurelabel
  uint8_t ui8_offset = getLabelOffset(mpc_devDefaultDeviceDescription->p_DevicePool);
  if (CNAMESPACE::strncmp(marrpch_structureLabel, (const char*)&mpc_devDefaultDeviceDescription->p_DevicePool[ui8_offset], 7) != 0)
  {
    getPoolForUpload();
  }
  else
  {
    if (mb_receivedLocalizationLabel)
    {
      char ch_temp[2] = { 'e', 'n' };
      #ifdef USE_ISO_TERMINAL
      //if there are no local settings in ISOTerminal take default language "en"
      if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientPtrByID(0) &&
          __IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInstPtr() &&
          (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->lastReceived != 0))
      {
        ch_temp[0] = ((__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->languageCode) >> 8) & 0xFF;
        ch_temp[1] = (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->languageCode) & 0xFF;
      }
      #endif
      if (CNAMESPACE::strncmp(marrpch_localizationLabel, ch_temp, 2) == 0)
      {
        men_uploadState = StateIdle;
        men_poolState = OPSuccessfullyUploaded;
        men_uploadStep = UploadNone;
        #ifdef DEBUG
        INTERNAL_DEBUG_DEVICE << "Stop Uploading - Pool already here..." << INTERNAL_DEBUG_DEVICE_ENDL;
        #endif
      }
      else
        getPoolForUpload();
    }
    else getPoolForUpload();
  }
}


/** if no structure label is found, choose a appropriate pool for upload
  */
void
DevPropertyHandler_c::getPoolForUpload()
{
  #ifdef USE_ISO_TERMINAL
  //if there are no local settings in ISOTerminal just take the default pool from the map
  // check first if ptr to client exists
  if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientPtrByID(0) &&
      __IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInstPtr() &&
      (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->lastReceived != 0))
  {
    //get local language from ISOTerminal
    char pc_langCode [2];
    pc_langCode[0] = ((__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->languageCode) >> 8) & 0xFF;
    pc_langCode[1] = (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->languageCode) & 0xFF;
    //compare with all stored pools -> take the first found pool
    STL_NAMESPACE::map<LanguageLabel_c, DevicePool_c>::iterator it_maps;
    for (it_maps = mmap_deviceDescription.begin();it_maps !=mmap_deviceDescription.end(); it_maps++)
    {
      if (CNAMESPACE::strncmp(it_maps->first.get(), pc_langCode, 2) == 0)
      {
        mpc_devPoolForUpload = &it_maps->second;
        return;
      }
    }
    //if no match (priority-list):
    //compare units
    for (it_maps = mmap_deviceDescription.begin();it_maps !=mmap_deviceDescription.end(); it_maps++)
    {
      //get all units from localization label
      if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->uDistance == (uint8_t)((it_maps->second.p_DevicePool[getLabelOffset(it_maps->second.p_DevicePool)+4] >> 6) & 0x3))
      {
        mpc_devPoolForUpload = &it_maps->second;
        return;
      }
      if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->uArea == (uint8_t)((it_maps->second.p_DevicePool[getLabelOffset(it_maps->second.p_DevicePool)+4] >> 4) & 0x3))
      {
        mpc_devPoolForUpload = &it_maps->second;
        return;
      }
      if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->uVolume == (uint8_t)((it_maps->second.p_DevicePool[getLabelOffset(it_maps->second.p_DevicePool)+4] >> 2) & 0x3))
      {
        mpc_devPoolForUpload = &it_maps->second;
        return;
      }
      if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->uMass == (uint8_t)((it_maps->second.p_DevicePool[getLabelOffset(it_maps->second.p_DevicePool)+4] >> 2) & 0x3))
      {
        mpc_devPoolForUpload = &it_maps->second;
        return;
      }
    }
    //compare date format
    for (it_maps = mmap_deviceDescription.begin();it_maps !=mmap_deviceDescription.end(); it_maps++)
    {
      if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->dFormat == (uint8_t)(it_maps->second.p_DevicePool[getLabelOffset(it_maps->second.p_DevicePool)+3] & 0xFF))
      {
        mpc_devPoolForUpload = &it_maps->second;
        return;
      }
    }
    //compare time format
    for (it_maps = mmap_deviceDescription.begin();it_maps !=mmap_deviceDescription.end(); it_maps++)
    {
      if (__IsoAgLib::getIsoTerminalInstance4Comm().getClientByID(0).getVtServerInst().getLocalSettings()->nTimeFormat == (uint8_t)((it_maps->second.p_DevicePool[getLabelOffset(it_maps->second.p_DevicePool)+2] >> 4) & 0x3))
      {
        mpc_devPoolForUpload = &it_maps->second;
        return;
      }
    }
  }
  #endif
  //if no matching pool was found just take the default pool
  if (mpc_devPoolForUpload == NULL) mpc_devPoolForUpload = mpc_devDefaultDeviceDescription;
}


/** send a request for Object Pool Transfer
  */
void
DevPropertyHandler_c::startUpload()
{
  //estimate size of bytestream
  uint32_t ui32_byteStreamLength = mpc_devPoolForUpload->devicePoolLength;
  mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                          procCmdPar_RequestOPTransferMsg,
                          (ui32_byteStreamLength & 0xff),
                          (ui32_byteStreamLength >> 8) & 0xff,
                          (ui32_byteStreamLength >> 16) & 0xff,
                          (ui32_byteStreamLength >> 24) & 0xff,
                          0xff, 0xff, 0xff);
  getCanInstance4Comm() << *mpc_data;
  mui32_uploadTimestamp = HAL::getTime();
  mui32_uploadTimeout = DEF_TimeOut_OPTransfer;

  men_uploadState = StateUploadPool;
  men_uploadStep = UploadWaitForRequestOPTransferResponse;
  #ifdef DEBUG
  INTERNAL_DEBUG_DEVICE << "Wait for response for request OP transfer..." << INTERNAL_DEBUG_DEVICE_ENDL;
  #endif
}


/** if a pool couldn't be uploaded, register error in IsoTerminal and set the necessary states
  */
void
DevPropertyHandler_c::outOfMemory()
{ // can't (up)load the pool.
  getILibErrInstance().registerError( iLibErr_c::RemoteServiceOutOfMemory, iLibErr_c::TaskController );
  men_uploadStep = UploadFailed; // no timeout needed
  men_poolState = OPCannotBeUploaded;
  #ifdef DEBUG
  INTERNAL_DEBUG_DEVICE << "upload failed, no retry" << INTERNAL_DEBUG_DEVICE_ENDL;
  #endif
}


/** put a new change designator command in the send-queue
    @return true, if command was queued
  */
bool
DevPropertyHandler_c::sendCommandChangeDesignator(uint16_t aui16_objectID, const char* apc_newString, uint8_t stringLength)
{
  // if string is shorter than length, it's okay to send - if it's longer, we'll clip - as client will REJECT THE STRING
  uint8_t strLen = (CNAMESPACE::strlen(apc_newString) < stringLength) ? CNAMESPACE::strlen(apc_newString) : stringLength;
  if (CNAMESPACE::strlen(apc_newString) <= 32)
  {
    ml_sendUpload.push_back(SendUploadBase_c (aui16_objectID, apc_newString, strLen, procCmdPar_ChangeDesignatorMsg));
    return true;
  }
  //DEBUG OUT
  //INTERNAL_DEBUG_DEVICE << "New Designator value exceeds a length of 32 characters! Choose a shorter name!"
  return false;
}


/** start Upload from the change designator value
    decide either using a single CAN Pkg or the mulitsendstreamer for strings longer than 4 characters
  */
void
DevPropertyHandler_c::startUploadCommandChangeDesignator()
{
  // Set new state
  men_uploadState = StateUploadCommand;

  // Get first element from queue
  SendUploadBase_c* actSend = &ml_sendUpload.front();

  // Set time-out values
  mui32_uploadTimeout = actSend->getUploadTimeout();
  mui32_uploadTimestamp = HAL::getTime();

  if ((actSend->vec_uploadBuffer.size() < 9)) {
    /// Fits into a single CAN-Pkg!
    mpc_data->setExtCanPkg8 (3, 0, 203, mui8_tcSourceAddress, mpc_wsMasterIdentItem->getIsoItem()->nr(),
                          actSend->vec_uploadBuffer [0], actSend->vec_uploadBuffer [1],
                          actSend->vec_uploadBuffer [2], actSend->vec_uploadBuffer [3],
                          actSend->vec_uploadBuffer [4], actSend->vec_uploadBuffer [5],
                          actSend->vec_uploadBuffer [6], actSend->vec_uploadBuffer [7]);
    getCanInstance4Comm() << *mpc_data;
    men_uploadCommand = UploadCommandWaitingForCommandResponse;
  }
  else
  {
    /// Use multi CAN-Pkgs [(E)TP], doesn't fit into a single CAN-Pkg!
    getMultiSendInstance().sendIsoTarget(mpc_wsMasterIdentItem->isoName(),
      getIsoMonitorInstance4Comm().isoMemberNr(mui8_tcSourceAddress).isoName(),
      &actSend->vec_uploadBuffer.front(), actSend->vec_uploadBuffer.size(), PROCESS_DATA_PGN, men_sendSuccess);
    men_uploadCommand = UploadMultiSendCommandWaitingForCommandResponse;
  }
}


/** finish the upload of a single command and delete it from the queue
  */
void
DevPropertyHandler_c::finishUploadCommandChangeDesignator()
{
  men_uploadState = StateIdle;
  men_uploadStep = UploadNone;

  //delete first processed cmd of the queue
  if (! ml_sendUpload.empty() ) ml_sendUpload.pop_front();
}


void
DevPropertyHandler_c::setDataNextStreamPart (MultiSendPkg_c* mspData, uint8_t bytes)
{
  uint16_t ui16_isoNameOffset= DEF_Transfer_Code /* uploadcommand */ + DEF_TableID /* type of element (3 byte) */
                               + DEF_ObjectID /*Object ID (2 byte)*/ + DEF_Designator_Length /* designatorlength */
                               + mpc_devPoolForUpload->p_DevicePool[DEF_Transfer_Code+DEF_TableID+DEF_ObjectID] /* designator */
                               + DEF_Software_Version_Length /* length of sw version */
                               + mpc_devPoolForUpload->p_DevicePool[DEF_Transfer_Code+DEF_TableID+DEF_ObjectID+DEF_Designator_Length+mpc_devPoolForUpload->p_DevicePool[DEF_Transfer_Code+DEF_TableID+DEF_ObjectID]];
  const bool cb_left = (ui16_isoNameOffset / 7) == (ui16_currentSendPosition / 7);
  const bool cb_right = ((ui16_isoNameOffset+7) / 7) == (ui16_currentSendPosition / 7);
  if (cb_left || cb_right)
  { // special overwriting
    uint8_t p14ui8_overlayBuffer[14];
    int index = 0;
    for (int arr_index=((ui16_isoNameOffset/7)*7); arr_index < (((ui16_isoNameOffset/7)*7)+14); index++, arr_index++)
      p14ui8_overlayBuffer[index] = mpc_devPoolForUpload->p_DevicePool[arr_index];
    // overwrite isoName
    const uint16_t ui16_tmpOffset = ui16_isoNameOffset%7;
    static_cast<const IdentItem_c*>(mpc_wsMasterIdentItem)->getIsoItem()->outputNameUnion()->getDataToString(
      p14ui8_overlayBuffer+ui16_tmpOffset );
    // send from overlayed buffer
    mspData->setDataPart (p14ui8_overlayBuffer, cb_left ? 0 : 7, bytes);
  }
  else
  { // normal sending
    mspData->setDataPart (mpc_devPoolForUpload->p_DevicePool, ui16_currentSendPosition, bytes);
  }
  ui16_currentSendPosition += bytes;
}


void
DevPropertyHandler_c::resetDataNextStreamPart()
{
  ui16_currentSendPosition = 0;
}


void
DevPropertyHandler_c::saveDataNextStreamPart ()
{
  ui16_storedSendPosition = ui16_currentSendPosition;
}


void
DevPropertyHandler_c::restoreDataNextStreamPart ()
{
  ui16_currentSendPosition = ui16_storedSendPosition;
}


uint32_t
DevPropertyHandler_c::getStreamSize ()
{
  return mpc_devPoolForUpload->devicePoolLength;
}


uint8_t
DevPropertyHandler_c::getFirstByte ()
{
  return mpc_devPoolForUpload->p_DevicePool[0];
}

};




