// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
////////////////////////////////////////////////////////////////
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif
#include "targetver.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
//--------------------------------------------------------------
#define CStr CStringA // nt add 2016/6/3
#include "stdio.h"
#include "malloc.h"
#include "math.h"
#include "gl\gl.h"
#include "API\VI_API.h"
#include "API\GP_API.h"
#include "API\GCT_API.h"
#include "Obj\Obj.h"
#include "Tools\Tools.h" // nt add 2009/5/9
#include "Tools\PV.h" // nt add 2009/5/9
#include "Tools\ReadWrite.h" // nt add 2010/4/22
#include "Tools\Math2D.h" // nt add 2020/4/11
#include "Option.h" // nt add 2010/11/28 
//--------------------------------------------------------------
int camGetSysVerNo() ; // nt add 2003/6/23
int camWake(void* pVI) ; // nt add 2009/9/12
int camSleep(void* pVI) ; // nt add 2009/9/12
//--------------------------------------------------------------
void camPromptUpdate() ; // nt add 2009/10/21
void camPromptAttach(char c) ; // nt add 2009/10/21
void camPromptAttach(CStr& str) ; // nt add 2009/10/21
void camPromptGet(CStr& str) ; // nt add 2009/10/21
void camPromptClear() ; // nt add 2009/10/21
void camPromptStr(CStr& str) ; // in MainFrm.cpp
void camPromptStr(char* text) ; // in MainFrm.cpp
void camPromptPt(double p[2]) ; // in MainFrm.cpp
////////////////////////////////////////////////////////////////












