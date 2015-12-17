// Archiver.cpp
//-- CArchiver -- common interface in 'Noah' for archiving routine --

#include "stdafx.h"
#include "Archiver.h"
#include "NoahApp.h"



CArcModule::CArcModule( const char* name, bool us )
	: m_dll(NULL)
{
	// SearchPath�̑O�ɃJ�����g�f�B���N�g����noah.exe�Ɠ����ꏊ��
	char prev_cur[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, prev_cur);
	kiSUtil::switchCurDirToExeDir();

	if( 0!=::SearchPath( NULL,name,NULL,MAX_PATH,m_name,NULL ) )
	{
		const char* xt=kiPath::ext(name);
		if( 0!=ki_strcmpi("dll",xt) )
		{
			// EXE�̏ꍇ
			m_type = us ? EXEUS : EXE;
		}
		else
		{
			// DLL�̏ꍇ
			m_dll = new kiArcDLLRaw(name);
			m_type = DLL;
			if(name<=xt-8&&xt[-6]=='G'&&xt[-5]=='C'&&xt[-4]=='A' )
				m_type = DLLGCA;
			else if(name==xt-6&&xt[-6]=='B'&&xt[-5]=='g'&&xt[-4]=='a' )
				m_type = DLLBGA;
		}
	}
	else
	{
		// �t�@�C�����������A�V�F���̃R�}���h�̏ꍇ
		// �o�b�t�@�I�[�o�[�t���[�̊댯�c(^^;
		ki_strcpy( m_name, name );
		m_type = SHLCMD;
	}

	// �J�����g��߂�
	::SetCurrentDirectory(prev_cur);
}

CArcModule::~CArcModule()
{
	delete m_dll;
}

int CArcModule::cmd( const char* cmd, bool mini )
{
	if( m_dll )
	{
		// �A�[�J�C�oDLL���[�h�Ȃ�ȒP�ɏI��
		char buf[1024];
		return m_dll->command( NULL, cmd, buf, sizeof(buf) );
	}

	// NT���ǂ����̃`�F�b�N��
	kiPath tmpdir;
	static const bool isNT =
		(app()->osver().dwPlatformId==VER_PLATFORM_WIN32_NT);
	static const char* const closeShell =
		(isNT ? "cmd.exe /c " : "command.com /c ");

	// �R�}���h������쐬
	kiVar theCmd( m_name );
	theCmd.quote();
	theCmd += ' ';
	theCmd += cmd;

	if( m_type==SHLCMD )
	{
		// �V�F���R�}���h�̏ꍇ
		theCmd = closeShell + theCmd;
	}
	else if( m_type==EXEUS )
	{
		// US���[�h�̏ꍇ
		if( isNT )
		{
			::SetEnvironmentVariable( "NOAHCMD", theCmd );
			theCmd = "%NOAHCMD%";
		}

		// �ؑփo�b�`�t�@�C������
		myapp().get_tempdir(tmpdir);
		kiPath batname(tmpdir);
		batname += "ncmd.bat";
		kiFile bat;
		bat.open( batname,false );
		bat.write( "@CHCP 437\r\n@", 12 );
		bat.write( theCmd, theCmd.len() );
		bat.write( "\r\n@CHCP 932\r\n", 13 );

		theCmd  = closeShell;
		theCmd += batname;
	}

	// �v���Z�X�J�n
	PROCESS_INFORMATION pi;
	STARTUPINFO si={sizeof(STARTUPINFO)};
	si.dwFlags    =STARTF_USESHOWWINDOW;
	si.wShowWindow=mini?SW_MINIMIZE:SW_SHOW;
	if( !::CreateProcess( NULL,const_cast<char*>((const char*)theCmd),
		NULL,NULL,FALSE,CREATE_NEW_PROCESS_GROUP|NORMAL_PRIORITY_CLASS,
		NULL,NULL, &si,&pi ) )
		return 0xffff;

	// �I���ҋ@
	::CloseHandle( pi.hThread );
	while( WAIT_OBJECT_0 != ::WaitForSingleObject( pi.hProcess, 500 ) )
		kiWindow::msg();
	int ex;
	::GetExitCodeProcess( pi.hProcess, (DWORD*)&ex );
	::CloseHandle( pi.hProcess );

	// ��n��
	if( m_type==EXEUS )
		tmpdir.remove();
	return ex;
}

void CArcModule::ver( kiStr& str )
{
	// �o�[�W�������𐮌`���ĕ\��
	char *verstr="----", buf[200];
	if( m_dll )
	{
		if( WORD ver=m_dll->getVer() )
		{
			WORD sub=m_dll->getVerSub();
			::wsprintf( verstr=buf, "%d.%02d%c", ver/100, ver%100, (sub<100)?0:sub/100+'a'-1 );
		}
	}
	else if( m_type != NOTEXIST )
	{
		// �\�Ȃ烊�\�[�X����̎擾�����݂�
		if( CArchiver::GetVersionInfoStr( m_name, buf, sizeof(buf) ) )
			verstr = buf;
		else
			verstr = "OK!";
	}

	char ans[300];
	::wsprintf( ans, "%-12s %s", kiPath::name(m_name), verstr );
	str = ans;
}

bool CArcModule::lst_dll( const arcname& aname, aflArray& files, const char* wild )
{
	if( !m_dll )
		return false;
	kiPath nm(aname.basedir); nm+=aname.lname;
	HANDLE h = m_dll->openArc( app()->mainhwnd(), nm, M_CHECK_FILENAME_ONLY|M_ERROR_MESSAGE_OFF );
	if( !h ) return false;

	int ct=0;
	files.forcelen( 1 );
	if( 0==m_dll->findfirst( h, wild, &files[0].inf ) )
	{
		do
		{
			INDIVIDUALINFO& iii = files[ct].inf;
			files[ct].isfile =
				 ( *files[ct].inf.szAttribute!='d'
				&& !kiPath::endwithyen(files[ct].inf.szFileName)
				&& !(m_dll->getAttr( h )&FILE_ATTRIBUTE_DIRECTORY) );
			files.forcelen( 1+(++ct) );
		} while( 0==m_dll->findnext( h, &files[ct].inf ) );
	}
	files.forcelen( ct );

	m_dll->closeArc( h );
	return true;
}

int CArcModule::cnt( const kiPath& aname, kiPath& dname, const char* wild )
{
	int ans = aUnknown;

	if( m_dll )
		if( HANDLE h = m_dll->openArc( app()->mainhwnd(), aname, M_CHECK_FILENAME_ONLY|M_ERROR_MESSAGE_OFF ) )
		{
			INDIVIDUALINFO inf1st, inf;
			if( 0==m_dll->findfirst( h, wild, &inf1st ) )
			{
				for( const char* y=inf1st.szFileName; *y && *y!='\\' && *y!='/'; y=kiPath::next(y) );
				if( y!=inf1st.szFileName )
				{
					if( 0!=m_dll->findnext( h, &inf ) )
						ans = *y ? aSingleDir : aSingleFile;
					else if( *y && (y-inf1st.szFileName!=1 || inf1st.szFileName[0]!='.') )
					{
						ans = aSingleDir;
						do
							if( !ki_memcmp( inf1st.szFileName, inf.szFileName, (y-inf1st.szFileName)+1 ) )
							{
								ans = aUnknown;
								break;
							}
						while( 0==m_dll->findnext( h, &inf ) );
					}
					if( ans==aSingleDir )
						inf1st.szFileName[y-inf1st.szFileName]='\0', dname+=inf1st.szFileName;
				}
			}
			m_dll->closeArc( h );
		}

	return ans;
}

bool CArcModule::lst_exe( const char* lstcmd, aflArray& files,
	const char* BL, int BSL, const char* EL, int SL, int dx )
	// BeginLine, BeginSkipLine, EndLine, SkipLine, delta-x
{
	files.forcelen(0);

	// ��ƕϐ�
	const int BLLEN = ki_strlen(BL);
	const int ELLEN = ki_strlen(EL);
	int /*ct=0,*/ step=BSL;

	// EXE�ȊO�̂��̂ł̓_��
	if( m_type!=EXE && m_type!=EXEUS )
		return false;

	// �R�}���h������쐬
	kiVar theCmd( m_name );
	theCmd.quote();
	theCmd += ' ';
	theCmd += lstcmd;

	// �p�C�v�쐬�i�����Ƃ��p��ON�BDupHan����̖ʓ|���̂Łc(^^;�j
	HANDLE rp, wp;
	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES),NULL,TRUE};
	::CreatePipe( &rp, &wp, &sa, 4096 );

	// �v���Z�X�J�n
	PROCESS_INFORMATION pi;
	STARTUPINFO si = {sizeof(STARTUPINFO)};
	si.dwFlags     = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
	si.wShowWindow = SW_MINIMIZE;
	si.hStdOutput  = si.hStdError = wp;
	BOOL ok = 
		::CreateProcess( NULL,const_cast<char*>((const char*)theCmd),NULL,
			NULL, TRUE, CREATE_NEW_PROCESS_GROUP|NORMAL_PRIORITY_CLASS,
			NULL, NULL, &si,&pi );
	::CloseHandle( wp );

	// ���s������p�C�v����đ��I��
	if( !ok )
	{
		::CloseHandle( rp );
		return false;
	}
	::CloseHandle( pi.hThread );

	// ��͍��etc(�o�b�t�@�̃T�C�Y�̓p�C�v�̃T�C�Y�̔{�ȏ�łȂ��Ă͂Ȃ�Ȃ�)
	char buf[8192], *end=buf;
	for( bool endpr=false; !endpr; )
	{
		// �I���ҋ@
		endpr = (WAIT_OBJECT_0==::WaitForSingleObject(pi.hProcess,500));
		kiWindow::msg();

		// �p�C�v����ǂ݂Ƃ�
		DWORD red;
		::PeekNamedPipe( rp, NULL, 0, NULL, &red, NULL );
		if( red==0 )
			continue;
		::ReadFile( rp, end, buf+sizeof(buf)-end, &red, NULL );
		end += red;

		// �s�ɕ���
		char *lss=buf;
		for( char *ls, *le=buf; le<end; ++le )
		{
			// �s����T��
			for( lss=ls=le; le<end; ++le )
				if( *le=='\n' )
					break;
			if( le==end )
				break;

			// �擪�s�X�L�b�v����
			if( *BL )
			{
				if( BLLEN<=le-ls && ki_memcmp(BL,ls,BLLEN) )
					BL = "";
			}
			// �s�X�e�b�v����
			else if( --step<=0 )
			{
				step = SL;

				// �I�[�s����
				if( ELLEN==0 )
					{ if( le-ls<=1 ) break; }
				else if( ELLEN<=le-ls && ki_memcmp(EL,ls,ELLEN) )
					break;

				// �����X�L�b�v����
				if( dx>=0 )
					ls += dx;
				// �����u���b�N�X�L�b�v����
				else
				{
					for( ;ls<le;++ls )
						if( *ls!=' ' && *ls!='\t' && *ls!='\r' )
							break;
					for( int t=dx; ++t; )
					{
						for( ;ls<le;++ls )
							if( *ls==' ' || *ls=='\t' && *ls=='\r' )
								break;
						for( ;ls<le;++ls )
							if( *ls!=' ' && *ls!='\t' && *ls!='\r' )
								break;
					}
				}
				// �t�@�C�����R�s�[
				if( ls<le )
				{
					arcfile af; ki_memzero(&af, sizeof(af));
					af.inf.dwOriginalSize = 0xffffffff;
//					ki_memzero( &files[ct].inf, sizeof(files[ct].inf) );
//					files[ct].inf.dwOriginalSize = 0xffffffff;

					int i=0;
					bool prev_is_space=false;
					while( i<FNAME_MAX32 && ls<le )
					{
						if( *ls==' ' )
						{
							if( prev_is_space )
								break;
							prev_is_space = true;
						}
						else if( *ls=='\t' || *ls=='\r' )
							break;
						else
							prev_is_space = false;

						af.inf.szFileName[i++] = *ls++;
//						files[ct].inf.szFileName[i++] = *ls++;
					}
					if( prev_is_space )
						--i;
					if( i )
					{
/*
						files[ct].inf.szFileName[i] = '\0';
						files[ct].isfile = true;
						files.forcelen( 1+(++ct) );
*/
						af.inf.szFileName[i] = '\0';
						af.isfile = true;
						files.add(af);
					}
				}
			}
		}
		// �o�b�t�@�V�t�g
		if( lss != buf )
			ki_memmov( buf, lss, end-lss ), end=buf+(end-lss);
		else if( end==buf+sizeof(buf) )
			end = buf;
	}

	// ���I��
	::CloseHandle( pi.hProcess );
	::CloseHandle( rp );
	return true;
}

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// �o�[�W������񃊃\�[�X�擾

bool CArchiver::GetVersionInfoStr( char* name, char* buf, size_t cbBuf )
{
	static bool old = mycnf().oldver();
	if( old )
		return false;

	DWORD dummy = 0;
	DWORD siz = ::GetFileVersionInfoSize( name, &dummy );
	if( siz == 0 )
		return false;

	bool got = false;
	BYTE* vbuf = new BYTE[siz];
	if( 0 != ::GetFileVersionInfo( name, 0, siz, vbuf ) )
	{
		WORD* tr = NULL;
		UINT cbTr = 0;

		// �ŏ��Ɍ���������ƃR�[�h�y�[�W�ŏ��擾
		if( ::VerQueryValue( vbuf,
			"\\VarFileInfo\\Translation", (void**)&tr, &cbTr )
		 && cbTr >= 4 )
		{
			char blockname[500]="";
			::wsprintf( blockname,
				"\\StringFileInfo\\%04x%04x\\ProductVersion",
				tr[0], tr[1] );

			char* inf = NULL;
			UINT cbInf = 0;
			if( ::VerQueryValue( vbuf, blockname, (void**)&inf, &cbInf )
			 && cbInf < cbBuf-1 )
			{
				for( char* v=buf; *inf && cbInf; ++inf,--cbInf )
					if( *inf != ' ' )
						*v++ = (*inf==',' ? '.' : *inf);
				*v = '\0';
				got = true;
			}
		}
		else
		{
			void* fi = NULL;
			UINT cbFi = 0;
			VS_FIXEDFILEINFO vffi;
			if( ::VerQueryValue( vbuf, "\\", &fi, &cbFi )
			 && sizeof(vffi)<=cbFi )
			{
				ki_memcpy( &vffi, fi, sizeof(vffi) );
				if( vffi.dwFileVersionLS >= 0x10000 )
					::wsprintf( buf, "%d.%d.%d", vffi.dwFileVersionMS>>16,
						vffi.dwFileVersionMS&0xffff, vffi.dwFileVersionLS>>16 );
				else
					::wsprintf( buf, "%d.%d", vffi.dwFileVersionMS>>16,
						vffi.dwFileVersionMS&0xffff );
				got = true;
			}
		}
	}

	delete [] vbuf;
	return got;
}
