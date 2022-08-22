// TLibDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\CAM.h"
#include "..\Models.h"
#include "..\Mills.h"
#include "..\SelSet.h"
#include "..\CAMDoc.h"
#include "TLibDlg.h"
#include "afxdialogex.h"
#include "FlatToolDlg.h"
#include "BallToolDlg.h"
#include "BarrelToolDlg.h"

// CTLibDlg �Ի���

IMPLEMENT_DYNAMIC(CTLibDlg, CDialogEx)

CTLibDlg::CTLibDlg(CCAMDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialogEx(CTLibDlg::IDD, pParent)
{
	m_pDoc = pDoc ; // nt add 2010/9/27
	m_pTG = NULL ;
	m_pTSG = NULL ;
	m_pTool = NULL ;
}

CTLibDlg::~CTLibDlg()
{
}

void CTLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTLibDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTLibDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTLibDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTLibDlg::OnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTLibDlg::OnClickedButton4)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CTLibDlg::OnClickedMfcButton1)
END_MESSAGE_MAP()


// CTLibDlg ��Ϣ�������
// ���
void CTLibDlg::OnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTLib* pTLib = (CTLib*)GetTLib() ;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1) ;
	if( pTLib &&
		pTree )
	{
		HTREEITEM hItem = GetSelected(), hTSG, hT ;
		if( hItem )
		{
			if( m_pTG && // ѡ��������򵶾�
				m_pTSG )
			{
				int subType = m_pTSG->GetSubType() ;
				hTSG = m_pTSG->GetItem() ;
				if( hTSG == 0 )
					return ;
				if( subType == toolSubTypeFlat )
				{
					CFlatToolDlg dlg ;
					if( dlg.DoModal() == IDOK )
					{
						CTool* pTool = new CTool() ;
						pTool->CreateFlat(5., 10.) ;
						// ����pTool����������...
						m_pTSG->Add(pTool) ;
						CString name ;
						pTool->GetName(name) ;
						hT = pTree->InsertItem(name, 0, 0, hTSG) ;
						pTree->SetItemData(hT, (DWORD_PTR)pTool) ;
						pTool->SetItem(hT) ;
						pTLib->SetModified() ;
						pTree->Invalidate(TRUE) ;
						return ;
					}
				}
				else
				if( subType == toolSubTypeBall )
				{
					CBallToolDlg dlg ;
					if( dlg.DoModal() == IDOK )
					{
						CTool* pTool = new CTool() ;
						pTool->CreateBall(5., 10.) ;
						// ����pTool����������...
						m_pTSG->Add(pTool) ;
						CString name ;
						pTool->GetName(name) ;
						hT = pTree->InsertItem(name, 1, 1, hTSG) ;
						pTree->SetItemData(hT, (DWORD_PTR)pTool) ;
						pTool->SetItem(hT) ;
						pTLib->SetModified() ;
						pTree->Invalidate(TRUE) ;
						return ;
					}
				}
				else
				if( subType == toolSubTypeTorus )
				{
				}
				else
				if( subType == toolSubTypeBarrel )
				{
					CBarrelToolDlg dlg ;
					if( dlg.DoModal() == IDOK )
					{
					}
				}
			}
		}
	}
}

// ɾ��
void CTLibDlg::OnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTLib* pTLib = (CTLib*)GetTLib() ;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1) ;
	if( pTLib &&
		pTree )
	{
		HTREEITEM hItem = GetSelected() ;
		if( hItem )
		{
			if( m_pTG )
			{
				if( AfxMessageBox(_T("ȷ��ɾ��?"), MB_YESNO) == IDYES )
				{
					if(	m_pTSG == NULL ) // ɾ����CTGroup:m_pTG
					{
						pTLib->Remove(m_pTG) ;
						delete m_pTG ;
					}
					else
					if( m_pTool == NULL ) // ɾ������CTSubGroup:m_pTSG
					{
						m_pTG->Remove(m_pTSG) ;
						delete m_pTSG ;
					}
					else // ɾ������CTool:m_pTool
					{
						m_pTSG->Remove(m_pTool) ;
						delete m_pTool ;
					}
					pTLib->SetModified() ;
					pTree->DeleteItem(hItem) ;
					pTree->Invalidate(TRUE) ;
				}
			}
		}
	}
}

// ����
void CTLibDlg::OnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTLib* pTLib = (CTLib*)GetTLib() ;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1) ;
	if( pTLib &&
		pTree )
	{
		HTREEITEM hItem = GetSelected(), hTSG, hT ;
		if( hItem )
		{
			if( m_pTG && // ѡ���˵���
				m_pTSG &&
				m_pTool )
			{
				hTSG = m_pTSG->GetItem() ;
				if( hTSG == 0 )
					return ;
				CTool* pTool = m_pTool->Copy() ;
				m_pTSG->Add(pTool) ;
				CString name ;
				pTool->GetName(name) ;
				hT = pTree->InsertItem(name, 0, 0, hTSG) ;
				pTree->SetItemData(hT, (DWORD_PTR)pTool) ;
				pTool->SetItem(hT) ;
				pTLib->SetModified() ;
				pTree->Invalidate(TRUE) ;
				return ;
			}
		}
	}
}

// �༭
void CTLibDlg::OnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTLib* pTLib = (CTLib*)GetTLib() ;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1) ;
	if( pTLib &&
		pTree )
	{
		HTREEITEM hItem = GetSelected(), hTSG ;
		if( hItem )
		{
			if( m_pTG && // ѡ���˵���
				m_pTSG &&
				m_pTool )
			{
				int subType = m_pTSG->GetSubType() ;
				hTSG = m_pTSG->GetItem() ;
				if( hTSG == 0 )
					return ;
				if( subType == toolSubTypeFlat )
				{
					CFlatToolDlg dlg ;
					if( dlg.DoModal() == IDOK )
					{
						// ����m_pTool����������...
						m_pTool->Recreate() ;
						pTLib->SetModified() ;
						return ;
					}
				}
				else
				if( subType == toolSubTypeBall )
				{
					CBallToolDlg dlg ;
					if( dlg.DoModal() == IDOK )
					{
						// ����m_pTool����������...
						m_pTool->Recreate() ;
						pTLib->SetModified() ;
						return ;
					}
				}
				else
				if( subType == toolSubTypeTorus )
				{
				}
				else
				if( subType == toolSubTypeBarrel )
				{
					CBarrelToolDlg dlg ;
					if( dlg.DoModal() == IDOK )
					{
						// ����m_pTool����������...
						m_pTool->Recreate() ;
						pTLib->SetModified() ;
						return ;
					}
				}
			}
		}
	}
}

// nt add 2010/9/27
// ѡ��ǰ����
void CTLibDlg::OnClickedMfcButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTLib* pTLib = (CTLib*)GetTLib() ;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1) ;
	if( pTLib &&
		pTree )
	{
		HTREEITEM hItem = GetSelected() ;
		if( hItem )
		{
			if( m_pTG && // ѡ���˵���
				m_pTSG &&
				m_pTool )
			{
				if( m_pDoc )
				{
					CMill* pMill = m_pDoc->GetMill() ;
					if( pMill )
					{
						CTool* pTool = m_pTool->Copy() ;
						pMill->SetTool(pTool) ;
					}
				}
			}
		}
	}
}

BOOL CTLibDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_images.Create(IDB_TOOLLIB, 16, 0, RGB(255, 0, 255)) ;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1) ;
	CTLib* pTLib = (CTLib*)GetTLib() ;
	if( pTree &&
		pTLib )
	{
		pTree->SetImageList(&m_images, TVSIL_NORMAL) ;
		HTREEITEM hRoot = pTree->InsertItem(_T("���߿�"), 4, 4);
		pTree->SetItemData(hRoot, 0) ;
		pTree->SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

		CString name ;
		HTREEITEM hTG, hTSG, hT ;
		int i, n = pTLib->GetNumOfGroup() ;
		for( i = 0 ; i < n ; i++ )
		{
			CTGroup* pTG = pTLib->GetGroup(i) ;
			if( pTG )
			{
				pTG->GetName(name) ;
				hTG = pTree->InsertItem(name, 4, 4, hRoot);
				pTree->SetItemData(hTG, (DWORD_PTR)pTG) ;
				pTG->SetItem(hTG) ;
				int j, m = pTG->GetNumOfSubGroup() ;
				for( j = 0 ; j < m ; j++ )
				{
					CTSubGroup* pTSG = pTG->GetSubGroup(j) ;
					if( pTSG )
					{
						pTSG->GetName(name) ;
						hTSG = pTree->InsertItem(name, 4, 4, hTG) ;
						pTree->SetItemData(hTSG, (DWORD_PTR)pTSG) ;
						pTSG->SetItem(hTSG) ;
						int k, s = pTSG->GetNumOfTool() ;
						for( k = 0 ; k < s ; k++ )
						{
							CTool* pTool = pTSG->GetTool(k) ;
							if( pTool )
							{
								pTool->GetName(name) ;
								int index = 0, subType ;
								subType = pTool->GetSubType() ;
								if( subType == toolSubTypeFlat )
									index = 0 ;
								else
								if( subType == toolSubTypeBall )
									index = 1 ;
								else
								if( subType == toolSubTypeTorus )
									index = 2 ;
								else
								if( subType == toolSubTypeBarrel )
									index = 3 ;
								hT = pTree->InsertItem(name, index, index, hTSG) ;
								pTree->SetItemData(hT, (DWORD_PTR)pTool) ;
								pTool->SetItem(hT) ;
							}
						}
						pTree->Expand(hTSG, TVE_EXPAND) ;
					}
				}
				pTree->Expand(hTG, TVE_EXPAND) ;
			}
		}
		pTree->Expand(hRoot, TVE_EXPAND) ;
	}

	SetBackgroundColor(RGB(200, 200, 255)) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTLibDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
	cmdDlgUI(0) ;
}

HTREEITEM CTLibDlg::GetSelected()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pTG = NULL ;
	m_pTSG = NULL ;
	m_pTool = NULL ;
	CTLib* pTLib = (CTLib*)GetTLib() ;
	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1) ;
	if( pTLib &&
		pTree )
	{
		HTREEITEM hItem = pTree->GetSelectedItem() ;
		if( hItem )
		{
			int i, n = pTLib->GetNumOfGroup() ;
			for( i = 0 ; i < n ; i++ )
			{
				CTGroup* pTG = pTLib->GetGroup(i) ;
				if( pTG )
				{
					HTREEITEM hTG = pTG->GetItem() ;
					if( hTG == hItem )
					{
						m_pTG = pTG ;
						return hItem ;
					}
					int j, m = pTG->GetNumOfSubGroup() ;
					for( j = 0 ; j < m ; j++ )
					{
						CTSubGroup* pTSG = pTG->GetSubGroup(j) ;
						if( pTSG )
						{
							HTREEITEM hTSG = pTSG->GetItem() ;
							if( hTSG == hItem )
							{
								m_pTG = pTG ;
								m_pTSG = pTSG ;
								return hItem ;
							}
							int k, s = pTSG->GetNumOfTool() ;
							for( k = 0 ; k < s ; k++ )
							{
								CTool* pTool = pTSG->GetTool(k) ;
								if( pTool )
								{
									HTREEITEM hTool = pTool->GetItem() ;
									if( hTool == hItem )
									{
										m_pTG = pTG ;
										m_pTSG = pTSG ;
										m_pTool = pTool ;
										return hItem ;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return 0 ;
}
