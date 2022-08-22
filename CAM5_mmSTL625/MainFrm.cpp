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

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "CAM.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////
// CMainFrame
IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_MODELTREE, &CMainFrame::OnModelTree)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()
//--------------------------------------------------------------
// CMainFrame ����/����
CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	m_pWndAttrib = NULL ; // nt add 2010/8/21
}

CMainFrame::~CMainFrame()
{
	if( m_pWndAttrib )
	{
		//m_pWndAttrib->Undock() ;
		delete m_pWndAttrib ;
	}
}
//--------------------------------------------------------------
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	CMFCRibbonStatusBarPane* pElement = new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE) ;
	pElement->SetText(_T("_                                                                                                                                   _")) ;
	m_wndStatusBar.AddElement(pElement, strTitlePane1);
	pElement = new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE) ;
	pElement->SetText(_T("_                                                         _")) ;
	m_wndStatusBar.AddExtendedElement(pElement, strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndMT.EnableDocking(CBRS_ALIGN_ANY); // nt del this line 2010/11/5!!!��ͼ���FY���������
	DockPane(&m_wndMT);
	m_wndMT.ShowPane(TRUE, FALSE, TRUE) ; // nt add 2010/8/21
			
	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cx = GetSystemMetrics(SM_CXSCREEN) ; // nt add 2001/10/16
	cs.cy = GetSystemMetrics(SM_CYSCREEN) ; // nt add 2001/10/16

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ����ģ����
	CString strMT;
	bNameValid = strMT.LoadString(IDS_CAM_VIEW);
	ASSERT(bNameValid);
	if (!m_wndMT.Create(strMT, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_MT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ�����ģ����������\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hMTIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CAM_VIEW_HC : IDI_CAM_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndMT.SetIcon(hMTIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
//--------------------------------------------------------------
// nt add 2010/8/21
BOOL CMainFrame::CreateAttribWnd(CDialogEx* pDlg, UINT ID)
{
	if( m_pWndAttrib )
		return FALSE ;

	m_pWndAttrib = new CDlgPane(pDlg, ID) ;
	CString strAttrib ;
	BOOL bNameValid = strAttrib.LoadString(IDS_ATTRIB_VIEW);
	ASSERT(bNameValid);
	if (!m_pWndAttrib->Create(strAttrib, 
							  this,
							  CRect(0, 0, 200, 200),
							  TRUE,
							  ID_VIEW_MT,
							  WS_CHILD | 
							  WS_VISIBLE | 
							  WS_CLIPSIBLINGS |
							  WS_CLIPCHILDREN |
							  CBRS_LEFT |
							  CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������Դ�������\n");
		return FALSE ; // δ�ܴ���
	}
	HICON hMTIcon = (HICON)::LoadImage(::AfxGetResourceHandle(), 
									   MAKEINTRESOURCE(IDI_ATTRIB),
									   IMAGE_ICON,
									   ::GetSystemMetrics(SM_CXSMICON),
									   ::GetSystemMetrics(SM_CYSMICON),
									   0);
	m_pWndAttrib->SetIcon(hMTIcon, FALSE);
	UpdateMDITabbedBarsIcons();
	m_pWndAttrib->EnableDocking(CBRS_ALIGN_ANY);
	CDockablePane* pTabbedBar = NULL;
	m_pWndAttrib->AttachToTabWnd(&m_wndMT, DM_SHOW, TRUE, &pTabbedBar);
	m_pWndAttrib->ShowPane(TRUE, FALSE, TRUE) ;

	return TRUE ;
}

// nt add 2010/8/21
void CMainFrame::CloseAttribWnd()
{
	if( m_pWndAttrib )
	{
		m_pWndAttrib->UndockPane(TRUE) ; // nt add 2010/11/28
		m_pWndAttrib->DestroyWindow() ;
		delete m_pWndAttrib ;
		m_pWndAttrib = NULL ;
	}
	return ;
}
//--------------------------------------------------------------
// nt add 2010/8/20
void CMainFrame::OnModelTree()
{
	if( m_wndMT.IsVisible() == FALSE )
		m_wndMT.ShowPane(TRUE, FALSE, TRUE) ;
}
//--------------------------------------------------------------
// CMainFrame message handlers
// prompting string, nt add 2009/10/21
static CStr prompting ; // nt add 2009/10/21
// prompting flag, nt add 2009/12/15, �����ʾ�ͼ�������ĳ�ͻ����
static int pf ; // =1:prompting, =0:not prompting
//--------------------------------------------------------------
// nt add 2009/10/21
void camPromptUpdate()
{
	CMainFrame* pMF = (CMainFrame*)theApp.m_pMainWnd ;
	CMFCRibbonStatusBar* pStatusBar = &(pMF->m_wndStatusBar) ;
	CString temp;
	temp = prompting;
	pStatusBar->GetElement(0)->SetText(temp) ;
	pStatusBar->GetExElement(0)->Redraw();
	pStatusBar->RedrawWindow();
	return ;
}

void camPromptAttach(char c)
{
	char s[2] ;
	s[0] = c ;
	s[1] = '\0' ;
	// nt add 2009/12/15
	if( pf == 1 )
		prompting = "" ;
	pf = 0 ;
	// end
	prompting += s ;
	camPromptUpdate() ;
	return ;
}

void camPromptAttach(CStr& str)
{
	prompting += str ;
	camPromptUpdate() ;
	return ;
}

void camPromptGet(CStr& str)
{
	str = prompting ;
	return ;
}

void camPromptClear()
{
	prompting = "" ;
	camPromptUpdate() ;
	return ;
}
//--------------------------------------------------------------
/*	2002/9/27 nt
 *	prompt str in statusbar
 */
void camPromptStr(CStr& str)
{
	prompting = str ; // nt add 2009/10/21
	camPromptUpdate() ; // nt add 2009/10/21
	pf = 1 ; // nt add 2009/12/15

	return ;
}

void camPromptStr(char* text)
{
	CStr str = text ;
	camPromptStr(str) ;

	return ;
}

void camPromptPt(double p[2])
{
	CMainFrame* pMF = (CMainFrame*)theApp.m_pMainWnd ;
	CMFCRibbonStatusBar* pStatusBar = &(pMF->m_wndStatusBar) ;
	/*CRect rect = pStatusBar->GetExElement(0)->GetRect() ;
	if( rect.right-rect.left < 150 )
	{
		rect.left = rect.right-150 ;
		pStatusBar->GetExElement(0)->SetRect(rect) ;
		rect = pStatusBar->GetElement(0)->GetRect() ;
		rect.right = rect.left+800 ;
		pStatusBar->GetElement(0)->SetRect(rect) ;
		pStatusBar->GetExElement(0)->SetTextAlwaysOnRight(0) ;
		pStatusBar->RecalcLayout();
	}*/
	CString str ;
	str.Format(_T("x = %5.3lf, y = %5.3lf"), p[0], p[1]) ;
	pStatusBar->GetExElement(0)->SetText(str) ;
	pStatusBar->GetExElement(0)->Redraw();
	pStatusBar->RedrawWindow();

	return ;
}
////////////////////////////////////////////////////////////////
