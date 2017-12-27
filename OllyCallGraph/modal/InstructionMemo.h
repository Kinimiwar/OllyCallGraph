#pragma once
#include "../stdafx.h"
#include "./InstLogItem.h"

#include "TreeImpl.h"
#include "ExprMap.h"

using namespace std;
using namespace od;


typedef struct InstStackItem {
	DWORD dwCallerIP;
	DWORD dwReturnAddress; //�������У�call ָ�����һ��ָ��; Ҳ���� [esp - 4]
} CallStackItem, *pCallStackItem;


// ָ���¼�����ڼ�¼������ڲ�����
class InstructionMemo :CObject
{
	DECLARE_SERIAL(InstructionMemo)

private:
	/**
	 * Key type is std::string, storing an cpu instruction address in memory dump.
	 * 
	 */
	typedef od::CTree<InstLogItem*> CallTreeNode;

	CallTreeNode m_callTree;

	/**
	 * �������õ�ȫ�������ģ���callָ���һ�η���ʱ����ָ���ַ��¼�����������С�
	 */
	CallTreeNode* m_pGlobalContext; 

	/**
	 * ��ǰִ��ָ�����ڵĺ���������
	 */
	CallTreeNode* m_pCurrentContext;

	stack<CallStackItem> callStack;

	std::unordered_map<DWORD, CExprMap> markers;

public:
	InstructionMemo();
	virtual ~InstructionMemo();

	/*
	 * �ڵ�ǰ�����������У����ָ�� CPU ָ���ַ��
	 * ����һ����־��
	 */
	void WatchAddr(DWORD addr);

	/*
	 * ��ͣ�� CALL ָ��ʱ�����м�¼
	 * ����һ����־��
	 */
	void WillCall(InstLogItem* logItem, CallStackItem &callItem);

	/*
	 * ��ͣ�� RET ָ��ʱ�����м�¼
	 * ����һ����־��
	 */
	void WillReturn(InstLogItem* logItem);


	void DestroyAllWatches(CallTreeNode &elem);

	/**
	 * m_callTree(data == NULL)
	 *    |
	 *    ��-m_globalContext(data == NULL)
	 *    |   
	 */
	void ResetGlobalContext();



protected:
	void ClearTree(CallTreeNode & tree);

private:
	/**
	 * �� DWORD ת��Ϊ string ���͡�
	 */
	std::string CString2String(CString str);

	void addLogItem(InstLogItem* logItem);

	void markAddress(DWORD ip);

};

