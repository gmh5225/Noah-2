// NoahAM.h
//-- CNoahArchiverManager -- control many archiver routines --

#ifndef AFX_NOAHAM_H__CCE30761_D91B_4570_931A_6C165B19B22F__INCLUDED_
#define AFX_NOAHAM_H__CCE30761_D91B_4570_931A_6C165B19B22F__INCLUDED_

#include "Archiver.h"

class CNoahArchiverManager
{
public: //-- �O�����C���^�[�t�F�C�X ------------

	// ������
	void init();

	// �t�@�C�����X�g���L��
	unsigned long set_files( const cCharArray& files );
	unsigned long file_num() { return m_FName.len(); }
	const kiPath& get_basepath() { return m_BasePath; }
	bool map_melters( int mode );
	bool map_compressor( const char* ext, const char* method, bool sfx );

	// ��( �𓀐�Dir�ȊO�̏��͒��ŏ���Ɏ擾���܂� )
	void do_melting( kiPath& destdir );
	// �{��( �𓀐�Dir�ȊO�̏��͒��ŏ���Ɏ擾���܂� )
	void do_listing( kiPath& destdir );
	// ���k
	void do_compressing( kiPath& destdir, bool each );


	// �o�[�W�������
	void get_version( kiStr& str );
	// ���k�`�����X�g
	void get_cmpmethod( const char* set, int& def_mhd, StrArray& mhd_list, bool need_ext=false, cCharArray* ext_list=NULL );
	// b2e����ȏ�ǂݍ��܂�Ă����true
	bool b2e_enabled() { return m_b2e; }


private: //-- �������� ---------------------------

	// �Q�d�t�H���_�����Ȃ�
	bool break_ddir( kiPath& dir, bool onlydir );
	CArchiver* fromExt( const char* ext );
	void generate_dirname( const char* src, kiPath& dst, bool rmn );

	kiPath   m_BasePath;
	wfdArray m_FName;
	kiArray<CArchiver*> m_AList;
	kiArray<kiPath> m_BasePathList;
	bool m_b2e;

	// �𓀗p���蓖��
	kiArray<CArchiver*> m_Melters;
	// ���k�p���蓖��
	CArchiver* m_Compressor;
	int        m_Method;
	bool       m_Sfx;

public:
	~CNoahArchiverManager()
		{
			for( unsigned int i=0; i!=m_AList.len(); i++ )
				delete m_AList[i];
		}
};

#endif
