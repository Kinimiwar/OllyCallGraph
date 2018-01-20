
// MFCApplication1View.h : CMFCApplication1View ��Ľӿ�
//

#pragma once


class CPluginAppView : public CTreeView
{
protected: // �������л�����
	CPluginAppView();
	DECLARE_DYNCREATE(CPluginAppView)

// ����
public:
	CPluginAppDoc* GetDocument() const;

// ����
public:

// ��д
public:	
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate(); // called first time after construct

protected:
	

// ʵ��
public:
	virtual ~CPluginAppView();


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CPluginAppView.cpp �еĵ��԰汾
inline CPluginAppDoc* CPluginAppView::GetDocument() const
{ return reinterpret_cast<CPluginAppDoc*>(m_pDocument); }
#endif

