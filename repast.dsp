# Microsoft Developer Studio Project File - Name="repast" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=repast - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "repast.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "repast.mak" CFG="repast - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "repast - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "repast - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "repast - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "repast - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "repast - Win32 Release"
# Name "repast - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Button.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Commodity.cpp
# End Source File
# Begin Source File

SOURCE=.\Customer.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomerMenuForm.cpp
# End Source File
# Begin Source File

SOURCE=.\DBForm.cpp
# End Source File
# Begin Source File

SOURCE=.\Department.cpp
# End Source File
# Begin Source File

SOURCE=.\Edit.cpp
# End Source File
# Begin Source File

SOURCE=.\ListView.cpp
# End Source File
# Begin Source File

SOURCE=.\login.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginForm.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\manager.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuForm.cpp
# End Source File
# Begin Source File

SOURCE=.\personnel.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# Begin Source File

SOURCE=.\service.cpp
# End Source File
# Begin Source File

SOURCE=.\StaffForm.cpp
# End Source File
# Begin Source File

SOURCE=.\Static.cpp
# End Source File
# Begin Source File

SOURCE=.\Tab.cpp
# End Source File
# Begin Source File

SOURCE=.\TableInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Wind.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Button.h
# End Source File
# Begin Source File

SOURCE=.\childwindowid.h
# End Source File
# Begin Source File

SOURCE=.\ComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Commodity.h
# End Source File
# Begin Source File

SOURCE=.\Customer.h
# End Source File
# Begin Source File

SOURCE=.\CustomerMenuForm.h
# End Source File
# Begin Source File

SOURCE=.\DBForm.h
# End Source File
# Begin Source File

SOURCE=.\Department.h
# End Source File
# Begin Source File

SOURCE=.\Edit.h
# End Source File
# Begin Source File

SOURCE=.\ListView.h
# End Source File
# Begin Source File

SOURCE=.\LoginForm.h
# End Source File
# Begin Source File

SOURCE=.\manager.h
# End Source File
# Begin Source File

SOURCE=.\MenuForm.h
# End Source File
# Begin Source File

SOURCE=.\personnel.h
# End Source File
# Begin Source File

SOURCE=.\RecordSet.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\service.h
# End Source File
# Begin Source File

SOURCE=.\StaffForm.h
# End Source File
# Begin Source File

SOURCE=.\Static.h
# End Source File
# Begin Source File

SOURCE=.\Tab.h
# End Source File
# Begin Source File

SOURCE=.\TableInfo.h
# End Source File
# Begin Source File

SOURCE=.\Wind.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# End Group
# End Target
# End Project
