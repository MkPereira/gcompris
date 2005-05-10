;;
;;  polish.nsh
;;
;;  Polish language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1250
;;
;;  Author: Jan Eldenmalm <jan.eldenmalm@amazingports.com>
;;  Version 2
;;


; License Page
!define GCOMPRIS_LICENSE_BUTTON			"Dalej >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name) jest wydzielone w licencji GPL. Udziela si� licencji wy��cznie do cel�w informacyjnych. $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"Zbiory Core GCompris oraz dll"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Wejd� na stron� GCompris Web Page"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (usu� program)"
!define GCOMPRIS_PROMPT_WIPEOUT			"Stary katalog GCompris zosta� usuni�ty. Czy chcesz kontunuowa�?$\r$\rNote: Wszystkie stare - niestandardowe plugin-y zosta�y usuni�te.$\r Ustawienia u�utkownika GCompris b�d� wy��czone."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"Wybrany katalog instalacyjny ju� istnieje. Jego zawarto�� $\r zostanie skasowana. Czy chcesz kontunuowa�?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"Deinstalator nie mo�e znale�� rejestr�w dla GCompris.$\r Wskazuje to na to, �e instalacj� przeprowadzi� inny u�ytkownik."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"Nie masz uprawnie� do deinstalacji tej aplikacji."
