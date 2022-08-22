// CurSmthDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "CurSmthDlg.h"
#include "afxdialogex.h"


// CCurSmthDlg �Ի���

IMPLEMENT_DYNAMIC(CCurSmthDlg, CDialogEx)

CCurSmthDlg::CCurSmthDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCurSmthDlg::IDD, pParent)
{
	m_g1 = FALSE ;
	m_tol = 0.1 ;
	m_factor = 50 ;
	m_bz = FALSE ; // nt add 2011/1/28
	m_method = 0 ; // nt add 2011/1/28
}

CCurSmthDlg::CCurSmthDlg(double tol, BOOL g1)
	: CDialogEx(CCurSmthDlg::IDD, NULL)
{
	m_g1 = g1 ;
	m_tol = tol ;
	m_factor = 50 ;
	m_bz = FALSE ; // nt add 2011/1/28
	m_method = 0 ; // nt add 2011/1/28
}

CCurSmthDlg::~CCurSmthDlg()
{
}

void CCurSmthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tol);
	DDV_MinMaxDouble(pDX, m_tol, 0.001, 10);
	DDX_Slider(pDX, IDC_SLIDER1, m_factor);
	DDV_MinMaxInt(pDX, m_factor, 0, 100);
	DDX_Check(pDX, IDC_CHECK1, m_g1);
	DDX_Check(pDX, IDC_CHECK2, m_bz);
}


BEGIN_MESSAGE_MAP(CCurSmthDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CCurSmthDlg::OnDeltaposSpin1)
	ON_COMMAND(IDAPPLY, OnApply)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
END_MESSAGE_MAP()


// CCurSmthDlg ��Ϣ�������


BOOL CCurSmthDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(200, 200, 255)) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCurSmthDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
	cmdDlgUI(1) ;
}


void CCurSmthDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
	cmdDlgUI(0) ;
}

void CCurSmthDlg::OnApply()
{
	m_method = 0 ;
	UpdateData(TRUE) ;
	cmdDlgUI(2) ;
}

void CCurSmthDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE) ;
	m_tol -= pNMUpDown->iDelta*0.01 ;
    UpdateData(FALSE) ;
	*pResult = 0;
}

// nt add 2011/1/28
void CCurSmthDlg::OnButton1()
{
	m_method = 1 ;
	UpdateData(TRUE) ;
	cmdDlgUI(2) ;
}

// nt add 2011/1/29
void CCurSmthDlg::OnButton2()
{
	m_method = 2 ;
	UpdateData(TRUE) ;
	cmdDlgUI(2) ;
}
