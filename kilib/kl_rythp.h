//--- K.I.LIB ---
// kl_rythp.h : interpretor for simple script langauage 'Rythp'

#ifndef AFX_KIRYTHPVM_H__4F3C28A9_7EFE_4605_A149_2C0B9A9236E5__INCLUDED_
#define AFX_KIRYTHPVM_H__4F3C28A9_7EFE_4605_A149_2C0B9A9236E5__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiVar : Rythp�p��Variant�ϐ��^�B�قƂ�ǂ�����kiStr�B

class kiVar : public kiStr
{
public:
	kiVar() : kiStr(20) {}
	explicit kiVar( const char* s ) : kiStr( s, 20 ){}
	explicit kiVar( const kiStr& s ) : kiStr( s, 20 ){}
	explicit kiVar( const kiVar& s ) : kiStr( s, 20 ){}
	void operator = ( const char* s ){ kiStr::operator =(s); }

	int getInt();
	kiVar& quote();
	kiVar& unquote();
};

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiRythpVM : �ŏ���Rythp�B���p�ɂ́A�h�����ēƎ��� exec_function ���������ׂ�

class kiRythpVM
{
public:
	kiRythpVM();
	virtual ~kiRythpVM() {}

public:
	// eval
	void eval( char* str, kiVar* ans=NULL );

protected:
	// ������K����eval��ϐ��u�������������`�Ŏ擾
	void getarg( char* a, bool b, kiVar* arg );

	// function���s�B[ bool=�����������H�A name=function���A a,b,c=�����A r=�Ԓl ]
	virtual bool exec_function( const kiVar& name,
		const CharArray& a, const BoolArray& b,int c, kiVar* r );

private:
	// �ϐ�
	kiVar ele[256];

	// �p�����[�^����
	static char* split_tonext( char* p );
	static char* split_toend( char* p );
	static bool split( char* buf, CharArray& argv, BoolArray& argb, int& argc );
};

#endif
