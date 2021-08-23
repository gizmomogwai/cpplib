########################
## Caption

Name "GLView"
#Caption "Babe Setup"
#Icon
#UninstallIcon
OutFile GLViewSetup.exe
SilentInstall normal
CRCCheck on
#BGGradient
#InstallColors
#UninstallText
#UninstallExeName

########################
## License

#LicenseText
#LicenseData

########################
## Component

ComponentText "This will install GLView on your computer."
InstType Minimal
#InstType Complete
#EnabledBitmap
#DisabledBitmap

########################
## DirectorySelection

DirShow show
DirText "Choose a Directory"
InstallDir $PROGRAMFILES\_gfx\GLView
#InstallDirRegKey

########################
## InstallPage Configuration

AutoCloseWindow false
ShowInstDetails show

########################
## Install Execution Commands

SetCompress auto


Section "MainProgram"
SectionIn "1-2-3-4-5-6-7-8"
SetOutPath "$INSTDIR"
File "Debug\glview.exe"
File "..\..\libs\glut32.dll"
File "readme.html"
SectionEnd

Function .onInstSuccess
  MessageBox MB_YESNO "Thank you for using GlView! View Readme now?" IDNO NoReadme
  ExecShell "" "$INSTDIR\readme.html"
  NoReadme:
  MessageBox MB_YESNO "Open Installationdirectory?" IDNO NoOpen
  Exec '"$WINDIR\explorer.exe" "$INSTDIR"'
  NoOpen:
FunctionEnd
