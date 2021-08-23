# Microsoft Developer Studio Project File - Name="glview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=glview - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "glview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "glview.mak" CFG="glview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glview - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "glview - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "glview - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../.." /I "../../includes" /D "NDEBUG" /D "_COMMAND" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib msvcrt.lib msvcprt.lib opengl32.lib glu32.lib glut32.lib user32.lib vecmath.lib lang.lib io.lib image.lib jpegCodec.lib pngCodec.lib libpng125.lib zlib114.lib libjpeg.lib libungif.lib jasperCodec.lib libjasper.lib gifCodec.lib tiffCodec.lib libtiff.lib /nologo /subsystem:console /machine:I386 /nodefaultlib /libpath:"../../libProjects/build" /libpath:"../../libs"

!ELSEIF  "$(CFG)" == "glview - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../.." /I "../../includes" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_COMMAND" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib msvcrtd.lib msvcprtd.lib opengl32.lib glu32.lib glut32.lib user32.lib vecmathd.lib langd.lib iod.lib imaged.lib jpegCodecD.lib pngCodecD.lib libpng125D.lib zlib114D.lib libjpeg.lib libungifd.lib jasperCodecD.lib libjasperD.lib gifCodecD.lib tiffCodecD.lib libtiff.lib libjasper-1.70.1.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib /pdbtype:sept /libpath:"../../libProjects/build" /libpath:"../../libs"
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "glview - Win32 Release"
# Name "glview - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "sg"

# PROP Default_Filter ""
# Begin Group "nodes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sg\nodes\Behavior.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Behavior.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Group.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Group.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Leaf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Leaf.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Node.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Node.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Root.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Root.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\SGObserver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\SGObserver.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Shape3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\Shape3D.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\TGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodes\TGroup.h
# End Source File
# End Group
# Begin Group "math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sg\math\RCTransform3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\math\RCTransform3D.h
# End Source File
# End Group
# Begin Group "visitors"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sg\visitors\BehaviorVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\BehaviorVisitor.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\OGLRenderVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\OGLRenderVisitor.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\OGLTextureActivator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\OGLTextureActivator.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\PrintVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\PrintVisitor.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\RenderVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\RenderVisitor.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\UpdateVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\UpdateVisitor.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\Visitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\visitors\Visitor.h
# End Source File
# End Group
# Begin Group "nodeComponents"

# PROP Default_Filter ""
# Begin Group "app"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\Appearance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\Appearance.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\PolygonAttributes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\PolygonAttributes.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\RenderingAttributes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\RenderingAttributes.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\Texture.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\app\Texture.h
# End Source File
# End Group
# Begin Group "geom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sg\nodeComponents\geom\IndexedTriangleArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\geom\IndexedTriangleArray.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\geom\TriangleArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\geom\TriangleArray.h
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\geom\TriangleArrayType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\nodeComponents\geom\TriangleArrayType.h
# End Source File
# End Group
# End Group
# Begin Group "data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sg\data\VertexData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\data\VertexData.h
# End Source File
# End Group
# Begin Group "conditions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sg\conditions\WakeupOnElapsedFrames.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\conditions\WakeupOnElapsedFrames.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\sg\SGObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sg\SGObject.h
# End Source File
# End Group
# Begin Group "sgtools"

# PROP Default_Filter ""
# Begin Group "nodeComponents No. 1"

# PROP Default_Filter ""
# Begin Group "geom No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sgtools\nodeComponents\geom\CubeGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\nodeComponents\geom\CubeGeometry.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=..\..\sgtools\Engine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\Engine.h
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\EngineCleanUp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\EngineCleanUp.h
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\GLUTEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\GLUTEngine.h
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\GLUTKeyEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\GLUTKeyEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\KeyEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\KeyEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\KeyListener.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\KeyListener.h
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\QuitKeyListener.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sgtools\QuitKeyListener.h
# End Source File
# End Group
# Begin Group "vecmath"

# PROP Default_Filter ""
# End Group
# Begin Group "util"

# PROP Default_Filter ""
# Begin Group "profile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\util\profile\ClearProfileVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ClearProfileVisitor.h
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\PrintProfileVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\PrintProfileVisitor.h
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\Profile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\Profile.h
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileList.h
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileObject.h
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\Profiler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\Profiler.h
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileStack.h
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\util\profile\ProfileVisitor.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ImageReader.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageReader.h
# End Source File
# Begin Source File

SOURCE=.\ImageViewNavigator.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageViewNavigator.h
# End Source File
# Begin Source File

SOURCE=.\LoadProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadProgress.h
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# ADD CPP /I "..\.." /I "..\..\includes"
# End Source File
# Begin Source File

SOURCE=.\RotationBehavior.cpp
# End Source File
# Begin Source File

SOURCE=.\RotationBehavior.h
# End Source File
# Begin Source File

SOURCE=.\SGUpdateThread.cpp
# End Source File
# Begin Source File

SOURCE=.\SGUpdateThread.h
# End Source File
# End Group
# Begin Group "libs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\libProjects\build\tiffCodecD.lib
# End Source File
# Begin Source File

SOURCE=..\..\libProjects\build\tiffCodec.lib
# End Source File
# Begin Source File

SOURCE=..\..\libProjects\build\io.lib
# End Source File
# Begin Source File

SOURCE=..\..\libProjects\build\ioD.lib
# End Source File
# Begin Source File

SOURCE=..\..\libProjects\build\lang.lib
# End Source File
# Begin Source File

SOURCE=..\..\libProjects\build\langD.lib
# End Source File
# End Group
# End Target
# End Project
