#pragma once


// CSurSmthDlg �Ի���

class CSurSmthDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSurSmthDlg)

public:
	CSurSmthDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CSurSmthDlg(double tol, BOOL g1);
	virtual ~CSurSmthDlg();

// �Ի�������
	enum { IDD = IDD_SURSMTHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_tol;
	int m_factor;
	BOOL m_g1;
	BOOL m_bz ; // 1=use Bezier surface
	int m_method ; // 0=smooth(�������Ż�), 1=optimize(ƽ��), 2=��͹
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnApply() ;
	afx_msg void OnButton1();
	afx_msg void OnButton2();
};
