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

// CAMDoc.h : CCAMDoc ��Ľӿ�
//
#pragma once

#include "ViewTree.h" // nt add 2010/9/9

////////////////////////////////////////////////////////////////
class CCommand ;
class CSelSet ;
class CPart ;
class CMill ;
class CPV ;
class CCAMView ;
//--------------------------------------------------------------
class CCAMDoc ;
typedef void (__thiscall CCAMDoc::*MHANDLER)() ; // message handler
//--------------------------------------------------------------
class CCAMDoc : public CDocument
{
private:
	// flag to be set 1 when destroying this CDocument
	int m_bDestroy ; // 0, 1 : nt add 2002/5/21
	// font
	LOGFONT m_lf ; // current document font
	// command
	CCommand* m_pCmd ; // current command
	int m_lastCmd ;
	// select set
	CSelSet* m_pSelSet ;
	COA m_ses ; // nt add 2009/12/5, Ŀ���Ǽ�ʰȡ����ĸ��Ӷ�
	// navigate
	int m_drawed ; // 0,1:not drawed, has drawed the navigated point
	PNT3D m_nav_p ; // navigated point
	// for preview
	CPV* m_pPV ; // nt add 2002/5/21
	// workplane
	double m_gridSize ; // work plane grid size
	CRefPlane* m_pWorkPlane ; // current workplane

	// model
	CPart* m_pPart ; // part model
	// CAM
	CMill* m_pMill ; // nt add 2010/4/1
	// model tree
	CViewTree m_tree ; // model tree, nt add 2010/9/8
	CImageList m_images ; // nt add 2010/9/8
	HTREEITEM m_hPart ; // ��Ӧm_pPart, nt add 2010/9/8
	HTREEITEM m_hMill ; // ��Ӧm_pMill, nt add 2010/9/8

	// current color index and material index, nt add 2010/10/17
	//int m_colorIndex ; // from 0 to 255
	//int m_materialIndex ; // from 256 to 256+41
	// ��������ת�Ƶ���theApp.m_option, nt 2010/11/28

public:
	CCAMView* GetActiveView() ; // nt add 2003/2/15
	int IsDestroying() ; // nt add 2002/5/21

	void AddPV(CPV* pPV) ; // nt add 2002/5/21
	void RemovePV() ;

	void GetLogFont(LOGFONT* pLF) ;
	double GetGridSize() ;
	void SetGridSize(double gridSize) ;
	CRefPlane* GetWorkPlane() ;
	CPart* GetPart() ;
	CMill* GetMill() ; // nt add 2010/6/2
	int GetBox(double min[3], double max[3]) ; // nt add 2009/5/9
	int AddFeature(CFeature* pF) ; // nt add 2009/12/17
	int DelFeature(CFeature* pF) ; // nt add 2010/9/1
	int AddStep(CStep* pStep) ; // nt add 2010/11/29
	int DelStep(CStep* pStep) ; // nt add 2010/11/29
	int AddLin(PNT3D p, PNT3D q) ; // nt add 2010/3/24
	int AddPt(PNT3D p) ; // nt add 2010/12/27
	CSelSet* GetSelSet() ;
	void ClearSelSet() ; // nt add 2011/8/22
	int GetNumOfSelected() ; // nt add 2009/12/5
	int GetSelected(int type, int max) ; // nt add 2009/12/5
	void* GetObj(int i) ; // nt add 2009/12/5
	int GetType(int i) ; // nt add 2009/12/5
	double GetU(int i) ; // nt add 2009/12/5
	double GetV(int i) ; // nt add 2009/12/18
	int GetGPP(PNT3D gpp) ; // nt add 2021/6/24 geometry picked position
	
	void Draw(void* pVI, int drawMode) ;
	void Redraw() ;
	void OnActivate() ; // nt add 2010/9/9
	CViewTree* GetTree() ; // nt add 2010/9/9
	int RebuildModelTree() ; // nt add 2010/9/9
	
	void ClearCmd() ;
	void ClearCmdAll() ;
	int HasCmd() ; // nt add 2009/12/17
	int GetLastCmd() ;
	int SetLastCmd(int cmd) ;

	int Navigate(DNAVI* dn) ;
	int NavigateKeyPt(DNAVI* dn) ; // nt add 2010/3/26
	void DrawNavP(int mode) ; // mode = 0(eraze) or 1(draw)

	void OnMouseMove(int nFlags, double p[3], double v[3], void* pVI) ; // nt 2000/7/18
	void OnLButtonDown(int nFlags, double p[3], double v[3], void* pVI) ; // nt 2000/7/18
	void OnLButtonUp(int nFlags, double p[3], double v[3], void* pVI) ; // nt 2000/7/18
	void OnRButtonDown(int nFlags, double p[3], double v[3], void* pVI) ; // nt 2000/7/18
	void OnRButtonUp(int nFlags, double p[3], double v[3], void* pVI) ; // nt 2000/7/18
	int OnReturn() ; // nt add 2009/10/21
	int AddPtWithColor(PNT3D p,int color) ;
	void Compare(CURVE* curve, BSCUR* nurbs, INTERVAL* interval, int nSample) ;
	void Compare(SURFACE* surface, BSSUR* nurbs, BOXUV* boxuv, int nSample) ;

protected: // �������л�����
	CCAMDoc();
	DECLARE_DYNCREATE(CCAMDoc)

// ����
public:
	//UINT m_cmdID ; // ��ǰ������ID
	MHANDLER m_mh ; // message handler=CCAMDoc�ĳ�Ա����,default value=NULL
	CDialogEx* m_pDlg ; // ��ǰ����ʹ�õĶԻ���
	int m_nStep ; // ����״̬�ĵڼ���, default value = 0
	int m_ui ; // ��ǰ�û�����״̬:-1=idle,0=cancel,1=ok,2=apply, nt modify 2010/8/28

// ����
public:
	int ChkCmd(MHANDLER mh) ; // �������״̬��nt add 2010/8/22
	int OnCmd(MHANDLER mh, CDialogEx* pDlg, int ID) ; // �����������Ի���nt add 2010/8/22
	int CmdDlgUI(int ui) ; // ����Ի����û�������nt add 2010/8/22
	int CmdEnd() ; // ���������nt add 2010/8/22
	int FreeCmdDlg() ; // �ͷ�����ڼ��Ի���, nt add 2010/8/22

	// smf add 2022/10/09
	// �������������C:\\Test\\OutPutChordalHeight.txt��
	void OutPutChordalHeight(double *iChordalHeight, int iNum);

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CCAMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
public:
	void SetSearchContent(const CString& value);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSaveNURBS();
	afx_msg void OnFileLoadGE();
	afx_msg void OnFileSaveFeatures();
	afx_msg void OnFileLoadFeatures();
	afx_msg void OnFileSaveSTL();
	afx_msg void OnFileLoadIGES();
	afx_msg void OnEditDelete();
	afx_msg void OnEditMove();
	afx_msg void OnEditRotate();
	afx_msg void OnEditScale();
	afx_msg void OnEditMirror();
	afx_msg void OnEditColor();
	afx_msg void OnEditWidth();
	afx_msg void OnEditMove2Ori();
	afx_msg void OnInsertWPlane();
	afx_msg void OnInsertOffset();
	afx_msg void OnInsertNormalPlane();
	afx_msg void OnInsertPlane3P();
	afx_msg void OnInsertPlane2P();
	afx_msg void OnInsertPlaneX();
	afx_msg void OnInsertPlaneY();
	afx_msg void OnInsertPlaneZ();
	afx_msg void OnInsertTanPln();
	afx_msg void OnInsertPlaneMove();
	afx_msg void OnInsertRefPt();
	afx_msg void OnInsertInterp();
	afx_msg void OnInsertLin();
	afx_msg void OnInsertCircle();
	afx_msg void OnInsertEll();
	afx_msg void OnInsertArcRAA();
	afx_msg void OnInsertArcLL();
	afx_msg void OnInsertArc();
	afx_msg void OnInsertLine2Cir();
	afx_msg void OnInsertFilletCir();
	afx_msg void OnInsertFilletCur();
	afx_msg void OnInsertBC();
	afx_msg void OnInsertCurves();
	afx_msg void OnInsertUVCurve();
	afx_msg void OnInsertSurBorder();
	afx_msg void OnInsertIntCur();
	afx_msg void OnInsertIsoCur();
	afx_msg void OnInsertPlane();
	afx_msg void OnInsertExtrude();
	afx_msg void OnInsertRevolve();
	afx_msg void OnInsertRule();
	afx_msg void OnInsertBndSur4();
	afx_msg void OnInsertLoft();
	afx_msg void OnInsertSweep();
	afx_msg void OnInsertPipe();
	afx_msg void OnInsertConnect();
	void InsertConnect1() ;
	void InsertConnect2() ;
	afx_msg void OnInsertFill();
	afx_msg void OnInsertFileSur();
	afx_msg void OnInsertCyl();
	afx_msg void OnInsertSph();
	afx_msg void OnInsertCone();
	afx_msg void OnInsertTorus();
	afx_msg void OnInsertOffSur();
	afx_msg void OnInsertPts();
	afx_msg void OnInsertMPoints2Curve();
	afx_msg void OnInsertSurPts();
	afx_msg void OnInsertPic();
	afx_msg void OnInsertPCloud();
	afx_msg void OnInsertFitSur();
	afx_msg void OnInsertPath5();
	afx_msg void OnInsertMinDist();
	afx_msg void OnToolBreak();
	afx_msg void OnToolTrimCur();
	afx_msg void OnToolToNURBS();
	afx_msg void OnToolBCurG1();
	afx_msg void OnToolBCurG2();
	afx_msg void OnToolCurveExtend();
	afx_msg void OnToolSmthCur();
	afx_msg void OnToolMorph();
	afx_msg void OnToolTanLin2();
	afx_msg void OnToolCurPts();
	afx_msg void OnToolChkCurGx() ;
	afx_msg void OnToolChkG0();
	afx_msg void OnToolChkG1();
	afx_msg void OnToolBSurG1();
	afx_msg void OnToolBSurG2();
	afx_msg void OnToolChkSurGx();
	afx_msg void OnToolMeshSur();
	afx_msg void OnToolCompPrj();
	afx_msg void OnToolTest();
	afx_msg void OnToolModSurCPt();
	afx_msg void OnToolModSurIPt();
	afx_msg void OnToolCutSur();
	afx_msg void OnToolRevUV();
	afx_msg void OnToolSurClose();
	afx_msg void OnToolSurSmth();
	afx_msg void OnToolMeshRefine();
	afx_msg void OnAnalysisCurvatureComb();
	afx_msg void OnAnalysisDrawUV();
	afx_msg void OnAnalysisRefine();
	afx_msg void OnAnalysisControlPts();
	afx_msg void OnAnalysisMetric();
	afx_msg void OnAnalysisDist();
	afx_msg void OnAnalysisDist2();
	afx_msg void OnAnalysisCCG();
	afx_msg void OnAnalysisCFG();
	afx_msg void OnNCModel();
	afx_msg void OnNCMCS();
	afx_msg void OnNCParameters();
	afx_msg void OnNCMachine();
	afx_msg void OnNCMaterialLib();
	afx_msg void OnNCPDesign();
	afx_msg void OnNCToolLib();
	afx_msg void OnNCProgram();
	afx_msg void OnNCPostProcess();
	afx_msg void OnNCExportCLF();
	afx_msg void OnNCExportDoc();
	afx_msg void OnSimMotion();
	afx_msg void OnTest();
	afx_msg void OnToolChkMesh(); // nt add 2021/6/13
	afx_msg void OnToolChkBnd(); // nt add 2021/6/13
	afx_msg void OnToolOption(); // nt add 2021/6/16
	afx_msg void OnToolOptTri1(); // nt add 2021/8/13
	afx_msg void OnToolOptTri2(); // nt add 2021/8/13
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
#endif // SHARED_HANDLERS
};
////////////////////////////////////////////////////////////////
