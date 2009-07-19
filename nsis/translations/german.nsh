;;
;;  german.nsh
;;
;;  German language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: Bjoern Voigt <bjoern@cs.tu-berlin.de>, 2005.
;;  Version 3
;;

; Startup checks
!define INSTALLER_IS_RUNNING			"Der Installer l�uft schon."
!define GCOMPRIS_IS_RUNNING				"Eine Instanz von GCompris l�uft momentan schon. Beenden Sie GCompris und versuchen Sie es nochmal."

; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Besuchen Sie die Windows GCompris-Webseite"

; GCompris Section Prompts and Texts
!define GCOMPRIS_PROMPT_WIPEOUT			"Ihr altes GCompris-Verzeichnis soll gel�scht werden. M�chten Sie fortfahren?$\r$\rHinweis: Alle nicht-Standard Plugins, die Sie evtl. installiert haben werden$\rgel�scht. GCompris-Benutzereinstellungen sind nicht betroffen."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Das Installationsverzeichnis, das Sie angegeben haben, existiert schon. Der Verzeichnisinhalt$\rwird gel�scht. M�chten Sie fortfahren?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"Der Deinstaller konnte keine Registrierungsschl�ssel f�r GCompris finden.$\rEs ist wahrscheinlich, dass ein anderer Benutzer diese Anwendunng installiert hat."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"Sie haben keine Berechtigung, diese Anwendung zu deinstallieren."
