//--- K.I.LIB ---
// kl_dnd.h : drag and drop operation

#ifndef AFX_KIDROPSOURCE_H__141BEF0D_0DA2_4156_93E4_313535916A23__INCLUDED_
#define AFX_KIDROPSOURCE_H__141BEF0D_0DA2_4156_93E4_313535916A23__INCLUDED_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiDataObject : �h���b�v�f�[�^�Ƃ��Ă̕W������

class kiDataObject : public IDataObject
{
protected: // �h���N���X��������

	virtual bool giveData( const FORMATETC& fmt, STGMEDIUM* stg, bool firstcall ) = 0;
	void addFormat( const FORMATETC& frm )
		{
			m_FormatList.add( frm );
		}

protected:	//-- IUnknown -----------

	kiDataObject();
	STDMETHODIMP         QueryInterface( REFIID, void** );
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
private:
	ULONG                m_cRef;

private: //-- IDataObject ------------

	STDMETHODIMP GetData( FORMATETC*, STGMEDIUM* );
	STDMETHODIMP QueryGetData( FORMATETC* );
	STDMETHODIMP EnumFormatEtc( DWORD, IEnumFORMATETC** );
	STDMETHODIMP GetDataHere( FORMATETC*, STGMEDIUM* )
		{
			return E_NOTIMPL;
		}
	STDMETHODIMP GetCanonicalFormatEtc( FORMATETC*, FORMATETC* )
		{
			return E_NOTIMPL;
		}
	STDMETHODIMP SetData( FORMATETC*, STGMEDIUM*, BOOL )
		{
			return E_NOTIMPL;
		}
	STDMETHODIMP DAdvise( FORMATETC*, DWORD, IAdviseSink*, DWORD* )
		{
			return OLE_E_ADVISENOTSUPPORTED;
		}
	STDMETHODIMP DUnadvise( DWORD )
		{
			return OLE_E_NOCONNECTION;
		}
	STDMETHODIMP EnumDAdvise( IEnumSTATDATA** )
		{
			return OLE_E_ADVISENOTSUPPORTED;
		}

private: //-- �������� -----------------

	kiArray<FORMATETC> m_FormatList;
	bool m_bFirst;
	friend class kiDataObject_Enum;

public:
	void begin()
		{
			m_bFirst = true;
		}
};

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
// kiDropSource : �h���b�v���Ƃ��Ă̕W������

class kiDropSource : public IDropSource
{
public: //-- �h���b�O���h���b�v���s�I

	static bool DnD( kiDataObject* pObj, DWORD efct, DWORD* pefct=NULL );

private: //-- IUnknown

	kiDropSource();
	STDMETHODIMP         QueryInterface( REFIID, void** );
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	ULONG                m_cRef;

private: //-- IDropSource

	STDMETHODIMP QueryContinueDrag( BOOL, DWORD );
	STDMETHODIMP GiveFeedback( DWORD );
};

#endif
