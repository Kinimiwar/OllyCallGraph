#include "../stdafx.h"

#include "WatchWnd.h"



CWatchWnd::CWatchWnd()
{
}


CWatchWnd::~CWatchWnd()
{
}



BEGIN_MESSAGE_MAP(CWatchWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CWatchWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);
	m_wndList.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}



int CWatchWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	CRect rectClient;
	GetClientRect(rectClient);

	DWORD style = TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		WS_CHILD | WS_VISIBLE | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT;
	CRect dump(0, 0, 200, 200);
	if (!m_wndTree.Create(style, dump, this, 1))
		return -1;

	//LVS_REPORT
	m_wndList.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_EX_GRIDLINES, rectClient, this, 1);

	MakeDefaultColumns();

	AdjustLayout();
	return 0;
}

void CWatchWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	/*m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);*/

	AdjustLayout();
}

void CWatchWnd::MakeDefaultColumns()
{
	LV_COLUMN colName;
	colName.pszText = _T("����");
	colName.mask = LVCF_TEXT | LVCF_MINWIDTH;
	m_wndList.InsertColumn(0, &colName);
	m_wndList.SetColumnWidth(0, 100);

	LV_COLUMN colValue;
	colValue.pszText = _T("ֵ");
	colValue.mask = LVCF_TEXT;
	m_wndList.InsertColumn(1, &colValue);
	m_wndList.SetColumnWidth(1, 200);

	LV_COLUMN colType;
	colType.pszText = _T("����");
	colType.mask = LVCF_TEXT;
	m_wndList.InsertColumn(2, &colType);
	m_wndList.SetColumnWidth(2, 100);


	//��������
	int index = m_wndList.GetItemCount();
	LV_ITEM item;
	memset(&item, 0, sizeof(LV_ITEM));
	
	m_wndList.InsertItem(&item);
}

//���ñ���Զ��п�
void CWatchWnd::AutoResizeColumns()
{
	int length = m_wndList.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < length; ++i)
		m_wndList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}
