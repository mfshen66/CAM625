// CPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "CPDlg.h"
#include "afxdialogex.h"


// CCPDlg �Ի���

IMPLEMENT_DYNAMIC(CCPDlg, CDialogEx)

CCPDlg::CCPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCPDlg::IDD, pParent)
{

}

CCPDlg::~CCPDlg()
{
}

void CCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCPDlg, CDialogEx)
END_MESSAGE_MAP()


// CCPDlg ��Ϣ�������


BOOL CCPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(200, 200, 255)) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCPDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CCPDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}
