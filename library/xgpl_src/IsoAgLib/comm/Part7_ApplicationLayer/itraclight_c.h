/*
  itraclight_c.h: working on Base Data Msg Type Light; stores, updates
    and delivers all base data informations from CanCustomer_c derived
    for CAN sending and receiving interaction; from SchedulerTask_c
    derived for interaction with other IsoAgLib objects

  (C) Copyright 2009 - 2019 by OSB AG

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Usage under Commercial License:
  Licensees with a valid commercial license may use this file
  according to their commercial license agreement. (To obtain a
  commercial license contact OSB AG via <http://isoaglib.com/en/contact>)

  Usage under GNU General Public License with exceptions for ISOAgLib:
  Alternatively (if not holding a valid commercial license)
  use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#ifndef ITRACLIGHT_C_H
#define ITRACLIGHT_C_H

#if _MSC_VER
  #pragma message ( "warning: iTracLight_c is deprecated and will be removed in a future release! Please migrate to using the new class iTractorLighting_c." )
#elif __GNUC__
  #warning "iTracLight_c is deprecated and will be removed in a future release! Please migrate to using the new class iTractorLighting_c."
#endif

#include <IsoAgLib/comm/Part5_NetworkManagement/iidentitem_c.h>
#include "ibasetypes.h"
#include "impl/traclight_c.h"


// Begin Namespace IsoAgLib
namespace IsoAgLib {

  /** stores, updates  and delivers lighting data information;
      Derive from BaseCommon_c some fundamental funktionality for all base data
      Derive from SchedulerTask_c to register in Scheduler_c for timeEvent trigger
      Derive from CANCustomer to register FilterBox'es in CanIo_c to receive CAN messages
      Derive from SINGLETON to create a Singleton which manages one global accessible singleton
      per IsoAgLib instance (if only one IsoAgLib instance is defined in application config, no overhead is produced).
    */
  class iTracLight_c : private __IsoAgLib::TracLight_c {
  public:

  /** @param apc_ident pointer to the variable of the responsible member instance. If NULL the module cannot send requests!
      @param at_identMode set mode to either IsoAgLib::IdentModeImplement or IsoAgLib::IdentModeTractor
      @return true -> configuration was successfull
    */
  bool config ( iIdentItem_c* apc_ident, IsoAgLib::IdentMode_t at_identMode = IsoAgLib::IdentModeImplement, uint16_t aui16_suppressMask = 0 )
  { return TracLight_c::config_base ( apc_ident, at_identMode, aui16_suppressMask ); }


    /** set a lighting command in tractor mode or set a response on a lighting command in implement mode
        @param t_command command to set
        @param t_val command value
      */
    void setCommand(const IsoAgLib::IsoCommandFlag_t t_command, const IsoAgLib::IsoActiveFlag_t t_val)
    {TracLight_c::setCommand(t_command, t_val); }

    /** get the number of responses from implements to a command from the tractor
        @return number of responding implements to a command
      */
    int getCount() const {return TracLight_c::getCount();}

    /** get the status of a light of a special implement
        possible errors:
          * iLibErr_c::Range index exceeds map size
        @param ai_index index of implement
        @param at_command which light
        @return status of the light of the implement
      */
    IsoAgLib::IsoActiveFlag_t getByIndex(const unsigned int ai_index, const IsoAgLib::IsoCommandFlag_t at_command)
    {return TracLight_c::getByIndex(ai_index, at_command);}

    /** get the status of a light of a special implement
        possible errors:
          * iLibErr_c::Range the implement with sa has not responded to command from the tractor
        @param sa         source address of implement
        @param t_command  which light
        @return           status of the light of the implement
      */
    IsoAgLib::IsoActiveFlag_t getBySa(const uint8_t sa, const IsoAgLib::IsoCommandFlag_t t_command)
    {return TracLight_c::getBySa(sa, t_command);}

    /** get command which the tractor send
        @param t_command  command from the tractor
        @return           value of the command which the tractor send
      */
    IsoAgLib::IsoActiveFlag_t getCommand(const IsoAgLib::IsoCommandFlag_t t_command) const
    {return TracLight_c::getCommand(t_command);}

    /** find out if a particular implement has responded to a command from the tractor
        @param sa   source address of the sought implement
        @return     has responded to a command (true), else (false)
      */
    bool find(const uint8_t sa) const {return TracLight_c::find(sa);}

  private:
#if ( PRT_INSTANCE_CNT == 1 )
    friend iTracLight_c& getITracLightInstance();
#endif
    friend iTracLight_c& getITracLightInstance( unsigned instance );

  };

#if ( PRT_INSTANCE_CNT == 1 )
  inline iTracLight_c& getITracLightInstance()
  { return static_cast<iTracLight_c&>(__IsoAgLib::getTracLightInstance( 0 )); }
#endif
  inline iTracLight_c& getITracLightInstance( unsigned instance )
  { return static_cast<iTracLight_c&>(__IsoAgLib::getTracLightInstance( instance )); }

}
#endif
