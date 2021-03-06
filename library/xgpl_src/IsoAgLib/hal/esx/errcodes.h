/*
  errcodes.h: header for the ESX error codes

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
#ifndef __ESX_ERRCODES_H__
#define __ESX_ERRCODES_H__

namespace HAL {
  extern "C" {
    #include <commercial_BIOS/bios_esx/Xos20err.h>
  }
} // __HAL

/* --- map BIOS error codes to target independent HAL codes --- */
#define HAL_NO_ERR            C_NO_ERR
#define HAL_BUSY_ERR          C_BUSY
#define HAL_CONFIG_ERR        C_CONFIG
#define HAL_RANGE_ERR         C_RANGE
#define HAL_NOACT_ERR         C_NOACT
#define HAL_OVERFLOW_ERR      C_OVERFLOW
#define HAL_UNKNOWN_ERR       C_UNKNOWN_ERR

#endif
