// RevDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "RevDlg.h"
#include "afxdialogex.h"


// CRevDlg �Ի���

IMPLEMENT_DYNAMIC(CRevDlg, CDialogEx)

CRevDlg::CRevDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRevDlg::IDD, pParent)
{
	m_mode = -1 ;
}

CRevDlg::~CRevDlg()
{
}

void CRevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRevDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CRevDlg::OnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CRevDlg::OnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CRevDlg::OnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CRevDlg::OnClickedMfcbutton4)
END_MESSAGE_MAP()


// CRevDlg ��Ϣ�������
BOOL CRevDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBackgroundColor(RGB(200, 200, 255)) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRevDlg::OnClickedMfcbutton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mode = 0 ;
	cmdDlgUI(2) ;
}


void CRevDlg::OnClickedMfcbutton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mode = 1 ;
	cmdDlgUI(2) ;
}

void CRevDlg::OnClickedMfcbutton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mode = 2 ;
	cmdDlgUI(2) ;
}


void CRevDlg::OnClickedMfcbutton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	cmdDlgUI(0) ;
}
