#pragma once
#include "../stdafx.h"
#define MEMO_DELETE(x) {delete x; x = NULL;}

using namespace std;

namespace pt = boost::property_tree;

typedef struct InstStackItem {
	DWORD dwCallerIP;
	DWORD dwReturnAddress; //�������У�call ָ�����һ��ָ��; Ҳ���� [esp - 4]
} CallItem, *pCallItem;


class InstLogItem 
{
private:
	CString* pJmpAddr;
	CString* pCallSymbol;
	CString* pCallComment;
	CString* pRetSymbol;
	CString* pRetComment;
	InstLogItem();
	~InstLogItem();

public:
	static InstLogItem* Create(DWORD dwInstructionAddress, char jmpSymbol[256], char jmpComment[256], char retSymbol[256], char retComment[256]);
	static InstLogItem* Create(DWORD dwInstructionAddress, char jmpSymbol[256], char jmpComment[256]);
	static void Destroy(InstLogItem ** pInstLogItem);
};


// ָ���¼�����ڼ�¼������ڲ�����
class InstructionMemo
{
private:
	pt::ptree functionTreeRoot;
	stack<CallItem> callStack;

public:
	InstructionMemo();
	virtual ~InstructionMemo();

private:
	
	void InsertInstruction(char * instruction);
	void Call(CallItem &callItem);
	void Return();
};

