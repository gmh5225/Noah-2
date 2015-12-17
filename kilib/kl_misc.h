//--- K.I.LIB ---
// kl_misc.h : common-classes for K.I.LIB

#ifndef AFX_KILIBBASE_H__89998F34_A9FE_4A27_A159_671F85AA9383__INCLUDED_
#define AFX_KILIBBASE_H__89998F34_A9FE_4A27_A159_671F85AA9383__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// �g�p����O���֐������ƂȂ��}�N�������Ă���
// �ǋL�F���ł���Ȃ��Ƃ�����񂾁c�H�@���@�̂̎���(^^;

#define ki_strlen(p)      ::lstrlen(p)
#define ki_strcpy(p,s)    ::lstrcpy(p,s)
#define ki_strcat(p,s)    ::lstrcat(p,s)
#define ki_strcmp(p,s)    ::lstrcmp(p,s)
#define ki_strcmpi(p,s)   ::lstrcmpi(p,s)
#define ki_memzero(p,l)   ::ZeroMemory(p,l)
#define ki_memcpy(p,s,l)  ::CopyMemory(p,s,l)
#define ki_memmov(p,s,l)  ::MoveMemory(p,s,l)
#define ki_memset(p,c,l)  ::FillMemory(p,l,c)
inline bool ki_memcmp( const char* x, const char* y, int l )
{
	while( *x++==*y++ && --l );
	return l==0;
}

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiArray : �z��̂悤�ȃL���[�̂悤�ȑ㕨

template <class T> class kiArray
{
public: //-- �O�����C���^�[�t�F�C�X --------------------------

	// �����T�C�Y( 10�`255 )�ŏ�����
	kiArray( unsigned char start_size=10 )
		{
			m_pArray = new T[ m_ALen=start_size ];
			m_Len = 0;
		}

	// �z�����ɂ���
	void empty()
		{
			m_Len = 0;
		}

	// �v�f�����擾
	unsigned long len() const
		{
			return m_Len;
		}

	// �����Ɉ�ǉ�
	void add( const T& obj )
		{
			if( m_Len>=m_ALen )
			{
				T* p = new T[ m_ALen<<=1 ];
				for( unsigned long i=0; i!=m_Len; i++ )
					p[i] = m_pArray[i];
				delete [] m_pArray;
				m_pArray = p;
			}
			m_pArray[ m_Len++ ] = obj;
		}

	// �v�f�ɃA�N�Z�X
	T& operator []( unsigned long i )
		{
			return m_pArray[i];
		}
	const T& operator []( unsigned long i ) const
		{
			return m_pArray[i];
		}

	// �z��R�s�[
	kiArray<T>& operator = ( const kiArray<T>& o )
		{
			if( &o != this )
			{
				empty();
				for( unsigned int i=0; i!=o.len(); i++ )
					add( o[i] );
			}
			return *this;
		}

	//-- ������Ɗ댯�ȃ��\�b�h�Q
	void alloc( unsigned long x )
		{
			if( x > m_ALen )
			{
				T* p = new T[ m_ALen=(m_ALen<<1)>x?(m_ALen<<1):x ];
				for( unsigned long i=0; i!=m_Len; i++ )
					p[i] = m_pArray[i];
				delete [] m_pArray;
				m_pArray = p;
			}
		}
	void forcelen( unsigned long x )
		{
			alloc( x );
			m_Len = x;
		}

private: //-- �������� -----------------------------------

	T* m_pArray;
	unsigned long m_Len, m_ALen;

public:

	virtual ~kiArray()
		{
			delete [] m_pArray;
		}
};

#define  BoolArray kiArray<bool>
#define  CharArray kiArray<char*>
#define cCharArray kiArray<const char*>
#define   StrArray kiArray<kiStr>

#endif
