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

// CAM.h : CAM Ӧ�ó������ͷ�ļ�
//
#pragma once

////////////////////////////////////////////////////////////////
// nt �ر����������д��룬����򿪿��ܵ���VC2010����
//#ifndef __AFXWIN_H__
//	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
//#endif
#include "resource.h"       // ������
// CCAMApp:
// �йش����ʵ�֣������ CAM.cpp
//
class CCAMApp : public CWinAppEx
{
public:
	void* m_pVI ; // nt add 2009/12/17
	void* m_pTLib ; // nt add 2010/9/24

	// system option, nt add 2010/11/28
	OPTION m_option ;

public:
	CCAMApp();
	~CCAMApp(); // nt add 2009/12/22

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
};

extern CCAMApp theApp;
//--------------------------------------------------------------
// nt add 2009/12/16
int camGetSysVerNo() ;
void camSetDocVerNo(int verNo) ; // nt add 2021/8/13
int camGetDocVerNo() ; // nt add 2021/8/13
int camWake(void* pVI) ;
int camSleep(void* pVI) ;
OPTION* camGetOption() ; // nt add 2010/11/28
void camSetOption(OPTION* option) ; // nt add 2021/6/16
void* camGetMTView() ; // nt add 2020/5/12
//--------------------------------------------------------------
// nt add 2010/8/22 common global functions
int cmdDlgUI(int ui) ;
//--------------------------------------------------------------
void* GetTLib() ; // nt add 2010/9/24
////////////////////////////////////////////////////////////////