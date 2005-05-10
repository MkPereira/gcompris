;;
;;  japanese.nsh
;;
;;  Japanese language strings for the Windows GCompris NSIS installer.
;;  Windows Code page: 932
;;
;;  Author: "Takeshi Kurosawa" <t-kuro@abox23.so-net.ne.jp>
;;  Version 2
;;


; License Page
!define GCOMPRIS_LICENSE_BUTTON			"���� >"
!define GCOMPRIS_LICENSE_BOTTOM_TEXT		"$(^Name)��GPL���C�Z���X�̌��Ń����[�X����Ă��܂��B���C�Z���X�͂����ɎQ�l�̂��߂����ɒ񋟂���Ă��܂��B $_CLICK"

; Components Page
!define GCOMPRIS_SECTION_TITLE                  "GCompris"
!define GCOMPRIS_SECTION_DESCRIPTION		"GCompris�̊j�ƂȂ�t�@�C����dll"


; Installer Finish Page
!define GCOMPRIS_FINISH_VISIT_WEB_SITE		"Windows GCompris��Web�y�[�W��K��Ă��������B"

; GCompris Section Prompts and Texts
!define GCOMPRIS_UNINSTALL_DESC			"GCompris (�폜�̂�)"
!define GCOMPRIS_PROMPT_WIPEOUT			"�Â�GCompris�̃t�H���_�̍폜�Ɋւ��āB���s���܂���?$\r$\r����: ���Ȃ��̃C���X�g�[���������ׂĂ̔�W���ȃv���O�C���͍폜����܂��B$\rGCompris�̐ݒ�͉e�����󂯂܂���B"
!define GCOMPRIS_PROMPT_DIR_EXISTS		"���Ȃ��̎w�肵���C���X�g�[����̃t�H���_�͂��łɑ��݂��Ă��܂��B���e�͂��ׂ�$\r�폜����܂��B���s���܂���?"



; Uninstall Section Prompts
!define un.GCOMPRIS_UNINSTALL_ERROR_1		"�A���C���X�g�[����GCompris�̃��W�X�g���G���g���𔭌��ł��܂���ł����B$\r�����炭�ʂ̃��[�U�ɃC���X�g�[�����ꂽ�ł��傤�B"
!define un.GCOMPRIS_UNINSTALL_ERROR_2		"���Ȃ��͂��̃A�v���P�[�V�������A���C���X�g�[�����錠���������Ă��܂���B"
