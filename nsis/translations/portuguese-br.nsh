;;
;;  portuguese-br.nsh
;;
;;  Portuguese (BR) language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: Maur�cio de Lemos Rodrigues Collares Neto <mauricioc@myrealbox.com>, 2003.
;;  Version 2
;;


; License Page
!define GCOMPRIS_LICENSE_BUTTON			"Avan�ar >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name) � distribu�do sob a licen�a GPL. Esta licen�a � disponibilizada aqui apenas para fins informativos. $_CLICK" 

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"Arquivos e bibliotecas principais do GCompris"


; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (apenas remover)"
!define GCOMPRIS_PROMPT_WIPEOUT			"Sua antiga instala��o do GCompris est� prestes a ser removida. Voc� gostaria de continuar?$\r$\rNota: Quaisquer plugins n�o-padr�o que voc� pode ter instalado ser�o removidos.$\rAs configura��es de usu�rio do GCompris n�o ser�o afetadas."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"O diret�rio de instala��o do que voc� especificou j� existe. Qualquer conte�do$\rser� deletado. Deseja continuar?"



; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Visite a p�gina da web do GCompris para Windows"

; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"O desinstalador n�o p�de encontrar entradas de registro do GCompris.$\r� prov�vel que outro usu�rio tenha instalado esta aplica��o."
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"Voc� n�o tem permiss�o para desinstalar essa aplica��o."
