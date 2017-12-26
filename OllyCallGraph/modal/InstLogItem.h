#pragma once
#include "../stdafx.h"

class InstructionMemo;

class InstLogItem : CObject
{
	DECLARE_SERIAL(InstLogItem)

	friend class InstructionMemo;

private:
	CString* ip; //address of instruction in cpu.
	CString* pJmpAddr; //jump target address
	CString* pCallSymbol;
	CString* pCallComment;
	CString* pRetSymbol;
	CString* pRetComment;
	InstLogItem();
	~InstLogItem();

	std::list<std::string> expressionList; //ʹ�ñ��ʽ��

public:
	/**
	 * ����ǰ��ַ��ӱ��ʽ��¼
	 */
	void AddWatch(std::string expression);
	static InstLogItem* Create(DWORD ip, DWORD jmpAddr, char jmpSymbol[256], char jmpComment[256], char retSymbol[256], char retComment[256]);
	static InstLogItem* Create(DWORD ip, DWORD jmpAddr, char jmpSymbol[256], char jmpComment[256]);
	static InstLogItem* Create(DWORD ip);
	static void Destroy(InstLogItem ** pInstLogItem);


};