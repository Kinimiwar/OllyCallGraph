
// MFCApplication1.h : MFCApplication1 Ӧ�ó������ͷ�ļ�
//
#pragma once
#include "../stdafx.h"

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "../resource.h"       // ������


// CMFCApplication1App:
// �йش����ʵ�֣������ MFCApplication1.cpp
//

class PluginApp : public CWinAppEx
{
public:
	PluginApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	// for translating Windows messages in main message pump
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	
	BOOL OpenWindow();
	
// ʵ��
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	
	DECLARE_MESSAGE_MAP()
};

extern PluginApp pluginApp;
