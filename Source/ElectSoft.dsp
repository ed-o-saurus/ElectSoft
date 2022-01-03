# Microsoft Developer Studio Project File - Name="ElectSoft" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ElectSoft - Win32 Sim_Ballot
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ElectSoft.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ElectSoft.mak" CFG="ElectSoft - Win32 Sim_Ballot"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ElectSoft - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ElectSoft - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ElectSoft - Win32 Sim_Ballot" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ElectSoft - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ElectSoft - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "ElectSoft - Win32 Sim_Ballot"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ElectSoft___Win32_Sim_Ballot"
# PROP BASE Intermediate_Dir "ElectSoft___Win32_Sim_Ballot"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Sim_Ballot"
# PROP Intermediate_Dir "Sim_Ballot"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_SIM_BALLOT" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ElectSoft - Win32 Release"
# Name "ElectSoft - Win32 Debug"
# Name "ElectSoft - Win32 Sim_Ballot"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlignDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BallotOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\BallotPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CommSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\Count.cpp
# End Source File
# Begin Source File

SOURCE=.\CountDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CountReport.cpp
# End Source File
# Begin Source File

SOURCE=.\ElectSoft.cpp
# End Source File
# Begin Source File

SOURCE=.\ElectSoft.rc
# End Source File
# Begin Source File

SOURCE=.\ElectSoftDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ElectSoftView.cpp
# End Source File
# Begin Source File

SOURCE=.\FillGPL.cpp
# End Source File
# Begin Source File

SOURCE=.\Group.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintBallot.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintBallotDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Printing.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintRace.cpp
# End Source File
# Begin Source File

SOURCE=.\RaceDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistyInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanBallot.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanBallotDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ScannerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanning.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanRace.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Student.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeServerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeSocket.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlignDialog.h
# End Source File
# Begin Source File

SOURCE=.\BallotOrder.h
# End Source File
# Begin Source File

SOURCE=.\BallotPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\CommSettings.h
# End Source File
# Begin Source File

SOURCE=.\Count.h
# End Source File
# Begin Source File

SOURCE=.\CountDialog.h
# End Source File
# Begin Source File

SOURCE=.\CountReport.h
# End Source File
# Begin Source File

SOURCE=.\ElectSoft.h
# End Source File
# Begin Source File

SOURCE=.\ElectSoftDoc.h
# End Source File
# Begin Source File

SOURCE=.\ElectSoftView.h
# End Source File
# Begin Source File

SOURCE=.\Group.h
# End Source File
# Begin Source File

SOURCE=.\PrintBallot.h
# End Source File
# Begin Source File

SOURCE=.\PrintBallotDialog.h
# End Source File
# Begin Source File

SOURCE=.\PrinterInterface.h
# End Source File
# Begin Source File

SOURCE=.\Printing.h
# End Source File
# Begin Source File

SOURCE=.\PrintRace.h
# End Source File
# Begin Source File

SOURCE=.\RaceDialog.h
# End Source File
# Begin Source File

SOURCE=.\RegistyInterface.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScanBallot.h
# End Source File
# Begin Source File

SOURCE=.\ScanBallotDialog.h
# End Source File
# Begin Source File

SOURCE=.\ScannerInterface.h
# End Source File
# Begin Source File

SOURCE=.\Scanning.h
# End Source File
# Begin Source File

SOURCE=.\ScanRace.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Student.h
# End Source File
# Begin Source File

SOURCE=.\TimeServerDialog.h
# End Source File
# Begin Source File

SOURCE=.\TimeSocket.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\checkbox.ico
# End Source File
# Begin Source File

SOURCE=.\count.ico
# End Source File
# Begin Source File

SOURCE=.\election.ico
# End Source File
# Begin Source File

SOURCE=.\program.ico
# End Source File
# Begin Source File

SOURCE=.\races.ico
# End Source File
# Begin Source File

SOURCE=.\students.ico
# End Source File
# End Group
# End Target
# End Project
