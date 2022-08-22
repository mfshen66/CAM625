// PDesignDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "..\Models.h"
#include "..\Mills.h"
#include "..\SelSet.h"
#include "..\CAMDoc.h"
#include "CPDlg.h"
#include "PDesignDlg.h"
#include "afxdialogex.h"


// CPDesignDlg �Ի���

IMPLEMENT_DYNAMIC(CPDesignDlg, CDialogEx)

CPDesignDlg::CPDesignDlg(CCAMDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialogEx(CPDesignDlg::IDD, pParent)
{
	m_pDoc = pDoc ;
	m_name = _T("");
	m_gm = 0 ;
}

CPDesignDlg::~CPDesignDlg()
{
}

void CPDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDV_MaxChars(pDX, m_name, 100);
}

BEGIN_MESSAGE_MAP(CPDesignDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPDesignDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPDesignDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPDesignDlg::OnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPDesignDlg::OnClickedButton4)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CPDesignDlg::OnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CPDesignDlg::OnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CPDesignDlg::OnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CPDesignDlg::OnClickedMfcbutton4)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CPDesignDlg::OnClickedMfcbutton5)
	ON_BN_CLICKED(IDC_MFCBUTTON6, &CPDesignDlg::OnClickedMfcbutton6)
	ON_COMMAND(IDC_RADIO1, &CPDesignDlg::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &CPDesignDlg::OnRadio2)
	ON_COMMAND(IDC_RADIO3, &CPDesignDlg::OnRadio3)
END_MESSAGE_MAP()


// CPDesignDlg ��Ϣ�������
BOOL CPDesignDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CButton* pB ;
	if( m_gm == 0 )
		pB = (CButton*)GetDlgItem(IDC_RADIO1) ; // CStep workpiece
	else
	if( m_gm == 1 )
		pB = (CButton*)GetDlgItem(IDC_RADIO2) ; // CStep part
	else
		pB = (CButton*)GetDlgItem(IDC_RADIO3) ; // CStep psurfaces
	pB->SetCheck(1) ;

	// �����б�
	CVSListBox* pLB = (CVSListBox*)GetDlgItem(IDC_MFCVSLISTBOX1) ;
	if( pLB &&
		m_pDoc )
	{
		CString name ;
		CPart* pPart = m_pDoc->GetPart() ;
		CMill* pMill = m_pDoc->GetMill() ;
		if( pPart &&
			pMill )
		{
			int i, n = pMill->GetNumOfStep() ;
			for( i = 0 ; i < n ; i++ )
			{
				CStep* pStep = pMill->GetStep(i) ;
				if( pStep )
				{
					pStep->GetName(name) ;
					pLB->AddItem(name, (DWORD_PTR)pStep) ;
				}
			}
		}
	}

	SetBackgroundColor(RGB(200, 200, 255)) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ���
void CPDesignDlg::OnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CVSListBox* pLB = (CVSListBox*)GetDlgItem(IDC_MFCVSLISTBOX1) ;
	if( pLB &&
		m_pDoc )
	{
		CString name ;
		CPart* pPart = m_pDoc->GetPart() ;
		CMill* pMill = m_pDoc->GetMill() ;
		if( pPart &&
			pMill )
		{
			CStep* pStep = new CStep() ;
			int no = pMill->GetMaxStepNo()+1 ;
			pStep->SetNo(no) ;
			CString name ;
			name.Format(_T("����%d"), no) ;
			pStep->SetName(name) ;
			CP cp ;
			pMill->GetCP(&cp) ;
			pStep->SetCP(&cp) ;
			CTool* pTool = pMill->GetTool() ;
			if( pTool )
			{
				pStep->SetTool(pTool->Copy()) ;
			}
			RFRAME lf ;
			pMill->GetMCS(&lf) ;
			pStep->SetMCS(&lf) ;
			//pMill->Add(pStep) ;
			m_pDoc->AddStep(pStep) ; // nt add 2010/11/29
			pLB->AddItem(name, (DWORD_PTR)pStep) ;
		}
	}
}

// ɾ��
void CPDesignDlg::OnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CVSListBox* pLB = (CVSListBox*)GetDlgItem(IDC_MFCVSLISTBOX1) ;
	if( pLB &&
		m_pDoc )
	{
		CPart* pPart = m_pDoc->GetPart() ;
		CMill* pMill = m_pDoc->GetMill() ;
		int index = pLB->GetSelItem() ;
		if( pPart &&
			pMill &&
			index >= 0 )
		{
			if( AfxMessageBox(_T("ȷ��ɾ������?"), MB_YESNO) == IDYES )
			{
				CStep* pStep = (CStep*)pLB->GetItemData(index) ;
				pLB->RemoveItem(index) ;
				if( pStep )
				{
					pMill->Delete(pStep) ;
				}
			}
		}
	}
}

// ����
void CPDesignDlg::OnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CVSListBox* pLB = (CVSListBox*)GetDlgItem(IDC_MFCVSLISTBOX1) ;
	if( pLB &&
		m_pDoc )
	{
		CPart* pPart = m_pDoc->GetPart() ;
		CMill* pMill = m_pDoc->GetMill() ;
		int index = pLB->GetSelItem() ;
		if( pPart &&
			pMill &&
			index >= 0 )
		{
			CStep* pStep = (CStep*)pLB->GetItemData(index) ;
			if( pStep )
			{
				CStep* pCopy = pStep->Copy() ;
				pMill->Add(pCopy) ;
				CString name ;
				pCopy->GetName(name) ;
				pLB->AddItem(name, (DWORD_PTR)pCopy) ;
			}
		}
		else
			camPromptStr("ѡ��Ҫ���ƵĹ���!") ;
	}
}

// �༭
void CPDesignDlg::OnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CVSListBox* pLB = (CVSListBox*)GetDlgItem(IDC_MFCVSLISTBOX1) ;
	if( pLB &&
		m_pDoc )
	{
		CPart* pPart = m_pDoc->GetPart() ;
		CMill* pMill = m_pDoc->GetMill() ;
		int index = pLB->GetSelItem() ;
		if( pPart &&
			pMill &&
			index >= 0 )
		{
			m_pStep = (CStep*)pLB->GetItemData(index) ;
			if( m_pStep )
			{
				m_pStep->GetName(m_name) ;
				UpdateData(FALSE) ;
			}
		}
		else
			camPromptStr("ѡ��Ҫ�༭�Ĺ���!") ;
	}
}

// ���Ӽ���
void CPDesignDlg::OnClickedMfcbutton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_pStep &&
		m_pDoc )
	{
		CPart* pPart = m_pDoc->GetPart() ;
		if( pPart )
		{
			int k, m = 1, types[2] = {ftRefSur, ftRefCur} ;
			if( m_gm == gmtPSurface )
				m = 2 ;
			for( k = 0 ; k < m ; k++ )
			{
				int i, n = m_pDoc->GetSelected(types[k], 10000) ;
				for( i = 0 ; i < n ; i++ )
				{
					CFeature* pF = (CFeature*)m_pDoc->GetObj(i) ;
					if( pF )
					{
						int no = pF->GetNo() ;
						m_pStep->AddGeometry(m_gm, no) ;
					}
				}
			}
		}
	}
}

// ���ټ���
void CPDesignDlg::OnClickedMfcbutton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_pStep &&
		m_pDoc )
	{
		int i, n = m_pDoc->GetSelected(-1, 10000) ;
		CPart* pPart = m_pDoc->GetPart() ;
		if( pPart &&
			n > 0 )
		{
			for( i = 0 ; i < n ; i++ )
			{
				CFeature* pF = (CFeature*)m_pDoc->GetObj(i) ;
				if( pF )
				{
					int no = pF->GetNo() ;
					m_pStep->DeleteGeometry(m_gm, no) ;
				}
			}
		}
	}
}

// ��ʾ
void CPDesignDlg::OnClickedMfcbutton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_pStep &&
		m_pDoc )
	{
		int i, n = m_pStep->GetNumOfGeometry(m_gm) ;
		CPart* pPart = m_pDoc->GetPart() ;
		CSelSet* pSelSet = m_pDoc->GetSelSet() ;
		if( pPart &&
			pSelSet )
		{
			for( i = 0 ; i < n ; i++ )
			{
				int no = m_pStep->GetGeometryNo(m_gm, i) ;
				CFeature* pF = pPart->GetFeatureByNo(no) ;
				if( pF )
					pSelSet->AddSelected(pF) ;
			}
		}
	}
}

// �������ģ��
void CPDesignDlg::OnClickedMfcbutton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_pStep )
		m_pStep->ClearModel(m_gm) ;
	if( m_pDoc )
	{
		CSelSet* pSelSet = m_pDoc->GetSelSet() ;
		if( pSelSet )
			pSelSet->Clear() ;
	}
}

// ��������
void CPDesignDlg::OnClickedMfcbutton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_pStep )
	{
		CCPDlg dlg ;
		if( dlg.DoModal() == IDOK )
		{
			//CP cp ;
			//...
			// m_pStep->SetCP(&cp) ;
		}
	}
	else
		camPromptStr("��ѡ��Ҫ�༭�Ĺ���!") ;
}

// �ӹ�����ϵ
void CPDesignDlg::OnClickedMfcbutton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_pDoc &&
		m_pStep ) // ��ǰ�����ڱ༭�Ĺ���
	{
		int n = m_pDoc->GetSelected(ftRefPlane, 1) ;
		if( n > 0 )
		{
			CRefPlane* pRefPlane = (CRefPlane*)m_pDoc->GetObj(0) ;
			if( pRefPlane )
			{
				RFRAME lf ;
				pRefPlane->GetLF(&lf) ;
				m_pStep->SetMCS(&lf) ;
			}
		}
		else
			camPromptStr("��ʰȡ�ӹ�����ϵ!") ;
	}
}

void CPDesignDlg::OnRadio1()
{
	// TODO: �ڴ���������������
	m_gm = 0 ;
}

void CPDesignDlg::OnRadio2()
{
	// TODO: �ڴ���������������
	m_gm = 1 ;
}

void CPDesignDlg::OnRadio3()
{
	// TODO: �ڴ���������������
	m_gm = 0 ;
}

void CPDesignDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
	cmdDlgUI(0) ;
}
