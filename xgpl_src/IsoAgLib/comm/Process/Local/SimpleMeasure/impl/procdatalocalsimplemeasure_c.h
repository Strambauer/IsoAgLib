/***************************************************************************
                          procdatalocalsimplemeasure_c.h  -
                             managing of local process data object
                             -------------------
    begin                : Fri Apr 07 2000
    copyright            : (C) 2000 - 2004 by Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
    type                 : Header
    $LastChangedDate$
    $LastChangedRevision$
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
#ifndef PROCDATA_LOCAL_SIMPLEMEASURE_H
#define PROCDATA_LOCAL_SIMPLEMEASURE_H

/* *************************************** */
/* ********** include headers ************ */
/* *************************************** */
#include "../../impl/procdatalocalbase_c.h"
#include "../../StdSetpointElements/impl/setpointlocal_c.h"

// Begin Namespace IsoAgLib
namespace __IsoAgLib {
// ****************************************************************************************
// ************************** ProcDataLocalSimpleMeasure_c **************************
// ****************************************************************************************

/**
  @brief Internal implementation for managing of local process data object with restricted
  measurement data feature set ( %i.e. without measurement programs
  -> only one shot value requests are supported ).

  Has __IsoAgLib::SetpointLocal_c / IsoAgLib::iSetpointLocal_c
  as member for doing setpoint specific jobs.
  \n
  Projects which use this class, must include the files and succeding subdirectories
  of the following subdirectories of xgpl_src/IsoAgLib/Process:
  - \e Local/StdSetpointElements,
  - \e StdSetpointElements and
  - \e impl
  \n
  Example:
  \code
  // define local device type
  IsoAgLib::GetyPos c_myGtp( 1, 0 );
  // creation of process data instance
  iProcDataLocalSimpleMeasure_c c_workState;
  // init for LIS=0, local device type/subtype=1/0, complete work width=0xFF,
  // target process data/PRI=2, pointer to my local device type ( to resolve dynamic SA at time of cmd send ),
  // load/store measurememnt data to/from EEPROM
  c_workState.init( 0, myGtp, 0x1, 0x0, 0xFF, 2, c_myGtp, &c_myGtp, false, 0x1234 );

  // update current measurement value ( real value, which can differ from commanded value )
  c_workState.setMasterVal( 100 );
  // backend in IsoAgLib doesn't provide measurement programs ( only single one-shot value requests )

  // check if unhandled setpoints are received
  if ( c_workState.setpoint().unhandledCnt() > 0 ) {
    if ( ! c_workState.setpoint().existMaster() ) {
      for ( uint8_t ind = 0; ind < c_workState.setpoint().unhandledCnt(); ind++ )
      { // now decide on all received setpoints
        if ( ( c_workState.setpoint().unhandledCnt() == 1 )
          && ( ( c_workState.setpoint().unhandledFirst().exact() == 100 ) // undhandledFirst() is shortcut for unhandledInd( 0 )
            || ( c_workState.setpoint().unhandledInd( 0 ).exact() == 0   ) ) )
        { // as no master exist, and only one setpoint received -> simply accept if value is 0 or 100
          c_workState.setpoint().unhandledFirst().setMaster( true );
        }
      }
    }
    else if ( ( c_workState.setpoint().unhandledMaster().exact() == 100 )
           || ( c_workState.setpoint().unhandledMaster().exact() == 0 ) )
    { // simply accept new master if 0 or 100
      c_workState.setpoint().acceptNewMaster();
    }
    // send answer for all received setpoints
    c_workState.setpoint().answerAllUnhandled();
  }
  \endcode

  @author Dipl.-Inform. Achim Spangler
*/
class ProcDataLocalSimpleMeasure_c : public ProcDataLocalBase_c  {

public:
  /**
    constructor which can set all element vars

    possible errors:
        * Err_c::badAlloc not enough memory to insert first  MeasureProgLocal
    ISO parameter
    @param ps_elementDDI optional pointer to array of structure IsoAgLib::ElementDDI_s which contains DDI, element, isSetpoint and ValueGroup
                         (array is terminated by ElementDDI_s.ui16_element == 0xFFFF)

    DIN parameter
    @param rui8_lis optional LIS code of this instance
    @param rui8_wert optional WERT code of this instance
    @param rui8_inst optional INST code of this instance
    @param rui8_zaehlnum optional ZAEHLNUM code of this instance

    @param rc_gtp optional GETY_POS code of Process-Data
    @param rui8_pri PRI code of messages with this process data instance (default 2)
    @param rc_ownerGtp optional GETY_POS of the owner
    @param rpc_gtp pointer to updated GETY_POS variable of owner
    @param rb_cumulativeValue
             -# for process data like distance, time, area
                 the value of the measure prog data sets is updated
                 on master value update dependent on the value increment
                 since the last master value update
                 -> if a remote member resets his data set copy, datas of
                    other members aren't changed
                 -> if this data is saved in EEPROM, the main application
                    needn't take into account the initial EEPROM value, as
                     setting of the master val is independent from EEPROM
             -#  for values like speed, state, rpm aren't updated by increment,
                  -> the given master value is propagated equally to all
                      measure prog data sets
                  -> if this data is saved in EEPROM, the stored value is loaded
                     as initial master value, and is initially propagated to all
                     measure prog data sets
    @param rui16_eepromAdr optional adress where value is stored in EEPROM
    @param rpc_processDataChangeHandler optional pointer to handler class of application
    @param ri_singletonVecKey optional key for selection of IsoAgLib instance (default 0)
  */
  ProcDataLocalSimpleMeasure_c(
#ifdef USE_ISO_11783
                               const IsoAgLib::ElementDDI_s* ps_elementDDI = NULL,
#endif
#ifdef USE_DIN_9684
                               uint8_t rui8_lis = 0xFF,
                               uint8_t rui8_wert = 0,
                               uint8_t rui8_inst = 0,
                               uint8_t rui8_zaehlnum = 0xFF,
#endif
                               const GetyPos_c& rc_gtp = GetyPos_c::GetyPosInitialProcessData,
                               uint8_t rui8_pri = 2,
                               const GetyPos_c& rc_ownerGtp = GetyPos_c::GetyPosUnspecified,
                               const GetyPos_c *rpc_gtp = NULL,
                               bool rb_cumulativeValue = false,
#ifdef USE_EEPROM_IO
                               uint16_t rui16_eepromAdr = 0xFFFF,
#endif
                               IsoAgLib::ProcessDataChangeHandler_c *rpc_processDataChangeHandler = NULL,
                               int ri_singletonVecKey = 0
      );

  /**
    initialise this ProcDataLocalSimpleMeasure_c instance to a well defined initial state

    possible errors:
        * Err_c::badAlloc not enough memory to insert first  MeasureProgLocal
    ISO parameter
    @param ps_elementDDI optional pointer to array of structure IsoAgLib::ElementDDI_s which contains DDI, element, isSetpoint and ValueGroup
                         (array is terminated by ElementDDI_s.ui16_element == 0xFFFF)

    DIN parameter
    @param rui8_lis optional LIS code of this instance
    @param rui8_wert optional WERT code of this instance
    @param rui8_inst optional INST code of this instance
    @param rui8_zaehlnum optional ZAEHLNUM code of this instance

    @param rc_gtp optional GETY_POS code of Process-Data
    @param rui8_pri PRI code of messages with this process data instance (default 2)
    @param rc_ownerGtp optional GETY_POS of the owner
    @param rpc_gtp pointer to updated GETY_POS variable of owner
    @param rb_cumulativeValue
             -# for process data like distance, time, area
                 the value of the measure prog data sets is updated
                 on master value update dependent on the value increment
                 since the last master value update
                 -> if a remote member resets his data set copy, datas of
                    other members aren't changed
                 -> if this data is saved in EEPROM, the main application
                    needn't take into account the initial EEPROM value, as
                     setting of the master val is independent from EEPROM
             -#  for values like speed, state, rpm aren't updated by increment,
                  -> the given master value is propagated equally to all
                      measure prog data sets
                  -> if this data is saved in EEPROM, the stored value is loaded
                     as initial master value, and is initially propagated to all
                     measure prog data sets
    @param rui16_eepromAdr optional adress where value is stored in EEPROM
    @param rpc_processDataChangeHandler optional pointer to handler class of application
    @param ri_singletonVecKey optional key for selection of IsoAgLib instance (default 0)
  */
  void init(
#ifdef USE_ISO_11783
            const IsoAgLib::ElementDDI_s* ps_elementDDI,
#endif
#ifdef USE_DIN_9684
            uint8_t rui8_lis = 0xFF,
            uint8_t rui8_wert = 0,
            uint8_t rui8_inst = 0,
            uint8_t rui8_zaehlnum = 0xFF,
#endif
            const GetyPos_c& rc_gtp = GetyPos_c::GetyPosInitialProcessData,
            uint8_t rui8_pri = 2,
            const GetyPos_c& rc_ownerGtp = GetyPos_c::GetyPosUnspecified,
            const GetyPos_c *rpc_gtp = NULL, bool rb_cumulativeValue = false,
#ifdef USE_EEPROM_IO
            uint16_t rui16_eepromAdr = 0xFFFF,
#endif
            IsoAgLib::ProcessDataChangeHandler_c *rpc_processDataChangeHandler = NULL,
            int ri_singletonVecKey = 0
      );


  /** default destructor which has nothing to do */
  ~ProcDataLocalSimpleMeasure_c();
  /** deliver a reference to the setpoint management class */
  SetpointLocal_c& setpoint( void ) { return c_setpoint; };
  /** deliver a reference to the setpoint management class */
  const SetpointLocal_c& setpointConst( void ) const { return c_setpoint; };

  /**
    perform periodic actions
    delete all running measure programs of members which are >3sec inactive;
    deletion of outdated setpoints is managed by SetpointLocal_c::timeEvent
    @return true -> all planned executions performed
  */
  virtual bool timeEvent( void );

private: // Private methods
  /** processing of a setpoint message */
  virtual void processSetpoint();
 private:
  /** flexible management of setpoint */
  SetpointLocal_c c_setpoint;
};


}
#endif
