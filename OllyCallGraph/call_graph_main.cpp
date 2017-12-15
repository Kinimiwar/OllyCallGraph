#define STRICT                         // Avoids some type mismatches
//#include <windows.h> //MFC中已经包含该头文件
#include "stdafx.h"
#include <stdio.h>

#include "resource.h"
#include "ui/PluginApp.h"


static HINSTANCE hinst;				//Plugin DLL instance
static HWND      hwmain;            // Handle of main OllyDbg window
static HWND      hwcmd;             // Handle of function call trace window

static char g_szPluginName[] = "Function Call Trace";

static HWND CreateFCTWindow();
BOOL DestroyFCTWindow();


// 唯一的一个 PluginApp 对象
PluginApp pluginApp;

static HINSTANCE GetGlobalInstance() {
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	HINSTANCE hInst = pModuleState->m_hCurrentInstanceHandle;
	return hInst;
}

extc int _export cdecl ODBG_Plugindata(char shortname[32]) {
	strcpy_s(shortname, 32, g_szPluginName);
	return PLUGIN_VERSION;
}


extc int _export cdecl ODBG_Plugininit(int ollydbgversion, HWND hw, ulong * features) {
	if (ollydbgversion < PLUGIN_VERSION) {
		return -1;
	}

	hinst = GetGlobalInstance();
	hwmain = hw;

	Addtolist(0, 0, "FCT Plugin v0.1");
	Addtolist(0, -1, "Copyright (C) 2017 yezhang989");

	if (Plugingetvalue(VAL_RESTOREWINDOWPOS) != 0 && Pluginreadintfromini(hinst, "Restore FCT Window", 0) != 0) {
		CreateFCTWindow();
	}
	return 0;
}
// Function adds items to main OllyDbg menu (origin=PM_MAIN).
extc int _export cdecl ODBG_Pluginmenu(int origin, char data[4096], void *item) {
	if (origin != PM_MAIN)
		return 0;                          // No pop-up menus in OllyDbg's windows

	strcpy_s(data, 4096,  "0 &Open|2 &About");
	return 1;
};

// Receives commands from main menu.
extc void _export cdecl ODBG_Pluginaction(int origin, int action, void *item) {
	if (origin != PM_MAIN)
		return;
	switch (action) {
	case 0:                            // "Start", creates window
		CreateFCTWindow();
		break;
	case 1:                            // "Stop", opens help file

		break;
	case 2:                            // "About", displays plugin info
		MessageBox(hwmain,
			L"Function Call Graph plugin v0.10\nWritten by yezhang989",
			L"FCT", MB_OK | MB_ICONINFORMATION);
		break;
	default: break;
	};
};

// Command line window recognizes global shortcut Alt+F1.
extc int _export cdecl ODBG_Pluginshortcut(
	int origin, int ctrl, int alt, int shift, int key, void *item) {
	if (ctrl == 0 && alt == 1 && shift == 0 && key == VK_F1) {

		Addtolist(0, 0, "Pressed Alt + F1");

		//Createcmdlinewindow();
		return 1;
	};                       // Shortcut recognized
	return 0;                            // Shortcut not recognized
};

// User opens new or restarts current application, clear command line history.
extc void _export cdecl ODBG_Pluginreset(void) {

	//Addline(NULL);
};

// OllyDbg calls this optional function when user wants to terminate OllyDbg.
extc int _export cdecl ODBG_Pluginclose(void) {
	
	// For automatical restoring, mark in .ini file whether command line window
	// is still open and save coordinates. (WM_CLOSE is not sent in this case).
	Pluginwriteinttoini(hinst, "Restore command line window", hwcmd != NULL);
	if (hwcmd != NULL) {
		//GetWindowRect(hwcmd, &rc);
		//Pluginwriteinttoini(hinst, "Command line window X", rc.left);
		//Pluginwriteinttoini(hinst, "Command line window Y", rc.top);
	};
	DestroyFCTWindow();

	return 0;
};



// 窗口插件主窗体
static HWND CreateFCTWindow(){	

	

	pluginApp.m_nCmdShow = SW_SHOW;
	pluginApp.OpenWindow();

	CWnd* hwnd = pluginApp.GetMainWnd();
	
	return hwnd->GetSafeHwnd();;
}



BOOL DestroyFCTWindow() {
	
	return TRUE;
}



