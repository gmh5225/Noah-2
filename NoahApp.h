// NoahApp.h
//-- CNoahApp -- application object of 'Noah' --

#ifndef AFX_NOAHAPP_H__11AA6C03_4946_4279_B79C_F28896001357__INCLUDED_
#define AFX_NOAHAPP_H__11AA6C03_4946_4279_B79C_F28896001357__INCLUDED_

#include "NoahAM.h"
#include "NoahCM.h"

class CNoahApp : public kiApp  
{
public: //-- �O�����C���^�[�t�F�C�X ------

	//-- ���k/�𓀍��
	void do_cmdline( bool directcall=false );
	void do_files( const cCharArray& files,
				   const cCharArray* opts=NULL,
				   bool basicaly_ignore=false );

	//-- �G�p(��)
	void open_folder( const kiPath& path,int from=0 );
	void get_tempdir( kiPath& tmp );
	bool is_writable_dir( const kiPath& path );

	//-- Noah�I�u�W�F�N�g�擾�p�}�N��
#	define myapp() (*(CNoahApp*)app())
#	define myarc() (*(((CNoahApp*)app())->arc()))
#	define mycnf() (*(((CNoahApp*)app())->cnf()))

public: //-- �������� --------------------

	CNoahArchiverManager* arc(){ return &m_arcMan; }
	CNoahConfigManager* cnf()  { return &m_cnfMan; }
private:
	void run( kiCmdParser& cmd );

	CNoahArchiverManager m_arcMan;
	CNoahConfigManager   m_cnfMan;
	kiCmdParser*         m_pCmd;

	kiPath m_tmpDir;
	UINT   m_tmpID;
};

#endif
