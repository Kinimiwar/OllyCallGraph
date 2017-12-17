#pragma once
#include "main.h"

static HINSTANCE hinst;				//Plugin DLL instance
static HWND      hwmain;            // Handle of main OllyDbg window
static HWND      hwtrace;             // Handle of function call trace window

static char g_szPluginName[] = "Function Call Trace";




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
	switch (origin) 
	{
	case PM_MAIN:
		strcpy_s(data, 4096, "0 &Open|2 &About");
		break;
	case PM_DISASM:
		strcpy_s(data, 4096, "0 &标记并跟踪");
		break;
	default:
		return 0;
	}
	
	
	return 1;
};

void handleMainMenu(int action, void * item) {
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
}

//处理反汇编界面上的右键菜单
void handleDisasmMenu(int action, void * item) {
	t_dump * dump = NULL;
	t_module * module = NULL;
	char * moduleName = NULL;
	ulong addr;
	t_memory * memory = NULL;
	t_result result;
	char * expr = "[[esp+8]+0xc]";

	switch (action)
	{
	case 0:
		if (hwtrace == NULL) {
			CreateFCTWindow();
		}
		dump = (t_dump *)item;
		addr = dump->addr; //CPU指令地址
		module = Findmodule(addr);
		if (module == 0){
			return;
		}

		moduleName = module->name;
		memory = Findmemory(addr);
		
		Expression(&result, expr, 0, 0, NULL, dump->base, dump->size, dump->threadid);

		if (result.type == DEC_UNKNOWN)
		{//表达式出错

		}
		break;
	default:
		break;
	}
}

// Receives commands from main menu.
extc void _export cdecl ODBG_Pluginaction(int origin, int action, void *item) {
	
	switch (origin) {
	case PM_MAIN:
		handleMainMenu(action, item);
		break;
	case PM_DISASM:
		handleDisasmMenu(action, item);
		break;
	default:break;
	}
	
};

// Command line window recognizes global shortcut Alt+F1.
extc int _export cdecl ODBG_Pluginshortcut(
	int origin, int ctrl, int alt, int shift, int key, void *item) {
	if (ctrl == 0 && alt == 1 && shift == 0 && key == VK_F1) {

		Addtolist(0, 0, "Pressed Alt + F1");

		return 1;
	};                       // Shortcut recognized
	return 0;                            // Shortcut not recognized
};

// User opens new or restarts current application, clear command line history.
extc void _export cdecl ODBG_Pluginreset(void) {

	
};

// OllyDbg calls this optional function when user wants to terminate OllyDbg.
extc int _export cdecl ODBG_Pluginclose(void) {
	
	// For automatical restoring, mark in .ini file whether command line window
	// is still open and save coordinates. (WM_CLOSE is not sent in this case).
	Pluginwriteinttoini(hinst, "Restore command line window", hwtrace != NULL);
	if (hwtrace != NULL) {
		//GetWindowRect(hwcmd, &rc);
		//Pluginwriteinttoini(hinst, "Command line window X", rc.left);
		//Pluginwriteinttoini(hinst, "Command line window Y", rc.top);
	};
	DestroyFCTWindow();

	return 0;
};


extc int _export cdecl ODBG_Pausedex(int reason, int extdata, t_reg *reg, DEBUG_EVENT *debugevent){
	t_result result;
	char * expr = "[[esp+8]+0xc]";

	t_memory * memory = NULL;
	ulong ip = reg->ip;

	char cmd[MAXCMDSIZE];

	ulong cmdLen = Readcommand(ip, cmd); //读取指令
	uchar srcdes[MAXCMDSIZE];

	t_disasm disams;
	ulong des;

	char disamResult[TEXTLEN];

	if (cmdLen != 0)
	{
		cmdLen = Disasm((uchar*)cmd, cmdLen, ip, srcdes, &disams, DISASM_CODE, debugevent->dwThreadId);
		switch (disams.cmdtype)
		{
		case C_JMP:
			strcpy_s(disamResult, strlen(disams.result)+1, disams.result);
			if (disams.jmpconst != 0)
			{
				//是常量跳转指令
				des = disams.jmpconst;
			}
			else
			{
				des = disams.jmpaddr;
			}

			break;
		case C_JMC:
			break;
		case C_CAL:
			break;
		case C_RET:
			break;
		}
		
	}

	ulong destSize = 0;
	uchar * calldest = Finddecode(ip, &destSize);

	if (calldest != NULL)
	{
		//得到了解析后的数据

	}

	ulong beginIp= Findprocbegin(ip);
	ulong endIp = Findprocend(ip);
	char procName[TEXTLEN];

	int procLen;

	//发生了错误
	if (beginIp == 0)
	{
		procLen = Findname(ip, NM_ANYNAME, procName);
		procLen = Findname(ip, NM_LABEL, procName);
		procLen = Findname(ip, NM_LIBRARY, procName); //
		procLen = Findname(ip, NM_EXPORT, procName);
		procLen = Findname(ip, NM_IMPORT, procName);
	}
	else {
		procLen = Findname(beginIp, NM_ANYNAME, procName);
	}
	



	memory = Findmemory(reg->ip);

	Expression(&result, expr, 0, 0, NULL, memory->base, memory->size, debugevent->dwThreadId);

	if (result.type == DEC_UNKNOWN)
	{//表达式出错

	}

	NotifyWindow(FCT_OD_PAUSEDEX, (WPARAM)reason, (LPARAM)reg);
	

	return 0;
}

static void NotifyWindow(UINT message, WPARAM wParam, LPARAM lParam) {
	pluginApp.GetMainWnd()->PostMessageW(message, wParam, lParam);
}



// 窗口插件主窗体
static HWND CreateFCTWindow(){	

	pluginApp.m_nCmdShow = SW_SHOW;
	pluginApp.OpenWindow();

	CWnd* hwnd = pluginApp.GetMainWnd();
	
	hwtrace = hwnd->GetSafeHwnd();

	return hwtrace;
}



BOOL DestroyFCTWindow() {
	
	return TRUE;
}



