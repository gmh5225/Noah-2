//--- K.I.LIB ---
// kl_cmd.h : commandline parser

#include "stdafx.h"
#include "kilib.h"


//------------------------ ������̃����������Ȃ� -----------------------//


kiCmdParser::kiCmdParser( char* cmd, bool ignoreFirst )
{
	m_Buffer = NULL;
	if( cmd )
		doit( cmd, ignoreFirst );
}

kiCmdParser::kiCmdParser( const char* cmd, bool ignoreFirst )
{
	m_Buffer=NULL;
	if( cmd )
	{
		m_Buffer = new char[ ki_strlen(cmd)+1 ];
		ki_strcpy( m_Buffer, cmd );
		doit( m_Buffer, ignoreFirst );
	}
}

kiCmdParser::~kiCmdParser()
{
	delete [] m_Buffer;
}


//---------------------------- �����̏��� -----------------------------//


void kiCmdParser::doit( char* start, bool ignoreFirst )
{
	char* p=start;
	char endc;
	bool first = true;

	while( *p!='\0' )
	{
		// �]���ȋ󔒂̓X�L�b�v
		while( *p==' ' ) //|| *p=='\t' || *p=='\r' || *p=='\n' )
			p++;

		// " ��������A���̎|�L�^���Ă���Ɉ�i�߂�
		if( *p=='"' )
			endc='"', p++;
		else
			endc=' ';

		// end-of-text �Ȃ�I��
		if( *p=='\0' )
			break;

		if( first && ignoreFirst )
			first = false;
		else
		{
			// ������ۑ�
			if( *p=='-' )
				m_Switch.add( p );
			else
				m_Param.add( p );
		}

		// �����̏I���ցc
		while( *p!=endc && *p!='\0' )
			p++;

		// �I����'\0'�ɂ��邱�Ƃɂ���āA��������؂�
		if( *p!='\0' )
			*(p++) = '\0';
	}
}
