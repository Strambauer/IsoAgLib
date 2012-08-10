/***************************************************************************
                          measureproglocal_c.cpp - object for managing local

  (C) Copyright 2009 - 2012 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/

/* *************************************** */
/* ********** include headers ************ */
/* *************************************** */
#include "measureproglocal_c.h"
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/process_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/processdatachangehandler_c.h>
#include <IsoAgLib/comm/Part7_ApplicationLayer/impl/tracmove_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/procdatalocal_c.h>


namespace __IsoAgLib {

void MeasureProgLocal_c::init(
  ProcDataLocal_c *const apc_processData,
  int32_t ai32_masterVal,
  int32_t ai32_initialVal,
  const IsoName_c& ac_callerISOName)
{
  MeasureProgBase_c::init( apc_processData, ai32_initialVal, ac_callerISOName  );

  mi32_lastMasterVal = ai32_masterVal;
  if (ai32_initialVal != 0)
  { // set medSum, medCnt to initial value read from EEPROM
    mi32_medCnt = 1;
    mi32_medSum = ai32_initialVal;
  }
  else
  {
    mi32_medCnt = mi32_medSum = 0;
  }

  mi32_integ = 0;

  mlist_thresholdInfo.clear();
}

const MeasureProgLocal_c& MeasureProgLocal_c::operator=(const MeasureProgLocal_c& acrc_src){
  // call base class operator
  MeasureProgBase_c::operator=(acrc_src);

  assignFromSource( acrc_src );

  // return reference to source
  return acrc_src;
}

MeasureProgLocal_c::MeasureProgLocal_c(const MeasureProgLocal_c& acrc_src)
   : MeasureProgBase_c(acrc_src){
  assignFromSource( acrc_src );
}

void MeasureProgLocal_c::assignFromSource( const MeasureProgLocal_c& acrc_src )
{ // copy element vars
  mi32_lastMasterVal = acrc_src.mi32_lastMasterVal;
  mi32_medCnt = acrc_src.mi32_medCnt;
  mi32_medSum = acrc_src.mi32_medSum;
  mi32_integ = acrc_src.mi32_integ;
}

MeasureProgLocal_c::~MeasureProgLocal_c(){
}

bool MeasureProgLocal_c::start(Proc_c::type_t ren_type,
                        Proc_c::doSend_t ren_doSend, int32_t ai32_masterVal){
  // call start function of base class
  MeasureProgBase_c::start(ren_type, ren_doSend);
  mi32_lastMasterVal = ai32_masterVal;
  bool b_sendVal = true;

  // start the given subprog items
  for (Vec_MeasureSubprogIterator pc_iter = mvec_measureSubprog.begin(); pc_iter != mvec_measureSubprog.end(); pc_iter++)
  {
    if (pc_iter->doSend() != ren_doSend)
      //MeasureSubprog_c not matching!
      continue;

    switch (pc_iter->type() & ren_type)
    {
      case Proc_c::TimeProp:
        pc_iter->start(System_c::getTime());
        men_accumProp = Proc_c::AccumTime;
        break;
      #if defined(USE_BASE) || defined(USE_TRACTOR_MOVE)
      case Proc_c::DistProp:
        pc_iter->start(int32_t(getTracMoveInstance4Comm().distTheor()));
        men_accumProp = Proc_c::AccumDist;
        break;
      #endif
      case Proc_c::MaximumThreshold:
      {
        pc_iter->start();
        b_sendVal = false; // do not send value when a threshold is set
        const ThresholdInfo_s s_thresholdInfo = {ren_type, ren_doSend, pc_iter->increment(), true};
        mlist_thresholdInfo.push_front(s_thresholdInfo);
        break;
      }
      case Proc_c::MinimumThreshold:
      {
        pc_iter->start();
        b_sendVal = false;  // do not send value when a threshold is set
        const ThresholdInfo_s s_thresholdInfo = {ren_type, ren_doSend, pc_iter->increment(), false};
        mlist_thresholdInfo.push_front(s_thresholdInfo);
        break;
      }
      case Proc_c::OnChange:
        pc_iter->start(val());
        break;
      case Proc_c::NullType: break; // just to make compiler happy
    } // switch
  } // for

  // send first values: if now without success mark for later resend with true
  bool triggeredIncrement = false;
  if (b_sendVal)
    triggeredIncrement = !sendRegisteredVals(ren_doSend);

  // set the timer period for process_c to a low value (maybe the new programm triggers soon)
  getProcessInstance4Comm().resetTimerPeriod();

  // return if successful sent starting values
  return triggeredIncrement;
}

bool MeasureProgLocal_c::start(Proc_c::type_t ren_type, Proc_c::doSend_t ren_doSend)
{
  return start(ren_type, ren_doSend, mi32_lastMasterVal);
}

bool MeasureProgLocal_c::stop(bool /* b_deleteSubProgs */, Proc_c::type_t ren_type, Proc_c::doSend_t ren_doSend){
  // send the registered values
  bool b_sendResult = true;
  if ((Proc_c::MinimumThreshold != ren_type) && (Proc_c::MaximumThreshold != ren_type)
      && (Proc_c::NullType != ren_type) ) // do not send values for threshold resets and NullType
  {
    b_sendResult = sendRegisteredVals();
  }

  if (Proc_c::NullType == ren_type)
    MeasureProgBase_c::stop();
  else
  { // ISO: clear only the appropriate MeasureSubprog from the sub prog list
    for (Vec_MeasureSubprogIterator pc_iter = mvec_measureSubprog.begin(); pc_iter != mvec_measureSubprog.end();)
    {
      if ((pc_iter->type() == ren_type) && (pc_iter->doSend() == ren_doSend))
      {
        pc_iter = mvec_measureSubprog.erase(pc_iter);
      }
      else
        pc_iter++;
    }
  }

  // cleanup corresponding threshold info
  if ((Proc_c::MaximumThreshold & ren_type) || (Proc_c::MinimumThreshold & ren_type))
  { // search corresponding threshold info
    for (List_ThresholdInfoIterator ps_iterThreshold = mlist_thresholdInfo.begin(); ps_iterThreshold != mlist_thresholdInfo.end();)
    {
      if ((ps_iterThreshold->en_type == ren_type) && (ps_iterThreshold->en_doSend == ren_doSend))
        ps_iterThreshold = mlist_thresholdInfo.erase(ps_iterThreshold);
      else
        ps_iterThreshold++;
    }
  }

  return b_sendResult;
}

bool MeasureProgLocal_c::sendValForGroup( ProcessCmd_c::ValueGroup_t en_valueGroup, const IsoName_c& ac_targetISOName) const
{
  ProcessPkg_c pkg;
  // prepare general command in process pkg
  pkg.mc_processCmd.setValues(false /* isSetpoint */, false, /* isRequest */
                                                           en_valueGroup, ProcessCmd_c::setValue);
  return processDataConst().sendValISOName( pkg, ac_targetISOName, valForGroup(en_valueGroup));
}

bool MeasureProgLocal_c::sendSetpointValForGroup( ProcessCmd_c::ValueGroup_t en_valueGroup, const IsoName_c& ac_targetISOName) const {
  ProcessPkg_c pkg;
  // prepare general command in process pkg
  pkg.mc_processCmd.setValues(true /* isSetpoint */, false, /* isRequest */
                                                              en_valueGroup, ProcessCmd_c::setValue);
  return processDataConst().sendValISOName( pkg, ac_targetISOName, setpointValForGroup(en_valueGroup));
}

int32_t MeasureProgLocal_c::setpointValForGroup(ProcessCmd_c::ValueGroup_t en_valueGroup) const {
  int32_t i32_value = 0;
  ProcDataLocal_c* pc_procdata = pprocessData();
  if (pc_procdata->setpointExistMaster())
  {
    switch (en_valueGroup)
    {
      case ProcessCmd_c::exactValue:
        i32_value = pc_procdata->setpointExactValue();
        break;
      case ProcessCmd_c::defaultValue:
        i32_value = pc_procdata->setpointDefaultValue();
        break;
      case ProcessCmd_c::minValue:
        i32_value = pc_procdata->setpointMinValue();
        break;
      case ProcessCmd_c::maxValue:
        i32_value = pc_procdata->setpointMaxValue();
        break;
      default:
        IsoAgLib::getILibErrInstance().registerNonFatal( IsoAgLib::iLibErr_c::ProcData, getMultitonInst() );
    }
  }
  return i32_value;
}

bool MeasureProgLocal_c::processMsg( const ProcessPkg_c& arc_data )
{
  bool b_result = MeasureProgBase_c::processMsg( arc_data );

  // call base function - if base function returns true, nothing else must be done
  if (!b_result)
  {
    if (arc_data.senderItem() == NULL)
    { // sender with SA 0xFE is not of interest here!
      return true;
    }

    // backup sender isoname before answering with resetValForGroup() or sendValForGroup() (modification during send in c_pkg !)
    const IsoName_c c_senderIsoNameOrig = arc_data.senderItem()->isoName();

    // ISO: value in message contains reset value
    const int32_t ci32_val = arc_data.getValue();
    const uint32_t cui32_ddi = arc_data.getValue();

    // the message was a value message -> evaluate it here
    if ( arc_data.mc_processCmd.getCommand() == ProcessCmd_c::setValue)
    { // write - accept only write actions to local data only if this is reset try

      resetValForGroup(arc_data.mc_processCmd.getValueGroup(), ci32_val);

      if (Proc_c::defaultDataLoggingDDI == arc_data.DDI())
      { // setValue command for default data logging DDI stops measurement (same as TC task status "suspended")
        getProcessInstance4Comm().processTcStatusMsg(0, c_senderIsoNameOrig, true /* ab_skipLastTcStatus */);
      }

      // call handler function if handler class is registered
      if ( processDataConst().getProcessDataChangeHandler() != NULL )
        processDataConst().getProcessDataChangeHandler()->processMeasurementReset( pprocessData(), cui32_ddi, ci32_val, c_senderIsoNameOrig.toConstIisoName_c());
    } // write
    else
    { // read -> answer wanted value
      sendValForGroup( arc_data.mc_processCmd.getValueGroup(), c_senderIsoNameOrig );

      if ((Proc_c::defaultDataLoggingDDI == arc_data.DDI()) &&
          (processDataConst().getProcessDataChangeHandler() != NULL ))
        // call handler function if handler class is registered
        processDataConst().getProcessDataChangeHandler()->processDefaultLoggingStart( pprocessData(), cui32_ddi, ci32_val, c_senderIsoNameOrig.toConstIisoName_c() );
    } // read
  }

  return true;
}

MeasureProgLocal_c::MeasureProgLocal_c(
  ProcDataLocal_c *const apc_processData,
  int32_t ai32_masterVal,
  int32_t ai32_initialVal,
  const IsoName_c& ac_callerISOName)
: MeasureProgBase_c(apc_processData, ai32_initialVal, ac_callerISOName )
{
  init( apc_processData, ai32_masterVal, ai32_initialVal, ac_callerISOName );
}

void MeasureProgLocal_c::setVal(int32_t ai32_val){
  int32_t i32_incr =  ai32_val - mi32_lastMasterVal;
  int32_t i32_time =  System_c::getTime();
  int32_t i32_timeDelta = i32_time - mi32_lastTime;
  int32_t i32_oldDelta = mi32_delta;
  mi32_lastTime = i32_time;

  // update values:
  // for cumulative values -> update mi32_val by increment
  // else take the actual given master value
  mi32_lastMasterVal = ai32_val;
  if (processData().mb_cumulativeValue) mi32_val += i32_incr;
  else mi32_val = ai32_val;

  // update min max
  if (val() > max()) setMax(val());
  if (val() < min()) setMin(val());

  // claculate delta and accel in 1/s
  if (i32_timeDelta > 0)
  { // if two calls to this function follow immediate
    mi32_delta = (i32_incr * 1000) / i32_timeDelta;
    mi32_accel = ((mi32_delta - i32_oldDelta) * 1000) / i32_timeDelta;

  }

  // now check if one subprog triggers
  bool b_singleTest = false;
  for (Vec_MeasureSubprogIterator pc_iter = mvec_measureSubprog.begin();
       pc_iter != mvec_measureSubprog.end(); pc_iter++)
  {
    bool triggeredIncrement = false;
    switch (pc_iter->type())
    {
      case Proc_c::TimeProp:
        triggeredIncrement = pc_iter->updateTrigger(i32_time);
        //triggeredIncrement = (b_singleTest)? true : triggeredIncrement;
        // update med/integ
        updatePropDepVals();
        break;
      case Proc_c::DistProp:
        #if defined(USE_BASE) || defined(USE_TRACTOR_MOVE)
        triggeredIncrement = pc_iter->updateTrigger(int32_t(getTracMoveInstance4Comm().distTheor()));
        #endif
        //triggeredIncrement = (b_singleTest)? true : triggeredIncrement;
        // update med/integ
        updatePropDepVals();
        break;
      case Proc_c::OnChange:
        triggeredIncrement = pc_iter->updateTrigger(val());
        //triggeredIncrement = (b_singleTest)? true : triggeredIncrement;
        break;
      case Proc_c::NullType: break; // just to make compiler happy
      default: ;
    } // switch

    // if triggeredIncrement == true the registered values should be sent
    if (triggeredIncrement)
    { // send the registered values
      if (!minMaxLimitsPassed(pc_iter->doSend()))
      {
        // omit this value send
        continue;
      }
      // if at least one send try had success reset triggeredIncrement
      sendRegisteredVals();
    }
  } // for
}

bool MeasureProgLocal_c::sendRegisteredVals(Proc_c::doSend_t ren_doSend){
  bool b_success = false;

  ProcessCmd_c::ValueGroup_t en_valueGroup;

  switch (ren_doSend)
  {
    case Proc_c::DoValForDefaultSetpoint: en_valueGroup = ProcessCmd_c::defaultValue; break;
    case Proc_c::DoValForMinSetpoint:
    case Proc_c::DoValForMinMeasurement:
      en_valueGroup = ProcessCmd_c::minValue; break;
    case Proc_c::DoValForMaxSetpoint:
    case Proc_c::DoValForMaxMeasurement:
      en_valueGroup = ProcessCmd_c::maxValue; break;
    case Proc_c::DoValForExactSetpoint:   en_valueGroup = ProcessCmd_c::exactValue; break;
    default:                              en_valueGroup = ProcessCmd_c::noValue;
  }

  if (ProcessCmd_c::noValue != en_valueGroup)
    // get value from corresponding setpoint and send it
    b_success = (sendSetpointValForGroup( en_valueGroup, isoName()))?true : b_success;

  // normal measurement (no measurement on setpoint DDI)
  if (Proc_c::DoVal == ren_doSend)
    b_success = (sendValForGroup( ProcessCmd_c::exactValue, isoName()))?true : b_success;

  return b_success;
}

void MeasureProgLocal_c::initVal(int32_t ai32_val){
  // first call the base function
  MeasureProgBase_c::initVal(ai32_val);

  mi32_medSum = mi32_integ = ai32_val;
  mi32_medCnt = 1;
}

bool MeasureProgLocal_c::resetVal(int32_t ai32_val){
  // send resetted val
  bool b_sendSuccess;

  ProcessPkg_c pkg;

  // prepare general command in process pkg
  pkg.mc_processCmd.setValues(false /* isSetpoint */, false, /* isRequest */
                                                              ProcessCmd_c::exactValue, ProcessCmd_c::setValue);
  // allow reset with value
  //mi32_val = 0;
  mi32_val = ai32_val;

  b_sendSuccess = processData().sendValISOName( pkg, mc_isoName, val());

  return b_sendSuccess;
}

bool MeasureProgLocal_c::resetInteg()
{
  mi32_integ = 0;
  // do not send a message to remote instance
  return true;
}

bool MeasureProgLocal_c::resetMed()
{
  mi32_medCnt = 0;
  mi32_medSum = 0;
  // do not send a message to remote instance
  return true;
}

bool MeasureProgLocal_c::resetMin()
{
  ProcessPkg_c pkg;
  // prepare general command in process pkg
  pkg.mc_processCmd.setValues(false /* isSetpoint */, false, /* isRequest */
                                                              ProcessCmd_c::minValue, ProcessCmd_c::setValue);
  mi32_min = 0;
  return processData().sendValISOName( pkg, mc_isoName, min());
}

bool MeasureProgLocal_c::resetMax()
{
  ProcessPkg_c pkg;
  // prepare general command in process pkg
  pkg.mc_processCmd.setValues(false /* isSetpoint */, false, /* isRequest */
                                                              ProcessCmd_c::maxValue, ProcessCmd_c::setValue);
  mi32_max = 0;
  return processData().sendValISOName( pkg, mc_isoName, max());
}

bool MeasureProgLocal_c::timeEvent( uint16_t *pui16_nextTimePeriod )
{
  if ( Scheduler_Task_c::getAvailableExecTime() == 0 ) return false;
  int32_t i32_time = Scheduler_Task_c::getLastRetriggerTime();

  bool b_singleTest;
  int32_t i32_nextTimePeriod;
  int32_t i32_distTheor;

  for (Vec_MeasureSubprogIterator pc_iter = mvec_measureSubprog.begin(); pc_iter != mvec_measureSubprog.end(); pc_iter++)
  {
    bool triggeredIncrement = false;
    b_singleTest = false;
    i32_nextTimePeriod = 0;
    switch (pc_iter->type())
    {
      case Proc_c::TimeProp:
        triggeredIncrement = pc_iter->updateTrigger(i32_time);
        // if b_singleTest is true set triggeredIncrement to true,
        // otherwise let it unchanged
        //triggeredIncrement = (b_singleTest)? true : triggeredIncrement;
        // update med/integ
        if ((triggeredIncrement)&&(men_accumProp == Proc_c::AccumTime))updatePropDepVals();

        // calculate next timer period
        i32_nextTimePeriod = pc_iter->nextTriggerTime(i32_time);

        break;
      case Proc_c::DistProp:
        #if defined(USE_BASE) || defined(USE_TRACTOR_MOVE)
        i32_distTheor = getTracMoveInstance4Comm().distTheor();
        triggeredIncrement = pc_iter->updateTrigger(i32_distTheor);
        #else
        i32_distTheor = 0;
        #endif
        //triggeredIncrement = (b_singleTest)? true : triggeredIncrement;
        // update med/integ
        if ((triggeredIncrement)&&(men_accumProp == Proc_c::AccumTime))updatePropDepVals();

        // calculate next timer period
        i32_nextTimePeriod = pc_iter->nextTriggerTime(i32_distTheor);

        break;
      case Proc_c::OnChange:
        b_singleTest = pc_iter->updateTrigger(val());
        //triggeredIncrement = (b_singleTest)? true : triggeredIncrement;
        break;
      default:
        break;
    } // switch

    if (i32_nextTimePeriod && pui16_nextTimePeriod)
    {
      if ( (i32_nextTimePeriod > 0) // something valid to set
            // *pui16_nextTimePeriod not yet set or i32_nextTimePeriod smaller => set
            && ((0 == *pui16_nextTimePeriod) || (i32_nextTimePeriod < *pui16_nextTimePeriod))
          )
      {
        *pui16_nextTimePeriod = i32_nextTimePeriod;
      }
    }

    // if triggeredIncrement == true the registered values should be sent
    // if needed an old unsuccessfull send try is redone (deactivated!)
    if (triggeredIncrement)
    {
      if (!minMaxLimitsPassed(pc_iter->doSend()))
      {
        // omit this value send
        continue;
      }
      sendRegisteredVals(pc_iter->doSend());
    }
  }

  return true;
}

bool MeasureProgLocal_c::minMaxLimitsPassed(Proc_c::doSend_t ren_doSend) const
{
  bool b_checkMin = false;
  bool b_checkMax = false;
  int32_t i32_maxVal = 0;
  int32_t i32_minVal = 0;

  for (List_ThresholdInfoConstIterator ps_iterThreshold = mlist_thresholdInfo.begin(); ps_iterThreshold != mlist_thresholdInfo.end(); ps_iterThreshold++)
  {
    if (ps_iterThreshold->en_doSend == ren_doSend)
    {
      switch (ps_iterThreshold->en_type)
      {
        case Proc_c::MaximumThreshold: b_checkMax = true; i32_maxVal = ps_iterThreshold->i32_threshold; break;
        case Proc_c::MinimumThreshold: b_checkMin = true; i32_minVal = ps_iterThreshold->i32_threshold; break;
        default: ;
      }
    }
  }

  if ( b_checkMin && b_checkMax && (i32_maxVal < i32_minVal) && ((i32_maxVal >= val()) || (i32_minVal <= val())) )
    return true;

  if ( (b_checkMin && i32_minVal > val() ) ||
       (b_checkMax && i32_maxVal < val() ) )
    return false;

  return true;
}

void MeasureProgLocal_c::updatePropDepVals()
{
  incrInteg(val()); // increment integral
  // update medium based on actual val and count of actual calculated vals
  incrMedSum(val());

  incrMedCnt(); // increment medCnt to calc medium from integ
}


} // end of namespace __IsoAgLib
