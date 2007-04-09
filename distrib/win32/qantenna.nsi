; General stuff
; -------------

!define VERSION "0.1"

Name "QAntenna"
OutFile "qantenna-${VERSION}.exe"

InstallDir $PROGRAMFILES\QAntenna

; Preparing
; ---------

!include "MUI.nsh"
!define MUI_ABORTWARNING
Var STARTMENU_FOLDER
var MUI_TEMP

; Pages
; -----

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\COPYING"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Localization
; ------------

!insertmacro MUI_LANGUAGE "English"
LangString DESC_SecQAntenna	${LANG_ENGLISH} "The main QAntenna application itself."
LangString DESC_SecLocal	${LANG_ENGLISH} "Localization files for QAntenna. The following languages are curently available: English, ..."
LangString DESC_SecNEC		${LANG_ENGLISH} "An electromagnetic analysis tool required by QAntenna. Only deselect this if you already installed it."
LangString DESC_SecExample	${LANG_ENGLISH} "Some example NEC files that could be used with QAntenna."


; Sections
; --------

Section "-QAntenna" SecQAntenna
	SetOutPath $INSTDIR
	File "..\src\bin\qantenna.exe"
	File "mingwm10.dll"
	WriteUninstaller "$INSTDIR\Uninstall.exe"

	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
		CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\QAntenna.lnk" "$INSTDIR\qantenna.exe"
		CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
	!insertmacro MUI_STARTMENU_WRITE_END

SectionEnd 

Section "NEC2++" SecNEC
	SetOutPath $INSTDIR
	FILE "nec2++.exe"
SectionEnd

Section "Localization" SecLocal
	SetOutPath $INSTDIR
	FILE "..\qt\ts\qantenna_da.qm"
	FILE "..\qt\ts\qantenna_de.qm"
	FILE "..\qt\ts\qantenna_es.qm"
	FILE "..\qt\ts\qantenna_fr.qm"
	FILE "..\qt\ts\qantenna_it.qm"
	FILE "..\qt\ts\qantenna_nl.qm"
	FILE "..\qt\ts\qantenna_pl.qm"
	FILE "..\qt\ts\qantenna_ru.qm"
	FILE "..\qt\ts\qantenna_sv.qm"
SectionEnd

Section "Examples" SecExample
	SetOutPath "$INSTDIR\examples"
	FILE "..\examples\19el_432_tonna.nec"
	FILE "..\examples\adrian.nec"
	FILE "..\examples\ant.nec"
	FILE "..\examples\centfeed.nec"
	FILE "..\examples\EX1.nec"
	FILE "..\examples\EX2.nec"
	FILE "..\examples\EX3.nec"
	FILE "..\examples\EX4.nec"
	FILE "..\examples\EX5.nec"
	FILE "..\examples\EX6.nec"
	FILE "..\examples\EX7.nec"
	FILE "..\examples\quad17m-1.nec"
	FILE "..\examples\spaceship.nec"
	FILE "..\examples\tri_7.nec"
	FILE "..\examples\yagi8sq_ch1.nec"
	FILE "..\examples\yagi.nec"
	FILE "..\examples\yg2_5el_50.nec"
	FILE "..\examples\yg_4el_20.nec"
	FILE "..\examples\yg_6el.nec"
	FILE "..\examples\yg_16el_220.nec"
	FILE "..\examples\LICENSE-NEC.FILES"
SectionEnd

; Uninstaller
; -----------

Section "Uninstall"
	Delete "$INSTDIR\qantenna.exe"
	Delete "$INSTDIR\mingwm10.dll"

	Delete "$INSTDIR\nec2++.exe"
	
	Delete "$INSTDIR\qantenna_da.qm"
	Delete "$INSTDIR\qantenna_de.qm"
	Delete "$INSTDIR\qantenna_es.qm"
	Delete "$INSTDIR\qantenna_fr.qm"
	Delete "$INSTDIR\qantenna_it.qm"
	Delete "$INSTDIR\qantenna_nl.qm"
	Delete "$INSTDIR\qantenna_pl.qm"
	Delete "$INSTDIR\qantenna_ru.qm"
	Delete "$INSTDIR\qantenna_sv.qm"

	Delete "$INSTDIR\examples\19el_432_tonna.nec"
	Delete "$INSTDIR\examples\adrian.nec"
	Delete "$INSTDIR\examples\ant.nec"
	Delete "$INSTDIR\examples\centfeed.nec"
	Delete "$INSTDIR\examples\EX1.nec"
	Delete "$INSTDIR\examples\EX2.nec"
	Delete "$INSTDIR\examples\EX3.nec"
	Delete "$INSTDIR\examples\EX4.nec"
	Delete "$INSTDIR\examples\EX5.nec"
	Delete "$INSTDIR\examples\EX6.nec"
	Delete "$INSTDIR\examples\EX7.nec"
	Delete "$INSTDIR\examples\quad17m-1.nec"
	Delete "$INSTDIR\examples\spaceship.nec"
	Delete "$INSTDIR\examples\tri_7.nec"
	Delete "$INSTDIR\examples\yagi8sq_ch1.nec"
	Delete "$INSTDIR\examples\yagi.nec"
	Delete "$INSTDIR\examples\yg2_5el_50.nec"
	Delete "$INSTDIR\examples\yg_4el_20.nec"
	Delete "$INSTDIR\examples\yg_6el.nec"
	Delete "$INSTDIR\examples\yg_16el_220.nec"
	Delete "$INSTDIR\examples\LICENSE-NEC.FILES"


	Delete "$INSTDIR\Uninstall.exe"
	RMDir "$INSTDIR\examples"
	RMDir "$INSTDIR"

  	!insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
    
  	Delete "$SMPROGRAMS\$MUI_TEMP\QAntenna.lnk"
	Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"
	RMDir "$SMPROGRAMS\$MUI_TEMP"
SectionEnd

; Description
; -----------

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${SecQAntenna} $(DESC_SecQAntenna)
	!insertmacro MUI_DESCRIPTION_TEXT ${SecNEC} $(DESC_SecNEC)
	!insertmacro MUI_DESCRIPTION_TEXT ${SecLocal} $(DESC_SecLocal)
	!insertmacro MUI_DESCRIPTION_TEXT ${SecExample} $(DESC_SecExample)
!insertmacro MUI_FUNCTION_DESCRIPTION_END
