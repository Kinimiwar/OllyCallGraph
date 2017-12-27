#pragma once
#include "../stdafx.h"

class CExprMap
{
private:
	DWORD m_addr;

	std::vector<CString> exprList; //ʹ�ñ��ʽ��

public:
	CExprMap();
	CExprMap(DWORD addr);
	CExprMap(const CExprMap& rhs); //copy constructor

	virtual ~CExprMap();

	/**
	* ����ǰ��ַ��ӱ��ʽ��¼
	*/
	void AddWatch(CString expression);

	void replaceExpr(int index, CString expr);

	void removeWatch(CString expression);

	bool containsWatch(CString expression);

	void clearWatches();
};

