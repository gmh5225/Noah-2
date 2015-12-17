//--- K.I.LIB ---
// kl_app.h : application class for K.I.LIB

#ifndef AFX_KIAPP_H__AC24C8AF_2187_4873_83E8_AB4F2325017B__INCLUDED_
#define AFX_KIAPP_H__AC24C8AF_2187_4873_83E8_AB4F2325017B__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// �ėp�A�v���P�[�V�����N���X

class kiApp
{
friend kiApp* app();
friend void kilib_startUp();

public: //-- �O�����C���^�[�t�F�C�X --------------------------

	// �C���X�^���X
	HINSTANCE inst() const
		{
			return m_hInst;
		}

	// ���C���E�C���h�E
	HWND mainhwnd() const
		{
			return m_pMainWnd ? m_pMainWnd->hwnd() : NULL;
		}
	kiWindow* mainwnd() const
		{
			return m_pMainWnd;
		}
	void setMainWnd( kiWindow* wnd )
		{
			m_pMainWnd = wnd;
		}

	// �n�r�o�[�W����
	const OSVERSIONINFO& osver() const
		{
			return m_OsVer;
		}

	// ���b�Z�[�W�{�b�N�X
	int msgBox( const char* msg, const char* caption=NULL, UINT type=MB_OK )
		{
			return ::MessageBox( mainhwnd(), msg, caption, type );
		}

	// �V�F���̃A���P�[�^�Ń��������
	void shellFree( void* ptr ) const
		{
			m_pShellAlloc->Free( ptr );
		}

	// ���z�R�[�h vKey �̃L�[�͉�����Ă��邩�H
	static bool keyPushed( int vKey )
		{
			return( 0!=(::GetAsyncKeyState( vKey )>>15) );
		}

	// CommonControl / OLE ������
	void shellInit()
		{
			if( !m_bShellInit )
			{
				::InitCommonControls();
				::OleInitialize( NULL );
				m_bShellInit = true;
			}
		}

#ifdef KILIB_LOG
	void log( const char* str )
		{
			if( !m_log.isOpened() )
			{
				kiPath logtxt( kiPath::Exe ); logtxt += "log.txt";
				m_log.open( logtxt, false );
			}
			m_log.write( str, ki_strlen(str) );
			m_log.write( "\r\n", 2 );
		}
#endif

protected: //-- �h���N���X���� -----------------------------

	// �N�����ɌĂ΂��֐��B�K�{�B
	virtual void run( kiCmdParser& cmd ) = 0;

protected: //-- �������� -----------------------------------

	kiApp()
		{
			st_pApp = this;
			m_hInst = ::GetModuleHandle( NULL );
			m_pMainWnd = NULL;
			m_bShellInit = false;
			m_OsVer.dwOSVersionInfoSize = sizeof( m_OsVer );
			::GetVersionEx( &m_OsVer );
			::SHGetMalloc( &m_pShellAlloc );
		}

protected:

	virtual ~kiApp()
		{
			m_pShellAlloc->Release();
			if( m_bShellInit )
				::OleUninitialize();
		}

private:

	HINSTANCE      m_hInst;
	IMalloc*       m_pShellAlloc;
	bool           m_bShellInit;
	OSVERSIONINFO  m_OsVer;
	kiWindow*      m_pMainWnd;
	static kiApp* st_pApp;
#ifdef KILIB_LOG
	kiFile         m_log;
#endif
};

#endif
