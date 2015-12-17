//--- K.I.LIB ---
// kl_reg.h : registry and ini-file operation

#ifndef AFX_KIREGKEY_H__4FD5E1B3_B8FE_45B3_B19E_3D30407C94BA__INCLUDED_
#define AFX_KIREGKEY_H__4FD5E1B3_B8FE_45B3_B19E_3D30407C94BA__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// ���W�X�g�����쁕ini����

class kiRegKey
{
public: //-- �O�����C���^�[�t�F�C�X --------------------------

	// �J��������
	bool open( HKEY parent, LPCTSTR keyname, REGSAM access = KEY_ALL_ACCESS );
	bool create( HKEY parent, LPCTSTR keyname, REGSAM access = KEY_ALL_ACCESS );
	void close()
		{
			if( m_hKey )
				RegCloseKey( m_hKey );
		}

	// �T�u�L�[�����݂����ۂ�
	bool exist( LPCTSTR keyname )
		{
			HKEY k;
			if( ERROR_SUCCESS==RegOpenKeyEx( m_hKey,keyname,0,KEY_READ,&k ) )
			{
				RegCloseKey( k );
				return true;
			}
			return false;
		}
	// HKEY�փL���X�g
	operator HKEY() const
		{
			return m_hKey;
		}

	// �l�𓾂�
	bool get( LPCTSTR valname, DWORD* val );
	bool get( LPCTSTR valname, BYTE* val, DWORD siz );
	bool get( LPCTSTR valname, kiStr* val );

	// �l��ݒ�
	bool set( LPCTSTR valname, DWORD val );
	bool set( LPCTSTR valname, BYTE* val, DWORD siz );
	bool set( LPCTSTR valname, LPCTSTR val );

	// �폜
	bool del( LPCTSTR valname );
	bool delSubKey( LPCTSTR keyname );

public: //-- �������� -----------------------------------

	kiRegKey()
		{
			m_hKey = NULL;
		}

	virtual ~kiRegKey()
		{
			close();
		}

private:

	HKEY m_hKey;
	static bool delSubKeyRecursive( HKEY k, LPCTSTR n );
};

class kiIniFile
{
public: //-- �O�����C���^�[�t�F�C�X --------------------------

	// ini�t�@�C������ݒ�
	void setFileName( const char* ini, bool exepath=true );
	void setSection( const char* section )
		{ m_CurSec = section; }

	// �ǂݍ���
	// �� ���ӁIgetStr�̕Ԓl�͓����o�b�t�@�ȈׁA
	// ���@�@�@ �Ăяo������ȊO�͓��e��ۏ؂��Ȃ��B
	int getInt( const char* key, int defval );
	bool getBool( const char* key, bool defval );
	const char* getStr( const char* key, const char* defval );

	// ��������
	bool putStr( const char* key, const char* val );
	bool putInt( const char* key, int val );
	bool putBool( const char* key, bool val );

private: //-- �������� -----------------------------------

	kiPath m_FileName;
	kiStr m_CurSec;
	char m_StrBuf[256];
};

#endif
