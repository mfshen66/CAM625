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

#pragma once

#include "ViewTree.h"

class CMTViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CMTView : public CDockablePane
{
// ����
public:
	CMTView();

	void AdjustLayout();
	void OnChangeVisualStyle();

// ����
protected:

	CViewTree m_wndTree;
	CImageList m_images;
	CViewTree* m_pViewTree ; // �������ͷŸ�CViewTree
	CMTViewToolBar m_wndToolBar;
	void* m_pObj ; // �����Ҽ��˵�ʱ�����obj, nt add 2010/11/29

protected:
	void FillMTView();

// ʵ��
public:
	virtual ~CMTView();
	void OnActivate() ; // nt add 2010/9/8
	CViewTree* GetViewTree() ; // nt add 2020/5/12
	void SetViewTree(CViewTree* pViewTree) ; // nt add 2020/5/12

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnEditDelete();
	afx_msg void OnEditColor();
	afx_msg void OnEditWidth();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	CView* GetView() ; // nt add 2010/11/29

	DECLARE_MESSAGE_MAP()
};

