# Microsoft Developer Studio Project File - Name="kinst" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** �ҏW���Ȃ��ł������� **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=kinst - Win32 Debug
!MESSAGE ����͗L����Ҳ�̧�قł͂���܂���B ������ۼު�Ă�����ނ��邽�߂ɂ� NMAKE ���g�p���Ă��������B
!MESSAGE [Ҳ�̧�ق̴���߰�] ����ނ��g�p���Ď��s���Ă�������
!MESSAGE 
!MESSAGE NMAKE /f "kinst.mak".
!MESSAGE 
!MESSAGE NMAKE �̎��s���ɍ\�����w��ł��܂�
!MESSAGE ����� ײݏ��ϸۂ̐ݒ���`���܂��B��:
!MESSAGE 
!MESSAGE NMAKE /f "kinst.mak" CFG="kinst - Win32 Debug"
!MESSAGE 
!MESSAGE �I���\������� Ӱ��:
!MESSAGE 
!MESSAGE "kinst - Win32 Release" ("Win32 (x86) Application" �p)
!MESSAGE "kinst - Win32 Debug" ("Win32 (x86) Application" �p)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "kinst"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kinst - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../tmp/relui"
# PROP Intermediate_Dir "../tmp/relui"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /entry:"kilib_startUp" /subsystem:windows /machine:I386 /out:"../Release/uninst.exe" /opt:"nowin98"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "kinst - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../tmp/dbgui"
# PROP Intermediate_Dir "../tmp/dbgui"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "KILIB_LOG" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /entry:"kilib_startUp" /subsystem:windows /debug /machine:I386 /out:"../Debug/uninst.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "kinst - Win32 Release"
# Name "kinst - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\kinst.cpp
# End Source File
# Begin Source File

SOURCE=.\kinst.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\del.ico
# End Source File
# Begin Source File

SOURCE=..\noah.ico
# End Source File
# Begin Source File

SOURCE=.\noah.ico
# End Source File
# Begin Source File

SOURCE=.\real.ico
# End Source File
# End Group
# Begin Group "kilib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\kilib\kilib.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kilibext.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_app.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_app.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_carc.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_carc.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_cmd.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_cmd.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_dnd.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_dnd.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_file.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_file.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_find.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_find.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_misc.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_reg.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_reg.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_rythp.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_rythp.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_str.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_str.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_wcmn.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_wcmn.h
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_wnd.cpp
# End Source File
# Begin Source File

SOURCE=..\kilib\kl_wnd.h
# End Source File
# End Group
# End Target
# End Project
