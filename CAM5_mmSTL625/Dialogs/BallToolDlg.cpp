// BallToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "BallToolDlg.h"
#include "afxdialogex.h"


// CBallToolDlg �Ի���

IMPLEMENT_DYNAMIC(CBallToolDlg, CDialogEx)

CBallToolDlg::CBallToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBallToolDlg::IDD, pParent)
{

}

CBallToolDlg::~CBallToolDlg()
{
}

void CBallToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBallToolDlg, CDialogEx)
	ON_COMMAND(IDAPPLY, &CBallToolDlg::OnApply)
END_MESSAGE_MAP()


// CBallToolDlg ��Ϣ�������


BOOL CBallToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CBallToolDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CBallToolDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CBallToolDlg::OnApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
