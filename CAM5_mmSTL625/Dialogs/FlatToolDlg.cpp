// FlatToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "FlatToolDlg.h"
#include "afxdialogex.h"


// CFlatToolDlg �Ի���

IMPLEMENT_DYNAMIC(CFlatToolDlg, CDialogEx)

CFlatToolDlg::CFlatToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFlatToolDlg::IDD, pParent)
{

}

CFlatToolDlg::~CFlatToolDlg()
{
}

void CFlatToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFlatToolDlg, CDialogEx)
	ON_COMMAND(IDAPPLY, &CFlatToolDlg::OnApply)
END_MESSAGE_MAP()


// CFlatToolDlg ��Ϣ�������


BOOL CFlatToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CFlatToolDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CFlatToolDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CFlatToolDlg::OnApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
