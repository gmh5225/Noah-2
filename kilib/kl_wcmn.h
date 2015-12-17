//--- K.I.LIB ---
// kl_wcmn.h : windows-common-interface operatin

#ifndef AFX_KIWINCOMMON_H__0686721C_CAFB_4C2C_9FE5_0F482EA6A60B__INCLUDED_
#define AFX_KIWINCOMMON_H__0686721C_CAFB_4C2C_9FE5_0F482EA6A60B__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// �V�F�����[�e�B���e�B�[�N���X

class kiSUtil
{
public:
	// �J�����g�f�B���N�g���ޔ�
	static void switchCurDirToExeDir();

	// �u�t�H���_�̑I���v�_�C�A���O
	static bool getFolderDlg( char* buf, HWND par, const char* title, const char* def );
	static void getFolderDlgOfEditBox( HWND wnd, HWND par, const char* title );

	// �Ή�����g���q�p�A�C�R���́A�V�X�e���C���[�W���X�g�̃C���f�b�N�X��Ԃ��B
	static int getSysIcon( const char* ext );

	// �Ō�̃G���[��\��
	static void msgLastError( const char* msg = NULL );

	// �����ւ̃V���[�g�J�b�g�쐬
	static void createShortCut( const kiPath& at, const char* name );

	// �t�@�C�������݂���H
	static bool exist( const char* fname );
	static bool isdir( const char* fname );

	// �J�����g�f�B���N�g�������S�ȂƂ���Ɉڂ���LoadLibrary
	static HMODULE loadLibrary(LPCTSTR lpFileName)
	{
		char original_cur[MAX_PATH], sys[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH, original_cur);
		::GetSystemDirectory(sys, MAX_PATH);
		::SetCurrentDirectory(sys);
		HMODULE han = ::LoadLibrary(lpFileName);
		::SetCurrentDirectory(original_cur);
		return han;
	}
};

#endif
