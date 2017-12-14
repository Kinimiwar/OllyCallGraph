
// MFCApplication1.cpp : ����Ӧ�ó��������Ϊ��
//

#include "../stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PluginApp.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "PluginAppDoc.h"
#include "PluginAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(PluginApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &PluginApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


PluginApp::PluginApp()
{
	// TODO:  ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCApplication1.AppID.NoVersion"));

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}



// CMFCApplication1App ��ʼ��

BOOL PluginApp::InitInstance()
{
	CWinApp::InitInstance();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;

	pluginApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_PluginAppTYPE,
		RUNTIME_CLASS(CPluginAppDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CPluginAppView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	return TRUE;
}

int PluginApp::ExitInstance()
{
	//TODO:  �����������ӵĸ�����Դ
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinAppEx::ExitInstance();
}

BOOL PluginApp::OpenWindow()
{
	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMDIFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ������ MDI ��ܴ���
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	// ��ͼ���ع��� MDI �˵��Ϳ�ݼ���
	//TODO:  ��Ӹ��ӳ�Ա�����������ض�
	//	Ӧ�ó��������Ҫ�ĸ��Ӳ˵����͵ĵ���
	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MFCApplication1TYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_MFCApplication1TYPE));

	

	// �������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(m_nCmdShow);

	pFrame->UpdateWindow();

	return TRUE;
}

// CMFCApplication1App ��Ϣ�������

void PluginApp::OnFileNew() 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
	// �����µ� MDI �Ӵ���
	pFrame->CreateNewChild(
		RUNTIME_CLASS(CChildFrame), IDR_MFCApplication1TYPE, m_hMDIMenu, m_hMDIAccel);
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void PluginApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCApplication1App ��Ϣ�������



