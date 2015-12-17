//--- K.I.LIB ---
// kl_str.h : string classes for K.I.LIB

#ifndef AFX_KISTR_H__1932CA2C_ACA6_4606_B57A_ACD0B7D1D35B__INCLUDED_
#define AFX_KISTR_H__1932CA2C_ACA6_4606_B57A_ACD0B7D1D35B__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiStr : �P��������

class kiStr
{
friend void kilib_startUp();

private: //-- �O���[�o���ȏ����������Ȃ� ---------------------

	static void init();

public: //-- �O�����C���^�[�t�F�C�X --------------------------

	// 2byte�����̏�����������(�����悤�ȋC��)
	static char* next( char* p )
		{ return p+st_lb[(*p)&0xff]; }
	static const char* next( const char* p )
		{ return p+st_lb[(*p)&0xff]; }
	static bool isLeadByte( char c )
		{ return st_lb[c&0xff]==2; }

	// ������
	kiStr( int start_size = 100 );
	kiStr( const char* s, int min_size = 100 );
	explicit kiStr( const kiStr& s );

	// ���Z�q
	kiStr& operator = ( const kiStr& );
	kiStr& operator = ( const char* s );
	kiStr& operator += ( const char* s );
	kiStr& operator += ( char c );
	bool operator == ( const char* s ) const;
	bool isSame( const char* s )       const;
	operator const char*()             const;
	int len()                          const;
	void lower()
		{ ::CharLower(m_pBuf); }
	void upper()
		{ ::CharUpper(m_pBuf); }
	kiStr& setInt( int n, bool cm=false );
	void replaceToSlash() {
		for(char* p=m_pBuf; *p; p=next(p))
			if(*p=='\\')
				*p='/';
	}

	// ���\�[�X���烍�[�h
	kiStr& loadRsrc( UINT id );

	kiStr& removeTrailWS();

protected: //-- �h���N���X���� -----------------------------

	char* m_pBuf;
	int   m_ALen;

private: //-- �������� -------------------------------------

	static char st_lb[256];

public:

	virtual ~kiStr();
};

inline const kiStr operator+(const kiStr& x, const kiStr& y)
	{ return kiStr(x) += y; }
inline const kiStr operator+(const char* x, const kiStr& y)
	{ return kiStr(x) += y; }
inline const kiStr operator+(const kiStr& x, const char* y)
	{ return kiStr(x) += y; }

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiPath : �p�X���L�̏����p�֐��t��������

class kiPath : public kiStr
{
public: //-- �O�����C���^�[�t�F�C�X --------------------------

	// ������
	kiPath() : kiStr( MAX_PATH ){}
	explicit kiPath( const char* s ) : kiStr( s, MAX_PATH ){}
	explicit kiPath( const kiStr& s ) : kiStr( s, MAX_PATH ){}
	explicit kiPath( const kiPath& s ) : kiStr( s, MAX_PATH ){}
	kiPath( int nPATH, bool bs = true ) : kiStr( MAX_PATH )
		{
			beSpecialPath( nPATH );
			if( nPATH != Exe_name )
				beBackSlash( bs );
		}

	// operator
	void operator = ( const char* s ){ kiStr::operator =(s); }

	// ����p�X�擾
	void beSpecialPath( int nPATH );
	enum { Win=0x1787, Sys, Tmp, Prg, Exe, Cur, Exe_name,
			Snd=CSIDL_SENDTO, Dsk=CSIDL_DESKTOP, Doc=CSIDL_PERSONAL };

	// �Z���p�X
	void beShortPath();

	// �Ō�̃o�b�N�X���b�V������
	void beBackSlash( bool add );

	// �f�B���N�g�����̂�
	bool beDirOnly();
	// �t�@�C����except�g���q�S��
	void getBody( kiStr& str ) const;
	// �t�@�C����except�g���q���
	void getBody_all( kiStr& str ) const;

	// �����K�wmkdir
	void mkdir();
	// �����K�wrmdir
	void remove();

	// �h���C�u�^�C�v
	UINT getDriveType() const;
	// �����f�B���N�g���ɂ��邩�ǂ���
	bool isInSameDir(const char* r) const;

	// [static] �f�B���N�g�������܂܂Ȃ��A�t�@�C�����̂ݒ��o
	static const char* name( const char* str );
	// [static] �Ō�̊g���q�B�������NULL
	static const char* ext( const char* str );
	// [static] �g���q�S���B�������NULL
	static const char* ext_all( const char* str );
	// [static] \ / �ŏI��邩�ۂ�
	static bool endwithyen( const char* str );

	// non-static-ver
	const char* name() const
		{ return name(m_pBuf); }
	const char* ext() const
		{ return ext(m_pBuf); }
	const char* ext_all() const
		{ return ext_all(m_pBuf); }
};

#endif
