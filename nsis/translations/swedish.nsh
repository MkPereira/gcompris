;;
;;  swedish.nsh
;;
;;  Swedish language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: Tore Lundqvist <tlt@mima.x.se>, 2003.
;;  Author: Peter Hjalmarsson <xake@telia.com>, 2005.
;;  Version 3
;;

; Make sure to update the GCOMPRIS_MACRO_LANGUAGEFILE_END macro in
; langmacros.nsh when updating this file

; Startup Checks
!define INSTALLER_IS_RUNNING			"Installationsprogrammet k�rs redan."
!define GCOMPRIS_IS_RUNNING			"En instans av Giam k�rs redan. Avsluta GCompris och f�rs�k igen."

; License Page
!define GCOMPRIS_LICENSE_BUTTON			"N�sta >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name) �r utgivet under GPL. Licensen finns tillg�nglig h�r f�r infromationssyften enbart. $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"GCompriss k�rnfiler och DLL:er"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Bes�k Windows-GCompriss hemsida"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (enbart f�r avinstallation)"
!define GCOMPRIS_PROMPT_WIPEOUT			"Din gamla GCompris-katalog kommer att raderas, vill du forts�tta?$\r$\rOBS! om du har installerat n�gra extra insticksmoduler kommer de raderas.$\rGCompriss anv�ndarinst�llningar kommer inte p�verkas."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Den katalog du vill installera i finns redan. Allt i katalogen$\rkommer att raderas, vill du forts�tta?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1         "Avinstalleraren kunde inte hitta registerv�rden f�r GCompris.$\rAntagligen har en annan anv�ndare installerat applikationen."
!define un.GCOMPRIS_UNINSTALL_ERROR_2         "Du har inte r�ttigheter att avinstallera den h�r applikationen."
