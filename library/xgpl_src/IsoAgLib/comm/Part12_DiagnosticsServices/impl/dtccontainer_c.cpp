/*
  dtccontainer.cpp - Stores and manages array of DTC elements

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

#include "dtccontainer_c.h"

namespace __IsoAgLib {

uint16_t DtcContainer_c::getDTCIndex(uint32_t SPN, IsoAgLib::FailureModeIndicator_en FMI) const
{
  uint16_t counter = 0;

  // search for DTC
  for (;counter < scui16_sizeDTCList ;++counter) // loop_all_DTCs
  {
    if ((marr_dtc[counter].ui32_spn == SPN)
      && (marr_dtc[counter].en_fmi == FMI))
      break;
  }
  return counter;
}

uint16_t DtcContainer_c::getFreeDTCIndex() const
{
  uint16_t counter = 0;

  // search for DTC
  for (;counter < scui16_sizeDTCList ;++counter) // loop_all_DTCs
  {
    if (marr_dtc[counter].ui32_spn == IsoAgLib::iDtc_s::spiNone)
      break;
  }
  return counter;
}

uint16_t DtcContainer_c::getNumberOfDtc(bool ab_searchForActiveDtc) const
{
  uint16_t ui16_countActiveDtc = 0;

  // search for active DTC
  for (uint16_t counter = 0;counter < scui16_sizeDTCList ;++counter) // loop_all_DTCs
  {
    if ((marr_dtc[counter].ui32_spn != IsoAgLib::iDtc_s::spiNone)
      && (marr_dtc[counter].b_active == ab_searchForActiveDtc))
      ++ui16_countActiveDtc;
  }
  return ui16_countActiveDtc;
}

void
DtcContainer_c::dtcClearPrevious()
{
  for (uint16_t counter = 0;counter < scui16_sizeDTCList ;++counter) // all_DTCs_in_array
  {
    IsoAgLib::iDtc_s& dtc = marr_dtc[counter];
    if (dtc.ui32_spn != IsoAgLib::iDtc_s::spiNone)
    { // valid one found
      if (!dtc.b_active)
      { // inactive == previously active
        // "remove it from the list".
        dtc.ui32_spn = IsoAgLib::iDtc_s::spiNone;
      }
      // else: active one, don't touch
    }
    // else: empty placeholder.
  }
}

} // end of namespace __IsoAgLib
