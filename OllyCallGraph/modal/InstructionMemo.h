#pragma once
#include "../stdafx.h"
#include "./InstLogItem.h"


using namespace std;

namespace pt = boost::property_tree;

typedef struct InstStackItem {
	DWORD dwCallerIP;
	DWORD dwReturnAddress; //�������У�call ָ�����һ��ָ��; Ҳ���� [esp - 4]
} CallStackItem, *pCallStackItem;


// ָ���¼�����ڼ�¼������ڲ�����
class InstructionMemo :CObject
{
private:
	pt::ptree functionTreeRoot;
	stack<CallStackItem> callStack;

public:
	InstructionMemo();
	virtual ~InstructionMemo();

private:
	/*
	 * �ڵ�ǰ�����������У����ָ�� CPU ָ���ַ��
	 */
	void WatchAddr(DWORD addr);

	/*
	 * �ݶ��� CALL ָ��ʱ�����м�¼
	 */
	void WillCall(InstLogItem* logItem, CallStackItem &callItem);

	/*
	 * ��ͣ�� RET ָ��ʱ�����м�¼
	 */
	void WillReturn(InstLogItem* logItem);

	void DestroyAll();

	DECLARE_SERIAL(InstructionMemo)
};

