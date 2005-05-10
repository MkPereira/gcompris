;;
;;  slovenian.nsh
;;
;;  Slovenian language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1250
;;
;;  Author: Martin Srebotnjak <miles@filmsi.net>
;;  Version 2
;;

!define INSTALLER_IS_RUNNING			"Name��anje �e poteka."
!define GCOMPRIS_IS_RUNNING				"Trenutno �e te�e razli�ica GComprisa. Prosimo zaprite GCompris in poskusite znova."

; License Page
!define GCOMPRIS_LICENSE_BUTTON			"Naprej >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name) je na voljo pod licenco GPL. Ta licenca je tu na voljo le v informativne namene. $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"Temeljne datoteke GComprisa"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Obi��ite spletno stran Windows GCompris"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (samo odstrani)"
!define GCOMPRIS_PROMPT_WIPEOUT			"Va� star imenik GCompris bo zbrisan. �elite nadaljevati?$\r$\rOpomba: Vsi nestandardni vti�niki, ki ste jih namestili, bodo zbrisani.$\rUporabni�ke nastavitve za GCompris se bodo ohranile."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Namestitveni imenik, ki ste ga navedli, �e obstaja. Vsa vsebina$\rbo zbrisana. �elite nadaljevati?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"Ne morem najti vnosov v registru za GCompris.$\rNajverjetneje je ta program namestil drug uporabnik."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"Za odstranitev programa nimate ustreznih pravic."
