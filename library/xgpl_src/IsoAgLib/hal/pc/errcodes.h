/*
  errcodes.h: header for the PSEUDO BIOS error codes

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
#ifndef __ERRCODES_H__
#define __ERRCODES_H__

#include "typedef.h"

#define HAL_NO_ERR         ((int16_t) 0 )
#define HAL_UNKNOWN_ERR    ((int16_t)-1 )
#define HAL_BUSY_ERR       ((int16_t)-4 )
#define HAL_RANGE_ERR      ((int16_t)-5 )
#define HAL_OVERFLOW_ERR   ((int16_t)-6 )
#define HAL_NOACT_ERR      ((int16_t)-8 )
#define HAL_CONFIG_ERR     ((int16_t)-10)

#endif
