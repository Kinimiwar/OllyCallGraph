#pragma once
#include "../stdafx.h"
#include "../modal/InstructionMemo.h"

class CPluginAppDoc : public CDocument
{
protected:
	CPluginAppDoc();
	DECLARE_DYNCREATE(CPluginAppDoc)
// ����
private:
	InstructionMemo memo;

public:
	InstructionMemo& getMemo();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif 

public:
	virtual ~CPluginAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif 
};

