;;
;;  catalan.nsh
;;
;;  Catalan language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: "Bernat L�pez" <bernatl@adequa.net>
;;  Version 2
;;  


; License Page
!define GCOMPRIS_LICENSE_BUTTON			"Seg�ent >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name) �s distribu�t sota llic�ncia GPLe. Podeu consultar la llic�ncia, nom�s per proposits informatius, aqu�. $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"Fitxers i dlls del nucli de GCompris"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Visita la p�gina web de GCompris per Windows"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (nom�s esborrar)"
!define GCOMPRIS_PROMPT_WIPEOUT			"El teu directori antic de GCompris ser� esborrat. Vols continuar?$\r$\rNota: Els plugins no est�ndards que tinguis instal.lats seran esborrats.$\rLes prefer�ncies d'usuari de GCompris no es veruan afectades."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"El directori d'instal.laci� que has especificat ja existeix. Tots els continguts$\rseran esborrats. Vols continuar?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"L'instal.lador podria no trobar les entrades del registre de GCompris.$\rProbablement un altre usuari ha instal.lat aquesta aplicaci�."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"No tens perm�s per desinstal.lar aquesta aplicaci�."
