/*
  analogi_c.cpp:
    implementation file for AnalogI_c, an object for analog input

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

#include "analogi_c.h"
#include <IsoAgLib/util/iassert.h>
#include <supplementary_driver/hal/hal_inputs.h>


namespace __IsoAgLib {

AnalogI_c::AnalogI_c(uint8_t ab_channel, IsoAgLib::iInput_c::analogType_t ren_analogType, bool ab_useMean, bool ab_fastAdc )
  : InputBase_c(ab_channel, IsoAgLib::iInput_c::analog)
{
  if ( ab_channel != 0xFF )
    init( ab_channel, ren_analogType, ab_useMean, ab_fastAdc );
}


void
AnalogI_c::init(uint8_t ab_channel, IsoAgLib::iInput_c::analogType_t ren_analogType, bool ab_useMean, bool ab_fastAdc)
{
  InputBase_c::init(ab_channel, IsoAgLib::iInput_c::analog);

  en_analogType = ren_analogType;
  b_useMean = ab_useMean;
  b_fastAdc = ab_fastAdc;

  int16_t iResult = ( ren_analogType == IsoAgLib::iInput_c::voltage )
                 ?HAL::init_analoginVolt(channelNr()):HAL::init_analoginCurrent(channelNr());
  switch (iResult)
  {
    case HAL_NO_ERR:
      // everything o.k. -> set fast analogin if wanted
      if (ab_fastAdc) HAL::setFastAnalogin(true);
      break;
    case HAL_RANGE_ERR:
    case HAL_CONFIG_ERR:
      isoaglib_assert( !"init error" );
      break;
  }
}


uint16_t
AnalogI_c::val() const
{
  int16_t i16_sensor;
  if (b_useMean)
  { // deliver the mean value
    if ( en_analogType == IsoAgLib::iInput_c::voltage ) i16_sensor =  HAL::getAdcMeanVoltage(channelNr());
    else i16_sensor =  HAL::getAdcMeanCurrent(channelNr());
  }
  else
  { // use normal value
    if ( en_analogType == IsoAgLib::iInput_c::voltage ) i16_sensor =  HAL::getAdcVoltage(channelNr());
    else i16_sensor =  HAL::getAdcCurrent(channelNr());
  }
  isoaglib_assert( i16_sensor != HAL_RANGE_ERR );
  return uint16_t( i16_sensor );
}


void
AnalogI_c::setFastAdc(bool ab_useFast)
{
  b_fastAdc = ab_useFast;

  HAL::setFastAnalogin(ab_useFast);
}


bool
AnalogI_c::active() const
{
  return (val() > 0);
}

AnalogI_c::ain_err_t
AnalogI_c::getState() const
{
  switch ( HAL::getAnalogInDiagState( channelNr() ) )
  {
    case HAL_ANALOGIN_OPEN:       return ain_openErr;
    case HAL_ANALOGIN_SHORTCUT:   return ain_shortcutErr;
    case HAL_ANALOGIN_OVERVOLT:   return ain_overvoltErr;
    case HAL_ANALOGIN_UNDERVOLT:  return ain_undervoltErr;
    default: return noAinErr;
  }
}

} // __IsoAgLib
