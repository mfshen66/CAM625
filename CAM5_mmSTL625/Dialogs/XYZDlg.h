#pragma once


// CXYZDlg �Ի���

class CXYZDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CXYZDlg)

public:
	CXYZDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXYZDlg();

// �Ի�������
	enum { IDD = IDD_XYZDLG };
public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	double m_x;
	double m_y;
	double m_z;
};
