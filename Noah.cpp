// Noah.cpp
// -- entrypoint etc for 'Noah'

#include "stdafx.h"
#include "NoahApp.h"
#include "resource.h"

#if _MSC_VER >= 1300
extern "C" { int _afxForceEXCLUDE; }
extern "C" BOOL WINAPI _imp__IsDebuggerPresent() { return FALSE; }
#endif

// �v���Z�X�������]�[��
class ProcessNumLimitZone
{
	HANDLE m_han;
public:
	ProcessNumLimitZone(int Max, const char* name)
		: m_han( ::CreateSemaphore( NULL, Max, Max, name ) )
	{
		if( m_han )
			::WaitForSingleObject( m_han, INFINITE );
		else
			kiSUtil::msgLastError("CreateSemaphore Failed");
	}
	~ProcessNumLimitZone()
	{
		if( m_han )
		{
			::ReleaseSemaphore( m_han, 1, NULL );
			::CloseHandle( m_han );
		}
	}
};

//----------------------------------------------//
//--------- Noah �̃G���g���|�C���g ------------//
//----------------------------------------------//

void kilib_create_new_app()
{
	//-- kilib �ɃA�v���P�[�V������ݒ�
	new CNoahApp;
}

void CNoahApp::run( kiCmdParser& cmd )
{
	//-- ������
	m_cnfMan.init();
	m_arcMan.init();

	//-- �R�}���h���C���p�����[�^�ێ�
	m_pCmd = &cmd;

	//-- �u�t�@�C�������n����ĂȂ� or Shift�����N���v�Ȃ�ݒ��ʕ\��
	if( cmd.param().len()==0 || keyPushed(VK_SHIFT) )
	{
		//-- Load-INI ( �S�� )
		m_cnfMan.load( All );
		//-- �ݒ��ʕ\��
		m_cnfMan.dialog();
	}
	else
	{
		//-- ���k�𓀂Ȃǂ̍��
		do_cmdline( true );
	}

	//-- �I������
	m_tmpDir.remove();
}

//----------------------------------------------//
//------------- ���k/�� �� ��� --------------//
//----------------------------------------------//

bool CNoahApp::is_writable_dir( const kiPath& path )
{
	// �v����ɁACDROM/DVDROM ��؂肽���B
	// FDD, PacketWrite��Disk ��؂�̂͂�����߂�B

	// RAMDISK, REMOTE, FIXED, UNKNOWN �ȃf�B�X�N�͏������݉\�ƌ��Ȃ�
	UINT drv = path.getDriveType();
	if( drv==DRIVE_REMOVABLE || drv==DRIVE_CDROM )
	{
		// �fWin95�ł͎g���Ȃ��֐��Ȃ̂�DynamicLoad
		typedef BOOL (WINAPI*pGDFSE)( LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER );
		pGDFSE pGetDiskFreeSpaceEx
			= (pGDFSE) ::GetProcAddress( ::GetModuleHandle("kernel32.dll"), "GetDiskFreeSpaceExA" );
		if( pGetDiskFreeSpaceEx )
		{
			// �󂫗e�ʂ�0�Ȃ�A�������ݕs�Ƃ݂Ȃ�
			ULARGE_INTEGER fs, dummy;
			pGetDiskFreeSpaceEx( path, &dummy, &dummy, &fs );
			if( fs.QuadPart == 0 )
				return false;
		}
	}
	return true;
}

void CNoahApp::do_cmdline( bool directcall )
{
	do_files( m_pCmd->param(), &m_pCmd->option(), !directcall );
}

void CNoahApp::do_files( const cCharArray& files,
						 const cCharArray* opts,
						 bool  basicaly_ignore )
{
	struct local {
		~local() {kiSUtil::switchCurDirToExeDir(); } // �f�B���N�g�����b�N���Ȃ��悤��
	} _;

	//-- Archiver Manager �Ƀt�@�C�������X�g���L������
	if( 0 == m_arcMan.set_files( files ) )
		return;

	//-- ��Ɨp�ϐ�
	enum { unknown, melt, compress }
			whattodo = unknown;
	bool	ctrl_mlt = keyPushed( VK_CONTROL );
	bool	ctrl_cmp = ctrl_mlt;
	bool	alt      = keyPushed( VK_MENU ) || keyPushed( VK_RWIN ) || keyPushed( VK_LWIN );
	const char *cmptype=NULL, *method=NULL;
	kiPath  destdir;
	kiStr tmp(300);

	//-- ( ��������� )�R�}���h���C���I�v�V����������
	if( opts )
		for( unsigned int i=0; i!=opts->len(); i++ )
			switch( (*opts)[i][1] )
			{
			case 'a':	if( !basicaly_ignore )
			case 'A':		whattodo = compress;	break;

			case 'x':	if( !basicaly_ignore )
			case 'X':		whattodo = melt;		break;

			case 'd':	if( !basicaly_ignore )
			case 'D':		destdir = (*opts)[i]+2;	break;

			case 'w':	if( !basicaly_ignore )
			case 'W':		alt = true;				break;

			case 't':	if( !basicaly_ignore )
			case 'T':		cmptype = (*opts)[i]+2;	break;

			case 'm':	if( !basicaly_ignore )
			case 'M':		method = (*opts)[i]+2;	break;

			case 'c':	if( !basicaly_ignore ) {
			case 'C':		if((*opts)[i][2]!='x') ctrl_cmp = true;
							if((*opts)[i][2]!='a') ctrl_mlt = true;
						break;}
			}

	//-- Load-INI ( ���샂�[�h�ݒ� )
	m_cnfMan.load( Mode );

	//-- ���k�𓀂̂ǂ�����s�������肷��B����͈ȉ��̒ʂ�B
	//
	// �E�R�}���h���C���ŁA���k�Ǝw�肳��Ă�Ζ������ň��k��
	//
	// �E�����łȂ���΁A�܂�Noah�̓��샂�[�h�擾
	// �@m0:���k��p  m1:���k�D��  m2:�𓀗D��  m3:�𓀐�p
	// �@�@�R�}���h���C���ŉ𓀂Ǝw�肳��Ă���� m3�B
	// �@�@�w�肪������΁Am_cnfMan ����ǂݍ��݁B
	//
	// �Em0 ���A'm1�ł������t�@�C��������' �̎��͖������ň��k��
	//
	// �E�����łȂ���΁A�𓀃��[�`�������蓖�ĂĂ݂�B
	// �@���̍ہAm3 �ȊO�̂Ƃ��͈�ł����蓖�Ď��s������G���[�����k��
	// �@m3 �ł��A������蓖�Ă��Ȃ���΃G���[�B�������I��

	if( whattodo != compress )
	{
		int mode = 3;
		if( whattodo != melt )
			mode = m_cnfMan.mode();

		if( mode==0 || ( mode==1 && m_arcMan.file_num()>=2 ) )
			whattodo = compress;
		else
		{
			//-- �𓀃��[�`�����蓖�ĂĂ݂�
			bool suc = m_arcMan.map_melters( mode );
			if( suc )
				whattodo = melt;
			else
			{
				if( mode != 3 )
					whattodo = compress;
				else
				{
					//-- �𓀐�p���[�h�����ǉ𓀕s�I�I
					msgBox( tmp.loadRsrc(IDS_M_ERROR) );
					return;
				}
			}
		}
	}

	if( whattodo == melt )
	{
		//-- �𓀐ݒ�͊���m_cnfMan.init()�Ń��[�h����Ă���c

		if( destdir.len()==0 )
		{
			//-- �𓀐�f�B���N�g���擾
			if( m_cnfMan.mdirsm() )
				if( is_writable_dir(m_arcMan.get_basepath()) )
					destdir = m_arcMan.get_basepath();
			if( destdir.len()==0 )
				destdir = m_cnfMan.mdir();
		}

		//-- ��
		if( ctrl_mlt )	m_arcMan.do_listing( destdir );
		else {
			ProcessNumLimitZone zone( mycnf().multiboot_limit(), "LimitterForNoahAtKmonosNet" );
			m_arcMan.do_melting( destdir );
		}
	}
	else
	{
		//-- Load-INI( ���k�ݒ� )
		m_cnfMan.load( Compress );

		if( destdir.len()==0 )
		{
			//-- ���k��f�B���N�g���擾
			if( m_cnfMan.cdirsm() )
				if( is_writable_dir(m_arcMan.get_basepath()) )
					destdir = m_arcMan.get_basepath();
			if( destdir.len()==0 )
				destdir = m_cnfMan.cdir();
		}
		if( !cmptype ) cmptype = m_cnfMan.cext();
		else if( !method ) method = "";
		if( !method  ) method  = m_cnfMan.cmhd();

		//-- ���k�p���[�`�������蓖��
		if( !m_arcMan.map_compressor( cmptype, method, ctrl_cmp ) )
		{
			//-- ���k�s�\�Ȍ`���I�I
			msgBox( tmp.loadRsrc(IDS_C_ERROR) );
			return;
		}

		//-- ���k
		ProcessNumLimitZone zone( mycnf().multiboot_limit(), "LimitterForNoahAtKmonosNet" );
		m_arcMan.do_compressing( destdir, alt );
	}
}

//----------------------------------------------//
//----------------- ���̑��G�p -----------------//
//----------------------------------------------//

// from= 0:normal 1:melt 2:compress
void CNoahApp::open_folder( const kiPath& path, int from )
{
	if( from==1 || from==2 ) //-- Shell�ɍX�V�ʒm
		::SHChangeNotify( SHCNE_UPDATEDIR, SHCNF_PATH, (const void*)(const char*)path, NULL );

	//-- �f�X�N�g�b�v��������J���Ȃ�
	kiPath dir(path), tmp(kiPath::Dsk,false);
	dir.beBackSlash(false), dir.beShortPath(), tmp.beShortPath();

	if( !tmp.isSame( dir ) )
	{
		//-- Load-INI( �t�H���_�J���ݒ� )
		m_cnfMan.load( OpenDir );
		if( (from==1 && !m_cnfMan.modir())
		 || (from==2 && !m_cnfMan.codir()) )
			return;
		
		char cmdline[1000];
		wsprintf( cmdline, m_cnfMan.openby(), (const char*)dir );
		::WinExec( cmdline, SW_SHOWDEFAULT );
	}
}

// �S�V�X�e�����ň�ӂȃe���|�����t�H���_������ĕԂ�
void CNoahApp::get_tempdir( kiPath& tmp )
{
	char buf[MAX_PATH];

	if( m_tmpDir.len()==0 )
	{
		::GetTempFileName( kiPath( kiPath::Tmp ), "noa", 0, buf );
		::DeleteFile( buf );
		m_tmpDir = buf;
		m_tmpDir.beBackSlash( true );
		m_tmpDir.mkdir();
		m_tmpID = ::GetCurrentProcessId();
	}

	::GetTempFileName( m_tmpDir, "noa", m_tmpID++, buf );
	::DeleteFile( buf );
	tmp = buf;
	tmp.beBackSlash( true );
	tmp.mkdir();
}
