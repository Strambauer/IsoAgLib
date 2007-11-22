#!/bin/sh
# ####################################################################### #
#                         update_makefile.sh  -
#                          Script to create file list, configuration
#                          headers and project files for applications
#                          based on a feature set specifying config file
#                            -------------------
#   begin                 Mon Aug 02 2004
#   copyright            : (C) 2004 - 2006 by Dipl.-Inform. Achim Spangler
#   email                : a.spangler@osb-ag:de
# ####################################################################### #

# ####################################################################### #
#                                                                         #
# This file is part of the "IsoAgLib", an object oriented program library #
# to serve as a software layer between application specific program and   #
# communication protocol details. By providing simple function calls for  #
# jobs like starting a measuring program for a process data value on a    #
# remote ECU, the main program has not to deal with single CAN telegram   #
# formatting. This way communication problems between ECU's which use     #
# this library should be prevented.                                       #
# Everybody and every company is invited to use this library to make a    #
# working plug and play standard out of the printed protocol standard.    #
#                                                                         #
# Copyright (C) 2000 - 2004 Dipl.-Inform. Achim Spangler                  #
#                                                                         #
# The IsoAgLib is free software; you can redistribute it and/or modify it #
# under the terms of the GNU General Public License as published          #
# by the Free Software Foundation; either version 2 of the License, or    #
# (at your option) any later version.                                     #
#                                                                         #
# This library is distributed in the hope that it will be useful, but     #
# WITHOUT ANY WARRANTY; without even the implied warranty of              #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       #
# General Public License for more details.                                #
#                                                                         #
# You should have received a copy of the GNU General Public License       #
# along with IsoAgLib; if not, write to the Free Software Foundation,     #
# Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA           #
#                                                                         #
# As a special exception, if other files instantiate templates or use     #
# macros or inline functions from this file, or you compile this file and #
# link it with other works to produce a work based on this file, this file#
# does not by itself cause the resulting work to be covered by the GNU    #
# General Public License. However the source code for this file must still#
# be made available in accordance with section (3) of the                 #
# GNU General Public License.                                             #
#                                                                         #
# This exception does not invalidate any other reasons why a work based on#
# this file might be covered by the GNU General Public License.           #
#                                                                         #
# Alternative licenses for IsoAgLib may be arranged by contacting         #
# the main author Achim Spangler by a.spangler@osb-ag:de                  #
# ####################################################################### #

# ####################################################################### #
# This file contains several helper functions to create
# project specific Makefiles based on several config variable
# settings. The vars are used to defined the features which are
# needed by the application
# ####################################################################### #
alias echo=$(which echo)
PARAMETER_TARGET_SYSTEM="UseConfigFile"
PARAMETER_CAN_DRIVER="UseConfigFile"
PARAMETER_RS232_DRIVER="UseConfigFile"


USE_EMBED_LIB_DIRECTORY="commercial_BIOS/bios_esx"
USE_EMBED_HEADER_DIRECTORY="commercial_BIOS/bios_esx"
USE_EMBED_LIBS="C756/Xos20l.lib Module/Xma20l.lib"
USE_EMBED_BIOS_SRC="Xos20go.asm Xos20err.c xos20esx.h XOS20EEC.H XOS20EEC.OBJ"
USE_EMBED_ILO="Xos20lcs.ilo"
USE_EMBED_COMPILER_DIR="c:/programme/tasking/c166"

USE_WIN32_LIB_DIRECTORY="C:/Development"
USE_WIN32_HEADER_DIRECTORY="C:/Development"
USE_WIN32_CAN_HW_TYPE="HWTYPE_VIRTUAL"

USE_STLPORT_HEADER_DIRECTORY="C:/STLport/stlport"
# USE_STLPORT_LIBRARY_DIRECTORY=""

# if spec file defines this, the setting is simply overwritten
APP_SEARCH_SRC_CONDITION="*.C *.cc *.c *.cpp *.cxx"
APP_SEARCH_HDR_CONDITION="*.h *.hpp"

APP_PATH_EXLCUDE=""
APP_SRC_EXCLUDE=""

ISOAGLIB_INSTALL_PATH="/usr/local"

USE_SYSTEM_DEFINE=""

GENERATE_FILES_ROOT_DIR=`pwd`

# this function is used to verify and
# correct the several project configuration
# variables
# if one of the following variables isn't set
# the corresponding default values are used
# + USE_LITTLE_ENDIAN_CPU=1 --> most CPU types have little endian number variable representation -> number variable can be converted directly from int variable memory representation into CAN little endian string
# + USE_CAN_DRIVER="simulating"|"sys"|"msq_server"|"socket_server" -> select wanted driver connection for CAN (deprecated: "rte"|"vector_canlib"|"vector_xl_drv_lib"|"sontheim")
# + USE_RS232_DRIVER="simulating"|"sys"|"rte" -> select wanted driver connection for RS232
# + CAN_BUS_CNT ( specify amount of available CAN channels at ECU; default 1 )
# + CAN_INSTANCE_CNT ( specify amount of CAN channels; default 1 )
# + PRT_INSTANCE_CNT ( specify amount of CAN channels to use for protocol; must be <= CAN_INSTANCE_CNT; default 1 )
# + RS232_INSTANCE_CNT ( specify amount of RS232 channels; default 1 )
# + PROJECT ( subdirectory name and executable filename defined by created Makefile )
# + REL_APP_PATH ( specify path to application of this project - error message if not given; use relative path!! )
# + APP_NAME ( optionally select single CC file for the main app - otherwise the whole given path is interpreted as part of this project )
#
# + PRJ_ISO11783=1 ( select ISO 11783, default not even ISO for internal CAN comm only )
# + PRJ_ISO_TERMINAL ( specify if ISO virtual terminal is wanted; default 0; only possible if PRJ_ISO11783=1 -> error message if not )
# + PRJ_BASE ( specify if Base data - main tractor information as PGN or LBS Base message - is wanted; default 0 )
# + PRJ_TRACTOR_GENERAL (only incorporate parts from BASE that provide tractor hitch and RPM information)
# + PRJ_TRACTOR_MOVE (only incorporate parts from BASE that provide tractor distance and speed information)
# + PRJ_TRACTOR_PTO (only incorporate parts from BASE that provide tractor PTO information)
# + PRJ_TRACTOR_LIGHT (only incorporate parts from BASE that provide tractor lighting information)
# + PRJ_TRACTOR_AUX (only incorporate parts from BASE that provide tractor auxiliary valve information)
# + PRJ_TRACTOR_GUIDANCE (only incorporate parts from BASE that provide tractor guidance information)
# + PRJ_TRACTOR_CERTIFICATION (only incorporate parts from BASE that provide tractor certification information)
# + PRJ_TIME_GPS (only incorporate parts from BASE that provide time and GPS information)
# + PRJ_PROCESS ( specify if process data should be used ; default 0 )
#   - PROC_LOCAL ( specify if local process data shall be used; must be activated for all types of local process data; default 0 )
#     o PROC_LOCAL_STD ( specify if full featured local process data shall be used; default 0 )
#     o PROC_LOCAL_SIMPLE_MEASURE ( specify if local process data with restricted measurement feature set shall be used; default 0 )
#     o PROC_LOCAL_SIMPLE_SETPOINT ( specify if local process data with restricted setpoint feature set shall be used; default 0 )
#     o PROC_LOCAL_SIMPLE_MEASURE_SETPOINT ( specify if process daza with maximum restricted feature set shall be used; default 0 )
#   - PROC_REMOTE ( specify if remote process data shall be used; must be activated for all types of remote process data; default 0 )
#     o PROC_REMOTE_STD ( specify if full featured remote process data shall be used; default 0 )
#     o PROC_REMOTE_SIMPLE_MEASURE ( specify if remote process data with restricted measurement feature set shall be used; default 0 )
#     o PROC_REMOTE_SIMPLE_SETPOINT ( specify if remote process data with restricted setpoint feature set shall be used; default 0 )
#     o PROC_REMOTE_SIMPLE_MEASURE_SETPOINT ( specify if process daza with maximum restricted feature set shall be used; default 0 )
#     o PROC_REMOTE_SIMPLE_MEASURE_SETPOINT_COMBINED ( specify if process daza with maximum restricted feature without any distinction between measurement and setpoint set shall be used; default 0 )
# + PRJ_DATASTREAMS ( specify if the input and output filestream should be accessed by IsoAgLib; provides target HAL for filestream handling; default 0 )
# + PRJ_EEPROM ( specify if the EEPROM should be accessed by IsoAgLib; provides important functions for local process data and local ISO items; default 0 )
# + PRJ_ACTOR ( specify if IsoAgLib extension for PWM access should be used; provides several utility and diagnostic functions; default 0 )
# + PRJ_SENSOR_DIGITAL ( specify if IsoAgLib extension for digital sensor data read should be used; provides several utility and diagnostic functions; default 0 )
# + PRJ_SENSOR_COUNTER ( specify if IsoAgLib extension for counting sensor data read should be used; provides several utility and diagnostic functions; default 0 )
# + PRJ_SENSOR_ANALOG ( specify if IsoAgLib extension for analog sensor data read should be used; provides several utility and diagnostic functions; default 0 )
# + PRJ_RS232 ( specify if IsoAgLib extension for C++ stream oriented I/O should be used; default 0 )

check_set_correct_variables()
{
  if [ "A$ISO_AG_LIB_PATH" = "A" ] ; then
  	echo "ERROR! Please specify the path to the root directory of IsoAgLib - i.e. where xgpl_src and IsoAgLibExamples are located"
  	exit 2
  else
    ISO_AG_LIB_INSIDE="../../$ISO_AG_LIB_PATH"
  fi
  # check if ISO_AG_LIB_PATH valid
  if test ! -d $ISO_AG_LIB_PATH ; then
    echo "ERROR! ISO_AG_LIB_PATH is not a directory"
  else
    if test ! -d "$ISO_AG_LIB_PATH/library" ; then
        echo "ERROR! No library found within ISO_AG_LIB ($ISO_AG_LIB_PATH) - maybe your directory is not updated?"
    fi
  fi
	
  if [ "A$PRJ_SEND_DEBUG" = "A" ] ; then
  	PRJ_SEND_DEBUG=0
  fi
  if [ "A$USE_FLOAT_DATA_TYPE" = "A" ] ; then
  	USE_FLOAT_DATA_TYPE=0
  fi
  if [ "A$OPTIMIZE_HEAPSIZE_IN_FAVOR_OF_SPEED" = "A" ] ; then
  	OPTIMIZE_HEAPSIZE_IN_FAVOR_OF_SPEED=0
  fi

  # set default USE_LITTLE_ENDIAN_CPU, so that quick number variable to CAN string conversions are possible
  if [ "A$USE_LITTLE_ENDIAN_CPU" = "A" ] ; then
  	USE_LITTLE_ENDIAN_CPU=1
  fi

  # set default USE_PCAN_LIB, so that quick number variable to CAN string conversions are possible
  if [ "A$USE_PCAN_LIB" = "A" ] ; then
  	USE_PCAN_LIB=0
  fi

  # set default USE_BIG_ENDIAN_CPU, so that quick number variable to CAN string conversions are possible
  if [ "A$USE_BIG_ENDIAN_CPU" = "A" ] ; then
  	USE_BIG_ENDIAN_CPU=0
  fi

	# option to not switch the system relais to ON, on startup
	# (default: set relais to ON on startup)
  if [ "A$PRJ_DO_NOT_START_RELAIS_ON_STARTUP" = "A" ] ; then
  	PRJ_DO_NOT_START_RELAIS_ON_STARTUP=0
  fi


  if [ "A$USE_VT_UNICODE_SUPPORT" = "A" ] ; then
    USE_VT_UNICODE_SUPPORT=0
  fi

  if [ "A$PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL" = "A" ] ; then
    PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
  fi

if [ "A$CAN_BUS_CNT" = "A" ] ; then
  	CAN_BUS_CNT=1
  fi
  if [ "A$CAN_BUS_USED" = "A" ] ; then
  	CAN_BUS_USED=0
  fi
  if [ "A$CAN_INSTANCE_CNT" = "A" ] ; then
  	CAN_INSTANCE_CNT=1
  fi
	if [ $CAN_BUS_CNT -lt $CAN_INSTANCE_CNT ] ; then
		echo "ERROR! The amount of available CAN BUS channels at ECU must be at least as high as wanted of used CAN instances"
		exit 2
	fi
  if [ "A$PRT_INSTANCE_CNT" = "A" ] ; then
  	PRT_INSTANCE_CNT=1
  elif [ $PRT_INSTANCE_CNT -gt $CAN_INSTANCE_CNT ] ; then
  	echo "ERROR! The Amount of protocol instances must be smaller or equal to amount of CAN instances"
    echo "Current false setting: PRT_INSTANCE_CNT=$PRT_INSTANCE_CNT \t CAN_INSTANCE_CNT=$CAN_INSTANCE_CNT"
    exit 2
  elif [ $PRT_INSTANCE_CNT -lt 1 ] ; then
  	echo "ERROR! There must be at least one protocol instance"
    exit 2
  fi
  if [ "A$RS232_INSTANCE_CNT" = "A" ] ; then
  	RS232_INSTANCE_CNT=1
  fi

  if test "A$PROJECT" = "A" -o -z $PROJECT ; then
  	echo "ERROR! Please set the variable PROJECT to the build sub-directory and executable filename"
    exit 2
  fi

  if test "A$REL_APP_PATH" = "A" -o -z "$REL_APP_PATH" ; then
  	echo "ERROR! Please set the variable REL_APP_PATH to the directory of the application sources"
    exit 2
  fi

  if [ "A$APP_NAME" = "A" ] ; then
  	APP_NAME=""
  fi

	if [ "A$PRJ_PROPRIETARY_PGN_INTERFACE" = "A" ] ; then
		PRJ_PROPRIETARY_PGN_INTERFACE=0
	fi

  if [ "A$PRJ_ISO11783" = "A" ] ; then
  	PRJ_ISO11783=0
		PRJ_ISO_TERMINAL=0
  fi
  if [ "A$PRJ_ISO_TERMINAL" = "A" ] ; then
		PRJ_ISO_TERMINAL=0
  fi
  if [ "A$PRJ_ISO_TERMINAL_SERVER" = "A" ] ; then
		PRJ_ISO_TERMINAL_SERVER=0
  fi
  if [ "A$PRJ_ISO_TERMINAL_LAYOUT_MANAGER" = "A" ] ; then
		PRJ_ISO_TERMINAL_LAYOUT_MANAGER=0
  fi

  if test $PRJ_ISO11783 -lt 1 -a $PRJ_ISO_TERMINAL -gt 0 ; then
  	echo "Warning overwrite setting of PRJ_ISO_TERMINAL == $PRJ_ISO_TERMINAL as ISO11783 is not activated"
    echo "Set PRJ_ISO11783 to 1 if you want ISO 11783 virtual terminal"
    PRJ_ISO_TERMINAL=0
  fi

	if [ "A$PRJ_RS232_OVER_CAN" = "A" ] ; then
		PRJ_RS232_OVER_CAN=0
	elif [ $PRJ_RS232_OVER_CAN -gt 0 ] ; then
		PRJ_RS232=1 # force activation of RS232 driver class when this special RS232 HAL is activated
	fi

  if [ "A$PRJ_MULTIPACKET_STREAM_CHUNK" = "A" ] ; then
  	PRJ_MULTIPACKET_STREAM_CHUNK=1
  fi

  if [ "A$PRJ_BASE" = "A" ] ; then
  	PRJ_BASE=0
	elif [ $PRJ_BASE -gt 0 ] ; then
		# activate all base data sub-features, when PRJ_BASE is activated
		PRJ_TRACTOR_GENERAL=1
		PRJ_TRACTOR_MOVE=1
		PRJ_TRACTOR_PTO=1
		PRJ_TIME_GPS=1
		PRJ_TRACTOR_LIGHT=1
		PRJ_TRACTOR_AUX=1
		PRJ_TRACTOR_GUIDANCE=1
		PRJ_TRACTOR_CERTIFICATION=1
	fi

  if [ "A$PRJ_TRACTOR_GENERAL" = "A" ] ; then
  	PRJ_TRACTOR_GENERAL=0
  fi
  if test "A$PRJ_TRACTOR_MOVE" = "A" -a "A$PRJ_TRACTOR_MOVE_SETPOINT" = "A" ; then
  	PRJ_TRACTOR_MOVE=0
		PRJ_TRACTOR_MOVE_SETPOINT=0
	elif test "A$PRJ_TRACTOR_MOVE" != "A" -a "A$PRJ_TRACTOR_MOVE_SETPOINT" = "A" ; then
		PRJ_TRACTOR_MOVE_SETPOINT=0
	elif test "A$PRJ_TRACTOR_MOVE" = "A" -a "A$PRJ_TRACTOR_MOVE_SETPOINT" != "A" ; then
		PRJ_TRACTOR_MOVE=1 # force basic trac move to compile in
  fi

  if test "A$PRJ_TRACTOR_PTO" = "A" -a "A$PRJ_TRACTOR_PTO_SETPOINT" = "A" ; then
  	PRJ_TRACTOR_PTO=0
		PRJ_TRACTOR_PTO_SETPOINT=0
	elif test "A$PRJ_TRACTOR_PTO" != "A" -a "A$PRJ_TRACTOR_PTO_SETPOINT" = "A" ; then
		PRJ_TRACTOR_PTO_SETPOINT=0
	elif test "A$PRJ_TRACTOR_PTO" = "A" -a "A$PRJ_TRACTOR_PTO_SETPOINT" != "A" ; then
		PRJ_TRACTOR_PTO=1 # force basic trac move to compile in
  fi
  if [ "A$PRJ_TRACTOR_LIGHT" = "A" ] ; then
  	PRJ_TRACTOR_LIGHT=0
  fi
  if [ "A$PRJ_TRACTOR_AUX" = "A" ] ; then
  	PRJ_TRACTOR_AUX=0
  fi
  if [ "A$PRJ_TIME_GPS" = "A" ] ; then
  	PRJ_TIME_GPS=0
  fi
  if [ "A$PRJ_TRACTOR_GUIDANCE" = "A" ] ; then
  	PRJ_TRACTOR_GUIDANCE=0
  fi
  if [ "A$PRJ_TRACTOR_CERTIFICATION" = "A" ] ; then
  	PRJ_TRACTOR_CERTIFICATION=0
  fi

	# and also deactivate the features that are only available with the extension directories
	EXT_BASE_SRC="$ISO_AG_LIB_PATH/library/xgpl_src/IsoAgLib/comm/Part7_ApplicationLayer/ext"

	if test ! -d $EXT_BASE_SRC  ; then
		# ISO is not active -> deactivate all ISO only features
		echo "Deactivate all ISO specific features, that are only available for registered users."
		echo "The directory $EXT_BASE_SRC with the extensional modules does not exist."
		echo "Please contact a.spangler@osb-ag.de when you want to register as user so that you can access the extensions area."
		PRJ_TRACTOR_LIGHT=0
		PRJ_TRACTOR_AUX=0
		PRJ_TRACTOR_GUIDANCE=0
		PRJ_TRACTOR_CERTIFICATION=0
	fi


  if [ "A$PRJ_PROCESS" = "A" ] ; then
  	PRJ_PROCESS=0
  fi

  if [ "A$PROC_LOCAL" = "A" ] ; then
  	PROC_LOCAL=0
  else
    if [ "A$PROC_LOCAL_STD" = "A" ] ; then
  	  PROC_LOCAL_STD=0
    fi
    if [ "A$PROC_LOCAL_SIMPLE_MEASURE" = "A" ] ; then
  	  PROC_LOCAL_SIMPLE_MEASURE=0
    fi
    if [ "A$PROC_LOCAL_SIMPLE_SETPOINT" = "A" ] ; then
  	  PROC_LOCAL_SIMPLE_SETPOINT=0
    fi
    if [ "A$PROC_LOCAL_SIMPLE_MEASURE_SETPOINT" = "A" ] ; then
  	  PROC_LOCAL_SIMPLE_MEASURE_SETPOINT=0
    fi
  fi

  if [ "A$PROC_REMOTE" = "A" ] ; then
  	PROC_REMOTE=0
  else
    if [ "A$PROC_REMOTE_STD" = "A" ] ; then
  	  PROC_REMOTE_STD=0
    fi
    if [ "A$PROC_REMOTE_SIMPLE_MEASURE" = "A" ] ; then
  	  PROC_REMOTE_SIMPLE_MEASURE=0
    fi
    if [ "A$PROC_REMOTE_SIMPLE_SETPOINT" = "A" ] ; then
  	  PROC_REMOTE_SIMPLE_SETPOINT=0
    fi
    if [ "A$PROC_REMOTE_SIMPLE_MEASURE_SETPOINT" = "A" ] ; then
  	  PROC_REMOTE_SIMPLE_MEASURE_SETPOINT=0
    fi
    if [ "A$PROC_REMOTE_SIMPLE_MEASURE_SETPOINT_COMBINED" = "A" ] ; then
  	  PROC_REMOTE_SIMPLE_MEASURE_SETPOINT_COMBINED=0
    fi
  fi

  if [ "A$PRJ_EEPROM" = "A" ] ; then
  	PRJ_EEPROM=0
  fi
  if [ "A$PRJ_DATASTREAMS" = "A" ] ; then
  	PRJ_DATASTREAMS=0
  fi
  if [ "A$PRJ_ACTOR" = "A" ] ; then
  	PRJ_ACTOR=0
  fi
  if [ "A$PRJ_SENSOR_DIGITAL" = "A" ] ; then
  	PRJ_SENSOR_DIGITAL=0
  fi
  if [ "A$PRJ_SENSOR_ANALOG" = "A" ] ; then
  	PRJ_SENSOR_ANALOG=0
  fi
  if [ "A$PRJ_SENSOR_COUNTER" = "A" ] ; then
  	PRJ_SENSOR_COUNTER=0
  fi
	if [ $PRJ_SEND_DEBUG -gt 0 ] ; then
		# if DEBUG messages are wanted, then RS232 is needed in any case
		PRJ_RS232=1
	elif [ "A$PRJ_RS232" = "A" ] ; then
  	PRJ_RS232=0
	fi
	if [ "A$PRJ_MULTIPACKET" = "A" ] ; then
  	PRJ_MULTIPACKET=0
  fi

  # preset some conditional vars
	INC_LOC_STD_MEASURE_ELEMENTS=0
  INC_LOC_SIMPLE_MEASURE_ELEMENTS=0
	INC_LOC_STD_SETPOINT_ELEMENTS=0
  INC_LOC_SIMPLE_SETPOINT_ELEMENTS=0
	INC_REM_STD_MEASURE_ELEMENTS=0
  INC_REM_SIMPLE_MEASURE_ELEMENTS=0
	INC_REM_STD_SETPOINT_ELEMENTS=0
  INC_REM_SIMPLE_SETPOINT_ELEMENTS=0
}

# this function uses the "find" cmd
# to derive based on the selected features the
# corresponding file list into filelist_$PROJECT_PURE.txt
create_filelist( )
 {
  COMM_PROC_FEATURES=""

  if [ $PRJ_PROCESS -gt 0 ] ; then
    if [ -n "$COMM_PROC_FEATURES" ] ; then
      COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o "
    fi
    COMM_PROC_FEATURES="$COMM_PROC_FEATURES -name 'processdatachangehandler_c.*' -o -name 'iprocess_c.*' -o -name 'elementddi_s.h' -o -name 'proc_c.h' -o -path '*/Part7_ProcessData/impl/proc*' -o -path '*/Part7_ProcessData/igeneralcommand*' -o -path '*/Part7_ProcessData/impl/generalcommand*' -o -path '*/Part7_ProcessData/*procdata*base_c.h'"

    if [ $PRJ_ISO11783 -gt 0 -a $PROC_LOCAL -gt 0 ] ; then
	# allow DevPropertyHandler
	COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part10_TaskController_Client/i*devproperty*'"
    else
	COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o \( -path '*/Part10_TaskController_Client/i*devproperty*' -a -not -name 'devproperty*' \)"
    fi

    if [ $PROC_LOCAL -gt 0 ] ; then
      COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/impl/*'"

      if [ $PROC_LOCAL_STD -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/Std/*'"
        INC_LOC_STD_MEASURE_ELEMENTS=1
        INC_LOC_STD_SETPOINT_ELEMENTS=1
      fi
      if [ $PROC_LOCAL_SIMPLE_MEASURE -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/SimpleMeasure/*'"
        INC_LOC_STD_SETPOINT_ELEMENTS=1
      fi
      if [ $PROC_LOCAL_SIMPLE_SETPOINT -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/SimpleSetpoint/*'"
        INC_LOC_STD_MEASURE_ELEMENTS=1
        INC_LOC_SIMPLE_SETPOINT_ELEMENTS=1
      fi
      if [ $PROC_LOCAL_SIMPLE_MEASURE_SETPOINT -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/SimpleMeasureSetpoint/*'"
        INC_LOC_SIMPLE_SETPOINT_ELEMENTS=1
      fi

      if [ $INC_LOC_STD_MEASURE_ELEMENTS -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/StdMeasureElements/*'"
      fi
      if [ $INC_LOC_STD_SETPOINT_ELEMENTS -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/StdSetpointElements/*'"
      fi
      if [ $INC_LOC_SIMPLE_SETPOINT_ELEMENTS -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Local/SimpleSetpointElements/*'"
      fi
    fi
    if [ $PROC_REMOTE -gt 0 ] ; then
      COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/impl/*'"

      if [ $PROC_REMOTE_STD -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/Std/*'"
        INC_REM_STD_MEASURE_ELEMENTS=1
        INC_REM_STD_SETPOINT_ELEMENTS=1
      fi
      if [ $PROC_REMOTE_SIMPLE_MEASURE -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/SimpleMeasure/*'"
        INC_REM_SIMPLE_MEASURE_ELEMENTS=1
        INC_REM_STD_SETPOINT_ELEMENTS=1
      fi
      if [ $PROC_REMOTE_SIMPLE_SETPOINT -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/SimpleSetpoint/*'"
        INC_REM_STD_MEASURE_ELEMENTS=1
        INC_REM_SIMPLE_SETPOINT_ELEMENTS=1
      fi
      if test $PROC_REMOTE_SIMPLE_MEASURE_SETPOINT -gt 0 -a $PROC_REMOTE_SIMPLE_MEASURE_SETPOINT_COMBINED -gt 0   ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/SimpleMeasureSetpoint/*'"
        INC_REM_SIMPLE_MEASURE_ELEMENTS=1
        INC_REM_SIMPLE_SETPOINT_ELEMENTS=1
      elif [ $PROC_REMOTE_SIMPLE_MEASURE_SETPOINT -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -name '*procdataremotesimplesetpointsimplemeasure_c.*'"
        INC_REM_SIMPLE_MEASURE_ELEMENTS=1
        INC_REM_SIMPLE_SETPOINT_ELEMENTS=1
      elif [ $PROC_REMOTE_SIMPLE_MEASURE_SETPOINT_COMBINED -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -name '*procdataremotesimplesetpointsimplemeasurecombined_c.*'"
			fi
      if [ $INC_REM_STD_MEASURE_ELEMENTS -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/StdMeasureElements/*'"
      fi
      if [ $INC_REM_SIMPLE_MEASURE_ELEMENTS -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/SimpleMeasureElements/*'"
      fi
      if [ $INC_REM_STD_SETPOINT_ELEMENTS -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/StdSetpointElements/*'"
      fi
      if [ $INC_REM_SIMPLE_SETPOINT_ELEMENTS -gt 0 ] ; then
        COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/Remote/SimpleSetpointElements/*'"
      fi
    fi

    if test $INC_LOC_STD_MEASURE_ELEMENTS -gt 0 -o $INC_REM_STD_MEASURE_ELEMENTS -gt 0 ; then
      COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/StdMeasureElements/*'"
    fi
    if test $INC_LOC_STD_SETPOINT_ELEMENTS -gt 0 -o $INC_REM_STD_SETPOINT_ELEMENTS -gt 0 ; then
      COMM_PROC_FEATURES="$COMM_PROC_FEATURES -o -path '*/Part7_ProcessData/StdSetpointElements/*'"
    fi

  fi

  #USE_TARGET_SYSTEM="pc"
	case "$USE_TARGET_SYSTEM" in
		pc*)
			HAL_PATH="pc"
			;;
		*)
			HAL_PATH=$USE_TARGET_SYSTEM
			;;
	esac

  COMM_FEATURES=" -path '*/IsoAgLib/typedef.h' -o -path '*/hal/"$HAL_PATH"/typedef.h' -o -name 'isoaglib_config.h' -o -path '*/hal/config.h'"
  if [ $PRJ_BASE -gt 0 ] ; then
    if [ $PRJ_ISO11783 -lt 1 ] ; then
      # no trac light
      COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -not -name '*traclight*' -a -not -name '*trac*setpoint*' -a -not -name '*tracaux*' -a -not -name '*tracguidance*' -a -not -name '*traccert*' \)"
    else
# until the setpoint classes for PTO and Move are fully implemented, the setpoint classes are NOT integrated into project files
      COMM_FEATURES="$COMM_FEATURES -o -path '*/Part7_ApplicationLayer/*'"
#      COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -not -name '*trac*setpoint*' \) "
    fi
  fi
  if test $PRJ_TRACTOR_GENERAL -gt 0 -o $PRJ_TRACTOR_MOVE -gt 0 -o $PRJ_TRACTOR_PTO -gt 0 -o $PRJ_TRACTOR_LIGHT -gt 0 -o $PRJ_TRACTOR_AUX -gt 0 -o $PRJ_TIME_GPS -gt 0 -o $PRJ_TRACTOR_GUIDANCE -gt 0 -o $PRJ_TRACTOR_CERTIFICATION -gt 0; then
	  COMM_FEATURES="$COMM_FEATURES -o -name 'ibasetypes.h' -o -name 'basecommon_c*'"
	fi
  if [ $PRJ_TRACTOR_GENERAL -gt 0 ] ; then
    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*tracgeneral_c*' \)"
  fi
  if test $PRJ_TRACTOR_MOVE -gt 0 -a $PRJ_TRACTOR_MOVE_SETPOINT -gt 0 ; then
	    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*tracmove*' \)"
  elif test $PRJ_TRACTOR_MOVE -gt 0 -a $PRJ_TRACTOR_MOVE_SETPOINT -lt 1 ; then
	    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*tracmove_c.*' \)"
  fi
  if test $PRJ_TRACTOR_PTO -gt 0 -a $PRJ_TRACTOR_PTO_SETPOINT -gt 0 ; then
	    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*tracpto*' \)"
  elif test $PRJ_TRACTOR_PTO -gt 0 -a $PRJ_TRACTOR_PTO_SETPOINT -lt 1 ; then
	    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*tracpto_c.*' \)"
  fi
  if test $PRJ_TRACTOR_LIGHT -gt 0 -a $PRJ_ISO11783 -gt 0 ; then
    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*traclight*' \)"
  else
	PRJ_TRACTOR_LIGHT=0
  fi
  if test $PRJ_TRACTOR_AUX -gt 0 -a $PRJ_ISO11783 -gt 0 ; then
		# tracaux is only defined for ISO 11783
    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*tracaux*' \)"
	else
	PRJ_TRACTOR_AUX=0
	fi
	if test $PRJ_TRACTOR_GUIDANCE -gt 0 -a $PRJ_ISO11783 -gt 0 ; then
		# tracguidance is only defined for ISO 11783
    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*tracguidance*' \)"
	else
	PRJ_TRACTOR_GUIDANCE=0
  fi
	if test $PRJ_TRACTOR_CERTIFICATION -gt 0 -a $PRJ_ISO11783 -gt 0 ; then
		# tracguidance is only defined for ISO 11783
    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*traccert*' \)"
	else
	PRJ_TRACTOR_CERTIFICATION=0
  fi
  if [ $PRJ_TIME_GPS -gt 0 ] ; then
    COMM_FEATURES="$COMM_FEATURES -o \( -path '*/Part7_ApplicationLayer/*' -a -name '*timeposgps*' \)"
  fi

	if [ $PRJ_PROPRIETARY_PGN_INTERFACE -gt 0 ] ; then
		COMM_FEATURES="$COMM_FEATURES -o -path '*/ProprietaryCan/*'"
	fi

  if [ $PRJ_ISO_TERMINAL_SERVER -gt 0 ] ; then
    PRJ_MULTIPACKET=1
  fi
  if [ $PRJ_ISO_TERMINAL -gt 0 ] ; then
		if [ $PRJ_ISO_TERMINAL_LAYOUT_MANAGER -gt 0 ] ; then
	    COMM_FEATURES="$COMM_FEATURES -o -path '*/Part6_VirtualTerminal_Client/*'"
		else
	    COMM_FEATURES="$COMM_FEATURES -o -path '*/Part6_VirtualTerminal_Client/i*'"
		fi
    PRJ_MULTIPACKET=1
  fi
	if [ $PRJ_PROPRIETARY_PGN_INTERFACE -gt 0 ] ; then
    PRJ_MULTIPACKET=1
	fi
  if [ $PRJ_DATASTREAMS -lt 1 ] ; then
		if test $PRJ_ISO_TERMINAL -gt 0 -o $PRJ_TIME_GPS -gt 0 ; then
	    COMM_FEATURES="$COMM_FEATURES -o -path '*/driver/datastreams/volatilememory_c.cpp'"
		fi
  fi
  if test $PRJ_MULTIPACKET -gt 0 -o $PROC_LOCAL -gt 0   ; then
  	PRJ_MULTIPACKET=1
  	if [ $PRJ_ISO11783 -gt 0 ] ; then
			COMM_FEATURES="$COMM_FEATURES -o -path '*/Part3_DataLink/i*multi*' -o -path '*/Part3_DataLink/impl/stream_c.*' -o -path '*/Part3_DataLink/istream_c.*' -o -path '*/supplementary_driver/driver/datastreams/streaminput_c.h'  -o -path '*/IsoAgLib/convert.h'"
			if [ $PRJ_MULTIPACKET_STREAM_CHUNK -gt 0 ] ; then
				COMM_FEATURES="$COMM_FEATURES -o -path '*/Part3_DataLink/impl/streamchunk_c.*' -o -path '*/Part3_DataLink/impl/chunk_c.*'"
			else
				COMM_FEATURES="$COMM_FEATURES -o -path '*/Part3_DataLink/impl/streamlinear_c.*'"
			fi
		fi
  fi

	DRIVER_FEATURES=" -path '*/hal/"$HAL_PATH"/can/can*.h'  -o  -path '*/hal/"$HAL_PATH"/can/hal_can*' -o -path '*/hal/can.h' -o -path '*/driver/system*' -o -path '*/hal/"$HAL_PATH"/system*' -o -path '*/hal/system.h' -o -path '*/hal/"$HAL_PATH"/errcodes.h' -o -path '*/hal/"$HAL_PATH"/config.h'"


  echo "CAN driver: $USE_CAN_DRIVER"
	if [ $USE_CAN_DRIVER = "simulating" ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_simulating*'"
		if [ $PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL -gt 0 ] ; then
			echo 'The selected CAN driver "simulating" does NOT provide the enhanced CAN processing.'
			echo 'Thus the project files will be generated without enhanced CAN processing'
			PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
		fi
	elif [ $USE_CAN_DRIVER = "rte" ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_rte*'"
	elif [ $USE_CAN_DRIVER = "msq_server" ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_client_msq*' -o -path '*/hal/"$HAL_PATH"/can/msq_helper*'"
	elif [ $USE_CAN_DRIVER = "socket_server" ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_client_sock*'"
	elif [ $USE_CAN_DRIVER = "sys" ] ; then
		if [ $PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL -gt 0 ] ; then
			echo 'The selected CAN driver "simulating" does NOT provide the enhanced CAN processing.'
			echo 'Thus the project files will be generated without enhanced CAN processing'
			PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
		fi
		PLATFORM=`uname`
		if [ $USE_TARGET_SYSTEM = "pc_linux" ] ; then
			DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_linux_sys*'"
		elif [ $USE_TARGET_SYSTEM = "pc_win32" ] ; then
			DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_w32_sys*'"
		fi
	elif  [ $USE_CAN_DRIVER = "vector_canlib" ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_w32_vector_canlib*'"
	elif  [ $USE_CAN_DRIVER = "vector_xl_drv_lib" ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_w32_vector_xl_drv_lib*'"
	elif  [ $USE_CAN_DRIVER = "sontheim" ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/can/target_extension_can_w32_sontheim_canlpt*'"
	else
		echo 'ERROR! Please set the config variable "USE_CAN_DRIVER" to one of "simulating"|"sys"|"msq_server"|"socket_server" (deprecated: "rte"|"vector_canlib"|"vector_xl_drv_lib"|"sontheim")'
		echo 'Current Setting is $USE_CAN_DRIVER'
		exit 3
	fi

	if [ $PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL -lt 1 ] ; then
    #in NOT enhanced can hal -> we need to integrate the sources for the central CAN FIFO
    DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/generic_utils/can/*'"
	fi

  if [ $PRJ_EEPROM -gt 0 ] ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/driver/eeprom/*' -o -path '*/hal/"$HAL_PATH"/eeprom/*' -o -path '*/hal/eeprom.h' -o -name 'eeprom_adr.h'"
  fi
  if [ $PRJ_DATASTREAMS -gt 0 ] ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/driver/datastreams/*' -o -path '*/hal/"$HAL_PATH"/datastreams/*' -o -path '*/hal/datastreams.h'"
  fi
  if [ $PRJ_ACTOR -gt 0 ] ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/driver/actor*' -o -path '*/hal/"$HAL_PATH"/actor/*' -o -path '*/hal/actor.h'"
  fi
  if [ $PRJ_SENSOR_DIGITAL -gt 0 ] ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -name '*digitali_c.*'"
  fi
  if [ $PRJ_SENSOR_ANALOG -gt 0 ] ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -name '*analogi*'"
  fi
  if [ $PRJ_SENSOR_COUNTER -gt 0 ] ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -name '*counteri*'"
  fi
	if test $PRJ_SENSOR_DIGITAL -gt 0 -o $PRJ_SENSOR_ANALOG -gt 0 -o $PRJ_SENSOR_COUNTER -gt 0 ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/sensor/*' -o -name '*sensorbase_c.*' -o -name '*sensor_c.*' -o -name '*sensori_c.*' -o -path '*/hal/sensor.h'"
	fi
  if [ $PRJ_RS232 -gt 0 ] ; then
    DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/driver/rs232/*' -o -path '*/hal/rs232.h' -o -path '*/hal/"$HAL_PATH"/rs232/rs232.h'"
		if [ $PRJ_RS232_OVER_CAN -gt 0 ] ; then
			DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/virtualDrivers/rs232/*'"
		else
			DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/rs232/rs232/*'"
			echo "RS232 driver: $USE_RS232_DRIVER"
			if [ $USE_RS232_DRIVER = "simulating" ] ; then
				DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/rs232/target_extension_rs232_simulating*'"
			elif [ $USE_RS232_DRIVER = "rte" ] ; then
				DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/rs232/target_extension_rs232_rte*'"
			elif [ $USE_RS232_DRIVER = "sys" ] ; then
			  if [ $USE_TARGET_SYSTEM = "pc_win32" ] ; then
					DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/rs232/target_extension_rs232_w32_sys*'"
				else
					DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/rs232/target_extension_rs232_linux_sys*'"
				fi
	#			PRJ_DEFINES="$PRJ_DEFINES USE_REAL_RS232"
	#			DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/rs232/target_extension_rs232_simulating*'"
			else
				echo 'ERROR! Please set the config variable "USE_RS232_DRIVER" to one of "simulating"|"sys"|"rte"|"vector_canlib"|"vector_xl_drv_lib"|"sontheim"'
				echo 'Current Setting is $USE_RS232_DRIVER'
				exit 3
			fi
		fi
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/hal/"$HAL_PATH"/rs232/rs232_target_extensions.h'"
  fi

	# add the standard driver directory sources for CAN
	if [ $PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL -gt 0 ] ; then
		DRIVER_FEATURES="$DRIVER_FEATURES -o \( -path '*/driver/can/*' -a -not -name 'msgobj*' \)"
	else
		DRIVER_FEATURES="$DRIVER_FEATURES -o -path '*/driver/can/*'"
	fi


  LIB_ROOT="$ISO_AG_LIB_INSIDE/library/xgpl_src"
  SRC_EXT="\( -name '*.c' -o -name '*.cc' -o -name '*.cpp' \)"
  HDR_UTEST_EXT="\( -name '*-test.h' \)"
  HDR_UTEST_MOCK_EXT="\( -name '*-mock.h' \)"
  TESTRUNNER_EXT="\( -name 'testrunner.cpp' \)"


  # go back to directory where config file resides
  mkdir -p $1
	cd $1
	# echo "create filelist with 1 $1 and GENERATE_FILES_ROOT_DIR $GENERATE_FILES_ROOT_DIR"
  # mkdir tmpdir
  mkdir -p $PROJECT
  cd $PROJECT
	FILELIST_LIBRARY_HDR="filelist"'__'"$PROJECT_hdr.library.txt"
	FILELIST_LIBRARY_PURE="filelist"'__'"$PROJECT.library.txt"

	FILELIST_APP_HDR="filelist"'__'"$PROJECT_hdr.app.txt"
	FILELIST_APP_PURE="filelist"'__'"$PROJECT.app.txt"

	FILELIST_COMBINED_HDR="filelist"'__'"$PROJECT_hdr.txt"
	FILELIST_COMBINED_PURE="filelist"'__'"$PROJECT.txt"

	if [ "A$DOXYGEN_EXPORT_DIR" = "A" ] ; then
		FILELIST_DOXYGEN_READY="filelist"'__'"$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER-doc.txt"
	else
		FILELIST_DOXYGEN_READY="$DOXYGEN_EXPORT_DIR/filelist"'__'"$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER-doc.txt"
	fi


  rm -f "$FILELIST_LIBRARY_PURE" "$FILELIST_LIBRARY_HDR"
	rm -f "$FILELIST_APP_PURE" "$FILELIST_APP_HDR"
	rm -f "$FILELIST_COMBINED_PURE" "$FILELIST_COMBINED_HDR"

  touch "$FILELIST_LIBRARY_PURE" "$FILELIST_APP_PURE" "$FILELIST_COMBINED_PURE"
  # find central elements
  if [ $PRJ_ISO11783 -lt 1 ] ; then
	EXCLUDE_FROM_SYSTEM_MGMT="-a -not -path '*/ISO11783/*'" # OBSOLETE? Folder has been deleted.
  else
	EXCLUDE_FROM_SYSTEM_MGMT=""
  fi
  rm -f .exec.tmp

  FIND_TEMP_PATH="-path '*/Scheduler/*' -o -path '*/Part5_NetworkManagement/*' -o -path '*/util/*' -o -path '*/Part3_DataLink/impl/can*' "
  # find wanted process data communication features
  if [ "$COMM_PROC_FEATURES" != "" ] ; then
    FIND_TEMP_PATH="$FIND_TEMP_PATH -o $COMM_PROC_FEATURES"
  fi
  # find wanted other communication features
  if [ "$COMM_FEATURES" != "" ] ; then
    FIND_TEMP_PATH="$FIND_TEMP_PATH -o $COMM_FEATURES"
  fi
  #find optional HW features
  if [ "$DRIVER_FEATURES" != "" ] ; then
    FIND_TEMP_PATH="$FIND_TEMP_PATH -o $DRIVER_FEATURES"
  fi
    
  echo "find $LIB_ROOT -follow $SRC_EXT -a \( $FIND_TEMP_PATH \) $EXCLUDE_FROM_SYSTEM_MGMT -printf '%h/%f\n' >> $FILELIST_LIBRARY_PURE" >> .exec.tmp
  echo "find $LIB_ROOT -follow -name '*.h' -a \( $FIND_TEMP_PATH \) $EXCLUDE_FROM_SYSTEM_MGMT -printf '%h/%f\n' >> $FILELIST_LIBRARY_HDR" >> .exec.tmp
  
  # find application files
	FIRST_LOOP="YES"
	APP_SRC_PART=""
	if [ "A$APP_SRC_FILE" != "A" ] ; then
		APP_SRC_PART="-and \( "
		for itemSrcInclude in $APP_SRC_FILE ; do
			if [ $FIRST_LOOP != "YES" ] ; then
				APP_SRC_PART="$APP_SRC_PART -or"
			else
				FIRST_LOOP="NO"
			fi
			APP_SRC_PART="$APP_SRC_PART -name \"$itemSrcInclude\""
		done
		APP_SRC_PART="$APP_SRC_PART \)"
	fi

	FIRST_LOOP="YES"
	EXCLUDE_PATH_PART=""
	if [ "A" != "A$APP_PATH_EXLCUDE"  ] ; then
		EXCLUDE_PATH_PART="-and -not \( "
		for itemPathExclude in $APP_PATH_EXLCUDE ; do
			if [ $FIRST_LOOP != "YES" ] ; then
				EXCLUDE_PATH_PART="$EXCLUDE_PATH_PART -or"
			else
				FIRST_LOOP="NO"
			fi
			EXCLUDE_PATH_PART="$EXCLUDE_PATH_PART -path \"$itemPathExclude\""
		done
		EXCLUDE_PATH_PART="$EXCLUDE_PATH_PART \)"
	fi

	FIRST_LOOP="YES"
	EXCLUDE_SRC_PART=""
	if [ "A" != "A$APP_SRC_EXCLUDE"  ] ; then
		EXCLUDE_SRC_PART="-and -not \( "
		for itemSrcExclude in $APP_SRC_EXCLUDE ; do
			if [ $FIRST_LOOP != "YES" ] ; then
				EXCLUDE_SRC_PART="$EXCLUDE_SRC_PART -or"
			else
				FIRST_LOOP="NO"
			fi
			EXCLUDE_SRC_PART="$EXCLUDE_SRC_PART -name \"$itemSrcExclude\""
		done
		EXCLUDE_SRC_PART="$EXCLUDE_SRC_PART \)"
	fi


	FIRST_LOOP="YES"
	APP_SEARCH_SRC_TYPE_PART="\( "

	# remove the joker '*' from the file type spec, as this causes only trouble
	APP_SEARCH_SRC_CONDITION=$(echo "$APP_SEARCH_SRC_CONDITION" |sed 's|\*||g')

	for itemSrcType in $APP_SEARCH_SRC_CONDITION ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			APP_SEARCH_SRC_TYPE_PART="$APP_SEARCH_SRC_TYPE_PART -or"
		else
			FIRST_LOOP="NO"
		fi
		APP_SEARCH_SRC_TYPE_PART="$APP_SEARCH_SRC_TYPE_PART -name '*$itemSrcType'"
	done
	APP_SEARCH_SRC_TYPE_PART="$APP_SEARCH_SRC_TYPE_PART \)"


	FIRST_LOOP="YES"
	APP_SEARCH_HDR_TYPE_PART="\( "
	for itemHdrType in $APP_SEARCH_HDR_CONDITION ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			APP_SEARCH_HDR_TYPE_PART="$APP_SEARCH_HDR_TYPE_PART -or"
		else
			FIRST_LOOP="NO"
		fi
		APP_SEARCH_HDR_TYPE_PART="$APP_SEARCH_HDR_TYPE_PART -name \"$itemHdrType\""
	done
	APP_SEARCH_HDR_TYPE_PART="$APP_SEARCH_HDR_TYPE_PART \)"

	for EACH_REL_APP_PATH in $REL_APP_PATH ; do
		echo "find $ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH/ -follow $APP_SEARCH_SRC_TYPE_PART $APP_SRC_PART $EXCLUDE_PATH_PART $EXCLUDE_SRC_PART -printf '%h/%f\n' >> $FILELIST_APP_PURE" >> .exec.tmp
		echo "find $ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH/ -follow $APP_SEARCH_HDR_TYPE_PART $APP_SRC_PART $EXCLUDE_PATH_PART $EXCLUDE_SRC_PART -printf '%h/%f\n' >> $FILELIST_APP_HDR" >> .exec.tmp
	done

  sh .exec.tmp

	cat $FILELIST_LIBRARY_PURE $FILELIST_APP_PURE > $FILELIST_COMBINED_PURE
	cat $FILELIST_LIBRARY_HDR $FILELIST_APP_HDR > $FILELIST_COMBINED_HDR
  rm -f .exec.tmp

	# create list with suitable block definition for doxygen import
	# start main block for all files for project
	#echo "/**" > $FILELIST_DOXYGEN_READY
	#echo "* \section FileLists$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of Files for $PROJECT ." >> $FILELIST_DOXYGEN_READY
	#echo "*/" >> $FILELIST_DOXYGEN_READY
	#echo "/*@{*/" >> $FILELIST_DOXYGEN_READY
	echo -e "\n\n \section FileLists$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of Files for $PROJECT with CAN Driver $USE_CAN_DRIVER and RS232 Driver $USE_RS232_DRIVER" > $FILELIST_DOXYGEN_READY

	# write block of source files
	#echo "/**" >> $FILELIST_DOXYGEN_READY
	#echo "* \section SrcList$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of Sourcefiles for $PROJECT ." >> $FILELIST_DOXYGEN_READY
	#echo "*/" >> $FILELIST_DOXYGEN_READY
	#echo "/*@{*/" >> $FILELIST_DOXYGEN_READY
	echo -e "\n\n \section SrcList$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of Sourcefiles for $PROJECT with CAN Driver $USE_CAN_DRIVER and RS232 Driver $USE_RS232_DRIVER" >> $FILELIST_DOXYGEN_READY
	echo "\code" >> $FILELIST_DOXYGEN_READY
  cat $FILELIST_COMBINED_PURE >> $FILELIST_DOXYGEN_READY
	echo "\endcode" >> $FILELIST_DOXYGEN_READY
	#echo "/*@}*/" >> $FILELIST_DOXYGEN_READY

	echo "" >> $FILELIST_DOXYGEN_READY

	# write block of header files
	#echo "/**" >> $FILELIST_DOXYGEN_READY
	#echo "* \section HdrList$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of Sourcefiles for $PROJECT ." >> $FILELIST_DOXYGEN_READY
	#echo "*/" >> $FILELIST_DOXYGEN_READY
	#echo "/*@{*/" >> $FILELIST_DOXYGEN_READY
	echo -e "\n\n \section HdrList$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of Headers for $PROJECT with CAN Driver $USE_CAN_DRIVER and RS232 Driver $USE_RS232_DRIVER" >> $FILELIST_DOXYGEN_READY
	echo "\code" >> $FILELIST_DOXYGEN_READY
	cat $FILELIST_COMBINED_HDR >> $FILELIST_DOXYGEN_READY
	echo "\endcode" >> $FILELIST_DOXYGEN_READY
	#echo "/*@}*/" >> $FILELIST_DOXYGEN_READY

	# write end of main block of all project files
	#echo "/*@}*/" >> $FILELIST_DOXYGEN_READY

	cat $FILELIST_COMBINED_HDR >> $FILELIST_COMBINED_PURE
	rm -f $FILELIST_COMBINED_HDR


  # go back to directory where config file resides
	cd $1

  return
}

# this function uses the "find" cmd
# to derive based on the selected features the
# corresponding file list into filelist_$FILELIST_UTEST_PURE.txt
# and filelist_$FILELIST_UTEST_MOCK_PURE.txt
create_utest_filelist()
{
	FILELIST_UTEST_PURE="filelist"'__'"$PROJECT.utest.txt"
	FILELIST_UTEST_MOCK_PURE="filelist"'__'"$PROJECT.utest.mock.txt"
	FILELIST_UTEST_MODSUT_PURE="filelist"'__'"$PROJECT.utest.modsut.txt"
	FILELIST_UTEST_RUNNER_PURE="filelist"'__'"$PROJECT.utest.runner.txt"

	# go to project directory
	cd $PROJECT

	# create new files containing the file lists
	rm -f "$FILELIST_UTEST_PURE" "$FILELIST_UTEST_MOCK_PURE" "$FILELIST_UTEST_MODSUT_PURE" "$FILELIST_UTEST_RUNNER_PURE"
	touch "$FILELIST_UTEST_PURE" "$FILELIST_UTEST_MOCK_PURE" "$FILELIST_UTEST_MODSUT_PURE" "$FILELIST_UTEST_RUNNER_PURE"

	# find unit test files (*-test.h)
	rm -f .exec.tmp
	echo "find ../../../ $HDR_UTEST_EXT -printf '%h/%f\n' >> $FILELIST_UTEST_PURE" > .exec.tmp
	sh .exec.tmp

	# find mock object files (*-mock.h)
	rm -f .exec.tmp
	echo "find ../../../ $HDR_UTEST_MOCK_EXT -printf '%h/%f\n' >> $FILELIST_UTEST_MOCK_PURE" > .exec.tmp
	sh .exec.tmp

	# determine modified software under test (MOD-SUT) files
cat $FILELIST_UTEST_PURE | sed -e 's!\(.*\)/utest/\(.*\)-test\.h!\1/\2_c.h!' >> $FILELIST_UTEST_MODSUT_PURE

	# find the testrunner (testrunner.cpp)
	rm -f .exec.tmp
	echo "find ../../../ $TESTRUNNER_EXT -printf '%h/%f\n' >> $FILELIST_UTEST_RUNNER_PURE" > .exec.tmp
	sh .exec.tmp

	rm -f .exec.tmp
}

# function to create the project specific autogenerated
# config header
# autogen_project_config.h
create_autogen_project_config()
{
  # go to project dir - below config dir
	cd $1/$PROJECT
	PLATFORM=`uname`
	if [ $PLATFORM = "Linux" ] ; then
		ENDLINE="\n"
	else
		ENDLINE="\r\n"
	fi

    for FIRST_REL_APP_PATH in $REL_APP_PATH ; do
	# CONFIG_NAME=$ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/.config_$PROJECT.h
	CONFIG_NAME=$ISO_AG_LIB_INSIDE/$FIRST_REL_APP_PATH/config_$PROJECT.h
			VERSION_FILE_NAME=$ISO_AG_LIB_INSIDE/$FIRST_REL_APP_PATH/version.h
			if [ ! -f $VERSION_FILE_NAME ] ; then
				echo    "#ifndef POOL_VERSION"            > $VERSION_FILE_NAME
				echo -e "\t#define POOL_VERSION 1.0"     >> $VERSION_FILE_NAME
				echo    "#endif"                         >> $VERSION_FILE_NAME
				echo    "#ifndef FIRMWARE_VERSION"       >> $VERSION_FILE_NAME
				echo -e "\t#define FIRMWARE_VERSION 1.0" >> $VERSION_FILE_NAME
				echo    "#endif"                         >> $VERSION_FILE_NAME
			fi
	break;
    done

	if [ "A$DOXYGEN_EXPORT_DIR" = "A" ] ; then
		CONFIG_HEADER_DOXYGEN_READY="config_header"'__'"$PROJECT-doc.txt"
	else
		CONFIG_HEADER_DOXYGEN_READY="$DOXYGEN_EXPORT_DIR/config_header"'__'"$PROJECT-doc.txt"
	fi

  # first backup individual settings after line
	# START_INDIVIDUAL_PROJECT_CONFIG
	if [ -f $CONFIG_NAME ] ; then
		grep -A1000 "// START_INDIVIDUAL_PROJECT_CONFIG"  $CONFIG_NAME > $CONFIG_NAME.bak
	else
		touch $CONFIG_NAME.bak
	fi
	rm -f $CONFIG_NAME
	# write INST counts
	CONFIG_HEADER_FILENAME=`basename $CONFIG_NAME`
	echo "// File: $CONFIG_HEADER_FILENAME" > $CONFIG_NAME
	echo "// IMPORTANT: Never change the first block of this header manually!!!" >> $CONFIG_NAME
	echo "//            All manual changes are overwritten by the next call of \"update_makefile.sh $CONF_FILE\" " >> $CONFIG_NAME
	echo "//            Perform changes direct in the feature and project setup file $CONF_FILE"  >> $CONFIG_NAME
	echo "//  ALLOWED ADAPTATION: Move the to be adapted defines from the middle block to the end after" >> $CONFIG_NAME
	echo "//                      the line START_INDIVIDUAL_PROJECT_CONFIG and remove the comment indication there."  >> $CONFIG_NAME
	echo "//                      All commented out defines in the middle block will be upated on next \"update_makefile.sh $CONF_FILE\" call,"  >> $CONFIG_NAME
	echo "//                      if the corresponding value in isoaglib_config.h changed" >> $CONFIG_NAME

	echo -e "\n\n// include an external file for definition of pool and firmware versions" >> $CONFIG_NAME
	echo    "#include \"version.h\""  >> $CONFIG_NAME

	echo -e "$ENDLINE" >> $CONFIG_NAME
	echo    "#ifndef "$USE_SYSTEM_DEFINE     >> $CONFIG_NAME
	echo    "#define "$USE_SYSTEM_DEFINE     >> $CONFIG_NAME
	echo    "#endif // "$USE_SYSTEM_DEFINE     >> $CONFIG_NAME
	echo    "#define PRJ_USE_AUTOGEN_CONFIG config_$PROJECT.h" >> $CONFIG_NAME
	for SinglePrjDefine in $PRJ_DEFINES ; do
		echo "#ifndef $SinglePrjDefine" >> $CONFIG_NAME
		echo "#define $SinglePrjDefine" >> $CONFIG_NAME
		echo "#endif // $SinglePrjDefine" >> $CONFIG_NAME
	done
	echo -e "$ENDLINE" >> $CONFIG_NAME


	echo -e "#define CAN_BUS_CNT $CAN_BUS_CNT $ENDLINE" >> $CONFIG_NAME
	echo -e "#define CAN_BUS_USED $CAN_BUS_USED $ENDLINE" >> $CONFIG_NAME
	echo -e "#define CAN_INSTANCE_CNT $CAN_INSTANCE_CNT $ENDLINE" >> $CONFIG_NAME
	echo -e "#define PRT_INSTANCE_CNT $PRT_INSTANCE_CNT $ENDLINE" >> $CONFIG_NAME
	echo -e "#define RS232_INSTANCE_CNT $RS232_INSTANCE_CNT $ENDLINE" >> $CONFIG_NAME

  echo "// Decide if the CPU stores number variables in BIG or LITTLE endian byte order in memory." >> $CONFIG_NAME
  echo "// Most CPU will use LITTLE ENDIAN. Only some types of ARM, mostly 68k and PowerPC CPU types will use big endian." >> $CONFIG_NAME
  echo "// Please check the manual of your targret cpu. This setting is used to activate some quick number conversion algorithms," >> $CONFIG_NAME
  echo "// which provide quick conversion from number variable to CAN strings ( which are always little endian in ISO ) - and other way." >> $CONFIG_NAME
	if [ $USE_LITTLE_ENDIAN_CPU -gt 0 ] ; then
		echo -e "#define OPTIMIZE_NUMBER_CONVERSIONS_FOR_LITTLE_ENDIAN$ENDLINE" >> $CONFIG_NAME
	else
		echo -e "// #define OPTIMIZE_NUMBER_CONVERSIONS_FOR_LITTLE_ENDIAN$ENDLINE" >> $CONFIG_NAME
	fi
	if [ $USE_BIG_ENDIAN_CPU -gt 0 ] ; then
		echo -e "#define OPTIMIZE_NUMBER_CONVERSIONS_FOR_BIG_ENDIAN$ENDLINE" >> $CONFIG_NAME
	else
		echo -e "// #define OPTIMIZE_NUMBER_CONVERSIONS_FOR_BIG_ENDIAN$ENDLINE" >> $CONFIG_NAME
	fi

	if [ $USE_PCAN_LIB -gt 0 ] ; then
		echo -e "#define USE_PCAN_LIB$ENDLINE" >> $CONFIG_NAME
	else
		echo -e "// #define USE_PCAN_LIB$ENDLINE" >> $CONFIG_NAME
	fi

	if [ $PRJ_DO_NOT_START_RELAIS_ON_STARTUP -gt 0 ] ; then
		echo -e "#define CONFIG_DO_NOT_START_RELAIS_ON_STARTUP$ENDLINE" >> $CONFIG_NAME
	else
		echo -e "// #define CONFIG_DO_NOT_START_RELAIS_ON_STARTUP$ENDLINE" >> $CONFIG_NAME
	fi

	if [ $PRJ_RS232_OVER_CAN -gt 0 ] ; then
		echo -e "#define USE_RS232_OVER_CAN$ENDLINE" >> $CONFIG_NAME
	fi

  if [ $USE_VT_UNICODE_SUPPORT -gt 0 ] ; then
    echo -e "#define USE_VT_UNICODE_SUPPORT$ENDLINE" >> $CONFIG_NAME
  fi

  if [ $PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL -gt 0 ] ; then
		echo -e "#ifndef SYSTEM_WITH_ENHANCED_CAN_HAL$ENDLINE" >> $CONFIG_NAME
    echo -e "  #define SYSTEM_WITH_ENHANCED_CAN_HAL$ENDLINE" >> $CONFIG_NAME
		echo -e "#endif // SYSTEM_WITH_ENHANCED_CAN_HAL$ENDLINE" >> $CONFIG_NAME
  fi


	if [ $PRJ_BASE -gt 0 ] ; then
		echo -e "#ifndef USE_BASE $ENDLINE\t#define USE_BASE $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TRACTOR_GENERAL -gt 0 ; then
		echo -e "#ifndef USE_TRACTOR_GENERAL $ENDLINE\t#define USE_TRACTOR_GENERAL $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TRACTOR_MOVE -gt 0 ; then
		echo -e "#ifndef USE_TRACTOR_MOVE $ENDLINE\t#define USE_TRACTOR_MOVE $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TRACTOR_PTO -gt 0 ; then
		echo -e "#ifndef USE_TRACTOR_PTO $ENDLINE\t#define USE_TRACTOR_PTO $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TRACTOR_LIGHT -gt 0 ; then
		echo -e "#ifndef USE_TRACTOR_LIGHT $ENDLINE\t#define USE_TRACTOR_LIGHT $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TRACTOR_AUX -gt 0 ; then
		echo -e "#ifndef USE_TRACTOR_AUX $ENDLINE\t#define USE_TRACTOR_AUX $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TRACTOR_GUIDANCE -gt 0 ; then
		echo -e "#ifndef USE_TRACTOR_GUIDANCE $ENDLINE\t#define USE_TRACTOR_GUIDANCE $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TRACTOR_CERTIFICATION -gt 0 ; then
		echo -e "#ifndef USE_TRACTOR_CERTIFICATION $ENDLINE\t#define USE_TRACTOR_CERTIFICATION $ENDLINE#endif" >> $CONFIG_NAME
	fi
	if test $PRJ_TIME_GPS -gt 0 ; then
		echo -e "#ifndef USE_TIME_GPS $ENDLINE\t#define USE_TIME_GPS $ENDLINE#endif" >> $CONFIG_NAME
	fi

	if [ $PROC_LOCAL -gt 0 ] ; then
		echo -e "#ifndef USE_PROC_DATA_DESCRIPTION_POOL $ENDLINE\t#define USE_PROC_DATA_DESCRIPTION_POOL $ENDLINE#endif" >> $CONFIG_NAME
	fi

	echo "// Decide if HEAP allocation strategy shall reduce size about 5K to 10K in favour of speed" >> $CONFIG_NAME
	echo "// Strong Advice: Don't activate this, as long your target has not too tight memory restrictions" >> $CONFIG_NAME
	echo "// Initialization of CAN filters and of local process data might get too slow under worst case conditions" >> $CONFIG_NAME
	if [ $OPTIMIZE_HEAPSIZE_IN_FAVOR_OF_SPEED -gt 0 ] ; then
		echo -e "#define OPTIMIZE_HEAPSIZE_IN_FAVOR_OF_SPEED$ENDLINE" >> $CONFIG_NAME
	else
		echo -e "// #define OPTIMIZE_HEAPSIZE_IN_FAVOR_OF_SPEED$ENDLINE" >> $CONFIG_NAME
	fi

	echo "/** allow configuration by parameter value YES */" >> $CONFIG_NAME
	echo "#ifndef YES" >> $CONFIG_NAME
	echo "  #define YES 1" >> $CONFIG_NAME
	echo "#endif" >> $CONFIG_NAME
	echo "/** allow configuration by parameter value NO */" >> $CONFIG_NAME
	echo "#ifndef NO" >> $CONFIG_NAME
	echo "  #define NO 0" >> $CONFIG_NAME
	echo "#endif" >> $CONFIG_NAME


	if [ $USE_FLOAT_DATA_TYPE -gt 0 ] ; then
		echo "// Decide if float shall be used for the project" >> $CONFIG_NAME
		echo -e "#define USE_FLOAT_DATA_TYPE$ENDLINE" >> $CONFIG_NAME
	fi


	if [ $PRJ_PROCESS -gt 0 ] ; then
		echo -e "#ifndef USE_PROCESS $ENDLINE  #define USE_PROCESS $ENDLINE#endif" >> $CONFIG_NAME
		if [ $PROC_REMOTE -gt 0 ] ; then
			if [ $PROC_REMOTE_STD -gt 0 ] ; then
				echo -e "#ifndef USE_PROC_REMOTE_STD $ENDLINE  #define USE_PROC_REMOTE_STD $ENDLINE#endif" >> $CONFIG_NAME
			fi
			if [ $PROC_REMOTE_SIMPLE_MEASURE -gt 0 ] ; then
				echo -e "#ifndef USE_PROC_REMOTE_SIMPLE_MEASURE $ENDLINE  #define USE_PROC_REMOTE_SIMPLE_MEASURE $ENDLINE#endif" >> $CONFIG_NAME
			fi
			if [ $PROC_REMOTE_SIMPLE_SETPOINT -gt 0 ] ; then
				echo -e "#ifndef USE_PROC_REMOTE_SIMPLE_SETPOINT $ENDLINE  #define USE_PROC_REMOTE_SIMPLE_SETPOINT $ENDLINE#endif" >> $CONFIG_NAME
			fi
			if [ $PROC_REMOTE_SIMPLE_MEASURE_SETPOINT -gt 0 ] ; then
				echo -e "#ifndef USE_PROC_REMOTE_SIMPLE_MEASURE_SETPOINT $ENDLINE  #define USE_PROC_REMOTE_SIMPLE_MEASURE_SETPOINT $ENDLINE#endif" >> $CONFIG_NAME
			fi
			if [ $PROC_REMOTE_SIMPLE_MEASURE_SETPOINT_COMBINED -gt 0 ] ; then
				echo -e "#ifndef USE_PROC_SIMPLE_REMOTE_MEASURE_SETPOINT_COMBINED $ENDLINE  #define USE_PROC_SIMPLE_REMOTE_MEASURE_SETPOINT_COMBINED $ENDLINE#endif" >> $CONFIG_NAME
			fi
		fi
  else
  	# the default in isoaglib_config.h is to activate
    # PROCESS as long as USE_PROCESS_YN unset
		echo -e "#ifndef USE_PROCESS_YN $ENDLINE\t#define USE_PROCESS_YN NO $ENDLINE#endif" >> $CONFIG_NAME
	fi
  if [ $PRJ_EEPROM -gt 0 ] ; then
		echo -e "#ifndef USE_EEPROM_IO $ENDLINE\t#define USE_EEPROM_IO $ENDLINE#endif" >> $CONFIG_NAME
  else
  	# the default in isoaglib_config.h is to activate
    # EEPROM as long as USE_EEPROM_IO_YN unset
		echo -e "#ifndef USE_EEPROM_IO_YN $ENDLINE\t#define USE_EEPROM_IO_YN NO $ENDLINE#endif" >> $CONFIG_NAME
  fi

  if test $PRJ_DATASTREAMS -gt 0 -o $PRJ_ISO_TERMINAL -gt 0 -o $PRJ_TIME_GPS -gt 0 ; then
		echo -e "#ifndef USE_DATASTREAMS_IO $ENDLINE\t#define USE_DATASTREAMS_IO $ENDLINE#endif" >> $CONFIG_NAME
  else
  	# the default in isoaglib_config.h is to activate
    # DATASTREAMS as long as USE_DATASTREAMS_IO_YN unset
		echo -e "#ifndef USE_DATASTREAMS_IO_YN $ENDLINE\t#define USE_DATASTREAMS_IO_YN NO $ENDLINE#endif" >> $CONFIG_NAME
  fi

  if [ $PRJ_ISO11783 -gt 0 ] ; then
		echo -e "#ifndef USE_ISO_11783 $ENDLINE\t#define USE_ISO_11783 $ENDLINE#endif" >> $CONFIG_NAME
  	if [ $PRJ_ISO_TERMINAL -gt 0 ] ; then
			echo -e "#ifndef USE_ISO_TERMINAL $ENDLINE\t#define USE_ISO_TERMINAL $ENDLINE#endif" >> $CONFIG_NAME
    fi

	  if [ $PRJ_MULTIPACKET -gt 0 ] ; then
			if [ $PRJ_MULTIPACKET_STREAM_CHUNK -gt 0 ] ; then
				echo -e "#ifndef DEF_Stream_IMPL   $ENDLINE\t#define DEF_Stream_IMPL   StreamChunk   $ENDLINE#endif" >> $CONFIG_NAME
				echo -e "#ifndef DEF_Stream_c_IMPL $ENDLINE\t#define DEF_Stream_c_IMPL StreamChunk_c $ENDLINE#endif" >> $CONFIG_NAME
			else
				echo -e "#ifndef DEF_Stream_IMPL   $ENDLINE\t#define DEF_Stream_IMPL   StreamLinear   $ENDLINE#endif" >> $CONFIG_NAME
				echo -e "#ifndef DEF_Stream_c_IMPL $ENDLINE\t#define DEF_Stream_c_IMPL StreamLinear_c $ENDLINE#endif" >> $CONFIG_NAME
			fi
    fi
  	if [ $PRJ_ISO_TERMINAL_SERVER -gt 0 ] ; then
			echo -e "#ifndef USE_ISO_TERMINAL_SERVER $ENDLINE\t#define USE_ISO_TERMINAL_SERVER $ENDLINE#endif" >> $CONFIG_NAME
			echo "with ISO_TERMINAL_SERVER!"
    fi
  fi

	if [ $PRJ_SEND_DEBUG -gt 0 ] ; then
		echo -e "#ifndef DEBUG $ENDLINE\t#define DEBUG $ENDLINE#endif" >> $CONFIG_NAME
	fi

	# write overwriteable parts of isoaglib_config.h
	echo -e "$ENDLINE// The following configuration values can be overwritten." >> $CONFIG_NAME
	echo "// These settings are initially defined in isoaglib_config.h ." >> $CONFIG_NAME
	echo "// These settings are in commented-out, so that you can activate and adapt them by" >> $CONFIG_NAME
	echo -e "// moving them below the line with START_INDIVIDUAL_PROJECT_CONFIG$ENDLINE"  >> $CONFIG_NAME
	for conf_line in `grep "#define CONFIG_" $ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/isoaglib_config.h | sed 's/#define \(CONFIG_[a-zA-Z0-9_]*\).*/\1/g'` ; do
		conf_name=`echo $conf_line | sed 's/#define \(CONFIG_[a-zA-Z0-9_]*\).*/\1/g'`
		INDIV_CNT=`grep -c $conf_name $CONFIG_NAME.bak`
		if [ $INDIV_CNT -lt 1 ] ; then
			grep -B1 "#define $conf_line" $ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/isoaglib_config.h >> $CONFIG_NAME
			sed "s|#define $conf_name|// #define $conf_name|g" $CONFIG_NAME > $CONFIG_NAME.1
#			CMDLINE=`echo "sed -e 's|#define $conf_name|// #define $conf_name|g' $CONFIG_NAME > $CONFIG_NAME.1"`
#			echo $CMDLINE | sh
			mv $CONFIG_NAME.1 $CONFIG_NAME
			echo -e -n "$ENDLINE" >> $CONFIG_NAME
		fi
	done
	echo -e "$ENDLINE// DONT REMOVE THIS AND THE FOLLOWING LINE AS THEY ARE NEEDED TO DETECT YOUR PERSONAL PROJECT ADAPTATIONS!!!" >> $CONFIG_NAME
	FRESH=`grep -c "// START_INDIVIDUAL_PROJECT_CONFIG" $CONFIG_NAME.bak`
	if [ $FRESH -lt 1 ] ; then
		echo "// START_INDIVIDUAL_PROJECT_CONFIG" >> $CONFIG_NAME
	fi
	cat $CONFIG_NAME.bak >> $CONFIG_NAME
	rm -f $CONFIG_NAME.bak

	sed -e 's|^[ \t]*//|//|g' $CONFIG_NAME > $CONFIG_NAME.1
	sed -e 's|^[ \t]*/\*|/\*|g' $CONFIG_NAME.1 > $CONFIG_NAME
	rm -f $CONFIG_NAME.1


	echo -e "$ENDLINE$ENDLINE \section PrjConfig$PROJECT List of configuration settings for $PROJECT" > $CONFIG_HEADER_DOXYGEN_READY
	echo " This is only a copy with doxygen ready comment blocks from the original file $CONFIG_NAME " >> $CONFIG_HEADER_DOXYGEN_READY
	echo " This header is included by <IsoAgLib/library/xgpl_src/IsoAgLib/isoaglib_config.h> based on the" >> $CONFIG_HEADER_DOXYGEN_READY
	echo " project define #define PRJ_USE_AUTOGEN_CONFIG config_$PROJECT.h ( Important: place the directory of the application source files in the include search path )" >> $CONFIG_HEADER_DOXYGEN_READY
	echo "" >> $CONFIG_HEADER_DOXYGEN_READY
	echo " Use the file $CONF_FILE in the directory $1 as input file for $0 to create the project generation files." >> $CONFIG_HEADER_DOXYGEN_READY
	echo "\code" >> $CONFIG_HEADER_DOXYGEN_READY
	cat $CONFIG_NAME >> $CONFIG_HEADER_DOXYGEN_READY
	echo "\endcode" >> $CONFIG_HEADER_DOXYGEN_READY


  # go back to directory where config file resides
	cd $1
}

create_makefile()
{
  # go to project dir - below config dir
  DEV_PRJ_DIR="$1/$PROJECT"
  cd $DEV_PRJ_DIR
  mkdir -p "objects_library" "objects_app"
  MakefileFilelistLibrary="$1/$PROJECT/$FILELIST_LIBRARY_PURE"
  MakefileFilelistLibraryHdr="$1/$PROJECT/$FILELIST_LIBRARY_HDR"

  MakefileFilelistApp="$1/$PROJECT/$FILELIST_APP_PURE"

	MakefileFileListUTest="$1/$PROJECT/$FILELIST_UTEST_PURE"
	MakefileFileListUTestMock="$1/$PROJECT/$FILELIST_UTEST_MOCK_PURE"
	MakefileFileListUTestMODSUT="$1/$PROJECT/$FILELIST_UTEST_MODSUT_PURE"
	MakefileFileListUTestRunner="$1/$PROJECT/$FILELIST_UTEST_RUNNER_PURE"

	MakefileName="Makefile"
	MakefileNameLong="Makefile"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER"

	if [ "A$MAKEFILE_SKELETON_FILE" = "A" ] ; then
  	MAKEFILE_SKELETON_FILE="$DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/MakefileSkeleton.txt"
  fi

	# create Makefile Header
	echo "#############################################################################" > $MakefileNameLong
	echo "# Makefile for building: $PROJECT" >> $MakefileNameLong
	echo "# Project:               $PROJECT" >> $MakefileNameLong
	echo "#############################################################################" >> $MakefileNameLong
	echo ""  >> $MakefileNameLong
	echo "####### Project specific variables" >> $MakefileNameLong
	echo "TARGET = $PROJECT" >> $MakefileNameLong
	echo "ISOAGLIB_PATH = $ISO_AG_LIB_INSIDE" >> $MakefileNameLong
	echo "INSTALL_PATH = $ISOAGLIB_INSTALL_PATH" >> $MakefileNameLong
	echo -n "APP_INC = " >> $MakefileNameLong
	KDEVELOP_INCLUDE_PATH="$ISO_AG_LIB_INSIDE/library/xgpl_src;"
  for EACH_REL_APP_PATH in $REL_APP_PATH ; do
		echo -n "-I$ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH " >> $MakefileNameLong
		KDEVELOP_INCLUDE_PATH="$KDEVELOP_INCLUDE_PATH $ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH;"
  done
	for SingleInclPath in $PRJ_INCLUDE_PATH ; do
		echo -n " -I$ISO_AG_LIB_INSIDE/$SingleInclPath" >> $MakefileNameLong
		KDEVELOP_INCLUDE_PATH="$KDEVELOP_INCLUDE_PATH $ISO_AG_LIB_INSIDE/$SingleInclPath;"
	done
	echo "" >> $MakefileNameLong

	echo -e "\n####### Include a version definition file into the Makefile context - when this file exists"  >> $MakefileNameLong
	echo    "-include versions.mk" >> $MakefileNameLong


	echo "" >> $MakefileNameLong
	if [ $USE_CAN_DRIVER = "rte" -o $USE_RS232_DRIVER = "rte" -o $PRJ_CAN_DEVICE_FOR_SERVER = "rte" ] ; then
		echo "BIOS_LIB = /usr/local/lib/librte_client.a /usr/local/lib/libfevent.a" >> $MakefileNameLong
		# the new RTE library places the headers in /usr/local/include --> no special include paths are needed any more
		echo -n "BIOS_INC =" >> $MakefileNameLong
	fi

	echo -n -e "\nPROJ_DEFINES = \$(VERSION_DEFINES) -D$USE_SYSTEM_DEFINE -DPRJ_USE_AUTOGEN_CONFIG=config_$PROJECT.h" >> $MakefileNameLong
	for SinglePrjDefine in $PRJ_DEFINES ; do
		echo -n " -D$SinglePrjDefine" >> $MakefileNameLong
	done
	if [ $PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL -gt 0 ] ; then
		echo -n " -DSYSTEM_WITH_ENHANCED_CAN_HAL" >> $MakefileNameLong
	fi

	if [ $USE_CAN_DRIVER = "msq_server" ] ; then
		echo -n " -DCAN_DRIVER_MESSAGE_QUEUE" >> $MakefileNameLong
	fi
	if [ $USE_CAN_DRIVER = "socket_server" ] ; then
		echo -n " -DCAN_DRIVER_SOCKET" >> $MakefileNameLong
	fi

	echo -e "\n\n####### Definition of compiler binary prefix corresponding to selected target" >> $MakefileNameLong
	if [ "A$PRJ_COMPILER_BINARY_PRE" != "A" ] ; then
		echo "COMPILER_BINARY_PRE = \"$PRJ_COMPILER_BINARY_PRE\"" >> $MakefileNameLong

	else
		case $PRJ_DEFINES in
			*SYSTEM_A1*)
				echo "COMPILER_BINARY_PRE = /opt/hardhat/devkit/arm/xscale_le/bin/xscale_le-" >> $MakefileNameLong
				echo "SYSTEM_A1"
				;;
			*SYSTEM_MCC*)
				echo "COMPILER_BINARY_PRE = /opt/eldk/usr/bin/ppc_6xx-" >> $MakefileNameLong
				echo "SYSTEM_MCC"
				;;
			*)
				echo "COMPILER_BINARY_PRE = " >> $MakefileNameLong
				;;
		esac
	fi



	echo -e "\n\nfirst: all\n" >> $MakefileNameLong
	echo "####### Files" >> $MakefileNameLong
	echo -n "SOURCES_LIBRARY = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for CcFile in `grep -E "\.cc|\.cpp|\.c" $MakefileFilelistLibrary` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n '\\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$CcFile  " >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong

	echo -n "SOURCES_APP = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for CcFile in `grep -E "\.cc|\.cpp|\.c" $MakefileFilelistApp` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n '\\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$CcFile  " >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong

	echo -n "HEADERS_UTEST = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for CcFile in `grep -E "\.h" $MakefileFileListUTest` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n '\\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$CcFile  " >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong

	echo -n "HEADERS_UTEST_MOCKS = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for CcFile in `grep -E "\.h" $MakefileFileListUTestMock` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n '\\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$CcFile  " >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong

	echo -n "HEADERS_UTEST_MOD_SUT = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for CcFile in `grep -E "\.h" $MakefileFileListUTestMODSUT` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n '\\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$CcFile  " >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong

	echo -n "TESTRUNNER_SOURCES = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for CcFile in `grep -E "\.cpp" $MakefileFileListUTestRunner` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n '\\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$CcFile  " >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong
rm -f FileListInterfaceStart.txt FileListInterface.txt FileListInterface4Eval.txt FileListInternal.txt FileListInterface4EvalPre.txt FileListInterface4EvalPre.*.txt

cat "$MakefileFilelistLibraryHdr" | grep    "/impl/" > FileListInternal.txt
cat "$MakefileFilelistLibraryHdr" | grep    "/hal/"  >> FileListInternal.txt
cat "$MakefileFilelistLibraryHdr" | grep -v "/impl/" | grep -v /hal/ | grep -v ".cpp" > FileListInterface.txt

# it's a good idea to get the several typedef.h headers to the install set
grep typedef.h FileListInternal.txt >> FileListInterface.txt
grep -E "driver/*/i*.h" FileListInternal.txt >> FileListInterface.txt

cp -a FileListInterface.txt FileListInterfaceStart.txt
cp -a FileListInterface.txt FileListInterface4Eval.txt

DoRepeat="TRUE";
Iteration=0
while [ $DoRepeat = "TRUE" ] ; do
	DoRepeat="FALSE";
	for InterfaceFile in $(cat FileListInterface4Eval.txt); do
		for IncludeLine in $(grep "#include" $InterfaceFile | sed -e 's/.*#include[ \t\<\"]*\([^\>\"\t ]*\).*/\1/g'); do
			#BaseName=`basename $IncludeLine`;
			BaseName=`echo $IncludeLine | sed -e 's#.*xgpl_src/IsoAgLib/\(.*\)#\1#g' | sed -e 's#\.\./##g'`
			CntHeader=`echo $BaseName | grep -c '\.h'`;
	#echo "CntHeader $CntHeader";
			if [ $CntHeader -gt 0 ] ; then
	#      echo "Include Line fuer $IncludeLine mit Datei $BaseName";
				CntInterface=`grep -c "/$BaseName" FileListInterface.txt`
				CntInternal=`grep -c "/$BaseName" FileListInternal.txt`

	      #echo "Include Datei $BaseName kommt $CntInterface mal im Interface und $CntInternal mal intern vor";
				if test $CntInterface -lt 1 -a $CntInternal -gt 0 ; then
	#echo "Header $BaseName existiert noch nicht in Interface --> hinzufgen"
					grep $BaseName FileListInternal.txt >> FileListInterface.txt
					grep $BaseName FileListInternal.txt >> FileListInterface4EvalPre.txt
					DoRepeat="TRUE";
				fi
			fi
		done
	done
	if [ $DoRepeat = "TRUE" ] ; then
		Iteration=`expr $Iteration + 1`
		cp -a FileListInterface4EvalPre.txt FileListInterface4EvalPre.$Iteration.txt
		cp -a FileListInterface4EvalPre.txt FileListInterface4Eval.txt
		rm -f FileListInterface4EvalPre.txt
	fi
done
	echo -n "INSTALL_FILES_LIBRARY = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for InterfaceFile in `cat FileListInterface.txt` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n ' \\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$InterfaceFile" >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong

rm -f FileListInterfaceStart.txt FileListInterface.txt FileListInterface4Eval.txt FileListInternal.txt FileListInterface4EvalPre.txt FileListInterface4EvalPre.*.txt


	# build special target for CAN server
	if [ $USE_CAN_DRIVER = "msq_server" ] ; then
		mkdir -p objects_server
		echo -e "\n#Special Sources for CAN Server" >> $MakefileNameLong
		echo "SOURCES_SERVER = $ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/hal/pc/can/can_server_msq.cpp \\" >> $MakefileNameLong

		# now derive the source name of the specific CAN HAL module
		echo -e "\t\t$ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/hal/pc/can/can_server_"$PRJ_CAN_DEVICE_FOR_SERVER".cpp \\" >> $MakefileNameLong

    echo -e "\t\t$ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/hal/pc/can/msq_helper.cpp \\" >> $MakefileNameLong
		echo -e "\n#Special Rules for CAN Server" >> $MakefileNameLong

		cat $DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/MakefileCanServerPart.txt >> $MakefileNameLong
		if [ $USE_PCAN_LIB -gt 0 ] ; then
			echo -e "LIBS_CAN_SERVER	= -lpcan" >> $MakefileNameLong;
		fi

	fi
	# build special target for CAN server
	if [ $USE_CAN_DRIVER = "socket_server" ] ; then
		mkdir -p objects_server
		echo -e "\n#Special Sources for CAN Server" >> $MakefileNameLong
		echo "SOURCES_SERVER = $ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/hal/pc/can/can_server_sock.cpp \\" >> $MakefileNameLong

		# now derive the source name of the specific CAN HAL module
		echo -e "\t\t$ISO_AG_LIB_INSIDE/library/xgpl_src/IsoAgLib/hal/pc/can/can_server_"$PRJ_CAN_DEVICE_FOR_SERVER".cpp \\" >> $MakefileNameLong
		echo -e "\n#Special Rules for CAN Server" >> $MakefileNameLong

		cat $DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/MakefileCanServerPart.txt >> $MakefileNameLong
	fi

	cat $MAKEFILE_SKELETON_FILE >> $MakefileNameLong

	# add can_server creation to target "all"
	if [ $USE_CAN_DRIVER = "msq_server" -o $USE_CAN_DRIVER = "socket_server" ] ; then
		sed -e 's#all:#all: can_server#g'  $MakefileNameLong > $MakefileNameLong.1
		sed -e 's#LFLAGS   =#LFLAGS   = -pthread#g' $MakefileNameLong.1 > $MakefileNameLong
	fi

	rm -f $MakefileNameLong.1
	# replace the install rules for version.h and the app config file
	sed -e "s#_PROJECT_CONFIG_REPLACE_#$CONFIG_NAME#g"  $MakefileNameLong > $MakefileNameLong.1
	sed -e "s#_PROJECT_VERSION_REPLACE_#$VERSION_FILE_NAME#g" $MakefileNameLong.1 > $MakefileNameLong
	rm -f $MakefileNameLong.1

	# create a symbolic link to get this individual MakefileNameLong referred as "Makefile"
	rm -f "Makefile"
	ln -s $MakefileNameLong "Makefile"

	# now create pure application makefile which is based upon an installed library
	MakefileName="MakefileApp"
	MakefileNameLong="MakefileApp"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER"

	if [ "A$MAKEFILE_APP_SKELETON_FILE" = "A" ] ; then
  	MAKEFILE_APP_SKELETON_FILE="$DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/MakefileAppSkeleton.txt"
  fi


	# create Makefile Header
	echo "#############################################################################" > $MakefileNameLong
	echo "# Makefile for building: $PROJECT" >> $MakefileNameLong
	echo "# Project:               $PROJECT" >> $MakefileNameLong
	echo "#############################################################################" >> $MakefileNameLong
	echo ""  >> $MakefileNameLong
	echo "####### Project specific variables" >> $MakefileNameLong
	echo "TARGET = $PROJECT" >> $MakefileNameLong
	echo "ISOAGLIB_INSTALL_PATH = $ISOAGLIB_INSTALL_PATH" >> $MakefileNameLong
	echo -n "APP_INC = " >> $MakefileNameLong
	KDEVELOP_INCLUDE_PATH="$ISO_AG_LIB_INSIDE/library/xgpl_src;"
  for EACH_REL_APP_PATH in $REL_APP_PATH ; do
		echo -n "-I$ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH " >> $MakefileNameLong
		KDEVELOP_INCLUDE_PATH="$KDEVELOP_INCLUDE_PATH $ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH;"
  done
	for SingleInclPath in $PRJ_INCLUDE_PATH ; do
		echo -n " -I$ISO_AG_LIB_INSIDE/$SingleInclPath" >> $MakefileNameLong
		KDEVELOP_INCLUDE_PATH="$KDEVELOP_INCLUDE_PATH $ISO_AG_LIB_INSIDE/$SingleInclPath;"
	done
	echo "" >> $MakefileNameLong

	echo -e "\n####### Include a version definition file into the Makefile context - when this file exists"  >> $MakefileNameLong
	echo    "-include versions.mk" >> $MakefileNameLong


	echo "" >> $MakefileNameLong

	echo -n -e "\nPROJ_DEFINES = \$(VERSION_DEFINES) -D$USE_SYSTEM_DEFINE -DPRJ_USE_AUTOGEN_CONFIG=config_$PROJECT.h" >> $MakefileNameLong
	for SinglePrjDefine in $PRJ_DEFINES ; do
		echo -n " -D$SinglePrjDefine" >> $MakefileNameLong
	done

	echo -e "\n\n####### Definition of compiler binary prefix corresponding to selected target" >> $MakefileNameLong
	if [ "A$PRJ_COMPILER_BINARY_PRE" != "A" ] ; then
		echo "COMPILER_BINARY_PRE = \"$PRJ_COMPILER_BINARY_PRE\"" >> $MakefileNameLong

	else
		case $PRJ_DEFINES in
			*SYSTEM_A1*)
				echo "COMPILER_BINARY_PRE = /opt/hardhat/devkit/arm/xscale_le/bin/xscale_le-" >> $MakefileNameLong
				echo "SYSTEM_A1"
				;;
			*SYSTEM_MCC*)
				echo "COMPILER_BINARY_PRE = /opt/eldk/usr/bin/ppc_6xx-" >> $MakefileNameLong
				echo "SYSTEM_MCC"
				;;
			*)
				echo "COMPILER_BINARY_PRE = " >> $MakefileNameLong
				;;
		esac
	fi

	echo -e "\n\nfirst: all\n" >> $MakefileNameLong
	echo "####### Files" >> $MakefileNameLong
	echo -n "SOURCES_APP = " >> $MakefileNameLong
	FIRST_LOOP="YES"
	for CcFile in `grep -E "\.cc|\.cpp|\.c" $MakefileFilelistApp` ; do
		if [ $FIRST_LOOP != "YES" ] ; then
			echo -e -n '\\' >> $MakefileNameLong
			echo -e -n "\n\t\t" >> $MakefileNameLong
		else
			FIRST_LOOP="NO"
		fi
		echo -e -n "$CcFile  " >> $MakefileNameLong
	done
	echo -e "\n" >> $MakefileNameLong

	cat $MAKEFILE_APP_SKELETON_FILE >> $MakefileNameLong

	# add can_server creation to target "all"
	if [ $USE_CAN_DRIVER = "msq_server" ] ; then
		sed -e 's#all:#all: can_server#g'  $MakefileNameLong > $MakefileNameLong.1
		sed -e 's#LFLAGS   =#LFLAGS   = -pthread#g' $MakefileNameLong.1 > $MakefileNameLong
	fi
	rm -f $MakefileNameLong.1

	# create a symbolic link to get this individual MakefileNameLong referred as "Makefile"
	rm -f "MakefileApp"
	ln -s $MakefileNameLong "MakefileApp"


	# now create a Kdevelop3 project file
	cp -a $DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/kdevelop3Generic.kdevelop $PROJECT.kdevelop

	CMDLINE=`echo "sed -e 's/REPLACE_AUTHOR/$PROJECT_AUTHOR/g' $PROJECT.kdevelop > $PROJECT.kdevelop.1"`
	echo $CMDLINE | sh
	CMDLINE=`echo "sed -e 's/REPLACE_AUTHOR_EMAIL/$PROJECT_AUTHOR_EMAIL/g' $PROJECT.kdevelop.1 > $PROJECT.kdevelop"`
	echo $CMDLINE | sh
	CMDLINE=`echo "sed -e 's/REPLACE_PROJECT/$PROJECT/g' $PROJECT.kdevelop > $PROJECT.kdevelop.1"`
	echo $CMDLINE | sh
	CMDLINE=`echo "sed -e 's#REPLACE_INCLUDE#$KDEVELOP_INCLUDE_PATH#g' $PROJECT.kdevelop.1 > $PROJECT.kdevelop"`
	echo $CMDLINE | sh
#	mv $PROJECT.kdevelop.1 $PROJECT.kdevelop
	rm $PROJECT.kdevelop.1

	echo "# KDevelop Custom Project File List" > $PROJECT.kdevelop.filelist
	cat filelist__$PROJECT.txt >> $PROJECT.kdevelop.filelist


  cd $1

  return
}

# Generate suitable project file for the Win32 IDE "Dev-C++"
# which is OpenSource and is based on MinGW - i.e. gcc for Win32
# URL http://www.bloodshed.net/dev/devcpp.html
create_DevCCPrj() {
  DEV_PRJ_DIR="$1/../Dev-C++/$PROJECT"
  # echo "Create Projekt file for Dev-C++ in $DEV_PRJ_DIR"
  mkdir -p $DEV_PRJ_DIR/objects
  cd $DEV_PRJ_DIR
	# remove some file lists, which are not used for Dev-C++
	rm $FILELIST_LIBRARY_PURE $FILELIST_APP_PURE

  # org test
	PROJECT_FILE_NAME="$PROJECT"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER.dev"
  DevCcPrjFilelist="$1/$PROJECT/$FILELIST_COMBINED_PURE"

  # echo "Erzeuge $PROJECT_FILE_NAME"
  PROJECT_EXE_NAME="$PROJECT"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER.exe"
  CONFIG_HDR_NAME="config_""$PROJECT.h"

  UNIT_CNT_CC=`grep -c -E "\.cc|\.cpp|\.c" $DevCcPrjFilelist`
  UNIT_CNT_HDR=`grep -c -E "\.h|\.hpp" $DevCcPrjFilelist`
  UNIT_CNT=`expr $UNIT_CNT_CC + $UNIT_CNT_HDR`


  echo "[Project]" > $PROJECT_FILE_NAME
  echo "FileName=$PROJECT_FILE_NAME" >> $PROJECT_FILE_NAME
  echo "Name=$PROJECT" >> $PROJECT_FILE_NAME
  echo "UnitCount=$UNIT_CNT" >> $PROJECT_FILE_NAME


	cat <<-ENDOFHEADERA >> $PROJECT_FILE_NAME
	Type=1
	Ver=1
	ObjFiles=
	ENDOFHEADERA

	DEFINE_LINE='-D'"$USE_SYSTEM_DEFINE"'_@@_-DPRJ_USE_AUTOGEN_CONFIG='"$CONFIG_HDR_NAME"'_@@_'
	INCLUDE_DIR_LINE="../$ISO_AG_LIB_INSIDE;$ISO_AG_LIB_INSIDE/library/xgpl_src"
    for EACH_REL_APP_PATH in $REL_APP_PATH ; do
	INCLUDE_DIR_LINE="$INCLUDE_DIR_LINE;$ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH"
    done

	LIB_DIR_LINE=""
	LIB_FILE_LINE=""

	if  [ $USE_CAN_DRIVER = "vector_canlib" -o $PRJ_CAN_DEVICE_FOR_SERVER = "vector_canlib" ] ; then
		INCLUDE_DIR_LINE="$INCLUDE_DIR_LINE;$USE_WIN32_HEADER_DIRECTORY/CANLIB/dll"
		LIB_DIR_LINE="$USE_WIN32_LIB_DIRECTORY/CANLIB/dll"
		LIB_FILE_LINE="-lvcand32_@@_"
		DEFINE_LINE="$DEFINE_LINE"'-D__GNUWIN32__ -W -DWIN32 -D_CONSOLE -D_MBCS_@@_-D_Windows_@@_'
		DEFINE_LINE="$DEFINE_LINE"'_@@_-DUSE_CAN_CARD_TYPE='"$USE_WIN32_CAN_HW_TYPE"'_@@_'
	elif  [ $USE_CAN_DRIVER = "vector_xl_drv_lib" -o $PRJ_CAN_DEVICE_FOR_SERVER = "vector_xl" ] ; then
		INCLUDE_DIR_LINE="$INCLUDE_DIR_LINE;\"$USE_WIN32_HEADER_DIRECTORY/XL Driver Library/bin\""
		LIB_DIR_LINE="$USE_WIN32_LIB_DIRECTORY/XL Driver Library/bin"
		LIB_FILE_LINE="-lvxlapi_@@_"
		DEFINE_LINE="$DEFINE_LINE"'-D__GNUWIN32__ -W -DWIN32 -D_CONSOLE -D_MBCS_@@_-D_Windows_@@_'
		DEFINE_LINE="$DEFINE_LINE"'_@@_-DUSE_CAN_CARD_TYPE=XL_'"$USE_WIN32_CAN_HW_TYPE"'_@@_'
	elif  [ $USE_CAN_DRIVER = "sontheim" -o $PRJ_CAN_DEVICE_FOR_SERVER = "sontheim" ] ; then
		INCLUDE_DIR_LINE="$INCLUDE_DIR_LINE;\"$USE_WIN32_HEADER_DIRECTORY/Sontheim\";\"$USE_WIN32_HEADER_DIRECTORY/Sontheim/Capitest\""
		LIB_DIR_LINE="$USE_WIN32_LIB_DIRECTORY/Sontheim;$USE_WIN32_LIB_DIRECTORY/Sontheim/Capitest"
		LIB_FILE_LINE="-lvcanapi_@@_"
		DEFINE_LINE="$DEFINE_LINE"'-D__GNUWIN32__ -W -DWIN32 -D_CONSOLE -D_MBCS_@@_-D_Windows_@@_'
		DEFINE_LINE="$DEFINE_LINE"'_@@_-DUSE_CAN_CARD_TYPE='"$USE_WIN32_CAN_HW_TYPE"'_@@_'
	fi

	echo -n "Includes=$INCLUDE_DIR_LINE" >> $PROJECT_FILE_NAME
	for SingleInclPath in $PRJ_INCLUDE_PATH ; do
		echo -n ";$SingleInclPath" >> $PROJECT_FILE_NAME
	done
	echo "" >> $PROJECT_FILE_NAME

	echo "Libs=$LIB_DIR_LINE" >> $PROJECT_FILE_NAME
	echo "Linker=$LIB_FILE_LINE" >> $PROJECT_FILE_NAME

	cat <<-ENDOFHEADERA >> $PROJECT_FILE_NAME
	PrivateResource=
	ResourceIncludes=
	MakeIncludes=
	ENDOFHEADERA



	for SinglePrjDefine in $PRJ_DEFINES ; do
		DEFINE_LINE="$DEFINE_LINE"'-D'"$SinglePrjDefine"'_@@_'
	done

	echo "Compiler=$DEFINE_LINE" >> $PROJECT_FILE_NAME
	echo "CppCompiler=$DEFINE_LINE" >> $PROJECT_FILE_NAME

	cat <<-ENDOFHEADERB >> $PROJECT_FILE_NAME
	IsCpp=1
	Icon=
	ExeOutput=
	ObjectOutput=objects
	OverrideOutput=0
	ENDOFHEADERB

	echo "OverrideOutputName=$PROJECT_EXE_NAME" >> $PROJECT_FILE_NAME


	cat <<-ENDOFHEADERC >> $PROJECT_FILE_NAME
	HostApplication=
	Folders=
	CommandLine=
	UseCustomMakefile=0
	CustomMakefile=
	IncludeVersionInfo=0
	SupportXPThemes=0
	CompilerSet=0
	CompilerSettings=0000000000000000000000

	[VersionInfo]
	Major=0
	Minor=1
	Release=1
	Build=1
	LanguageID=1033
	CharsetID=1252
	CompanyName=
	FileVersion=
	FileDescription=Developed using the Dev-C++ IDE
	InternalName=
	LegalCopyright=
	LegalTrademarks=
	OriginalFilename=
	ProductName=
	ProductVersion=
	AutoIncBuildNr=0

	ENDOFHEADERC

	SOURCES=`cat $DevCcPrjFilelist`
	unit_ind=0
	for i in $SOURCES
	do
		if [ $i = "" ] ; then
  		continue
  	fi
  	unit_ind=`expr $unit_ind + 1`
  	echo "[Unit$unit_ind]" >> $PROJECT_FILE_NAME
  	echo "FileName=$i" >> $PROJECT_FILE_NAME
  	echo "CompileCpp=1" >> $PROJECT_FILE_NAME
  	echo "Folder=$PROJECT" >> $PROJECT_FILE_NAME
  	echo "Compile=1" >> $PROJECT_FILE_NAME
  	echo "Link=1" >> $PROJECT_FILE_NAME
  	echo "Priority=1000" >> $PROJECT_FILE_NAME
  	echo "OverrideBuildCmd=0" >> $PROJECT_FILE_NAME
  	echo "BuildCmd=" >> $PROJECT_FILE_NAME
		echo "" >> $PROJECT_FILE_NAME
	done

	cd $1
}

create_EdePrj()
{
  DEV_PRJ_DIR="$1/$PROJECT"
  # echo "Create Projekt file for EDE in $DEV_PRJ_DIR"
  mkdir -p $DEV_PRJ_DIR/Template.dir
  PROJECT_FILE_NAME="$PROJECT"'_'"$USE_TARGET_SYSTEM.pjt"
  EdePrjFilelist="$1/$PROJECT/$FILELIST_COMBINED_PURE"
  CONFIG_HDR_NAME="config_""$PROJECT.h"


	if [ $USE_EMBED_LIB_DIRECTORY = "commercial_BIOS/bios_esx" ] ; then
		## adopt the BIOS file, if $USE_EMBED_LIB_DIRECTORY and
		## and $USE_EMBED_HEADER_DIRECTORY reflect default value which doesn't match to defined target
		case "$USE_TARGET_SYSTEM" in
		esx)
			;;
		pc*)
			;;
		*)
			USE_EMBED_LIB_DIRECTORY="commercial_BIOS/bios_$USE_TARGET_SYSTEM"
			USE_EMBED_HEADER_DIRECTORY="commercial_BIOS/bios_$USE_TARGET_SYSTEM"
			;;
		esac
	fi



### @todo
  for EACH_REL_APP_PATH in $REL_APP_PATH ; do
	  if [ "M$USE_APP_PATH" = "M" ] ; then
			USE_APP_PATH=`echo "$ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH" | sed -e 's/\/[0-9a-zA-Z_+\-]*\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]+\\\.\.//g'`
		else
			USE_APP_PATH="$USE_APP_PATH"`echo ";$ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH" | sed -e 's/\/[0-9a-zA-Z_+\-]*\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]+\\\.\.//g'`
		fi
	done
	echo "USE_APP_PATH: $USE_APP_PATH"

	INCLUDE_APP_PATH_TASKING="$ISO_AG_LIB_INSIDE/$USE_EMBED_HEADER_DIRECTORY"
	for SingleInclPath in $PRJ_INCLUDE_PATH ; do
		INCLUDE_APP_PATH_TASKING="$INCLUDE_APP_PATH_TASKING;$SingleInclPath"
	done

  USE_EMBED_HEADER_DIRECTORY=`echo "$ISO_AG_LIB_INSIDE/$USE_EMBED_HEADER_DIRECTORY" | sed -e 's/\/[0-9a-zA-Z_+\-]+\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]+\\\.\.//g'`
  USE_EMBED_LIB_DIRECTORY=`echo "$ISO_AG_LIB_INSIDE/$USE_EMBED_LIB_DIRECTORY" | sed -e 's/\/[0-9a-zA-Z_+\-]+\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]+\\\.\.//g'`


  USE_EMBED_ILO=`echo "$USE_EMBED_LIB_DIRECTORY/$USE_EMBED_ILO" | sed -e 's/\/[0-9a-zA-Z_+\-]+\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]+\\\.\.//g'`

  USE_DEFINES="__TSW_CPP_756__,$USE_SYSTEM_DEFINE,PRJ_USE_AUTOGEN_CONFIG=$CONFIG_HDR_NAME"

	for SinglePrjDefine in $PRJ_DEFINES ; do
		USE_DEFINES="$USE_DEFINES"','"$SinglePrjDefine"
	done


  USE_TARGET_LIB_LINE=""
  for LIBRARY in $USE_EMBED_LIBS ; do
  	USE_TARGET_LIB_LINE="$USE_TARGET_LIB_LINE -Wo $USE_EMBED_LIB_DIRECTORY/$LIBRARY"
  done
  # echo "Library line: $USE_TARGET_LIB_LINE"
  USE_TARGET_LIB_LINE=`echo "$USE_TARGET_LIB_LINE" | sed -e 's/\/[0-9a-zA-Z_+\-]+\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]+\\\.\.//g'`

	# avoid UNIX style directory seperator "/" as it can disturb Tasking during the link process ( during compile, everything runs fine with UNIX style - WMK seems to have problems with it durign link and hex gen )
	ISO_AG_LIB_PATH_WIN=`echo "../$ISO_AG_LIB_INSIDE" | sed -e 's#/#=_=_#g'`
	USE_EMBED_LIB_DIRECTORY=`echo "$USE_EMBED_LIB_DIRECTORY" | sed -e 's#/#=_=_#g'`
	USE_EMBED_HEADER_DIRECTORY=`echo "$USE_EMBED_HEADER_DIRECTORY" | sed -e 's#/#=_=_#g'`
	USE_TARGET_LIB_LINE=`echo "$USE_TARGET_LIB_LINE" | sed -e 's#/#=_=_#g'`
	USE_EMBED_ILO=`echo "$USE_EMBED_ILO" | sed -e 's#/#=_=_#g'`
	USE_APP_PATH=`echo "$USE_APP_PATH" | sed -e 's#/#=_=_#g'`
	DEV_PRJ_DIR_WIN=`echo "$DEV_PRJ_DIR" | sed -e 's#/#=_=_#g'`
	USE_DEFINES=`echo "$USE_DEFINES" | sed -e 's#/#=_=_#g'`
	USE_EMBED_COMPILER_DIR=`echo "$USE_EMBED_COMPILER_DIR" | sed -e 's#/#=_=_#g'`

	# remove some file lists, which are not used for Dev-C++
	rm "$1/$PROJECT/$FILELIST_LIBRARY_PURE" "$1/$PROJECT/$FILELIST_APP_PURE"


	# Build Tasking Project File by: a) first stub part; b) file list c) second stub part
	cp -a $DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/EDE.part1.pjt $DEV_PRJ_DIR/$PROJECT_FILE_NAME

	CMDLINE=`echo "sed -e 's/\/[0-9a-zA-Z_+\-]*\/\.\.//g' $EdePrjFilelist > $EdePrjFilelist.1"`
	echo $CMDLINE | sh
	CMDLINE=`echo "sed -e 's#/#=_=_#g' $EdePrjFilelist.1 > $EdePrjFilelist"`
	echo $CMDLINE | sh
	CMDLINE=`echo "sed -e 's#=_=_[0-9a-zA-Z_+\-]+=_=_\.\.##g'  $EdePrjFilelist > $EdePrjFilelist.1"`
	echo $CMDLINE | sh
	CMDLINE=`echo "sed -e 's#=_=_[0-9a-zA-Z_+\-]+=_=_\.\.##g'  $EdePrjFilelist.1 > $EdePrjFilelist"`
	echo $CMDLINE | sh
  cat $EdePrjFilelist >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
  rm -f $EdePrjFilelist.1

	# insert specific BIOS/OS sources
	for BiosSrc in $USE_EMBED_BIOS_SRC ; do
		echo "$USE_EMBED_LIB_DIRECTORY/$BiosSrc" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
	done


  cat $DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/EDE.part2.pjt >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
  cd $DEV_PRJ_DIR
  sed -e "s#INSERT_PROJECT#$PROJECT#g" -e "s#INSERT_TARGET_LIB_DIRECTORY#$USE_EMBED_LIB_DIRECTORY#g" $PROJECT_FILE_NAME > $PROJECT_FILE_NAME.1
  sed -e "s#INSERT_ISO_AG_LIB_PATH#$ISO_AG_LIB_PATH_WIN#g" -e "s#INSERT_TARGET_HEADER_DIRECTORY#$USE_EMBED_HEADER_DIRECTORY#g" $PROJECT_FILE_NAME.1 > $PROJECT_FILE_NAME

  sed -e "s#INSERT_TARGET_LIB#$USE_TARGET_LIB_LINE#g" -e "s#INSERT_TARGET_ILO#$USE_EMBED_ILO#g" $PROJECT_FILE_NAME > $PROJECT_FILE_NAME.1

  sed -e "s#INSERT_APP_PATH#$USE_APP_PATH#g" -e "s#INSERT_PRJ_PATH#$DEV_PRJ_DIR_WIN#g" -e "s#INSERT_DEFINES#$USE_DEFINES#g" -e "s#INSERT_EMBED_COMPILER_DIR#$USE_EMBED_COMPILER_DIR#g" $PROJECT_FILE_NAME.1 > $PROJECT_FILE_NAME

  rm -f $PROJECT_FILE_NAME.1

	sed -e 's#=_=_#\\#g'  $PROJECT_FILE_NAME > $PROJECT_FILE_NAME.1
	sed -e 's#=_=_#\\#g'  $EdePrjFilelist > $EdePrjFilelist.1
	mv $EdePrjFilelist.1 $EdePrjFilelist

	# now set the target CPU if this varies from default CpuC167CS
	## also adopt the BIOS file, if $USE_EMBED_LIB_DIRECTORY and
  ## and $USE_EMBED_HEADER_DIRECTORY reflect default value which doesn't match to defined target
	case "$USE_TARGET_SYSTEM" in
		Dj1)
			sed -e 's#CpuC167CS#CpuC167CR#g' $PROJECT_FILE_NAME.1 > $PROJECT_FILE_NAME
			mv $PROJECT_FILE_NAME $PROJECT_FILE_NAME.1
			;;
		esxu)
			sed -e 's#CpuC167CS#CpuF269#g' $PROJECT_FILE_NAME.1 > $PROJECT_FILE_NAME
			mv $PROJECT_FILE_NAME $PROJECT_FILE_NAME.1
			;;
		esx)
			# do nothing here
			;;
	esac


	echo "Converted UNIX to Windows Linebreak in $PROJECT_FILE_NAME"
	cat $PROJECT_FILE_NAME.1 | gawk '{ sub("\r", ""); print $0;}' > $PROJECT_FILE_NAME
	cat $PROJECT_FILE_NAME | gawk '{ sub("$", "\r"); print $0;}' > $PROJECT_FILE_NAME.1
	mv $PROJECT_FILE_NAME.1 $PROJECT_FILE_NAME
}

create_VCPrj()
{

  DEV_PRJ_DIR=`echo "$1/$PROJECT" | sed -e 's/Dev-C++/VC6/g'`
  # echo "Create Projekt file for VC6 in $DEV_PRJ_DIR"
  mkdir -p $DEV_PRJ_DIR/Debug
	PROJECT_FILE_NAME="$PROJECT"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER.dsp"

  DspPrjFilelist="$1/$PROJECT/$FILELIST_COMBINED_PURE"
  CONFIG_HDR_NAME="config_""$PROJECT.h"

	# remove some file lists, which are not used for Dev-C++
	rm "$1/$PROJECT/$FILELIST_LIBRARY_PURE" "$1/$PROJECT/$FILELIST_APP_PURE"



  USE_DEFINES=`echo " /D "'"'"$USE_SYSTEM_DEFINE"'"' " /D "'"'"PRJ_USE_AUTOGEN_CONFIG=$CONFIG_HDR_NAME"'"' | sed -e 's/SYSTEM_PC/SYSTEM_PC_VC/g'`
	USE_d_DEFINES=`echo $USE_DEFINES | sed -e 's#/D#/d#g'`


	LIB_DIR_LINE=""
	LIB_FILE_LINE=""

	ISO_AG_LIB_PATH_WIN=`echo "../$ISO_AG_LIB_INSIDE" | sed -e 's#/#=_=_#g'`
	USE_STLPORT_HEADER_DIRECTORY=`echo "$USE_STLPORT_HEADER_DIRECTORY" | sed -e 's#\\\#_=_=#g'`
	USE_STLPORT_HEADER_DIRECTORY=`echo "$USE_STLPORT_HEADER_DIRECTORY" | sed -e 's#/#=_=_#g'`

	USE_WIN32_HEADER_DIRECTORY_WIN=`echo "$USE_WIN32_HEADER_DIRECTORY" | sed -e 's#/#=_=_#g'`
	USE_WIN32_HEADER_DIRECTORY_WIN=`echo "$USE_WIN32_HEADER_DIRECTORY_WIN" | sed -e 's#\\\#=_=_#g'`

	USE_WIN32_LIB_DIRECTORY_WIN=`echo "$USE_WIN32_LIB_DIRECTORY" | sed -e 's#/#=_=_#g'`
	USE_WIN32_LIB_DIRECTORY_WIN=`echo "$USE_WIN32_LIB_DIRECTORY_WIN" | sed -e 's#\\\#=_=_#g'`

	PRJ_INCLUDE_PATH_WIN=`echo "$PRJ_INCLUDE_PATH" | sed -e 's#/#=_=_#g'`

	if  [ $USE_CAN_DRIVER = "vector_canlib" -o $PRJ_CAN_DEVICE_FOR_SERVER = "vector_canlib" ] ; then
          USE_INCLUDE_PATHS='/I "'"$USE_STLPORT_HEADER_DIRECTORY"'" /I "'"$ISO_AG_LIB_PATH_WIN"'" /I "'"$ISO_AG_LIB_PATH_WIN=_=_xgpl_src"'" /I "'"$USE_WIN32_HEADER_DIRECTORY_WIN=_=_CANLIB=_=_dll"'"'
          USE_DEFINES="$USE_DEFINES"' /D ''"'"$USE_WIN32_CAN_HW_TYPE"'"'
          USE_d_DEFINES="$USE_d_DEFINES"' /d ''"'"$USE_WIN32_CAN_HW_TYPE"'"'
          LIB_DIR_LINE="$USE_WIN32_LIB_DIRECTORY_WIN=_=_CANLIB=_=_dll"
          echo "$USE_WIN32_LIB_DIRECTORY_WIN=_=_CANLIB=_=_dll=_=_vcandm32.lib" >> $DspPrjFilelist
          echo "$USE_WIN32_LIB_DIRECTORY_WIN=_=_CANLIB=_=_dll=_=_VCanD.h" >> $DspPrjFilelist
	elif  [ $USE_CAN_DRIVER = "vector_xl_drv_lib" -o $PRJ_CAN_DEVICE_FOR_SERVER = "vector_xl" ] ; then
          USE_INCLUDE_PATHS='/I "'"$USE_STLPORT_HEADER_DIRECTORY"'" /I "'"$ISO_AG_LIB_PATH_WIN"'" /I "'"$ISO_AG_LIB_PATH_WIN=_=_xgpl_src"'" /I "'"$USE_WIN32_HEADER_DIRECTORY_WIN=_=_XL Driver Library=_=_bin"'"'
          USE_DEFINES="$USE_DEFINES"' /D ''"'"XL_$USE_WIN32_CAN_HW_TYPE"'"'
          USE_d_DEFINES="$USE_d_DEFINES"' /d ''"'"XL_$USE_WIN32_CAN_HW_TYPE"'"'
          LIB_DIR_LINE="$USE_WIN32_LIB_DIRECTORY_WIN=_=_XL Driver Library=_=_bin"
          echo "$USE_WIN32_LIB_DIRECTORY_WIN=_=_XL Driver Library=_=_bin=_=_vxlapi.lib" >> $DspPrjFilelist
          echo "$USE_WIN32_LIB_DIRECTORY_WIN=_=_XL Driver Library=_=_bin=_=_vxlapi.h" >> $DspPrjFilelist
	elif  [ $USE_CAN_DRIVER = "sontheim" -o $PRJ_CAN_DEVICE_FOR_SERVER = "sontheim" ] ; then
          USE_INCLUDE_PATHS='/I "'"$USE_STLPORT_HEADER_DIRECTORY"'" /I "'"$ISO_AG_LIB_PATH_WIN"'" /I "'"$ISO_AG_LIB_PATH_WIN=_=_xgpl_src"'" /I "'"$USE_WIN32_HEADER_DIRECTORY_WIN=_=_Sontheim"'" /I "'"$USE_WIN32_HEADER_DIRECTORY_WIN=_=_Sontheim=_=_Capitest"'"'
          USE_DEFINES="$USE_DEFINES"' /D ''"'"XL_$USE_WIN32_CAN_HW_TYPE"'"'
          USE_d_DEFINES="$USE_d_DEFINES"' /d ''"'"XL_$USE_WIN32_CAN_HW_TYPE"'"'
          LIB_DIR_LINE=' /libpath:"'"$USE_WIN32_LIB_DIRECTORY_WIN=_=_Sontheim"'" /libpath:"'"$USE_WIN32_LIB_DIRECTORY_WIN=_=_Sontheim=_=_Capitest"'"'
          echo "$USE_WIN32_LIB_DIRECTORY_WIN=_=_Sontheim=_=CANAPI.H" >> $DspPrjFilelist
          echo "$USE_WIN32_LIB_DIRECTORY_WIN=_=_Sontheim=_=Capitest=_=CANAPI.H" >> $DspPrjFilelist
	elif  [ $USE_CAN_DRIVER = "socket_server" ] ; then
          USE_INCLUDE_PATHS='/I "'"$ISO_AG_LIB_PATH_WIN"'" /I "'"$ISO_AG_LIB_PATH_WIN=_=_xgpl_src"'"'
          USE_DEFINES="$USE_DEFINES"' /D "'CAN_DRIVER_SOCKET'"'
          USE_d_DEFINES="$USE_d_DEFINES"' /d "'CAN_DRIVER_SOCKET'"'
   fi

	for SingleInclPath in $PRJ_INCLUDE_PATH_WIN ; do
		USE_INCLUDE_PATHS="$USE_INCLUDE_PATHS"' /I "'"$SingleInclPath"'"'
	done


	sed -e 's#=_=_#\\#g'  $DspPrjFilelist > $DspPrjFilelist.1
	mv $DspPrjFilelist.1 $DspPrjFilelist

	#echo "Libs=$LIB_DIR_LINE"
	#echo "Linker=$LIB_FILE_LINE"

	for SinglePrjDefine in $PRJ_DEFINES ; do
		USE_DEFINES="$USE_DEFINES"' /D '"$SinglePrjDefine"
		USE_d_DEFINES="$USE_d_DEFINES"' /D '"$SinglePrjDefine"
	done

	for EACH_REL_APP_PATH in $REL_APP_PATH ; do
		EACH_REL_APP_PATH_KURZ=`echo "$ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH" | sed -e 's/\/[0-9a-zA-Z_+\-]*\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]+\\\.\.//g'`
		EACH_REL_APP_PATH_WIN=`echo "$EACH_REL_APP_PATH_KURZ" | sed -e 's#/#=_=_#g'`
		USE_INCLUDE_PATHS="$USE_INCLUDE_PATHS"' /I "'"$EACH_REL_APP_PATH_WIN"'"'
	done


  cp -a $DEV_PRJ_DIR/$ISO_AG_LIB_INSIDE/library/xgpl_src/build/projectGeneration/vc6_prj_base.dsp $DEV_PRJ_DIR/$PROJECT_FILE_NAME

	CMDLINE=`echo "sed -e 's#INSERT_PROJECT#$PROJECT#g'  $DEV_PRJ_DIR/$PROJECT_FILE_NAME > $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1"`
	echo $CMDLINE | sh

	CMDLINE=`echo "sed -e 's#INSERT_INCLUDE_PATHS#$USE_INCLUDE_PATHS#g'  $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1 > $DEV_PRJ_DIR/$PROJECT_FILE_NAME"`
	echo $CMDLINE | sh

	CMDLINE=`echo "sed -e 's#INSERT_DEFINES#$USE_DEFINES#g' $DEV_PRJ_DIR/$PROJECT_FILE_NAME > $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1"`
	echo $CMDLINE | sh

	CMDLINE=`echo "sed -e 's#INSERT_d_DEFINES#$USE_d_DEFINES#g' $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1 > $DEV_PRJ_DIR/$PROJECT_FILE_NAME"`
	echo $CMDLINE | sh

	CMDLINE=`echo "sed -e 's#INSERT_CAN_LIB_PATH#$LIB_DIR_LINE#g' $DEV_PRJ_DIR/$PROJECT_FILE_NAME > $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1"`
	echo $CMDLINE | sh

	USE_STLPORT_LIB_DIRECTORY=$(echo "$USE_STLPORT_HEADER_DIRECTORY" |sed 's|stlport|lib|g')
	CMDLINE=`echo "sed -e 's#INSERT_STLPORT_LIB_PATH#$USE_STLPORT_LIB_DIRECTORY#g' $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1 > $DEV_PRJ_DIR/$PROJECT_FILE_NAME"`
	echo $CMDLINE | sh



  sed -e 's#=_=_#\\#g'  $DEV_PRJ_DIR/$PROJECT_FILE_NAME > $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1
#  rm -f $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1
  mv $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1 $DEV_PRJ_DIR/$PROJECT_FILE_NAME


	SOURCES=`grep -E "\.cc|\.cpp|\.c|\.lib" $DspPrjFilelist`
	HEADERS=`grep -E "\.h|\.hpp" $DspPrjFilelist`

	cat <<-ENDOFHEADERB >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cc;cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
	ENDOFHEADERB

	for i in $SOURCES
	do
		if [ $i = "" ] ; then
  		continue
  	fi
  	echo "# Begin Source File" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
		filename=$(echo "$i" |sed 's|/|\\|g')
  	echo "SOURCE=$filename" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
  	echo "# End Source File" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
		echo "" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
	done

	cat <<-ENDOFHEADERB >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
# End Group

# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
	ENDOFHEADERB

	for i in $HEADERS
	do
		if [ $i = "" ] ; then
  		continue
  	fi
  	echo "# Begin Source File" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
		filename=$(echo "$i" |sed 's|/|\\|g')
  	echo "SOURCE=$filename" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
  	echo "# End Source File" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
		echo "" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
	done

	echo "# End Group" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
	echo "# End Target" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME
	echo "# End Project" >> $DEV_PRJ_DIR/$PROJECT_FILE_NAME

	echo "Convert UNIX to Windows Linebreak in $DEV_PRJ_DIR/$PROJECT_FILE_NAME"

	cat $DEV_PRJ_DIR/$PROJECT_FILE_NAME | gawk '{ sub("\r", ""); print $0;}' > $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1
	cat $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1 | gawk '{ sub("$", "\r"); print $0;}' > $DEV_PRJ_DIR/$PROJECT_FILE_NAME.2
	mv $DEV_PRJ_DIR/$PROJECT_FILE_NAME.2 $DEV_PRJ_DIR/$PROJECT_FILE_NAME
	rm $DEV_PRJ_DIR/$PROJECT_FILE_NAME.1
  cd $DEV_PRJ_DIR
  # org test
}

perform_everything()
{
	# verify and correct the variables
  check_set_correct_variables $1 $2

	# overwrite settings from config file with command line parameter settings
	if [ $PARAMETER_TARGET_SYSTEM != "UseConfigFile" ] ; then
		USE_TARGET_SYSTEM=$PARAMETER_TARGET_SYSTEM
		# echo "Use Parameter value for target system: $USE_TARGET_SYSTEM"
	# else
		# echo "Use Target System from config file: $USE_TARGET_SYSTEM"
	fi
	if [ $PARAMETER_CAN_DRIVER != "UseConfigFile" ] ; then
		USE_CAN_DRIVER=$PARAMETER_CAN_DRIVER
		#echo "Use Parameter value for can driver: $PARAMETER_CAN_DRIVER"
	fi
	if [ $PARAMETER_RS232_DRIVER != "UseConfigFile" ] ; then
		USE_RS232_DRIVER=$PARAMETER_RS232_DRIVER
		#echo "Use Parameter value for rs232 driver: $PARAMETER_RS232_DRIVER"
	fi

  if [ $USE_TARGET_SYSTEM = "pc_win32" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_PC"
  	GENERATE_FILES_ROOT_DIR="$1/../Dev-C++/"
  elif [ $USE_TARGET_SYSTEM = "pc_linux" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_PC"
  	GENERATE_FILES_ROOT_DIR="$1/kdevelop_make/"
  elif [ $USE_TARGET_SYSTEM = "esx" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_ESX"
  	GENERATE_FILES_ROOT_DIR="$1/../EDE/"
  elif [ $USE_TARGET_SYSTEM = "esxu" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_ESXu"
  	GENERATE_FILES_ROOT_DIR="$1/../EDE/"
  elif [ $USE_TARGET_SYSTEM = "c2c" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_C2C"
  	GENERATE_FILES_ROOT_DIR="$1/../EDE/"
  elif [ $USE_TARGET_SYSTEM = "imi" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_IMI"
  	GENERATE_FILES_ROOT_DIR="$1/../EDE/"
  elif [ $USE_TARGET_SYSTEM = "pm167" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_PM167"
  	GENERATE_FILES_ROOT_DIR="$1/../EDE/"
  elif [ $USE_TARGET_SYSTEM = "Dj1" ] ; then
		USE_SYSTEM_DEFINE="SYSTEM_DJ1"
  	GENERATE_FILES_ROOT_DIR="$1/../EDE/"
  fi
  GENERATE_FILES_ROOT_DIR=`echo "$GENERATE_FILES_ROOT_DIR" | sed -e 's/\/[0-9a-zA-Z_+\-]*\/\.\.//g' -e 's/\\[0-9a-zA-Z_+\-]*\\\.\.//g'`
  # echo "Create project for $USE_TARGET_SYSTEM in $GENERATE_FILES_ROOT_DIR"

  # now call the function create_filelist() which build
  # the file list based on the varibles defined above
  create_filelist $GENERATE_FILES_ROOT_DIR $2
  # call function which build the file list for the unit
  # tests
  create_utest_filelist

	# call function to create project specific config file
	create_autogen_project_config $GENERATE_FILES_ROOT_DIR $2

  if [ $USE_TARGET_SYSTEM = "pc_linux" ] ; then
    # call function to create the Makefile in the project dir
    create_makefile $GENERATE_FILES_ROOT_DIR $2
	  # check if a win32 project file whould be created
  elif [ $USE_TARGET_SYSTEM = "pc_win32" ] ; then
  	create_DevCCPrj $GENERATE_FILES_ROOT_DIR $2
    create_VCPrj $GENERATE_FILES_ROOT_DIR $2
  else
  	create_EdePrj $GENERATE_FILES_ROOT_DIR $2
  fi

	# jump to initial directory on start of script
  cd $3
}





# Usage: usage
# Print the usage.
usage () {
    cat <<EOF
Usage: $0 [OPTION] project_config_file
Create filelist, Makefile and configuration settings for a IsoAgLib project.

  -h, --help                        print this message and exit.
  --doxygen-export-directory=DIR    write the filelist and configuration files with doxygen documentation
                                    blocks to the given directory instead of the default directory of all generated files.
  --IsoAgLib-root=DIR               use the given root directory instead of the entry in the selected configuration file.
  --target-system=TARGET            produce the project definition files for the selected TARGET instead of the
                                    target which is specified in the configuration file
                                    ( "pc_linux"|"pc_win32"|"esx"|"esxu"|"c2c"|"imi"|"pm167"|"Dj1"|"mitron167" ).
  --pc-can-driver=CAN_DRIVER        produce the project definition files for the selected CAN_DRIVER if the project shall run on PC
                                    ( "simulating"|"sys"|"msq_server"|"socket_server", deprecated: "rte"|"vector_canlib"|"vector_xl_drv_lib"|"sontheim" ).
  --pc-rs232-driver=RS232_DRIVER    produce the project definition files for the selected RS232_DRIVER if the project shall run on PC
                                    ( "simulating"|"sys"|"rte" ).
  --little-endian-cpu               select configuration for LITTLE ENDIAN CPU type
  --big-endian-cpu                  select configuration for BIG ENDIAN CPU type
  --with-makefile-skeleton=filename define project specific MakefileSkeleton text file which is used as base for
                                    Makefiles (default: MakefileSkeleton.txt in the same directory as this script)

$0 parses the selected project configuration file and overwrites the default values for all contained settings.
It collects then the corresponding files which can then be imported to an individual IDE.
Additionally a project specific configuration header is created in the directory xgpl_src/Application_Config with the
name scheme ".config_<project_name>.h". If the #define PRJ_USE_AUTOGEN_CONFIG is set to ".config_<project_name>.h",
the central configuration header xgpl_src/IsoAgLib/isoaglib_config.h will include this header.
Please set additionally the SYSTEM_FOO for the wanted platform - $0 will output the correct define at the end of the
run.
Thus with these two DEFINE settings, the compiler can generate a clean running executable / HEX.

Report bugs to <Achim.Spangler@osb-ag.de>.
EOF
}

if [ $# -lt 1 ] ; then
	echo "ERROR! You must at least specify the configuration file for your project as parameter"
	exit 1
fi

# Check the arguments.
for option in "$@"; do
	case "$option" in
		-h | --help)
			usage
			exit 0 ;;
		--doxygen-export-directory=*)
			DOXYGEN_EXPORT_DIR_1=`echo "$option" | sed -e 's/--doxygen-export-directory=//'`
			mkdir -p "$DOXYGEN_EXPORT_DIR_1"
			CALL_DIR=`pwd`
			cd "$DOXYGEN_EXPORT_DIR_1"
			DOXYGEN_EXPORT_DIR=`pwd`
			cd $CALL_DIR ;;
		--IsoAgLib-root=*)
			ISOAGLIB_ROOT=`echo "$option" | sed 's/--IsoAgLib-root=//'`
			if [ ! -f "$ISOAGLIB_ROOT/library/xgpl_src/IsoAgLib/isoaglib_config.h" ] ; then
				echo "Directory $ISOAGLIB_ROOT doesn't contain valid IsoAgLib directory root. The file xgpl_src/IsoAgLib/isoaglib_config.h can't be found." 1>&2
				usage
				exit 1
			else
				CALL_DIR=`pwd`
				cd $ISOAGLIB_ROOT
				ISOAGLIB_ROOT=`pwd`
				cd $CALL_DIR
			fi ;;
		--target-system=*)
			PARAMETER_TARGET_SYSTEM=`echo "$option" | sed 's/--target-system=//'`
			;;
		--pc-can-driver=*)
			PARAMETER_CAN_DRIVER=`echo "$option" | sed 's/--pc-can-driver=//'`
			;;
		--pc-rs232-driver=*)
			PARAMETER_RS232_DRIVER=`echo "$option" | sed 's/--pc-rs232-driver=//'`
			;;
		--little-endian-cpu)
			PARAMETER_LITTLE_ENDIAN_CPU=1
			;;
		--big-endian-cpu)
			PARAMETER_LITTLE_ENDIAN_CPU=0
			;;
		--with-makefile-skeleton=*)
			RootDir=`pwd`
			MAKEFILE_SKELETON_FILE=$RootDir/`echo "$option" | sed 's/--with-makefile-skeleton=//'`
			;;
		--with-makefile-app-skeleton=*)
			RootDir=`pwd`
			MAKEFILE_APP_SKELETON_FILE=$RootDir/`echo "$option" | sed 's/--with-makefile-app-skeleton=//'`
			;;
		-*)
			echo "Unrecognized option $option'" 1>&2
			usage
			exit 1
			;;
    *)
			CONF_FILE=$option
			;;
    esac
done

# check if configuration file exists
if [ ! -f $CONF_FILE ] ; then
	echo "ERROR! configuration file $CONF_FILE does not exist!"
	exit 1
elif [ ! -r $CONF_FILE ] ; then
	echo "ERROR! configuration file $CONF_FILE is not readable!"
	exit 1
fi

START_DIR=`pwd`

cd `dirname $0`
SCRIPT_DIR=`pwd`

cd $START_DIR
cd `dirname $CONF_FILE`
CONF_DIR=`pwd`

cd $START_DIR

# echo "StartDir $START_DIR"
# echo "ScriptDir $SCRIPT_DIR"
# echo "ConfDir $CONF_DIR"

# now import the config setting file
. ./$CONF_FILE

# perform some checks based on user input
# check for correct target system setting
if [ $PARAMETER_TARGET_SYSTEM != "UseConfigFile" ] ; then
	USE_TARGET_SYSTEM=$PARAMETER_TARGET_SYSTEM
fi
case "$USE_TARGET_SYSTEM" in
	pc_linux | pc_win32 | esx | esxu | c2c | imi | pm167 | Dj1 | mitron167)
	;;
	*)
	echo "Unknown target system $USE_TARGET_SYSTEM" 1>&2
	usage
	exit 1 ;;
esac

# check for corrext CAN driver - and automatically adapt to embedded targets
if [ $PARAMETER_CAN_DRIVER != "UseConfigFile" ] ; then
	USE_CAN_DRIVER=$PARAMETER_CAN_DRIVER
	IS_CAN_SERVER=$(echo $PARAMETER_CAN_DRIVER | grep -c "msq_server")
	if [ $IS_CAN_SERVER -gt 0 ] ; then
		PRJ_CAN_DEVICE_FOR_SERVER=$(echo $PARAMETER_CAN_DRIVER | sed 's/msq_server_//g')
		USE_CAN_DRIVER="msq_server"
		PARAMETER_CAN_DRIVER="msq_server"
	fi
fi
#default for not-can_server
CAN_SERVER_FILENAME=$PARAMETER_CAN_DRIVER
case "$USE_CAN_DRIVER" in
	simulating)
		case "$USE_TARGET_SYSTEM" in
			pc_linux | pc_win32)
			;;
			*)
				echo "Override $USE_CAN_DRIVER CAN driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_CAN_DRIVER="sys"
				PARAMETER_CAN_DRIVER="sys"
			;;
		esac
	;;
	sys)
		case "$USE_TARGET_SYSTEM" in
			pc_linux | pc_win32)
				echo "A selection of sys CAN_DRIVER is only applicable for embedded targets." 1>&2
				usage
				exit 1
			;;
			*)
			;;
		esac
		# enhanced CAN HAL is not yet supported for the known embedded targets
		PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
	;;
	rte)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
			;;
			pc_win32)
				echo "RTE CAN driver can only used for target pc_linux" 1>&2
				usage
				exit 1
			;;
			*)
				echo "Override $USE_CAN_DRIVER CAN driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_CAN_DRIVER="sys"
				PARAMETER_CAN_DRIVER="sys"
			;;
		esac
	;;
	msq_server)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
			;;
			pc_win32)
				echo "Server Client CAN driver can only used for target pc_linux" 1>&2
				usage
				exit 1
			;;
			*)
				echo "Override $USE_CAN_DRIVER CAN driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_CAN_DRIVER="sys"
				PARAMETER_CAN_DRIVER="sys"
			;;
		esac
		# make sure, that PRJ_CAN_DEVICE_FOR_SERVER is automatically set, when not yet defined
		if [ "A$PRJ_CAN_DEVICE_FOR_SERVER" = "A" ] ; then
			case $PRJ_DEFINES in
				*SYSTEM_A1*)
					PRJ_CAN_DEVICE_FOR_SERVER="A1"
					;;
				*)
					PRJ_CAN_DEVICE_FOR_SERVER="pc"
					;;
			esac
		fi
		CAN_SERVER_FILENAME=${USE_CAN_DRIVER}_${PRJ_CAN_DEVICE_FOR_SERVER}
	;;
	socket_server)
		if [ "A$PRJ_CAN_DEVICE_FOR_SERVER" = "A" ] ; then
			case $PRJ_DEFINES in
				*SYSTEM_A1*)
					PRJ_CAN_DEVICE_FOR_SERVER="A1"
					;;
				*)
					PRJ_CAN_DEVICE_FOR_SERVER="pc"
					;;
			esac
		fi
		CAN_SERVER_FILENAME=can_server_sock_${PRJ_CAN_DEVICE_FOR_SERVER}
	;;
	vector_canlib)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
				echo "Vector CANLIB driver can only used for target pc_win32" 1>&2
				usage
				exit 1
			;;
			pc_win32)
			;;
			*)
				echo "Override $USE_CAN_DRIVER CAN driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_CAN_DRIVER="sys"
				PARAMETER_CAN_DRIVER="sys"
			;;
		esac
		# enhanced CAN HAL is not yet supported for vector_canlib
		PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
	;;
	vector_xl_drv_lib)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
				echo "Vector XL Driver Library can be only used for target pc_win32" 1>&2
				usage
				exit 1
			;;
			pc_win32)
			;;
			*)
				echo "Override $USE_CAN_DRIVER CAN driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_CAN_DRIVER="sys"
				PARAMETER_CAN_DRIVER="sys"
			;;
		esac
		# enhanced CAN HAL is not yet supported for vector_xl_drv_lib
		PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
	;;
	sontheim)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
				echo "Sontheim Driver Library can be only used for target pc_win32" 1>&2
				usage
				exit 1
			;;
			pc_win32)
				echo "The contents of the Sontheim CAN API ZIP file should be extracted in directory $USE_WIN32_HEADER_DIRECTORY/Sontheim so that CANAPI.DLL is in that directory!"
			;;
			*)
				echo "Override $USE_CAN_DRIVER CAN driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_CAN_DRIVER="sys"
				PARAMETER_CAN_DRIVER="sys"
			;;
		esac
		# enhanced CAN HAL is not yet supported for sontheim
		PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
	;;
	*)
		echo "Unknown CAN driver $USE_CAN_DRIVER" 1>&2
		usage
		exit 1
		;;
esac

case "$PRJ_CAN_DEVICE_FOR_SERVER" in
	rte)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
			;;
			pc_win32)
				echo "RTE CAN driver can only used for target pc_linux" 1>&2
				usage
				exit 1
			;;
		esac
	;;
	vector_canlib)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
				echo "Vector CANLIB driver can only used for target pc_win32" 1>&2
				usage
				exit 1
			;;
			pc_win32)
			;;
		esac
		# enhanced CAN HAL is not yet supported for vector_canlib
		PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
	;;
	vector_xl)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
				echo "Vector XL Driver Library can be only used for target pc_win32" 1>&2
				usage
				exit 1
			;;
			pc_win32)
			;;
		esac
		# enhanced CAN HAL is not yet supported for vector_xl_drv_lib
		PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
	;;
	sontheim)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
				echo "Sontheim Driver Library can be only used for target pc_win32" 1>&2
				usage
				exit 1
			;;
			pc_win32)
				echo "The contents of the Sontheim CAN API ZIP file should be extracted in directory $USE_WIN32_HEADER_DIRECTORY/Sontheim so that CANAPI.DLL is in that directory!"
			;;
		esac
		# enhanced CAN HAL is not yet supported for sontheim
		PRJ_SYSTEM_WITH_ENHANCED_CAN_HAL=0
	;;
esac



if [ $PARAMETER_RS232_DRIVER != "UseConfigFile" ] ; then
	USE_RS232_DRIVER=$PARAMETER_RS232_DRIVER
fi
case "$USE_RS232_DRIVER" in
	simulating)
		case "$USE_TARGET_SYSTEM" in
			pc_linux | pc_win32)
			;;
			*)
				echo "Override $USE_RS232_DRIVER RS232 driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_RS232_DRIVER="sys"
				PARAMETER_RS232_DRIVER="sys"
			;;
		esac
	;;
	sys)
	;;
	rte)
		case "$USE_TARGET_SYSTEM" in
			pc_linux)
			;;
			pc_win32)
				USE_RS232_DRIVER="sys"
				echo "RTE RS232 driver can only used for target pc_linux -> Override by sys"
			;;
			*)
				echo "Override $USE_RS232_DRIVER RS232 driver by system driver for embedded target $USE_TARGET_SYSTEM"
				USE_RS232_DRIVER="sys"
				PARAMETER_RS232_DRIVER="sys"
			;;
		esac
	;;
	*)
		echo "Unknown RS232 driver $USE_RS232_DRIVER" 1>&2
		usage
		exit 1
		;;
esac

# check for little/big endian setting
if [ "A$PARAMETER_LITTLE_ENDIAN_CPU" != "A" ] ; then
  USE_LITTLE_ENDIAN_CPU=$PARAMETER_LITTLE_ENDIAN_CPU
fi


# call the main function to create
# Makefile for defined config setting
perform_everything "$CONF_DIR" "$SCRIPT_DIR" "$START_DIR"


if [ $USE_LITTLE_ENDIAN_CPU -lt 1 ] ; then
  echo "Configure for BIG ENDIAN CPU"
else
  echo "Configure for LITTLE ENDIAN CPU"
fi


echo "Please set the following DEFINES for your compiler in the project settings:"
echo "$USE_SYSTEM_DEFINE PRJ_USE_AUTOGEN_CONFIG=config_$PROJECT.h $PRJ_DEFINES"
echo "Please add also the main application path ";
    for EACH_REL_APP_PATH in $REL_APP_PATH ; do
echo "$ISO_AG_LIB_INSIDE/$EACH_REL_APP_PATH;";
    done
echo " to the INCLUDE search path of the compiler"
echo "( Note: All this is already set for Win32 Dev-C++ and Visual C++ version 6.0 and above DSP project file, LINUX make, Kdevelop3 and Tasking EDE )"

if [ "A$DOXYGEN_EXPORT_DIR" != "A" ] ; then
	# doxygen export is specified -> copy config file there with suitable doc block
	CONF_BASE=`basename $CONF_FILE`
	CONFIG_SPEC_DOXYGEN_READY="$DOXYGEN_EXPORT_DIR/spec"'__'"$CONF_BASE"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER-doc.txt"
	#echo "/**" > $CONFIG_SPEC_DOXYGEN_READY
	#echo "* \section PrjSpec$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of configuration settings for $PROJECT ." >> $CONFIG_SPEC_DOXYGEN_READY
	#echo "* This is only a copy with doxygen ready comment blocks from the original file in IsoAgLib/compiler_projeckdevelop_make/ " >> $CONFIG_SPEC_DOXYGEN_READY
	#echo "* Use the file $CONF_FILE in this directory as input file for $0 to create the project generation files." >> $CONFIG_SPEC_DOXYGEN_READY
	#echo "*/" >> $CONFIG_SPEC_DOXYGEN_READY
	#echo "/*@{*/" >> $CONFIG_SPEC_DOXYGEN_READY
#	cat $CONF_FILE >> $CONFIG_SPEC_DOXYGEN_READY
	#sed -e "s/USE_TARGET_SYSTEM=\".*/USE_TARGET_SYSTEM=\"$USE_TARGET_SYSTEM\"/g" -e "s/USE_CAN_DRIVER=\".*/USE_CAN_DRIVER=\"$USE_CAN_DRIVER\"/g" -e "s/USE_RS232_DRIVER=\".*/USE_RS232_DRIVER=\"$USE_RS232_DRIVER\"/g" $CONF_FILE > /tmp/$CONF_BASE
	#cat /tmp/$CONF_BASE >> $CONFIG_SPEC_DOXYGEN_READY
	#rm -f /tmp/$CONF_BASE
	#echo "/*@}*/" >> $CONFIG_SPEC_DOXYGEN_READY

	echo -e "$ENDLINE$ENDLINE \section PrjSpec$PROJECT"'__'"$USE_TARGET_SYSTEM"'__'"$CAN_SERVER_FILENAME"'__'"$USE_RS232_DRIVER List of configuration settings for $PROJECT with CAN Driver $USE_CAN_DRIVER and RS232 Driver $USE_RS232_DRIVER" > $CONFIG_SPEC_DOXYGEN_READY
	echo " This is only a copy with doxygen ready comment blocks from the original file in IsoAgLib/compiler_projeckdevelop_make/ " >> $CONFIG_SPEC_DOXYGEN_READY
	echo " Use the file $CONF_FILE in this directory as input file for $0 to create the project generation files." >> $CONFIG_SPEC_DOXYGEN_READY
	echo "\code" >> $CONFIG_SPEC_DOXYGEN_READY
	sed -e "s/USE_TARGET_SYSTEM=\".*/USE_TARGET_SYSTEM=\"$USE_TARGET_SYSTEM\"/g" -e "s/USE_CAN_DRIVER=\".*/USE_CAN_DRIVER=\"$USE_CAN_DRIVER\"/g" -e "s/USE_RS232_DRIVER=\".*/USE_RS232_DRIVER=\"$USE_RS232_DRIVER\"/g" $SCRIPT_DIR/$CONF_FILE > /tmp/$CONF_BASE
	cat /tmp/$CONF_BASE >> $CONFIG_SPEC_DOXYGEN_READY
	echo "\endcode" >> $CONFIG_SPEC_DOXYGEN_READY
	rm -f /tmp/$CONF_BASE

fi