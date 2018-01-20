
// MFCApplication1View.cpp : CMFCApplication1View 类的实现
//

#include "../stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PluginApp.h"
#endif

#include "PluginAppDoc.h"
#include "PluginAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CPluginAppView, CTreeView)

BEGIN_MESSAGE_MAP(CPluginAppView, CTreeView)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CPluginAppView::CPluginAppView()
{
	// TODO:  在此处添加构造代码

}

CPluginAppView::~CPluginAppView()
{
}

BOOL CPluginAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}


void CPluginAppView::OnInitialUpdate()
{
	CTreeCtrl& tree = GetTreeCtrl();

	HTREEITEM hItem, hSubItem;
	hItem = tree.InsertItem(_T("Global"), TVI_ROOT); //在根结点上添加Parent1
}

// CMFCApplication1View 绘制

void CPluginAppView::OnDraw(CDC* /*pDC*/)
{
	CPluginAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}

// 成功返回0，失败返回 -1
int CPluginAppView::OnCreate(LPCREATESTRUCT lpcs)
{
	int result =  CTreeView::OnCreate(lpcs);
	return result;
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




// CMFCApplication1View 诊断

#ifdef _DEBUG
void CPluginAppView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CPluginAppView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CPluginAppDoc* CPluginAppView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPluginAppDoc)));
	return (CPluginAppDoc*)m_pDocument;
}

void CPluginAppView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{

}

#endif //_DEBUG


// CMFCApplication1View 消息处理程序
