// NoahCM.h
//-- CNoahConfigManager -- save / load / modify the setting of 'Noah' --

#ifndef AFX_NOAHCM_H__ACE475C1_D925_4F9E_BDCA_783B921E6FD5__INCLUDED_
#define AFX_NOAHCM_H__ACE475C1_D925_4F9E_BDCA_783B921E6FD5__INCLUDED_

class CNoahConfigManager;

class CNoahConfigDialog : public kiPropSheet
{
public:
	class CCmprPage : public kiPropSheetPage
	{
	public:
		CCmprPage();
	private:
		BOOL onInit();
		bool onOK();
		bool onCancel();
		BOOL CALLBACK proc( UINT msg, WPARAM wp, LPARAM lp );
		void correct( const char* ext, bool first );
		void SetUpToolTip();
	private:
		HWND m_tooltip;
	};
	class CMeltPage : public kiPropSheetPage
	{
	public:
		CMeltPage();
	private:
		BOOL onInit();
		bool onOK();
		BOOL CALLBACK proc( UINT msg, WPARAM wp, LPARAM lp );
		void correct();
	};
	class CWinXPage : public kiPropSheetPage
	{
	public:
		CWinXPage();
	private:
		BOOL onInit();
		BOOL CALLBACK proc( UINT msg, WPARAM wp, LPARAM lp );
		bool onOK();
	};
	class CAssPage : public kiDialog
	{
	public:
		CAssPage( HWND parent );
	private:
		BOOL onInit();
		BOOL CALLBACK proc( UINT msg, WPARAM wp, LPARAM lp );
		bool onOK();
	};
	class CInfoPage : public kiPropSheetPage
	{
	public:
		CInfoPage();
	private:
		BOOL onInit();
	};

public:
	CNoahConfigDialog();

private:
	bool onOK();
	bool onCancel();
	void onApply();
	void onHelp();
	void onCommand( UINT id );
	BOOL onInit();
	void onDrop( HDROP hdrop );
	static void shift_and_button();
};

enum loading_flag
{
	Mode    = 1,
	Melt    = 2,
	Compress= 4,
	Shell   = 8,
	OpenDir =16,
	All     =31,
};

class CNoahConfigManager
{
public: //-- ����

	void init();
	void load( loading_flag what );
	void save();
	void dialog();

public: //-- �ݒ荀�ڎ擾�p�C���^�[�t�F�C�X

	// Section: Mode
	const int     mode()  { return m_Mode; }  // 0:���� 1:���D 2:��D 3:���
	const bool  miniboot(){ return m_MiniBoot; } // �ŏ����N���H
	const bool  oldver()  { return m_OldVer; }// �Â��`���Ńo�[�W�����\��
	const int   extnum()  { return m_OneExt ? 1 : m_ZeroExt ? 0 : -1; } // ���ɖ��쐬���Ɋg���q�ƌ��Ȃ�����
	const int multiboot_limit() { return m_MbLim; } // ���d�N���������l
	// Section: Melt
	const kiPath& mdir()  { return m_MDir; }  // �𓀐�
	const bool    mdirsm(){ return m_MDirSm; }// �����f�B���N�g���ɉ𓀁H
	const int     mkdir() { return m_MkDir; } // 0:x 1:file 2:dir 3:o
	const bool    mnonum(){ return m_MNoNum; }// �����ȗ�
	const char*   kill()  { return m_Kill; }// OFF�ɂ���������[�`��
	// Section: Compress
	const kiPath& cdir()  { return m_CDir; }  // ���k��
	const bool    cdirsm(){ return m_CDirSm; }// �����f�B���N�g���Ɉ��k�H
	const kiStr&  cext()  { return m_CExt; }  // ���k�`��
	const kiStr&  cmhd()  { return m_CMhd; }  // ���k���\�b�h
	// Section: Shell
	// Section: OpenDir
	const bool    modir() { return m_MODir; } // �𓀌�J���H
	const bool    codir() { return m_CODir; } // ���k��J���H
	const kiStr&  openby(){ return m_OpenBy; }// �J���v���O����(�B��)

private: //-- �����ϐ�

	unsigned long m_Loaded;
	kiIniFile m_Ini;
	kiStr m_UserName;
	HINSTANCE m_hNoahXtDLL;
	enum { NOSHL, NOADMIN, SHLOK } m_bShlOK;

	// �ݒ荀��
	int    m_Mode;
	kiPath m_MDir, m_CDir;
	bool   m_MODir,m_CODir,m_MDirSm,m_CDirSm;
	int    m_MkDir;
	int    m_MbLim;
	kiStr  m_CExt;
	kiStr  m_OpenBy;
	kiStr  m_CMhd;
	bool   m_MNoNum;
	bool   m_SCSendTo,m_SCDesktop;
	kiStr  m_Kill;
	bool   m_SECmp, m_SEExt, m_bAsso[13];
	bool   m_MiniBoot;
	bool   m_OldVer;
	bool   m_OneExt, m_ZeroExt;

	// �֐����[�h
	FARPROC getProc( const char* name );

public:
	CNoahConfigManager()
		{
			m_hNoahXtDLL = NULL;
		}
	~CNoahConfigManager()
		{
			if( m_hNoahXtDLL )
				::FreeLibrary( m_hNoahXtDLL );
		}
friend class CNoahConfigDialog::CCmprPage;
friend class CNoahConfigDialog::CMeltPage;
friend class CNoahConfigDialog::CWinXPage;
friend class CNoahConfigDialog::CInfoPage;
friend class CNoahConfigDialog::CAssPage;
};

#endif
