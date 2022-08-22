#pragma once

struct LW
{
	LW(int dLW, CString strName)
		: dLW(dLW)
		, strName(strName)
	{} ;

	int dLW ;
	CString strName ;
} ;

// CWidthDlg �Ի���

class CWidthDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWidthDlg)

public:
	CWidthDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWidthDlg();

// �Ի�������
	enum { IDD = IDD_WIDTHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnApply() ;
	int GetWidth() ;
	void SetWidth(int width) ;

	int m_width ; // 1/100mm
	CComboBox m_cb ;
};
