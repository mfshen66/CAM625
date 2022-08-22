#pragma once


// CIsoCurDlg �Ի���

class CIsoCurDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIsoCurDlg)

public:
	CIsoCurDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIsoCurDlg();

// �Ի�������
	enum { IDD = IDD_ISOCURDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnApply() ;
	void SetBoxUV(double umin, double umax, double vmin, double vmax) ;
	void OnSelectedSur(void* pRefSur) ;

	BOOL m_selectedSur ;
	void* m_pRefSur ;
	double m_umin;
	double m_umax;
	double m_vmin;
	double m_vmax;
	int m_uvFlag; // 0=u, 1=v
	double m_u;
	double m_v;
};
