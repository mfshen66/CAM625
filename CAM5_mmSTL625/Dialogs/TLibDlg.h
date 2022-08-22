#pragma once


// CTLibDlg �Ի���

class CTLibDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTLibDlg)

public:
	CTLibDlg(CCAMDoc* pDoc, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTLibDlg();

// �Ի�������
	enum { IDD = IDD_TLIBDLG };
	CCAMDoc* m_pDoc ; // nt add 2010/9/27
	CImageList m_images ;
	CTGroup* m_pTG ;
	CTSubGroup* m_pTSG ;
	CTool* m_pTool ;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton4();
	afx_msg void OnClickedMfcButton1(); // nt add 2010/9/27
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	HTREEITEM GetSelected() ; // �������m_pTG, m_pTSG, m_pTool
};
