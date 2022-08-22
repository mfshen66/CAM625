/*	2010/3/30 nt
 *	the head file of CPath
 */
#ifndef _Path_h_
#define _Path_h_

////////////////////////////////////////////////////////////////
// CPath�ӹ�·��(��������Ϣ)
//--------------------------------------------------------------
// ���գ���������
enum EOpType
{
	opTypeUndefined = 0,
	opTypeRough = 1, // �ּӹ�
	opTypeHalfFinish = 2, // �뾫�ӹ�
	opTypeFinish = 3, // ���ӹ�
	opTypeClearance = 4 // ����ӹ�
} ;
//--------------------------------------------------------------
// ����·���ķ�ʽ
enum EOpMethod
{
	opMethodUndefined = 0,
	opMethodPlaneCut = 1, // ƽ��
	opMethodOffset = 2, // �Ⱦ�
	opMethodSpiral = 3, // ����
	opMethodIsoline = 4 // �Ȳ�����
} ;
//--------------------------------------------------------------
//enum EMotionType
//{
//	motionTypeUNDEFINED=0,  /* Motion type undefined. */
//	motionTypeRAPID=1, /* Motion type rapid. */
//	motionTypeENGAGE=2, /* Motion type engage. */
//	motionTypeCUT=3, /* Motion type cut. */
//	motionTypeRETRACT=4, /* Motion type retract. */
//	motionTypeFIRST_CUT=5, /* Motion type first cut. */
//	motionTypeAPPROACH=6, /* Motion type approach. */
//	motionTypeSTEPOVER=7, /* Motion type stepover. */
//	motionTypeDEPARTURE=8, /* Motion type departure. This is only valid for a lathe. */
//	motionTypeRETURN=9, /* Motion type return. */
//	motionTypeTRAVERSAL=10, /* Motion type traversal. */
//	motionTypeTHREAD_TURN=11, /* Motion type thread. This is only valid for a lathe*/
//	motionTypeFROM=12, /* Motion type from. */
//	motionTypeGOHOME=13, /* Motion type gohome. */
//	motionTypeCYCLE=14 /* Motion type cycle. */
//} ;

enum EFeedUnit
{
	feedUnitNONE=0, /* No feed unit. */
	feedUnitPER_MINUTE = 1, /* Feed units in minutes. */ // mm/min
	feedUnitPER_REVOLUTION = 2 /*Feed units in revolutions.*/ // mm/r
} ;

typedef struct _linear_motion LMOTION ;
struct _linear_motion
{
	PNT3D position ; /* Coordinates of the point. */
	VEC3D tool_axis ; /* Tool axis specification. */
	double feed_value ; /* Feed value. */
	int feed_unit ; /* Units of feed. */ // see EFeedUnit
	int type ; /* Motion type. */ // see EMotionType
} ;
//--------------------------------------------------------------
//	tool path node for 5 axis milling
typedef struct _pnode PNODE ; // path_node
struct _pnode
{
	int no ; // sequence no
	PNT3D pos ; // tool position, unit=mm
	VEC3D axis ; // tool axis, unit vector
	double fr ; // feed rate, mm/min
	int type ; // see EMotionType
} ;
//--------------------------------------------------------------
#define PATH_NUMPNODE 10000 // number of PNODE per pool
typedef PNODE* PPOOL ; // pool of PNODE
//#define camPath 80 // nt add 2010/6/2, old is 1000, nt modify 2010/8/24
class CPath : public CObj // nt modify 2010/11/29 old use CVO
{
private:
	CStr m_name ;
	BOX3D m_box ;
	int m_opType ; // ��������, EOpType
	int m_opMethod ; // �����ߵ���ʽ, see EOpMethod
	int m_no ; // sequence no, begin with 1

	// �ӹ��켣, nt modify 2010/5/27
	int m_npool ; // note that: m_npool = the size of array m_pools
	PPOOL* m_pools ; // m_pools[i]��PNODE����, ���С����PATH_NUMPNODE
	int m_n ; // m_pools��ǰn��pool�ѷ����˿ռ䣬ǰn-1��pool�Ѵ���PNODE
	int m_m ; // m_pools[n-1]���Ѿ�����m��PNODE
	// ��ǰ�����PNODE����=(n-1)*PATH_NUMPNODE+m
	//int m_color ;

public:
	CPath() ;
	~CPath() ;

	int Create(int npool) ;
	int GetName(CStr& name) ;
	int SetName(CStr& name) ;
	//int GetType() ;
	int GetOpType() ;
	void SetOpType(int opType) ;
	int GetOpMethod() ;
	void SetOpMethod(int opMethod) ;
	int GetNo() ;
	//int GetColor() ;
	//void SetColor(int color) ;
	int CalBox() ;
	int GetBox(BOX3D* box) ;
	int GetNumOfPNode() ;
	int GetPNode(int i, PNODE* pnode) ;
	int AddLinearMotion(LMOTION* lmotion) ;
	int EndAddMotion() ; // nt add 2010/6/2
	int Draw(void* pVI, int drawMode) ;
	//int Draw2(void* pVI, int drawMode) ;
	int Pick(PINFO* pi) ;
	int Serialize(CArchive& ar) ;
	int ToCL(CString& filePath) ; // nt add 2011/11/30
} ;
////////////////////////////////////////////////////////////////
#endif