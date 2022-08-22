/*	2010/3/29 nt
 *	the head file of CMill
 */
#ifndef _Mill_h_
#define _Mill_h_

////////////////////////////////////////////////////////////////
// CMill : ���ؼӹ���������
class CMill : public CObj
{
private:
	CStr m_name ; // nt add 2010/9/26
	// (1)����ģ��
	CIA m_workpiece ; // ��һЩ��CRefSur��ɣ���CMill�ͷſռ䣩�����Ǽӹ�ǰģ��
	CStr m_partName ; // ���ӹ������·��������
	CIA m_part ; // ��һЩ��CRefSur��ɣ���CMill�ͷſռ䣩�����Ǽӹ���ģ��
	// (2)����
	int m_material ; // ��������������
	// (3)����ģ��
	CMachine* m_pMachine ; // ����ģ��
	// (4)��ǰ����
	RFRAME m_lf ; // ��ǰ�ӹ�����ϵ
	CTool* m_pTool ; // ��ǰʹ�õ��ߣ���CMill�ͷſռ䣩
	CP m_cp ; // ��ǰ��������(cutting parameters)
	// (5)����(process_step)����
	COA m_steps ; // ��������
	BOX3D m_box ;

public:
	CMill() ;
	~CMill() ;

	void GetName(CStr& name) ;
	void SetName(CStr& name) ;
	int GetNumOfGeometry(int gmt) ; // nt add 2010/9/26
	int GetGeometryNo(int gmt, int index) ; // nt add 2010/9/26
	int AddGeometry(int gmt, int geometryNo) ; // nt add 2010/9/26
	int DeleteGeometry(int gmt, int geometryNo) ; // nt add 2010/9/26
	void ClearModel(int gmt) ; // nt add 2010/9/26
	int GetMCS(RFRAME* pLF) ; // ȡ�ӹ�����ϵ
	int SetMCS(RFRAME* pLF) ; // ���üӹ�����ϵ
	void GetCP(CP* pCP) ; // nt add 2010/9/26
	void SetCP(CP* pCP) ; // nt add 2010/9/26
	int GetPartName(CStr& partName) ;
	int SetPartName(CStr& partName) ;
	CTool* GetTool() ;
	void SetTool(CTool* pTool) ;
	CMachine* GetMachine() ;
	void SetMachine(CMachine* pMachine) ;
	int GetNumOfStep() ;
	CStep* GetStep(int index) ;
	int GetMaxStepNo() ; // nt add 2010/9/26
	int Add(CStep* pStep) ;
	int Delete(CStep* pStep) ;
	int CalBox() ;
	int GetBox(BOX3D* box) ;
	int Draw(void* pVI, int drawMode) ;
	int Pick(PINFO* pinfo) ;
	int	PickByBox(RFRAME* pLF, BOX2D* pBox, double r, COA& es) ; // 1:picked;2:pick none;0:error
	int Serialize(CArchive& ar) ;
} ;
////////////////////////////////////////////////////////////////

#endif