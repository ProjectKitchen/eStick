!include "WinMessages.nsh"

; set compressor and compresion level
SetCompress force
SetCompressor /SOLID lzma

; set the name of the installer
Name "eStickFlashTool"

; set the name of the installers executable
OutFile "eStick_FlashTool.exe"

; turn on some fancy XP look and feel
XPStyle on

AddBrandingImage left 180

BGGradient 00007f e5e5e5

InstProgressFlags smooth

BrandingText "FH Technikum Wien :: Elektronik"

ShowInstDetails show

; provide a default path where to install the program
InstallDir "c:\eStick\eStickFlashTool"

; change the icon of the installer
Icon eStickFlashTool.ico

;
Page directory
Page instfiles
Page custom customPage
UninstPage instfiles 
;--------------------------------

!macro BIMAGE IMAGE PARMS
	Push $0
	GetTempFileName $0
	File /oname=$0 "${IMAGE}"
	SetBrandingImage ${PARMS} $0
	Delete $0
	Pop $0
!macroend

Function .onGUIInit
  !insertmacro BIMAGE  "eStick.bmp" /RESIZETOFIT
FunctionEnd

; copy the files for the program and create some shortcuts
Function instImage
  !insertmacro BIMAGE "eStick.bmp" /RESIZETOFIT
  SetOutPath $INSTDIR
  ; copy all files recursively
  FILE /r * 
  ; create an uninstaller
  WriteUninstaller $INSTDIR\uninstaller.exe
  ; make a link in the start menu for the program and the uninstaller
  CreateDirectory "$SMPROGRAMS\eStick"
  CreateShortCut "$SMPROGRAMS\eStick\eStickFlashTool.lnk" "$INSTDIR\eStickFlashTool.exe" "" "$INSTDIR\eStickFlashTool.ico"
FunctionEnd  

Function customPage
	!insertmacro BIMAGE "eStick.bmp" /RESIZETOFIT
	Exec '"notepad.exe" "README"'
FunctionEnd

;--------------------------------

Section "eStickFlashTool"
  Call instImage
SectionEnd

;--------------------------------
; uninstall stuff
Section "un.Uninstall"
  !insertmacro BIMAGE "eStick.bmp" /RESIZETOFIT
  ; remove all the files
  RMDir /r $INSTDIR
  ; remove the entry in the start menu
  Delete "$SMPROGRAMS\eStick\eStickFlashTool.lnk"
  RMDir "$SMPROGRAMS\eStick"
SectionEnd
;--------------------------------
