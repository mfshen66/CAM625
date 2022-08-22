// ConDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "ConDlg.h"
#include "afxdialogex.h"


// CConDlg �Ի���

IMPLEMENT_DYNAMIC(CConDlg, CDialogEx)

CConDlg::CConDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConDlg::IDD, pParent)
{
	m_mode = -1 ;
}

CConDlg::~CConDlg()
{
}

void CConDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CConDlg::OnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CConDlg::OnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CConDlg::OnClickedMfcbutton3)
END_MESSAGE_MAP()


// CConDlg ��Ϣ�������
BOOL CConDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBackgroundColor(RGB(200, 200, 255)) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConDlg::OnClickedMfcbutton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mode = 0 ;
	cmdDlgUI(2) ;
}


void CConDlg::OnClickedMfcbutton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mode = 1 ;
	cmdDlgUI(2) ;
}


void CConDlg::OnClickedMfcbutton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	cmdDlgUI(0) ;
}
