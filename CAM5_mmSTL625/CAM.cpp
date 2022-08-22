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

// CAM.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CAM.h"
#include "Models.h"
#include "Mills.h" // nt add 2010/4/1
#include "MainFrm.h"
#include "ChildFrm.h"
#include "CAMDoc.h"
#include "CAMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////
// CCAMApp
BEGIN_MESSAGE_MAP(CCAMApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CCAMApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()
//--------------------------------------------------------------
// CCAMApp ����
CCAMApp::CCAMApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CAM.AppID.Version1.0"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_pVI = NULL ; // nt add 2009/12/17
	m_pTLib = NULL ; // nt add 2010/9/24

	// nt add 2010/11/28
	optionInit(&m_option) ;
}

// nt add 2009/12/22
CCAMApp::~CCAMApp()
{
	// nt add 2010/11/28 : save options
	CStr pathName =	cfFillFullPathName("Options.Dat") ;
	optionSave(&m_option, pathName) ;
	// end
	rgbsFree() ;
	// nt add 2010/9/24
	if( m_pTLib )
	{
		CTLib* pTLib = (CTLib*)m_pTLib ;
		if( pTLib->IsModified() )
			pTLib->Save() ;
		delete pTLib ; // free tool lib
		m_pTLib = NULL ;
	}
}
//--------------------------------------------------------------
// Ψһ��һ�� CCAMApp ����
CCAMApp theApp;

// CCAMApp ��ʼ��

BOOL CCAMApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("BUAA���ؼӹ����Ӧ�ó���V2010"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CAMTYPE,
		RUNTIME_CLASS(CCAMDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CCAMView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	m_nCmdShow = SW_SHOWMAXIMIZED ; // nt add 2009/12/18
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// register draw functions which are used in GP.dll, nt add 2001/11/24
	if( regDrawPt(viDrawPoint) != ERSUCSS ||
		regDrawLin(viDrawLine) != ERSUCSS ||
		regDrawPoly(viDrawPolyline) != ERSUCSS ||
		regDrawTris(viDrawTris) != ERSUCSS ||
		regDrawQuas(viDrawQuas) != ERSUCSS )
		return FALSE ;

	// nt add 2009/12/22 : �ο�
	CStr pathName = cfFillFullPathName("ACI.txt") ;
	rgbsCreate(pathName.GetBuffer(0)) ;

	// tool lib, nt add 2010/9/24
	pathName = cfFillFullPathName("TLib.txt") ;
	CTLib* pTLib = new CTLib() ;
	if( pTLib->Load(pathName) != 1 )
	{
		pTLib->CreateBasic() ;
		pTLib->SetModified() ;
	}
	m_pTLib = pTLib ;

	// nt add 2010/11/28 : options
	pathName = cfFillFullPathName("Options.Dat") ;
	optionLoad(&m_option, pathName) ;

	// nt add 2010/5/24, ��λĬ��Ϊmm
	gpSetTol(1.0e-5) ;
	gpSetAng(1.0e-11) ;
	double pre[3] ;
	pre[0] = 1. ;
	pre[1] = 0.2 ;
	pre[2] = 10. ;
	gpSetPre(pre) ;
	double dsc[3] ;
	dsc[0] = 2.5 ;
	dsc[1] = 0.2 ;
	dsc[2] = 10. ;
	gpSetDsc(dsc) ;
	//gpSetFit(0.001) ;
	double tes[3] ;
	tes[0] = 1. ;
	tes[1] = 1.047197551196597 ;
	tes[2] = 0.001 ;
	gpSetTes(tes) ;
	// nt add 2021/7/26
	gpSetFit(0.01) ;

	return TRUE;
}

int CCAMApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}
//--------------------------------------------------------------
// CCAMApp ��Ϣ�������
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CCAMApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
//--------------------------------------------------------------
// CCAMApp �Զ������/���淽��

void CCAMApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CCAMApp::LoadCustomState()
{
}

void CCAMApp::SaveCustomState()
{
}
//--------------------------------------------------------------
void CCAMApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
	TCHAR szFilter[] = _T("Part Files (*.Part)|*.part||") ;
	CFileDialog dlg(TRUE, _T("*.Part"), NULL, OFN_HIDEREADONLY, szFilter) ;
	if( dlg.DoModal() == IDOK )
	{
		CString ext = dlg.GetFileExt() ;
		CString pathName = dlg.GetPathName() ;
		if( ext == _T("Part") ||
			ext == _T("PART") ||
			ext == _T("part") )
			OpenDocumentFile(pathName) ;
	}
}
//--------------------------------------------------------------
int camGetSysVerNo()
{
	//return 5 ; // nt modify 2010/9/9
	return 6 ; // nt modify 2021/8/13
}

static int g_docVerNo ;

void camSetDocVerNo(int verNo)
{
	g_docVerNo = verNo ;
}

// �����ȵ���camSetDocVerNo()��������
int camGetDocVerNo()
{
	return g_docVerNo ;
}

// �ڲ�CView֮��Э��opengl��Դ
// nt add 2009/9/13
// nt rewrite 2011/7/7
int camWake(void* pVI)
{
	if( pVI )
	{
		if( theApp.m_pVI &&
			theApp.m_pVI != pVI ) // ��Ҫ�л���ǰ�����VI
			viSleep(theApp.m_pVI) ;
		HGLRC hGLRC = wglGetCurrentContext() ;
		if( hGLRC == NULL )
			viWake(pVI) ;
		theApp.m_pVI = pVI ;

		return 1 ;
	}
	else
		return 0 ;
}

// nt add 2009/9/13
int camSleep(void* pVI)
{
	if( pVI )
	{
		if( theApp.m_pVI == pVI ) // ��ǰ�����VI��������pVI
		{
			viSleep(theApp.m_pVI) ;
			theApp.m_pVI = NULL ;
		}
	}
	else
	{
		if( theApp.m_pVI ) // ��ǰ�����VI����pVI
		{
			viSleep(theApp.m_pVI) ;
			theApp.m_pVI = NULL ;
		}	
	}

	return 1 ;
}
//--------------------------------------------------------------
// nt add 2010/8/22, common global functions
int cmdDlgUI(int ui)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd() ;
	CMDIChildWnd* pChildFrame = pMainFrame->MDIGetActive() ;
	CCAMDoc* pDoc = (CCAMDoc*)(pChildFrame->GetActiveDocument()) ;
	if( pDoc )
	{
		pDoc->CmdDlgUI(ui) ;
		return 1 ;
	}
	else
		return 0 ;
}
//--------------------------------------------------------------
void* GetTLib()
{
	return theApp.m_pTLib ;
}
//--------------------------------------------------------------
// nt add 2010/11/28
OPTION* camGetOption()
{
	return &(theApp.m_option) ;
}

void camSetOption(OPTION* option)
{
	if( option )
		theApp.m_option = *option ;

	return ;
}

// nt add 2020/5/12
void* camGetMTView()
{
	CMainFrame* pWndMain = (CMainFrame*)AfxGetMainWnd();
	if( pWndMain == NULL )
		return NULL ;
	return &(pWndMain->m_wndMT) ;
}
////////////////////////////////////////////////////////////////

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAboutDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}

void CAboutDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}

CDocument* CCAMApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: �ڴ����ר�ô����/����û���
	CFileFind finder ; // nt add 2011/5/24, �������Ҳ�������ļ������µ�崻�
	BOOL bWorking = finder.FindFile(lpszFileName) ;
	if( bWorking == FALSE )
		return NULL ;

	return CWinAppEx::OpenDocumentFile(lpszFileName);
}
//==============================================================
