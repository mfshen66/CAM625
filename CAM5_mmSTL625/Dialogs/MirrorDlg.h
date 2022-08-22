#pragma once


// CMirrorDlg �Ի���

class CMirrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMirrorDlg)

public:
	CMirrorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMirrorDlg();

// �Ի�������
	enum { IDD = IDD_MIRRORDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_mirrorPlane;
	BOOL m_copy ;
	RFRAME m_lf ;
	int m_inited ;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnApply();
	void OnSelectedMirrorPlane(RFRAME* pLF);
};
