//--- K.I.LIB ---
// kl_cmd.h : commandline parser

#ifndef AFX_KICMDPARSER_H__843A27E0_5DBF_48AF_A748_FA7F111F699A__INCLUDED_
#define AFX_KICMDPARSER_H__843A27E0_5DBF_48AF_A748_FA7F111F699A__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiCmdParser : �R�}���h�������char*�̔z��ɕ���

class kiCmdParser
{
public: //-- �O�����C���^�[�t�F�C�X --------------------------

	// ������ŏ�����
	kiCmdParser( char* cmd, bool ignoreFirst=false );
	kiCmdParser( const char* cmd, bool ignoreFirst=false );

	// �X�C�b�`������̔z��
	cCharArray& option()
		{ return m_Switch; }

	// �X�C�b�`�ȊO�̕�����̔z��
	cCharArray& param()
		{ return m_Param; }

private: //-- �������� -----------------------------------

	void doit( char* start, bool ignoreFirst );
	cCharArray m_Param;
	cCharArray m_Switch;
	char* m_Buffer;

public:

	virtual ~kiCmdParser();
};

#endif
