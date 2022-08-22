#pragma once


// CModelDlg �Ի���

class CModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelDlg)

public:
	CModelDlg(CCAMDoc* pDoc, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModelDlg();

// �Ի�������
	enum { IDD = IDD_MODELDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	CCAMDoc* m_pDoc ;
	int m_gm ; // geometry model for CStep:0=workpiece,1=part

	virtual BOOL OnInitDialog();
	afx_msg void OnClickedMfcbutton1();
	afx_msg void OnClickedMfcbutton2();
	afx_msg void OnClickedMfcbutton3();
	afx_msg void OnClickedMfcbutton4();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
};
