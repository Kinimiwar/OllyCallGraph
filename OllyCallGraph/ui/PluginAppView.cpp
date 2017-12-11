
// MFCApplication1View.cpp : CMFCApplication1View ���ʵ��
//

#include "../stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PluginApp.h"
#endif

#include "PluginAppDoc.h"
#include "PluginAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CPluginAppView, CView)

BEGIN_MESSAGE_MAP(CPluginAppView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication1View ����/����

CPluginAppView::CPluginAppView()
{
	// TODO:  �ڴ˴���ӹ������

}

CPluginAppView::~CPluginAppView()
{
}

BOOL CPluginAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View ����

void CPluginAppView::OnDraw(CDC* /*pDC*/)
{
	CPluginAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CPluginAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPluginAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	pluginApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication1View ���

#ifdef _DEBUG
void CPluginAppView::AssertValid() const
{
	CView::AssertValid();
}

void CPluginAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPluginAppDoc* CPluginAppView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPluginAppDoc)));
	return (CPluginAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View ��Ϣ�������
