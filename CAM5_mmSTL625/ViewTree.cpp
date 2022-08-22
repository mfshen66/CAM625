// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

#include "stdafx.h"
#include "CAM.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "Models.h"
#include "Mills.h"
#include "SelSet.h"
#include "ViewTree.h"
#include "CAMDoc.h"
#include "CAMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree ��Ϣ�������

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hOld = pNMTreeView->itemOld.hItem ;
	HTREEITEM hNew = pNMTreeView->itemNew.hItem ;
	SHORT ctrlKey = GetKeyState(VK_CONTROL) ;
	// CTRL������, ������һѡ���ѡ��״̬
	if( hOld && 
		(ctrlKey&0xF0) )
		SetItemState(hOld, TVIS_SELECTED, TVIS_SELECTED) ;
	if( hNew )
		SetItemState(hNew, TVIS_SELECTED, TVIS_SELECTED) ;
	else
		goto Exit ;

	// nt add 2010/9/9, Ϊ��CSelSet����ͬ��...
	CMainFrame *pWndMain = (CMainFrame*)AfxGetMainWnd() ;
	CMDIChildWndEx* temp = (CMDIChildWndEx*)pWndMain->MDIGetActive() ;
	CChildFrame* pChild = (CChildFrame*)temp ;
    if( !pChild )
		goto Exit ;
    CCAMView* pView = (CCAMView*)pChild->GetActiveView() ;
    if( !pView )
		goto Exit ;
	CCAMDoc *pDoc = (CCAMDoc*)(pView->GetDocument()) ;
	if( !pDoc )
		goto Exit ;
	CViewTree* pT = pDoc->GetTree() ;
	CSelSet* pSelSet = pDoc->GetSelSet() ;
	if( pT == this &&
		pSelSet )
	{
		if( !(ctrlKey&0xF0) )
			pSelSet->Clear() ;
		CVO* pVO = (CVO*)GetItemData(hNew) ;
		pSelSet->AddSelected(pVO) ;
		glFlush() ;
	}

Exit:
	*pResult = 0;
}
