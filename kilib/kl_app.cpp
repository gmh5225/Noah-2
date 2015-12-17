//--- K.I.LIB ---
// kl_app.h : application class for K.I.LIB

#include "stdafx.h"
#include "kilib.h"

//------------ �B��̃A�v���P�[�V�����I�u�W�F�N�g�̊Ǘ� ------------//

kiApp* kiApp::st_pApp = NULL;

kiApp* app()
{
	return kiApp::st_pApp;
}

//-------------------- �X�^�[�g�A�b�v�R�[�h ------------------------//

void kilib_startUp()
{
	// �p�ꃍ�P�[���e�X�g�p
	//::SetThreadUILanguage(0x0409);

	//-- K.I.LIB ������
	kiStr::init();
	kiWindow::init();

	//-- �L�[�{�[�h��ԃN���A
	::GetAsyncKeyState( VK_SHIFT );

	//-- �A�v���P�[�V�����C���X�^���X���쐬
	kilib_create_new_app();
	if( app() )
	{
		// �R�}���h���C������
		kiCmdParser cmd( ::GetCommandLine(), true );

		// ���s
		app()->run( cmd );
	}

	//-- K.I.LIB �I��
	kiWindow::finish();

	delete app();
	::ExitProcess( 0 );
}

//--------------- C-Runtime�������R�[�h�폜����̏��� ---------------//

#if 1

int APIENTRY WinMain( HINSTANCE, HINSTANCE, char*, int )
{
	kilib_startUp();
	return 0;
}

#else

void* operator new( size_t siz )
{
	return (void*)::GlobalAlloc( GMEM_FIXED, siz );
}

void operator delete( void* ptr )
{
	::GlobalFree( (HGLOBAL)ptr );
}

void main()
{
	// main ���Ȃ��Ɖ��̂� libc.lib �������N�G���[�ɂȂ�̂Ń_�~�[
}

#endif

//--------------------------------------------------------------//
