;;
;;  slovak.nsh
;;
;;  Slovak language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1250
;;
;;  Author: dominik@internetkosice.sk
;;  Version 2


; License Page
!define GCOMPRIS_LICENSE_BUTTON			"�alej >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name) je vydan� pod GPL licenciou. T�to licencia je len pre informa�n� ��ely. $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"Jadro GCompris-u a nevyhnutn� DLL s�bory"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Nav�t�vi� webstr�nku Windows GCompris"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (len odstr�ni�)"
!define GCOMPRIS_PROMPT_WIPEOUT			"V� adres�r GCompris bude zmazan�. Chcete pokra�ova�?$\r$\rPozn�mka: V�etky pr�davne pluginy, ktor� ste nain�talovali bud� tie� zmazan�.$\rNastavenia u�ivate�sk�ho ��tu GCompris-u bud� ponechan�."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Adres�r, ktor� ste zadali, u� existuje. Jeho obsah bude zmazan�. Chcete pokra�ova�?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"In�tal�toru sa nepodarilo n�js� polo�ky v registri pre GCompris.$\rJe mo�n�, �e t�to aplik�ciu nain�taloval in� pou��vate�."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"Nem�te opr�vnenie na odin�tal�ciu tejto aplik�cie."
