#pragma once


// CCPDlg �Ի���

class CCPDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCPDlg)

public:
	CCPDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCPDlg();

// �Ի�������
	enum { IDD = IDD_CPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};
