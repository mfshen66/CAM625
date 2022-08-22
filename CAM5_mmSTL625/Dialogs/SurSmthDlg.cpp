// SurSmthDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "SurSmthDlg.h"
#include "afxdialogex.h"


// CSurSmthDlg �Ի���

IMPLEMENT_DYNAMIC(CSurSmthDlg, CDialogEx)

CSurSmthDlg::CSurSmthDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSurSmthDlg::IDD, pParent)
{
	m_g1 = FALSE ;
	m_tol = 0.1 ;
	m_factor = 50 ;
	m_bz = FALSE ; // nt add 2011/1/28
	m_method = 0 ; // nt add 2011/1/28
}

CSurSmthDlg::CSurSmthDlg(double tol, BOOL g1)
	: CDialogEx(CSurSmthDlg::IDD, NULL)
{
	m_g1 = g1 ;
	m_tol = tol ;
	m_factor = 50 ;
	m_bz = FALSE ; // nt add 2011/1/28
	m_method = 0 ; // nt add 2011/1/28
}

CSurSmthDlg::~CSurSmthDlg()
{
}

void CSurSmthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tol);
	DDV_MinMaxDouble(pDX, m_tol, 0.001, 10);
	DDX_Slider(pDX, IDC_SLIDER1, m_factor);
	DDV_MinMaxInt(pDX, m_factor, 0, 100);
	DDX_Check(pDX, IDC_CHECK1, m_g1);
	DDX_Check(pDX, IDC_CHECK2, m_bz);
}


BEGIN_MESSAGE_MAP(CSurSmthDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CSurSmthDlg::OnDeltaposSpin1)
	ON_COMMAND(IDAPPLY, OnApply)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
END_MESSAGE_MAP()


// CSurSmthDlg ��Ϣ�������


BOOL CSurSmthDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(200, 200, 255)) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSurSmthDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
	cmdDlgUI(1) ;
}


void CSurSmthDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
	cmdDlgUI(0) ;
}

void CSurSmthDlg::OnApply()
{
	m_method = 0 ;
	UpdateData(TRUE) ;
	cmdDlgUI(2) ;
}

void CSurSmthDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE) ;
	m_tol -= pNMUpDown->iDelta*0.01 ;
    UpdateData(FALSE) ;
	*pResult = 0;
}

// nt add 2011/1/28
void CSurSmthDlg::OnButton1()
{
	m_method = 1 ;
	UpdateData(TRUE) ;
	cmdDlgUI(2) ;
}

// nt add 2011/1/29
void CSurSmthDlg::OnButton2()
{
	m_method = 2 ;
	UpdateData(TRUE) ;
	cmdDlgUI(2) ;
}
