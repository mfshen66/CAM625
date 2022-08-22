#pragma once


// CPDesignDlg �Ի���

class CPDesignDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPDesignDlg)

public:
	CPDesignDlg(CCAMDoc* pDoc, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPDesignDlg();

// �Ի�������
	enum { IDD = IDD_PDESIGNDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	CCAMDoc* m_pDoc ;
	CStep* m_pStep ; // ��ǰ�༭�Ĺ���
	CString m_name ; // ��������
	int m_gm ; // geometry model for CStep:0=workpiece,1=part,2=protect_surfaces

	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton4();
	afx_msg void OnClickedMfcbutton1();
	afx_msg void OnClickedMfcbutton2();
	afx_msg void OnClickedMfcbutton3();
	afx_msg void OnClickedMfcbutton4();
	afx_msg void OnClickedMfcbutton5();
	afx_msg void OnClickedMfcbutton6();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
};
