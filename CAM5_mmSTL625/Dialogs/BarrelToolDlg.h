#pragma once


// CBarrelToolDlg �Ի���

class CBarrelToolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBarrelToolDlg)

public:
	CBarrelToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBarrelToolDlg();

// �Ի�������
	enum { IDD = IDD_BARRELTOOLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnApply();
};
