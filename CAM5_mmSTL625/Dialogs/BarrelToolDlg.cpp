// BarrelToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "BarrelToolDlg.h"
#include "afxdialogex.h"


// CBarrelToolDlg �Ի���

IMPLEMENT_DYNAMIC(CBarrelToolDlg, CDialogEx)

CBarrelToolDlg::CBarrelToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBarrelToolDlg::IDD, pParent)
{

}

CBarrelToolDlg::~CBarrelToolDlg()
{
}

void CBarrelToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBarrelToolDlg, CDialogEx)
	ON_COMMAND(IDAPPLY, &CBarrelToolDlg::OnApply)
END_MESSAGE_MAP()


// CBarrelToolDlg ��Ϣ�������


BOOL CBarrelToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CBarrelToolDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CBarrelToolDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CBarrelToolDlg::OnApply()
{
	// TODO: �ڴ���������������
}
