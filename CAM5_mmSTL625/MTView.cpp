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
#include "MainFrm.h"
#include "Models.h"
#include "Mills.h" // nt add 2010/4/1
#include "SelSet.h"
#include "CAMDoc.h"
#include "CAMView.h"
#include "MTView.h"
#include "Resource.h"
#include "CAM.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CMTView

CMTView::CMTView()
{
	m_pViewTree = NULL ;
	m_pObj = NULL ; // nt add 2010/11/29
}

CMTView::~CMTView()
{
}

BEGIN_MESSAGE_MAP(CMTView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_COLOR2, OnEditColor)
	ON_COMMAND(ID_EDIT_WIDTH2, OnEditWidth)
	ON_COMMAND(ID_EDIT_DELETE2, OnEditDelete)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar ��Ϣ�������

int CMTView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndTree.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("δ�ܴ����ļ���ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ������ͼͼ��:
	m_images.Create(IDB_MT_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndTree.SetImageList(&m_images, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	FillMTView();
	AdjustLayout();

	return 0;
}

void CMTView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CMTView::FillMTView()
{
	/*HTREEITEM hRoot = m_wndTree.InsertItem(_T("ģ��"), 0, 0);
	m_wndTree.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSrc = m_wndTree.InsertItem(_T("��׼��1"), 0, 0, hRoot);

	m_wndTree.InsertItem(_T("����1"), 1, 1, hSrc);
	m_wndTree.InsertItem(_T("����2"), 1, 1, hSrc);
	m_wndTree.InsertItem(_T("����3"), 1, 1, hSrc);
	m_wndTree.InsertItem(_T("����4"), 1, 1, hSrc);
	m_wndTree.InsertItem(_T("����5"), 1, 1, hSrc);
	m_wndTree.InsertItem(_T("����6"), 1, 1, hSrc);

	HTREEITEM hInc = m_wndTree.InsertItem(_T("����1"), 0, 0, hRoot);

	m_wndTree.InsertItem(_T("����1"), 2, 2, hInc);
	m_wndTree.InsertItem(_T("����2"), 2, 2, hInc);
	m_wndTree.InsertItem(_T("����3"), 2, 2, hInc);
	m_wndTree.InsertItem(_T("����4"), 2, 2, hInc);
	m_wndTree.InsertItem(_T("����6"), 2, 2, hInc);
	m_wndTree.InsertItem(_T("����7"), 2, 2, hInc);

	HTREEITEM hRes = m_wndTree.InsertItem(_T("��λ�켣1"), 0, 0, hRoot);

	m_wndTree.InsertItem(_T("����1"), 2, 2, hRes);
	m_wndTree.InsertItem(_T("����2"), 2, 2, hRes);
	m_wndTree.InsertItem(_T("����3"), 2, 2, hRes);
	m_wndTree.InsertItem(_T("����4"), 2, 2, hRes);

	m_wndTree.Expand(hRoot, TVE_EXPAND);
	m_wndTree.Expand(hSrc, TVE_EXPAND);
	m_wndTree.Expand(hInc, TVE_EXPAND);*/
}

void CMTView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree ;
	if( m_pViewTree == NULL )
		pWndTree = (CTreeCtrl*) &m_wndTree ;
	else
		pWndTree = m_pViewTree ;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	m_pObj = NULL ; // nt add 2010/11/29
	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			CVO* pVO = (CVO*)pWndTree->GetItemData(hTreeItem) ; // nt add 2010/11/29
			m_pObj = pVO ; // nt add 2010/11/29
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CMTView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, 
							  rectClient.left, 
							  rectClient.top,
							  rectClient.Width(),
							  cyTlb, 
							  SWP_NOACTIVATE | SWP_NOZORDER);
	if( m_pViewTree == NULL )
		m_wndTree.SetWindowPos(NULL, 
							   rectClient.left + 1, 
							   rectClient.top + cyTlb + 1,
							   rectClient.Width() - 2,
							   rectClient.Height() - cyTlb - 2,
							   SWP_NOACTIVATE | SWP_NOZORDER);
	else
		m_pViewTree->SetWindowPos(NULL, 
							      rectClient.left + 1,
							      rectClient.top + cyTlb + 1,
							      rectClient.Width() - 2,
							      rectClient.Height() - cyTlb - 2,
							      SWP_NOACTIVATE | SWP_NOZORDER);
}

void CMTView::OnProperties()
{
	//AfxMessageBox(_T("����...."));
	// nt add 2010/11/29
	if( m_pObj )
	{
		int type = ((CVO*)(m_pObj))->GetType() ;
		if( type == camStep )
		{
			CView* pView = GetView() ;
			if( pView )
			{
				pView->SendMessage(WM_COMMAND, ID_NC_PDESIGN) ;
			}
		}
	}
	m_pObj = NULL ;
}

void CMTView::OnFileOpen()
{
	// TODO: �ڴ˴���������������
}

void CMTView::OnFileOpenWith()
{
	// TODO: �ڴ˴���������������
}

void CMTView::OnDummyCompile()
{
	// TODO: �ڴ˴���������������
}

void CMTView::OnEditCut()
{
	// TODO: �ڴ˴���������������
}

void CMTView::OnEditCopy()
{
	// TODO: �ڴ˴���������������
}

void CMTView::OnEditClear()
{
	// TODO: �ڴ˴���������������
}

void CMTView::OnEditDelete()
{
	CView* pView = GetView() ;
	if( pView )
	{
		pView->SendMessage(WM_COMMAND, ID_EDIT_DELETE) ;
	}
}

void CMTView::OnEditColor()
{
	CView* pView = GetView() ;
	if( pView )
	{
		pView->SendMessage(WM_COMMAND, ID_EDIT_COLOR) ;
	}
}

void CMTView::OnEditWidth()
{
	CView* pView = GetView() ;
	if( pView )
	{
		pView->SendMessage(WM_COMMAND, ID_EDIT_WIDTH) ;
	}
}

void CMTView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CRect rectTree;
	if( m_pViewTree == NULL )
		m_wndTree.GetWindowRect(rectTree);
	else
		m_pViewTree->GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CMTView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	if( m_pViewTree == NULL )
		m_wndTree.SetFocus();
	else
		m_pViewTree->SetFocus() ;
}

void CMTView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ����*/);

	m_images.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_MT_VIEW_24 : IDB_MT_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_images.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_images.Add(&bmp, RGB(255, 0, 255));

	m_wndTree.SetImageList(&m_images, TVSIL_NORMAL);
}

// nt add 2010/9/9
void CMTView::OnActivate()
{
	CCAMView* pView = (CCAMView*)GetView() ;
    if( !pView )
		return ;
	CCAMDoc *pDoc = (CCAMDoc*)(pView->GetDocument()) ;
	if( !pDoc )
		return ;
	CViewTree* pViewTree = pDoc->GetTree() ; // ������ΪNULL
	if( pViewTree != m_pViewTree )
	{
		if( m_pViewTree )
			m_pViewTree->ShowWindow(FALSE) ; // �رյ�ǰ����ģ����m_pViewTree����ʾ
		m_wndTree.ShowWindow(FALSE) ;
		pViewTree->ShowWindow(TRUE) ; // ��ʾpViewTree
		m_pViewTree = pViewTree ;
		AdjustLayout() ;
	}

	return ;
}

// nt add 2010/11/29
CView* CMTView::GetView()
{
	CMainFrame *pWndMain = (CMainFrame*)AfxGetMainWnd() ;
	if( pWndMain == NULL )
		return NULL ;
	CMDIChildWndEx* temp = (CMDIChildWndEx*)pWndMain->MDIGetActive() ;
	if( temp == NULL )
		return NULL ;
	CChildFrame* pChild = (CChildFrame*)temp ;
    if( !pChild )
		return NULL ;
    return pChild->GetActiveView() ;
}

// nt add 2020/5/12
CViewTree* CMTView::GetViewTree()
{
	return m_pViewTree ;
}

// nt add 2020/5/12
void CMTView::SetViewTree(CViewTree* pViewTree)
{
	m_pViewTree = pViewTree ;
}