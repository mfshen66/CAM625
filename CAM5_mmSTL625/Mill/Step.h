/*	2010/9/25 nt
 *	the head file of CStep
 */
#ifndef _Step_h_
#define _Step_h_

////////////////////////////////////////////////////////////////
// CStep : ����
#define camStep 80 // nt add 2010/11/29

enum EGeometryModelType
{
	gmtWorkpiece = 0,
	gmtPart = 1,
	gmtPSurface = 2
} ;

class CStep : public CVO // nt modify 2010/11/29 old is CObj
{
private:
	int m_color ; // 0 to 255, ��ɫ������, nt add 2010/11/29
	CStr m_name ; // ����������
	int m_no ; // ���
	// (1)����ģ��
	CIA m_workpiece ; // ��һЩ��CRefSur��no��ɣ���CStep�ͷſռ䣩�����Ǽӹ�ǰģ��
	CIA m_part ; // ��һЩ��CRefSur��no��ɣ���CMill�ͷſռ䣩�����Ǽӹ���ģ��
	CIA m_psurfaces ; // �����棬��һЩ��CRefSur��CRefCur��no��ɣ���CStep�ͷſռ䣩
	// (2)��ǰ����
	RFRAME m_lf ; // ��ǰ�ӹ�����ϵ???
	CTool* m_pTool ; // ��ǰʹ�õ��ߣ���CStep�ͷſռ䣩
	CP m_cp ; // ��ǰ��������(cutting parameters)
	// (3)�켣
	CPath* m_pPath ;
	BOX3D m_box ;
	HTREEITEM m_hItem ; // nt add 2010/11/29

public:
	CStep() ;
	~CStep() ;

	int GetType() ; // nt add 2010/11/29
	CStep* Copy() ; // nt add 2010/9/26
	void GetName(CStr& name) ;
	void SetName(CStr& name) ;
	void GetName(CString& name) ; // nt add 2016/6/4
	void SetName(CString& name) ; // nt add 2016/6/4
	int GetNo() ;
	int SetNo(int no) ;
	int GetNumOfGeometry(int gmt) ; // nt add 2010/9/26
	int GetGeometryNo(int gmt, int index) ; // nt add 2010/9/26
	int AddGeometry(int gmt, int geometryNo) ; // nt add 2010/9/26
	int DeleteGeometry(int gmt, int geometryNo) ; // nt add 2010/9/26
	void ClearModel(int gmt) ; // nt add 2010/9/26
	int GetMCS(RFRAME* pLF) ; // ȡ�ӹ�����ϵ
	int SetMCS(RFRAME* pLF) ; // ���üӹ�����ϵ
	void GetCP(CP* pCP) ; // nt add 2010/9/26
	void SetCP(CP* pCP) ; // nt add 2010/9/26
	CTool* GetTool() ;
	void SetTool(CTool* pTool) ;
	CPath* GetPath() ;
	void SetPath(CPath* pPath) ;
	int GetColor() ;  // nt add 2010/11/29
	void SetColor(int color) ;  // nt add 2010/11/29
	HTREEITEM GetItem() ; // nt add 2010/11/29
	void SetItem(HTREEITEM hItem) ; // nt add 2010/11/29
	int CalBox() ;
	int GetBox(BOX3D* box) ;
	void SetBox(BOX3D* box) ; // nt add 2010/9/26
	int Draw(void* pVI, int drawMode) ;
	int Draw2(void* pVI, int drawMode) ; // nt add 2010/11/29
	int Pick(PINFO* pinfo) ;
	int	PickByBox(RFRAME* pLF, BOX2D* pBox, double r, COA& es) ; // 1:picked;2:pick none;0:error
	int Serialize(CArchive& ar) ;
} ;
////////////////////////////////////////////////////////////////
#endif