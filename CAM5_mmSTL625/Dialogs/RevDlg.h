#pragma once


// CRevDlg �Ի���

class CRevDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRevDlg)

public:
	CRevDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRevDlg();

// �Ի�������
	enum { IDD = IDD_REVDLG };
	int m_mode ; // 0=rev u, 1=rev v, 2=uv

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog() ;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedMfcbutton1();
	afx_msg void OnClickedMfcbutton2();
	afx_msg void OnClickedMfcbutton3();
	afx_msg void OnClickedMfcbutton4();
};
