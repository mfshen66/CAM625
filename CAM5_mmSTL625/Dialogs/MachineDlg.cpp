// MachineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "MachineDlg.h"
#include "afxdialogex.h"


// CMachineDlg �Ի���

IMPLEMENT_DYNAMIC(CMachineDlg, CDialogEx)

CMachineDlg::CMachineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMachineDlg::IDD, pParent)
{

}

CMachineDlg::~CMachineDlg()
{
}

void CMachineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMachineDlg, CDialogEx)
END_MESSAGE_MAP()


// CMachineDlg ��Ϣ�������


BOOL CMachineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(200, 200, 255)) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMachineDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
	cmdDlgUI(1) ;
}


void CMachineDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
	cmdDlgUI(0) ;
}
