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

// CAMView.h : CCAMView ��Ľӿ�
//

#pragma once

class CCommand ;
class CCAMView : public CView
{
protected: // �������л�����
	CCAMView();
	DECLARE_DYNCREATE(CCAMView)

// ����
public:
	CCAMDoc* GetDocument() const;

	int m_drawMode ; // nt 2000/5/13
	CCommand* m_pCmd ; // nt 2000/5/14
	void* m_pVI ; // nt 2000/5/13
	void* m_glf ; // nt add 2009/7/24, for testing
	PNT3D m_p ; // previous lbutton down position, nt add 2003/5/31
	// for tool motion simulation, nt add 2010/4/1
	UINT m_dt1 ; // ����CSim��ʱ����
	UINT m_t1 ;
	UINT m_dt2 ; // ���»��Ƶ�ʱ����
	UINT m_t2 ;
	CSim* m_pSim ;
	CSim5* m_pSim5 ; // nt add 2010/6/2
	CTool* m_pTool ; // ��ʱ
	GCODETPATH* m_pGT ; // ��ʱ

// ����
public:
	int GetDrawMode() ; // nt 2000/5/13
	void* GetVI() ; // nt 2000/5/13
	void ClearCmd() ; // nt 2000/10/7

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

// ʵ��
public:
	virtual ~CCAMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewPan();
	afx_msg void OnUpdateViewPan(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomByMouse();
	afx_msg void OnUpdateViewZoomByMouse(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomByBox();
	afx_msg void OnUpdateViewZoomByBox(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomAll();
	afx_msg void OnViewZoomOut();
	afx_msg void OnViewZoomIn();
	afx_msg void OnViewRotate();
	afx_msg void OnUpdateViewRotate(CCmdUI* pCmdUI);
	afx_msg void OnViewPerspective();
	afx_msg void OnViewParallel();
	afx_msg void OnViewSelect();
	afx_msg void OnViewXy();
	afx_msg void OnViewYz();
	afx_msg void OnViewZx();
	afx_msg void OnViewIso2();
	afx_msg void OnViewPlane();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFileGCode();
	afx_msg void OnViewSim();
	afx_msg void OnViewSim5();
	afx_msg void OnViewStop();
	afx_msg void OnViewDispOnOff();
	afx_msg void OnViewTri();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CAMView.cpp �еĵ��԰汾
inline CCAMDoc* CCAMView::GetDocument() const
   { return reinterpret_cast<CCAMDoc*>(m_pDocument); }
#endif

