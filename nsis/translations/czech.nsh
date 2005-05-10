;;
;;  czech.nsh
;;
;;  Czech language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: Jan Kolar <jan@e-kolar.net>
;;  Version 2
;;


; License Page
!define GCOMPRIS_LICENSE_BUTTON			"Dal�� >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"K pou�it� $(^Name) se vztahuje GPL licence. Licence je zde uvedena pouze pro Va�� informaci. $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"Z�kladn� soubory a DLL pro GCompris"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Nav�t�vit Windows GCompris Web Page"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (odinstalovat)"
!define GCOMPRIS_PROMPT_WIPEOUT			"V� star� adres�� pro GCompris bude vymaz�n. Chcete pokra�ovat?$\r$\rUpozorn�n�: Jak�koli nestandardn� roz���en� (plugin) , kter� m�te nainstalov�na budou ztracena.$\rU�ivatelsk� nastaven� pro GCompris budou zachov�na."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Adres�� kter� byl zad�n pro instalaci ji� existuje. Ve�ker� obsah$\rbude smaz�n. Chcete pokra�ovat?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"Odinstal�n� proces nem��e naj�t z�znamy pro GCompris v registrech.$\rPravd�podobn� instalaci t�to aplikace provedl jin� u�ivatel."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"Nem�te opr�vn�n� k odinstalaci t�to aplikace."
