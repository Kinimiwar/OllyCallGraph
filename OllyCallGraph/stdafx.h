
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#include "targetver.h"

#ifndef _ATL_ALLOW_CHAR_UNSIGNED //����ATL��֧��/J����ѡ�OllyDbgҪ��ʹ�� /J ѡ�����ʹ�øú궨��ѹ�ƴ�����Ϣ��
#define _ATL_ALLOW_CHAR_UNSIGNED
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <Plugin.h> //���� OllyDbg v1.10 �����ͷ�ļ�

#include <algorithm>
#include <list>
#include <stack>
#include <boost/property_tree/ptree.hpp>


#define OD_DELETE(x) {delete x; x = NULL;}






