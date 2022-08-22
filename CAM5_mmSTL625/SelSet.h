/*	1997/6/16 nt
 *	the head file of entity select set class CSelSet2D
 *	nt rewrite 2010/4/18 : ʹ֮�����ڴ��ģͼԪ��ʰȡ
 */
#ifndef _SelSet_h_
#define _SelSet_h_

#ifdef __cplusplus
///////////////////////////////////////////////////////////////
//	ѡ��
#define MAX_NUM_ET 100 // ��������ʵ���ϵ�����Ԫ��
#define MAX_NUM_SE 10 // ��Ҫʰȡ��, nt modify 2011/4/20 old is 8, nt modify 2022/6/15 old 9
//--------------------------------------------------------------
/*  1997/6/16 nt
 *  ѡ��
 *	nt rewrite 2010/4/18
 */
class CSelSet
{
private:
	void* m_pDoc ; // CDocument
	void* m_pVI ;

    int m_enabled ; // 0,1:disable select set,enable select set
	int	m_pickFlags[MAX_NUM_ET] ; // m_pickFlags[stEntity] == 0, not pick Entity; 1, pick

	int m_ppf ; // prompt-property-flag : nt add 2009/11/12
	CVO* m_prompting ; // ��ǰ��ʾ��ʵ��, nt modify 2010/4/18
	CVO* m_actived ; // ��ǰ�����ʵ��, nt modify 2010/4/18
	COA	m_selecteds ; // �ѱ�ѡ���ʵ�弯, ����CVO
	COA m_es ; // nt add 2010/4/18, only used in OnLButtonUp()

	double m_p1[3] ; // for LButtonDown pos, nt add 2002/12/5
	double m_p2[3] ; // for LButtonUp pos, nt add 2002/12/5
	int	m_draw ; // 0:not draw box, 1:box drawed, nt add 2002/12/6
public:
	CSelSet(void* pDoc) ;
	~CSelSet() ;

	void Clear() ; // ���ѡ��������ʵ��
	void ClearDrawFlag() ; // nt add 2009/9/17
	int	IsEnable() ; // 1:enable;0:disable
	void Enable() ; // enable select
	void Disable() ; // disable select
	void EnableEntityPick(int type) ; // enable an entity picking
    void DisableEntityPick(int type) ; // disable an entity picking
    int	IsEntityPickable(int type) ; // is an entity pickable
	int SetVI(void* pVI) ; // nt add 2010/4/18

	void SetPP(int flag) ; // nt add 2009/11/12
	// caller do not free the return memory
	CVO* GetPrompting() ; // nt modify 2010/4/18
	// caller do not free the return memory
	CVO* GetActived() ; // nt modify 2010/4/18
	int	GetNumOfSelected() ;
	// caller do not free the return memory
	CVO* GetSelected(int index) ; // local index
	// free CSelEles in entities by the caller
	int	GetSelected(int type, int nVO, COA& vos) ;
	int AddSelected(CVO* pVO) ; // 0:not add, 1:added, ��glFlush()
	int AddSelected2(CVO* pVO) ; // set pVO selected, nt add 2010/4/24
    
	// ��̬��ʾ��ѡ����
	int	OnMouseMove(int nFlags, double p[3], double v[3], void* pVI) ; // 0,1:error,success
	// ѡ��ǰ��ѡ����
	int	OnLButtonDown(int nFlags, double p[3], double v[3], void* pVI) ; // 0,1:error,success
	int	OnLButtonUp(int nFlags, double p[3], double v[3], void* pVI) ; // 0,1:error,success
	int	OnRButtonDown(int nFlags, double p[3], double v[3], void* pVI) ; // 0,1:error,success
	// ���ǰ��ѡ����
	int	OnLButtonDbClick(int nFlags, double p[3], double v[3], void* pVI) ; // 0,1:error,success

	void Draw() ; // nt add pVI 2010/4/18
private:
	void RemovePrompting() ;
	void RemoveActived() ;
	void RemoveSelected() ;
	void DrawBox() ; // nt add 2002/12/6
} ;
///////////////////////////////////////////////////////////////
#endif

#endif