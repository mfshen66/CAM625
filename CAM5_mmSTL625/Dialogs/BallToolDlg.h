#pragma once


// CBallToolDlg �Ի���

class CBallToolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBallToolDlg)

public:
	CBallToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBallToolDlg();

// �Ի�������
	enum { IDD = IDD_BALLTOOLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnApply();
};
