/*
  config.h: system dependent configs, defines and includes

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
#ifndef _HAL_PC_CONFIG_H_
#define _HAL_PC_CONFIG_H_


#define SYSTEM_PC
#define HAL_USE_SPECIFIC_FILTERS


#define HAL_CAN_BITRATE_LIST {10, 20, 40, 50, 100, 125, 250, 500, 1000}
#define HAL_CAN_BITRATE_CNT 9

/// define list of allowed speed settings
#define HAL_RS232_BAUDRATE_LIST {75, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}
#define HAL_RS232_BITRATE_CNT 10


// IsoAgLib counting for BUS-NR and MsgObj starts both in C-Style with 0
// -> all needed offsets shall be added at the lowest possible layer
//    ( i.e. direct in the BIOS/OS call)
// NOTE: For PC (CAN-Server) we have basically unlimited channels,
//       hence the max. BUS number is set to some quite high value of 31.
//       Should be really enough for everybody - just like 640kB of RAM on the PC ;-)
#define HAL_CAN_MAX_BUS_NR 31

// Intel x86 platforms (Windows PCs) are always little endian
#if defined( WIN32 )
#  define OPTIMIZE_NUMBER_CONVERSIONS_FOR_LITTLE_ENDIAN
#  define FLOAT_WORD_ORDER WORD_LO_HI
#elif defined( __GNUC__ )

#  if (!defined( OPTIMIZE_NUMBER_CONVERSIONS_FOR_BIG_ENDIAN ) && !defined( OPTIMIZE_NUMBER_CONVERSIONS_FOR_LITTLE_ENDIAN ) )
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#      define OPTIMIZE_NUMBER_CONVERSIONS_FOR_LITTLE_ENDIAN
#    endif
#    if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#      define OPTIMIZE_NUMBER_CONVERSIONS_FOR_BIG_ENDIAN
#    endif
#  endif

#  if (!defined( FLOAT_WORD_ORDER ) )
#    if defined( OPTIMIZE_NUMBER_CONVERSIONS_FOR_LITTLE_ENDIAN )
#      define FLOAT_WORD_ORDER WORD_LO_HI
#    elif defined( OPTIMIZE_NUMBER_CONVERSIONS_FOR_BIG_ENDIAN )
#      define FLOAT_WORD_ORDER BYTE_HI_LO
#    endif
#  endif

#endif

#if defined( WIN32 )
#define NOMINMAX
#endif

#define HAL_SIZEOF_INT 4

#define HUGE_MEM
#define NEAR_MEM
#define USE_NEAR_MEM


#define MAX_EEPROM_SEGMENT_SIZE 40

/** define max number of write try-cycle to EEPROM
    ( one cycle: write value, re-read, compare )
  */
#define MAX_EEPROM_WRITE_TRY_CYCLE_CNT 5

#ifndef CONFIG_HAL_PC_RTE_DEFAULT_SERVER
  #define CONFIG_HAL_PC_RTE_DEFAULT_SERVER "rte4"
#endif

/* Initialisierung Watchdog 0 */
#define WD_MAX_TIME      0//200        /* 128 ms                    */
#define WD_MIN_TIME      0      /* 0 ms                      */
#define UD_MAX           233    /* 16.7 V                    */
#define UD_MIN           100    /* 7.2 V                    */
#define CONFIG_RELAIS    255    /* Relais wird bei allen Fehlern abgeschaltet */
#define  CONFIG_RESET    0x10   /* (b 0001 0000) Reset bei WD Verzug      */


#endif
