;;
;;  hungarian.nsh
;;
;;  Default language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 1250
;;
;;  Author: Sutto Zoltan <suttozoltan@chello.hu
;;


; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"GCompris f�jlok �s dll-ek"


; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (csak elt�vol�t�s)"
!define GCOMPRIS_PROMPT_WIPEOUT			"Az �n kor�bbi GCompris k�nyvt�ra t�rl�dni fog. Folytatni szeretn�?$\r$\rMegjegyz�s: Minden �n �ltal telep�tett plugin t�rl�dni fog.$\rGCompris felhaszn�l�i be�ll�t�sokat ez nem �rinti."
!define GCOMPRIS_PROMPT_DIR_EXISTS		"A telep�t�skor megadott k�nyvt�r m�r l�tezik. Minden �llom�ny t�rl�dni fog.$\rFolytatni szeretn�?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1         "Az elt�vol�t� nem tal�lt GCompris registry bejegyz�seket.$\rVal�sz�n�leg egy m�sik felhaszn�l� telep�tette az alkalmaz�st."
!define un.GCOMPRIS_UNINSTALL_ERROR_2         "Nincs jogosults�ga az alkalmaz�s elt�vol�t�s�hoz."
