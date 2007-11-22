/***************************************************************************
              sensor.h - definition of Hardware Abstraction
                         Layer for sensor functions for Dj Hardware
                 -------------------
    begin    : 29 Jun 2006
    copyright: (C) 2006 Joel T. Morton (DICKEY-john Corp.)
    email    : jmorton@dickey-john:com
    type     : Header
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
 * Copyright (C) 1999 - 2004 Dipl.-Inform. Achim Spangler                  *
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

/* ************************************************************ */
/** \file supplementary_driver/hal/Dj1/sensor/sensor.h
 * The header <i>\<target\>/\<device\>/\<device\>.h</i> performs a name
   mapping between platform specific BIOS / OS function names
   and the function names, the IsoAgLib uses for hardware access.
   In this header only the groups for error codes, global system
   functions and CAN must be adopted to a new platform.
   If a simple name mapping is not possible for a specific
   function, the module targetExtensions can be used to implement
   the needed activity. The implementation of the DjBios version
   can be used to derive the meaning of the specific function.
*/
/* ************************************************************ */

#ifndef _HAL_DJ1_SENSOR_H_
#define _HAL_DJ1_SENSOR_H_

#include <IsoAgLib/hal/Dj1/config.h>
#include <IsoAgLib/hal/Dj1/typedef.h>
#include <IsoAgLib/hal/Dj1/errcodes.h>
//#include "sensor_target_extensions.h"

/* ******************************************************** */
/**
 * \name Basic BIOS limit constants
 */
#define ANALOG_INPUT_MIN  0
// only uncomment following line if  ANALOG_INPUT_MIN > 0
//#define ANALOG_INPUT_MIN_GREATER_ZERO
#define ANALOG_INPUT_MAX  15

#define DIGITAL_INPUT_MIN 0
// only uncomment following line if  DIGITAL_INPUT_MIN > 0
//#define DIGITAL_INPUT_MIN_GREATER_ZERO
#define DIGITAL_INPUT_MAX 17

#define COUNTER_INPUT_MIN 0
// only uncomment following line if  COUNTER_INPUT_MIN > 0
//#define COUNTER_INPUT_MIN_GREATER_ZERO
#define COUNTER_INPUT_MAX 17


namespace __HAL
{
  extern "C"
  {
    /** include the BIOS specific header into __HAL */
    #include <commercial_BIOS/bios_Dj1/DjBiosMVT.h>
  }
}

/**
   namespace with layer of inline (cost NO overhead -> compiler replaces
   inline function with call to orig BIOS function)
   functions between all IsoAgLib calls for BIOS and the corresponding BIOS functions
   --> simply replace the call to the corresponding BIOS function in this header
       for adaption to new platform
 */
namespace HAL
{
  /* ********************************* */
  /** \name Sensor_c Input BIOS functions */
/*@{*/
  #define DIGIN                  0   /* = 0; digital inputg*/
  #define RISING_EDGE            1   /* = 1; interrupt on rising edge*/
  #define FALLING_EDGE           2   /* = 2; interrupt on falling edge*/
  #define BOTH_EDGE              3   /* = 3; interrupt on both edges*/

  #define HIGH_ACTIV             1   /* = 1; input for aktiv high signals */
  #define LOW_ACTIV              0   /* = 0; input for aktiv low signals */


  /**
    initialize one of the [0..15] analog input channels to VOLTAGE input
      @param bNumber number of the analog input channel
      @param bitPullDownResistor set to TRUE to add an additional pull down resistor
      @return error state (HAL_NO_ERR == o.k.)
  */
  inline int16_t init_analoginVolt ( uint8_t bNumber, bool bitPullDownResistor = false )
  {
    /* Selectable Pull down resistors are not supported */
    return ( (__HAL::DjBios_AnalogInit(bNumber) == __HAL::BIOS_ANALOG_NO_ERR) ? HAL_NO_ERR : HAL_RANGE_ERR );
//    return ( HAL_NO_ERR );     /* TBD -- not yet supported */
  };


  /**
    initialize one of the [0..7] analog input channels to CURRENT input
      @param bNumber number of the analog input channel
      @return error state (HAL_NO_ERR == o.k.)
  */
  inline int16_t  init_analoginCurrent ( uint8_t bNumber )
  {
    return HAL_CONFIG_ERR;      /* Not Supported */
  };


  /**
    initialize one of the [0..0] digital input channels
      @param ab_channel number of the digital input channel
      @param bMode input mode {DIGIN, RISING_EDGE, FALLING_EDGE, BOTH_EDGE}
      @param bAktivhighlow {HIGH_ACTIV, LOW_ACTIV}
      @param pfFunctionName adress of function which is called on input events (NULL -> none)
      @return error state (HAL_NO_ERR == o.k.)
  */
  inline int16_t init_digin ( uint8_t ab_channel, uint8_t bMode,
                              uint8_t bAktivhighlow, void (*pfFunctionName)() )
  {
    __HAL::enum_DigMode eMode;

    if ( bMode == RISING_EDGE )
    {
      eMode = __HAL::BIOS_DIG_INT_RISING;
    } /* end if() */
    else if ( bMode == FALLING_EDGE )
    {
      eMode = __HAL::BIOS_DIG_INT_FALLING;
    } /* end if() */
    else if ( bMode == BOTH_EDGE )
    {
      eMode = __HAL::BIOS_DIG_INT_BOTH;
    } /* end if() */
    else               // DIGIN
    {
      eMode = __HAL::BIOS_DIG_IO;
    } /* end else() */
    return ( (__HAL::DjBios_DigInit ( ab_channel, eMode,
           (bAktivhighlow == HIGH_ACTIV)? __HAL::BIOS_DIG_HIGH : __HAL::BIOS_DIG_LOW,
      pfFunctionName) == __HAL::BIOS_DIG_NO_ERR) ? HAL_NO_ERR : HAL_CONFIG_ERR );
  }


  /**
    init counter for trigger events on digital input;
    rising edges are counted;
      @param ab_channel input channel to use [0..15]
      @param aui16_timebase timebase to calculate periods, frequency
                         should be at least longer than longest
                         awaited signal period [msec.]
      @param ab_activHigh true -> counter input is configured fo ACTIV_HIGH; else ACTIV_LOW
      @param ab_risingEdge true -> counter triggers on rising edge; else on falling edge
      @return C_NO_ERR if no error occured
  */
  inline int16_t init_counter ( uint8_t ab_channel, uint16_t aui16_timebase,
                                    bool ab_activHigh, bool ab_risingEdge )
  {
    return ( (__HAL::DjBios_CounterInit ( ab_channel, aui16_timebase,
                             ab_activHigh ? __HAL::BIOS_DIG_HIGH : __HAL::BIOS_DIG_LOW,
                             ab_risingEdge? __HAL::BIOS_DIG_HIGH : __HAL::BIOS_DIG_LOW) == __HAL::BIOS_DIG_NO_ERR) ? HAL_NO_ERR : HAL_CONFIG_ERR );
  };


  /**
    get counter value of an digital counter input
      @param ab_channel channel of counter [0..15]
      @return counter events since init or last reset
  */
  inline uint32_t getCounter ( uint8_t ab_channel )
  {
    return ( __HAL::DjBios_CounterGetValue(ab_channel) );
  };


  /**
    reset the given counter
      @param ab_channel channel of counter [0..15]
      @return C_NO_ERR ; C_RANGE if counter for ab_channel isn�t configured properly
  */
  inline int16_t resetCounter ( uint8_t ab_channel )
  {
    return ( (__HAL::DjBios_CounterReset(ab_channel) == __HAL::BIOS_DIG_NO_ERR) ? HAL_NO_ERR : HAL_CONFIG_ERR );
  };


  /**
    get period of counter channel
      @param ab_channel channel of counter [0..15]
      @return time between last two signals or 0xFFFF if time is longer than
            initially given timebase
  */
  inline uint16_t getCounterPeriod ( uint8_t ab_channel )
  {
    return ( __HAL::DjBios_CounterGetPeriod(ab_channel) );
  };


  /**
    get frequency of counter channel
      @param ab_channel channel of counter [0..15]
      @return frequency calculated from time between last two signals
            or 0 if time is longer than initially given timebase
  */
  inline uint16_t getCounterFrequency ( uint8_t ab_channel )
  {
    return ( __HAL::DjBios_CounterGetFreq(ab_channel) );
  };


  /**
    get time since last signal
      @param ab_channel channel of counter
      @return time since last signal [msec.]
  */
  inline uint32_t getCounterLastSignalAge(uint8_t ab_channel)
  {
    return ( __HAL::DjBios_CounterGetAge(ab_channel) );
  };

  /**
    set fast ADC mode ON or OFF
      @param bMode set fast ADC to ON or OFF
  */
  inline void setFastAnalogin ( bool bMode )
  {
    return;  /* Not supported */
  };


  /**
    get the measured voltage value of a channel in [mV]
      @param ab_channel measured channel
      @return voltage [0..18000] [mV] or HAL_RANGE_ERR on wrong input channel number
  */
  inline int16_t  getAdcVoltage ( uint8_t ab_channel )
  {
    int16_t Value;

    Value = __HAL::DjBios_AnalogGetVolts ( ab_channel );
    return ( Value < 0 ? HAL_RANGE_ERR : Value );
//    return ( 0 );                               /* TBD - Not yet supported */
  };


  /**
    get the MEDIUM of measured voltage value of a channel in [mV]
      @param ab_channel measured channel
      @return voltage [0..18000] [mV] or HAL_RANGE_ERR on wrong input channel number
  */
  inline int16_t  getAdcMeanVoltage ( uint8_t ab_channel )
  {
    int16_t Value;

    Value = __HAL::DjBios_AnalogGetVoltsFilter ( ab_channel );
    return ( Value < 0 ? HAL_RANGE_ERR : Value );
//    return ( 0 );                      /* TBD - Not yet supported (c2c) 1ms scan, 5ms Avg */
  };


  /**
    get the measured current value of a channel in [uA]
    @param ab_channel measured channel
    @return current [4000..20000] [uA] or HAL_RANGE_ERR on wrong input channel number
  */
  inline int16_t getAdcCurrent ( uint8_t ab_channel )
  {
    return HAL_RANGE_ERR;  /* Not supported */
  };


  /**
    get the MEDIUM of measured current value of a channel in [uA]
    @param ab_channel measured channel
    @return current [4000..20000] [uA] or HAL_RANGE_ERR on wrong input channel number
  */
  inline int16_t  getAdcMeanCurrent ( uint8_t ab_channel )
  {
    return HAL_RANGE_ERR;   /* Not supported */
  };


  /**
    get the diagnose ADC value from specified DIGITAL INPUT channel
    @param ab_channel channel number [0..15]
    @return ADC diagnose voltage [ or HAL_RANGE_ERR on wrong input channel number
  */
  inline int16_t  getDiginDiagnoseAdc ( uint8_t ab_channel )
  {
    return HAL_RANGE_ERR;   /* Not supported */
  };


  /**
    get the temperature
    @return temperature in degree [-40..85]
  */
  inline int16_t  getAdcTemp ( void )
  {
    return ( 0 );
  };



  /**
    deliver frequency of digital interrupt channel
      @param ab_channelNumber input channel number [DIN1..DIN16]
      @param b_useVirtual (default false) use virtual calculated
             value, if last trigger is lasted longer than last period
             -> virt_val uses time from last trigger to actual time
      @return frequency of triggered events [mHz] or BIOS_WARN on too less impulses
  */
  inline uint16_t getDiginFreq ( uint8_t ab_channelNumber, bool b_useVirtual = false )
  {
    /* Frequency Estimation on inputs configured for Digital is not supported.
       Use Counter configuration.  Channel may be configured for counter and
       digital at the same time.  This does not seem to be called from IsoAgLib */
    return ( 0 );  /* Not supported */
  };




  /**
    deliver state of digital input based on Activ-High/Low setting
    (evalutation of sensor signals independent from switching type)
    @param ab_channelNumber input channel number [DIN1..DIN16]
    @return ON, OFF or HAL_RANGE_ERR
  */
  inline int16_t getDiginOnoff ( uint8_t ab_channelNumber )
  {
    __HAL::enum_DigActive Value = __HAL::DjBios_DigGetState ( ab_channelNumber );
    if ( Value == __HAL::BIOS_DIG_ACTIVE )
    {
      return ( ON );
    } /* end if() */
    else if ( Value == __HAL::BIOS_DIG_INACTIVE )
    {
      return ( OFF );
    } /* end if() */
    else /* if ( Value == BIOS_DIG_BAD_CHAN ) */
    {
      return ( HAL_RANGE_ERR );
    } /* end if() */
  };


  /**
    deliver debounced state of digital input based on Activ-High/Low setting
    (evalutation of sensor signals independent from switching type)
      @param ab_channelNumber input channel number [DIN1..DIN16]
      @return ON, OFF or HAL_RANGE_ERR
  */
  inline int16_t getDiginOnoffStatic ( uint8_t ab_channelNumber )
  {
    __HAL::enum_DigActive Value = __HAL::DjBios_DigGetStateDebounce ( ab_channelNumber );
    if ( Value == __HAL::BIOS_DIG_ACTIVE )
    {
      return ( ON );
    } /* end if() */
    else if ( Value == __HAL::BIOS_DIG_INACTIVE )
    {
      return ( OFF );
    } /* end if() */
    else /* if ( Value == BIOS_DIG_BAD_CHAN ) */
    {
      return ( HAL_RANGE_ERR );
    } /* end if() */
  };

  /*@}*/
}
#endif