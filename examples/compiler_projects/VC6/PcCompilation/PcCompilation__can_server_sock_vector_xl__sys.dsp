# Microsoft Developer Studio Project File - Name="PcCompilation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=PcCompilation - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE
!MESSAGE NMAKE /f "PcCompilation.mak".
!MESSAGE
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE
!MESSAGE NMAKE /f "PcCompilation.mak" CFG="PcCompilation - Win32 Debug"
!MESSAGE
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE
!MESSAGE "PcCompilation - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "PcCompilation - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PcCompilation - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "C:\STLport\stlport" /I "..\..\..\.." /I "..\..\..\..\library\xgpl_src" /I "C:\Development\XL Driver Library\bin" /I "..\..\..\..\examples\src\GeneralTest\PcCompilation" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS"  /D "SYSTEM_PC_VC" /D "PRJ_USE_AUTOGEN_CONFIG=config_PcCompilation.h" /D "XL_HWTYPE_VIRTUAL" /D DEBUG /D ALLOW_PROPRIETARY_MESSAGES_ON_STANDARD_PROTOCOL_CHANNEL /D USE_CAN_SEND_DELAY_MEASUREMENT /D PROCESS_INVALID_PACKETS /D ENABLE_NMEA_2000_MULTI_PACKET /D ENABLE_MULTIPACKET_VARIANT_FAST_PACKET /D USE_CAN_MEASURE_BUSLOAD /D DEBUG_CAN_BUFFER_FILLING /D USE_PCAN_LIB /YX /FD /TP /c
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_PcCompilation.h" /d "XL_HWTYPE_VIRTUAL" /D DEBUG /D ALLOW_PROPRIETARY_MESSAGES_ON_STANDARD_PROTOCOL_CHANNEL /D USE_CAN_SEND_DELAY_MEASUREMENT /D PROCESS_INVALID_PACKETS /D ENABLE_NMEA_2000_MULTI_PACKET /D ENABLE_MULTIPACKET_VARIANT_FAST_PACKET /D USE_CAN_MEASURE_BUSLOAD /D DEBUG_CAN_BUFFER_FILLING /D USE_PCAN_LIB
# ADD RSC /l 0x407 /d "NDEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_PcCompilation.h" /d "XL_HWTYPE_VIRTUAL" /D DEBUG /D ALLOW_PROPRIETARY_MESSAGES_ON_STANDARD_PROTOCOL_CHANNEL /D USE_CAN_SEND_DELAY_MEASUREMENT /D PROCESS_INVALID_PACKETS /D ENABLE_NMEA_2000_MULTI_PACKET /D ENABLE_MULTIPACKET_VARIANT_FAST_PACKET /D USE_CAN_MEASURE_BUSLOAD /D DEBUG_CAN_BUFFER_FILLING /D USE_PCAN_LIB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib ws2_32.lib /nologo /subsystem:console /machine:I386 C:\Development\XL Driver Library\bin /libpath:"C:\STLport\lib"

!ELSEIF  "$(CFG)" == "PcCompilation - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "C:\STLport\stlport" /I "..\..\..\.." /I "..\..\..\..\library\xgpl_src" /I "C:\Development\XL Driver Library\bin" /I "..\..\..\..\examples\src\GeneralTest\PcCompilation" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS"  /D "SYSTEM_PC_VC" /D "PRJ_USE_AUTOGEN_CONFIG=config_PcCompilation.h" /D "XL_HWTYPE_VIRTUAL" /D DEBUG /D ALLOW_PROPRIETARY_MESSAGES_ON_STANDARD_PROTOCOL_CHANNEL /D USE_CAN_SEND_DELAY_MEASUREMENT /D PROCESS_INVALID_PACKETS /D ENABLE_NMEA_2000_MULTI_PACKET /D ENABLE_MULTIPACKET_VARIANT_FAST_PACKET /D USE_CAN_MEASURE_BUSLOAD /D DEBUG_CAN_BUFFER_FILLING /D USE_PCAN_LIB /YX /FD /TP /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_PcCompilation.h" /d "XL_HWTYPE_VIRTUAL" /D DEBUG /D ALLOW_PROPRIETARY_MESSAGES_ON_STANDARD_PROTOCOL_CHANNEL /D USE_CAN_SEND_DELAY_MEASUREMENT /D PROCESS_INVALID_PACKETS /D ENABLE_NMEA_2000_MULTI_PACKET /D ENABLE_MULTIPACKET_VARIANT_FAST_PACKET /D USE_CAN_MEASURE_BUSLOAD /D DEBUG_CAN_BUFFER_FILLING /D USE_PCAN_LIB
# ADD RSC /l 0x407 /d "_DEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_PcCompilation.h" /d "XL_HWTYPE_VIRTUAL" /D DEBUG /D ALLOW_PROPRIETARY_MESSAGES_ON_STANDARD_PROTOCOL_CHANNEL /D USE_CAN_SEND_DELAY_MEASUREMENT /D PROCESS_INVALID_PACKETS /D ENABLE_NMEA_2000_MULTI_PACKET /D ENABLE_MULTIPACKET_VARIANT_FAST_PACKET /D USE_CAN_MEASURE_BUSLOAD /D DEBUG_CAN_BUFFER_FILLING /D USE_PCAN_LIB
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept C:\Development\XL Driver Library\bin /libpath:"C:\STLport\lib"

!ENDIF

# Begin Target

# Name "PcCompilation - Win32 Release"
# Name "PcCompilation - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cc;cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\virtualDrivers\rs232\rs232_over_can.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\datastreams\targetfilestreamoutput_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\datastreams\targetfilestreaminput_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\actor\actor_target_extensions.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\sensor\sensor_target_extensions.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\rs232\impl\rs232io_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\filestreamoutput_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\filestreaminput_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\volatilememory_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\digitalo_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\actor_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\actoro_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\actorbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\sensorbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\counteri_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\sensor_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\digitali_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\analogirangecheck_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\sensori_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\analogi_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\iliberr_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\util_funcs.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\write_central_fifo.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\canfifo_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\eeprom\eeprom_target_extensions.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\eeprom\pc_eeditor_can.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\eeprom\pc_eeditor_rs232.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\system\system_target_extensions.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\hal_can_interface.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\target_extension_can_client_sock.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\igenericdata_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\impl\proprietarymessagehandler_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\impl\proprietarymessageclient_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\streamchunk_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multisendpkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\chunk_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\stream_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multisend_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\canpkgext_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multireceive_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\ischedulertask_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\scheduler_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\schedulertask_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\schedulerentry_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\istate_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\identitem_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofilterbox_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoitem_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isorequestpgn_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isosystempkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofiltermanager_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoname_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\baseitem_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isomonitor_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\processdatachangehandler_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleSetpoint\impl\procdataremotesimplesetpoint_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\StdMeasureElements\impl\measureprogremote_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\impl\procdataremotebase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleSetpointElements\impl\simplemanagesetpointremote_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleMeasure\impl\procdataremotesimplemeasure_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\StdSetpointElements\impl\setpointremote_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleMeasureElements\impl\simplemanagemeasureprogremote_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\Std\impl\procdataremote_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measureprogbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measuresubprog_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processelementbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procdatabase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procident_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processpkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processcmd_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\process_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleSetpoint\impl\procdatalocalsimplesetpoint_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\measureproglocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\managemeasureproglocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\impl\procdatalocalbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleSetpointElements\impl\simplemanagesetpointlocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleMeasure\impl\procdatalocalsimplemeasure_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleMeasureSetpoint\impl\procdatalocalsimplesetpointsimplemeasure_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdSetpointElements\impl\setpointlocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\Std\impl\procdatalocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointregister_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part10_TaskController_Client\impl\devpropertyhandler_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\isoterminalpkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectnumbervariable_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectellipse_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectmeter_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectauxiliaryfunction_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectlinearbargraph_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectrectangle_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectlineattributes_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectstring_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectworkingset_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobject_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectarchedbargraph_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputattributes_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectdatamask_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtserverinstance_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectkey_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectoutputlist_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputnumber_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectobjectpointer_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectalarmmask_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectoutputnumber_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectfillattributes_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectcontainer_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectstringvariable_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectauxiliaryinput_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectfontattributes_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\isoterminal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputlist_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectsoftkeymask_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectmacro_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectbutton_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectpicturegraphic_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectline_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectoutputstring_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputstring_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtclientservercommunication_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputboolean_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectpolygon_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobject_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\traccert_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\traclight_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracptosetpoint_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracguidancecommand_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracmovesetpoint_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracguidance_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracaux_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\tracgeneral_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\tracpto_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\basecommon_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\timeposgps_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\tracmove_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\eeprom\impl\eepromio_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\system\impl\system_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canio_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canpkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\cancustomer_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\msgobj_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\filterbox_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\ident_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\examples\src\GeneralTest\PcCompilation\PcCompilation.cpp
# End Source File

# Begin Source File
SOURCE=C:\Development\XL
# End Source File

# Begin Source File
SOURCE=Driver
# End Source File

# Begin Source File
SOURCE=Library\bin\vxlapi.lib
# End Source File

# End Group

# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\rs232.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\virtualDrivers\rs232\rs232_over_can.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\actor.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\sensor.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\rs232\rs232.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\rs232\rs232_target_extensions.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\datastreams\targetfilestreaminput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\datastreams\datastreams.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\datastreams\targetfilestreamoutput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\actor\actor.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\actor\actor_target_extensions.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\sensor\sensor.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\pc\sensor\sensor_target_extensions.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\hal\datastreams.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\rs232\impl\rs232io_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\rs232\irs232io_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\streaminput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\streamoutput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\filestreaminput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\volatilememory_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\filestreamoutput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\iactoro_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\digitalo_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\actorbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\actor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\impl\actoro_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\iactor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\actor\idigitalo_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\ianalogirangecheck_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\digitali_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\analogirangecheck_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\analogi_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\sensori_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\sensor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\counteri_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\impl\sensorbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\isensor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\ianalogi_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\idigitali_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\isensori_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\sensor\icounteri_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\iliberr_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\singleton_container_decl.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\singleton.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\singleton_container.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\util_funcs.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\compiler_adaptation.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\config.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\iutil_funcs.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\convert.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\canfifo_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\icanfifo.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\write_central_fifo.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\config.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\eeprom.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\system.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\eeprom\eeprom_target_extensions.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\eeprom\pc_eeditor_rs232.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\eeprom\pc_eeditor_can.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\eeprom\eeprom.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\system\system.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\system\system_target_extensions.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\config.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\can_server.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\hal_can_interface.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\can_typedef.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\can_target_extensions.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\can.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\typedef.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\errcodes.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\can.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\isoaglib_config.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\typedef.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\impl\proprietarymessagehandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\impl\proprietarymessageclient_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\igenericdata_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\iproprietarymessageclient_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\ext\ProprietaryCan\iproprietarymessagehandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\istream_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\imultireceive_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\imultisendstreamer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\chunk_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\stream_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multisend_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\canpkgext_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multireceive_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multisendpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\streamchunk_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\imultisend_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\ischedulertask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\schedulertask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\schedulerentry_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\scheduler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\ischeduler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\istate_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iidentitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisoname_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisofilter_s.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isomonitor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofilterbox_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\istate_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isorequestpgn_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\baseitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isosystempkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoname_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\identitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofiltermanager_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\saclaimhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isorequestpgnhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisomonitor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisoitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisofiltermanager_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\iprocess_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleSetpoint\impl\procdataremotesimplesetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleSetpoint\iprocdataremotesimplesetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\StdMeasureElements\imeasureprogremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\StdMeasureElements\impl\measureprogremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\impl\procdataremotebase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleSetpointElements\isimplemanagesetpointremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleSetpointElements\impl\simplemanagesetpointremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleMeasure\impl\procdataremotesimplemeasure_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleMeasure\iprocdataremotesimplemeasure_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\StdSetpointElements\impl\setpointremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\StdSetpointElements\isetpointremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\SimpleMeasureElements\impl\simplemanagemeasureprogremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\Std\impl\procdataremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\Std\iprocdataremote_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measuresubprog_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measureprogbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\iprocesscmd_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processwsmtaskmsghandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procident_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procdatabase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\proc_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\process_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processelementbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processcmd_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleSetpoint\impl\procdatalocalsimplesetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleSetpoint\iprocdatalocalsimplesetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\imeasureproglocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\managemeasureproglocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\measureproglocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\impl\procdatalocalbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleSetpointElements\impl\simplemanagesetpointlocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleSetpointElements\isimplemanagesetpointlocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleMeasure\impl\procdatalocalsimplemeasure_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleMeasure\iprocdatalocalsimplemeasure_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleMeasureSetpoint\impl\procdatalocalsimplesetpointsimplemeasure_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\SimpleMeasureSetpoint\iprocdatalocalsimplesetpointsimplemeasure_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdSetpointElements\isetpointlocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdSetpointElements\impl\setpointlocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\Std\impl\procdatalocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\Std\iprocdatalocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\proc_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\processdatachangehandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\isetpointregister_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointregister_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\elementddi_s.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part10_TaskController_Client\idevpropertyhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part10_TaskController_Client\impl\devpropertyhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobject_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectellipse_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectinputboolean_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectinputnumber_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectpolygon_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectstring_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\iisoterminal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectfillattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectstringvariable_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectobjectpointer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectmeter_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectnumbervariable_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectfontattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivttypes.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectinputattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectinputstring_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputnumber_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectfontattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectstring_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtclientservercommunication_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\isoterminalpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vttypes.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectbutton_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectrectangle_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectlinearbargraph_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectoutputnumber_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectmacro_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectpolygon_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectobjectpointer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectnumbervariable_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtserverinstance_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectstringvariable_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectfillattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectkey_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectalarmmask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectellipse_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputlist_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\isoterminal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectmeter_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectworkingset_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectlineattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectoutputstring_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputboolean_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectdatamask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectauxiliaryinput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputstring_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectauxiliaryfunction_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectinputattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectsoftkeymask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobject_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectcontainer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectarchedbargraph_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectpicturegraphic_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectoutputlist_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\impl\vtobjectline_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectoutputstring_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectalarmmask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectmacro_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectarchedbargraph_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectcontainer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectrectangle_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectline_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\iisoterminalobjectpool_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectlineattributes_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtincludes.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectworkingset_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectauxiliaryinput_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectinputlist_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectpicturegraphic_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectoutputnumber_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectoutputlist_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtclientservercommunication_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectsoftkeymask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectmask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectkey_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectauxiliaryfunction_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectbutton_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectdatamask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part6_VirtualTerminal_Client\ivtobjectlinearbargraph_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\itracptosetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracguidancecommand_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\traclight_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\traccert_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracptosetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracaux_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracmovesetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\impl\tracguidance_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\itraccert_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\itracaux_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\itracguidancecommand_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\itracguidance_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\itracmovesetpoint_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ext\itraclight_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\itracgeneral_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\itracpto_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\tracmove_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\basecommon_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\tracgeneral_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\timeposgps_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\impl\tracpto_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\itracmove_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\ibasetypes.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ApplicationLayer\itimeposgps_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\eeprom\ieepromio_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\eeprom\impl\eepromio_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\system\impl\system_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\system\isystem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\icanio_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\iident_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\cancustomer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\ident_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\filterbox_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\msgobj_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canio_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\icancustomer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\icanpkg_c.h
# End Source File

# Begin Source File
SOURCE=C:\Development\XL
# End Source File

# Begin Source File
SOURCE=Driver
# End Source File

# Begin Source File
SOURCE=Library\bin\vxlapi.h
# End Source File

# End Group
# End Target
# End Project