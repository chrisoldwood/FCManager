# Microsoft Developer Studio Project File - Name="FCManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FCManager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FCManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FCManager.mak" CFG="FCManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FCManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FCManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Win32/FCManager", MAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FCManager - Win32 Release"

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
# ADD CPP /nologo /W4 /WX /GX /O2 /I "..\WCL" /I "..\MDBL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX"AppHeaders.hpp" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /i "..\WCL" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "FCManager - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W4 /WX /Gm /GX /ZI /Od /I "..\WCL" /I "..\MDBL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fr /YX"AppHeaders.hpp" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /i "..\WCL" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FCManager - Win32 Release"
# Name "FCManager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BalSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\BalSheetView.cpp
# End Source File
# Begin Source File

SOURCE=.\BalShtItemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BalShtItemPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubDetailsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExpensesPage.cpp
# End Source File
# Begin Source File

SOURCE=.\FCManager.rc
# End Source File
# Begin Source File

SOURCE=.\FCMApp.cpp
# End Source File
# Begin Source File

SOURCE=.\FCMCmds.cpp
# End Source File
# Begin Source File

SOURCE=.\FCMDB.cpp
# End Source File
# Begin Source File

SOURCE=.\FCMDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\FCMMainWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FCMToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FCMView.cpp
# End Source File
# Begin Source File

SOURCE=.\FixtureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FixturePage.cpp
# End Source File
# Begin Source File

SOURCE=.\Fixtures.cpp
# End Source File
# Begin Source File

SOURCE=.\FixturesView.cpp
# End Source File
# Begin Source File

SOURCE=.\GridViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IncomePage.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Members.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberSubsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MembersView.cpp
# End Source File
# Begin Source File

SOURCE=.\MemNamePage.cpp
# End Source File
# Begin Source File

SOURCE=.\MemStatusPage.cpp
# End Source File
# Begin Source File

SOURCE=.\NamePage.cpp
# End Source File
# Begin Source File

SOURCE=.\NotesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NotesPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OpponentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OpponentPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Opponents.cpp
# End Source File
# Begin Source File

SOURCE=.\OpponentsView.cpp
# End Source File
# Begin Source File

SOURCE=.\PaymentsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PitchCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RefereeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Referees.cpp
# End Source File
# Begin Source File

SOURCE=.\RefereesView.cpp
# End Source File
# Begin Source File

SOURCE=.\RefNamePage.cpp
# End Source File
# Begin Source File

SOURCE=.\SecNamePage.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Stats.cpp
# End Source File
# Begin Source File

SOURCE=.\StatsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\StatTypes.cpp
# End Source File
# Begin Source File

SOURCE=.\Subs.cpp
# End Source File
# Begin Source File

SOURCE=.\SubsView.cpp
# End Source File
# Begin Source File

SOURCE=.\TableGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\TeamSelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TeamSels.cpp
# End Source File
# Begin Source File

SOURCE=.\TeamSelsView.cpp
# End Source File
# Begin Source File

SOURCE=.\TmpStats.cpp
# End Source File
# Begin Source File

SOURCE=.\TmpSubs.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewsBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewsMgr.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\AppHeaders.hpp
# End Source File
# Begin Source File

SOURCE=.\BalSheet.hpp
# End Source File
# Begin Source File

SOURCE=.\BalSheetView.hpp
# End Source File
# Begin Source File

SOURCE=.\BalShtItemDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\BalShtItemPage.hpp
# End Source File
# Begin Source File

SOURCE=.\ClubDetails.hpp
# End Source File
# Begin Source File

SOURCE=.\ClubDetailsDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\ExpensesPage.hpp
# End Source File
# Begin Source File

SOURCE=.\FCMApp.hpp
# End Source File
# Begin Source File

SOURCE=.\FCMCmds.hpp
# End Source File
# Begin Source File

SOURCE=.\FCMDB.hpp
# End Source File
# Begin Source File

SOURCE=.\FCMDoc.hpp
# End Source File
# Begin Source File

SOURCE=.\FCMMainWnd.hpp
# End Source File
# Begin Source File

SOURCE=.\FCMToolBar.hpp
# End Source File
# Begin Source File

SOURCE=.\FCMView.hpp
# End Source File
# Begin Source File

SOURCE=.\FixStats.hpp
# End Source File
# Begin Source File

SOURCE=.\FixStatTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\FixtureDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\FixturePage.hpp
# End Source File
# Begin Source File

SOURCE=.\Fixtures.hpp
# End Source File
# Begin Source File

SOURCE=.\FixturesView.hpp
# End Source File
# Begin Source File

SOURCE=.\GridViewDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\IncomePage.hpp
# End Source File
# Begin Source File

SOURCE=.\MemberDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\Members.hpp
# End Source File
# Begin Source File

SOURCE=.\MemberSubsDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\MembersView.hpp
# End Source File
# Begin Source File

SOURCE=.\MemNamePage.hpp
# End Source File
# Begin Source File

SOURCE=.\MemStats.hpp
# End Source File
# Begin Source File

SOURCE=.\MemStatTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\MemStatusPage.hpp
# End Source File
# Begin Source File

SOURCE=.\NamePage.hpp
# End Source File
# Begin Source File

SOURCE=.\NotesDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\NotesPage.hpp
# End Source File
# Begin Source File

SOURCE=.\OpponentDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\OpponentPage.hpp
# End Source File
# Begin Source File

SOURCE=.\Opponents.hpp
# End Source File
# Begin Source File

SOURCE=.\OpponentsView.hpp
# End Source File
# Begin Source File

SOURCE=.\OppStats.hpp
# End Source File
# Begin Source File

SOURCE=.\OppStatTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\PaymentsPage.hpp
# End Source File
# Begin Source File

SOURCE=.\PitchCtrl.hpp
# End Source File
# Begin Source File

SOURCE=.\PrintViewDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\RefereeDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\Referees.hpp
# End Source File
# Begin Source File

SOURCE=.\RefereesView.hpp
# End Source File
# Begin Source File

SOURCE=.\RefNamePage.hpp
# End Source File
# Begin Source File

SOURCE=.\RefStats.hpp
# End Source File
# Begin Source File

SOURCE=.\RefStatTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SecNamePage.hpp
# End Source File
# Begin Source File

SOURCE=.\StatisticDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\Stats.hpp
# End Source File
# Begin Source File

SOURCE=.\StatsPage.hpp
# End Source File
# Begin Source File

SOURCE=.\StatTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\Subs.hpp
# End Source File
# Begin Source File

SOURCE=.\SubsView.hpp
# End Source File
# Begin Source File

SOURCE=.\TableGrid.hpp
# End Source File
# Begin Source File

SOURCE=.\TeamSelDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\TeamSels.hpp
# End Source File
# Begin Source File

SOURCE=.\TeamSelsView.hpp
# End Source File
# Begin Source File

SOURCE=.\TmpStats.hpp
# End Source File
# Begin Source File

SOURCE=.\TmpSubs.hpp
# End Source File
# Begin Source File

SOURCE=.\ViewDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\ViewsBar.hpp
# End Source File
# Begin Source File

SOURCE=.\ViewsMgr.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\FCManager.rcv
# End Source File
# Begin Source File

SOURCE=.\Icon.ico
# End Source File
# Begin Source File

SOURCE=.\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\views.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\TODO.txt
# End Source File
# End Target
# End Project
