#pragma once


// CMachineDlg �Ի���

class CMachineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMachineDlg)

public:
	CMachineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMachineDlg();

// �Ի�������
	enum { IDD = IDD_MACHINEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};
