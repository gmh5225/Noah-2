//--- K.I.LIB ---
// kl_find.h : FindFirstFile wrapper

#ifndef AFX_KIFINDFILE_H__86462791_815C_4F44_9F16_802B54B411BA__INCLUDED_
#define AFX_KIFINDFILE_H__86462791_815C_4F44_9F16_802B54B411BA__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// �t�@�C������

class kiFindFile
{
public: //-- �O�����C���^�[�t�F�C�X --------------------------

	static bool findfirst( const char* wild, WIN32_FIND_DATA* pfd );
	bool begin( const char* wild );
	bool next( WIN32_FIND_DATA* pfd );

public: //-- �������� -----------------------------------

	kiFindFile()
		{ h = INVALID_HANDLE_VALUE; }
	virtual ~kiFindFile()
		{ close(); }
	void close();

private:
	HANDLE h;
	bool first;
	WIN32_FIND_DATA fd;
};

#endif
