#pragma once


// CFlatToolDlg �Ի���

class CFlatToolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFlatToolDlg)

public:
	CFlatToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFlatToolDlg();

// �Ի�������
	enum { IDD = IDD_FLATTOOLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnApply();
};
