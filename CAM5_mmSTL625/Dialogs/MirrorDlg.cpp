// MirrorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "MirrorDlg.h"
#include "afxdialogex.h"


// CMirrorDlg �Ի���

IMPLEMENT_DYNAMIC(CMirrorDlg, CDialogEx)

CMirrorDlg::CMirrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMirrorDlg::IDD, pParent)
{
	m_mirrorPlane = FALSE ;
	m_copy = TRUE ;
	mathInitRFrame(&m_lf) ;
	m_inited = 0 ;
}

CMirrorDlg::~CMirrorDlg()
{
}

void CMirrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_mirrorPlane);
	DDX_Check(pDX, IDC_CHECK2, m_copy);
}

BEGIN_MESSAGE_MAP(CMirrorDlg, CDialogEx)
	ON_COMMAND(IDAPPLY, OnApply)
END_MESSAGE_MAP()

// CMirrorDlg ��Ϣ�������
BOOL CMirrorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_inited = 1 ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMirrorDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
	cmdDlgUI(1) ;
}

void CMirrorDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE) ;
	cmdDlgUI(0) ;
}

void CMirrorDlg::OnApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE) ;
	cmdDlgUI(2) ;
}

void CMirrorDlg::OnSelectedMirrorPlane(RFRAME* pLF)
{
	if( pLF )
		m_lf = *pLF ;
	m_mirrorPlane = TRUE ;
	if( m_inited )
		UpdateData(FALSE) ;
}