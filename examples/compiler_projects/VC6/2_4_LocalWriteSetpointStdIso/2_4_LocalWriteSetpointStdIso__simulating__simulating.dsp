# Microsoft Developer Studio Project File - Name="2_4_LocalWriteSetpointStdIso" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=2_4_LocalWriteSetpointStdIso - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE
!MESSAGE NMAKE /f "2_4_LocalWriteSetpointStdIso.mak".
!MESSAGE
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE
!MESSAGE NMAKE /f "2_4_LocalWriteSetpointStdIso.mak" CFG="2_4_LocalWriteSetpointStdIso - Win32 Debug"
!MESSAGE
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE
!MESSAGE "2_4_LocalWriteSetpointStdIso - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "2_4_LocalWriteSetpointStdIso - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "2_4_LocalWriteSetpointStdIso - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2  /I "..\..\..\..\examples\src\Tutorials\2_ProcessData\2_4_LocalWriteSetpointStdIso" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS"  /D "SYSTEM_PC_VC" /D "PRJ_USE_AUTOGEN_CONFIG=config_2_4_LocalWriteSetpointStdIso.h" /YX /FD /TP /c
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_2_4_LocalWriteSetpointStdIso.h"
# ADD RSC /l 0x407 /d "NDEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_2_4_LocalWriteSetpointStdIso.h"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib ws2_32.lib /nologo /subsystem:console /machine:I386  /libpath:"C:\STLport\lib"

!ELSEIF  "$(CFG)" == "2_4_LocalWriteSetpointStdIso - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od  /I "..\..\..\..\examples\src\Tutorials\2_ProcessData\2_4_LocalWriteSetpointStdIso" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS"  /D "SYSTEM_PC_VC" /D "PRJ_USE_AUTOGEN_CONFIG=config_2_4_LocalWriteSetpointStdIso.h" /YX /FD /TP /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_2_4_LocalWriteSetpointStdIso.h"
# ADD RSC /l 0x407 /d "_DEBUG" /d "SYSTEM_PC_VC" /d "PRJ_USE_AUTOGEN_CONFIG=config_2_4_LocalWriteSetpointStdIso.h"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept  /libpath:"C:\STLport\lib"

!ENDIF

# Begin Target

# Name "2_4_LocalWriteSetpointStdIso - Win32 Release"
# Name "2_4_LocalWriteSetpointStdIso - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cc;cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\filterbox_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\cancustomer_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\msgobj_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\ident_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canio_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canpkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\system\impl\system_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\canfifo_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\write_central_fifo.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\target_extension_can_simulating.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\hal_can_interface.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\system\system_target_extensions.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\util_funcs.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\iliberr_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\streamchunk_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\chunk_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\stream_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multireceive_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\canpkgext_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multisendpkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multisend_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointregister_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procident_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processelementbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processpkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\process_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processcmd_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procdatabase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdSetpointElements\impl\setpointlocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\impl\procdatalocalbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\Std\impl\procdatalocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\measureproglocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\managemeasureproglocal_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\processdatachangehandler_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measureprogbase_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measuresubprog_c.cpp
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
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part10_TaskController_Client\impl\devpropertyhandler_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\istate_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoname_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoitem_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isomonitor_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofiltermanager_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isosystempkg_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofilterbox_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\baseitem_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\identitem_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isorequestpgn_c.cpp
# End Source File

# Begin Source File
SOURCE=..\..\..\..\examples\src\Tutorials\2_ProcessData\2_4_LocalWriteSetpointStdIso\2_4_LocalWriteSetpointStdIso.cpp
# End Source File

# End Group

# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\icanpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\iident_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\icanio_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\msgobj_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canio_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\ident_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\cancustomer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\canpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\impl\filterbox_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\can\icancustomer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\system\isystem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\driver\system\impl\system_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\typedef.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\isoaglib_config.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\config.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\write_central_fifo.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\canfifo_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\generic_utils\can\icanfifo.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\config.h
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
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\can\can_server.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\system\system_target_extensions.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\system\system.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\typedef.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\pc\errcodes.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\system.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\hal\can.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\config.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\iutil_funcs.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\singleton.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\impl\singleton_container_decl.h
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
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\convert.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\util\iliberr_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\imultireceive_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\istream_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multisendpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\canpkgext_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\multireceive_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\impl\streamchunk_c.h
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
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\imultisendstreamer_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part3_DataLink\imultisend_c.h
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
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointregister_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdSetpointElements\impl\setpointbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\iprocess_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\elementddi_s.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\proc_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procdatabase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\procident_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processwsmtaskmsghandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\process_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processpkg_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processcmd_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\impl\processelementbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdSetpointElements\isetpointlocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdSetpointElements\impl\setpointlocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\impl\procdatalocalbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\Std\impl\procdatalocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\Std\iprocdatalocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\imeasureproglocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\measureproglocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Local\StdMeasureElements\impl\managemeasureproglocal_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\Remote\impl\procdataremotebase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measuresubprog_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part7_ProcessData\StdMeasureElements\impl\measureprogbase_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\ischeduler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\schedulerentry_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\schedulertask_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Scheduler\impl\scheduler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part10_TaskController_Client\idevpropertyhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part10_TaskController_Client\impl\devpropertyhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisofilter_s.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isomonitor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\identitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofilterbox_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\saclaimhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isorequestpgnhandler_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isosystempkg_c.h
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
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isoname_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\impl\isofiltermanager_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisoname_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisoitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iidentitem_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\istate_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisomonitor_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\IsoAgLib\comm\Part5_NetworkManagement\iisofiltermanager_c.h
# End Source File

# Begin Source File
SOURCE=..\..\..\..\library\xgpl_src\supplementary_driver\driver\datastreams\streaminput_c.h
# End Source File

# End Group
# End Target
# End Project