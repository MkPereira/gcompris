;;
;;  spanish.nsh
;;
;;  Spanish language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;  Translator: Javier Fernandez-Sanguino Pe�a
;;
;;  Version 2
;;


; License Page
!define GCOMPRIS_LICENSE_BUTTON			"Siguiente >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name) se distribuye bajo la licencia GPL. Esta licencia se incluye aqu� s�lo con prop�sito informativo: $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"Ficheros y dlls principales de Core"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Visite la p�gina Web de GCompris Windows"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (s�lo eliminar)"
!define GCOMPRIS_PROMPT_WIPEOUT			"Su directorio antig�o de GCompris va a ser borrado. �Desea continuar?$\r$\rObservaci�n: cualquier aplique no est�ndar que pudiera haber instalado ser� borrado.$\r�sto no afectar� a sus preferencias de usuario en GCompris."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"El directorio de instalaci�n que ha especificado ya existe. Todos los contenidos$\rser� borrados. �Desea continuar?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1         "El desinstalador no pudo encontrar las entradas en el registro de GCompris.$\rEs probable que otro usuario instalara la aplicaci�n."
!define un.GCOMPRIS_UNINSTALL_ERROR_2         "No tiene permisos para desinstalar esta aplicaci�n."
