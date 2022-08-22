/*	2001/11/16 nt
 *	head file of feature definitions
 */
#ifndef _Feature_h_
#define _Feature_h_

////////////////////////////////////////////////////////////////
//	Features
/*	1999/8/19 nt
 *	EFeatureType
 */
enum EFeatureType
{
	ftOrigin = 0,
	ftRefPlane = 1,
	ftRefAxis = 2,
	ftRefPt = 3,
	ftRefCur = 4,
	ftRefSur = 5,
	ftPic = 6,
	ftSketch = 7,
	ftPrimitive = 8,
	ftHole = 9,
	ftRib = 10,
	ftDraft = 11,
	ftFillet = 12,
	ftChamfer = 13,
	ftCavity = 14,
	ftPattern = 15,
	ftMirror = 16,
	ftTriangle = 17, // nt add 2010/11/14
	ftMark = 18 // nt add 2011/4/20
} ;

/*	1999/8/20 nt
 *	EFeatureState
 */
enum EFeatureState
{
	fsNormal,
	fsSelected,
	fsActived,
	fsSuppressed,
	fsRollback,
	fsDeleted,
	fsEditing,
	fsInvalid,
	fsDangling
} ;
//--------------------------------------------------------------
#define FEATURE_VISIBLE 1
#define FEATURE_PICK 2
#define FEATURE_FREEZE 4
#define FEATURE_PRINT 8

/*	1999/8/19 nt
 *	CFeature
 */
class CFeature : public CVO
{
protected:
	CStr m_name ; // ����������
	int m_featId ; // ������Ӧ�Ĳ�����stepId
	int m_no ; // nt add 2010/9/26, �����ڼ���ģ��
	int m_createTime ; // time elapse since 1970/1/1/00/00, set when create
	int m_lastModifyTime ; // time elapse since 1970/1/1/00/00, set by Update()
	int m_it ; // inner time, m_it++when feature edit or update
	int m_waitUpdateFlag ; // 1���������Ҫ����(���ȶ�״̬);0�������(�ȶ�״̬)
	int m_flags ; // nt add 2010/9/9
	int m_color ; // ��������ɫ, ������color����(<=255)Ҳ������material����(>255)
	int	m_state ; // ������״̬
	HTREEITEM m_hItem ; // nt add 2010/9/9
	BOX3D m_box ;
public:
	CFeature() ;
	virtual ~CFeature() ;

	virtual int	GetType() = 0 ; // return EFeatureType
	virtual CFeature* Copy() = 0 ; // nt 2009/5/27 �ſ�

	//int GetFeatId() ;	
	//void SetFeatId(int featId) ;
	int GetNo() ;
	void SetNo(int no) ;
	void GetName(CStr& name) ;
	void SetName(CStr& name) ;
	void GetName(CString& name); // nt add 2016/6/4
	void SetName(CString& name); // nt add 2016/6/4
	HTREEITEM GetItem() ; // nt add 2010/9/9
	void SetItem(HTREEITEM hItem) ; // nt add 2010/9/9
	int GetFlags() ; // nt add 2012/10/12
	void SetFlags(int flags) ; // nt add 2012/10/12
	//int GetCreateTime() ;
	//int GetLastModifyTime() ;
	//int GetIT() ;
	int GetColor() ;
	int SetColor(int color) ;
	int SetDrawColor(int drawMode) ; // nt add 2009/12/21
	int SetDrawColor2(int drawMode) ; // nt add 2011/7/6
	int	GetState() ;
	void SetState(int state) ;
	int	GetBox(BOX3D* box) ;
	void SetBox(BOX3D* box) ; // nt add 2014/3/19
	virtual int CalBox() = 0 ;
	virtual int Move(VEC3D v) = 0 ; // nt add 2009/5/27
	virtual int Rotate(PNT3D pivot, VEC3D axis, double angle) = 0 ; // nt add 2009/5/27
	virtual int Mirror(PNT3D pivot, VEC3D normal) = 0 ; // nt add 2010/10/17
	virtual int Scale(double scale) = 0 ; // nt add 2010/9/11
	//int GetWaitUpdateFlag() ;
	//void SetWaitUpdateFlag(int flag) ;

	//virtual int FindFathers(COA& fathers) = 0 ; // Ѱ�������ĸ�,���ظ���Ŀ,�޷��������ⲿ���������ڲ�����
	//int FindAllFathers(COA& features, COA& fathers) ; // Ѱ�����и�,������Ŀ
	//int FindChildren(COA& features, COA& children) ; // Ѱ����������,��������Ŀ
	//int FindAllChildren(COA& features, COA& children) ; // Ѱ��������,��������Ŀ

	//int NeedUpdate() = 0 ; // 1:������Ҫ����;0:�����������
	//int Suppress(int flag = 1) ; // ���������ָ�����,0,1:error,sucess
	//int RollBack(int flag = 1) ; // ��������, 0,1:error,sucess
	//int Delete(int flag = 1) ; // ����ɾ��, 0,1:error,sucess

	virtual void Prompt(CStr& str) ; // nt add 2010/10/12
	virtual int Pick(PINFO* pi) = 0 ;
	virtual int PickByBox(RFRAME* pLF, BOX2D* pLB, double r) = 0 ; // nt add 2010/4/22
	//virtual int Update() = 0 ; // 1:�������³ɹ�;0:��������ʧ��
	virtual int Draw(void* pVI, int drawMode) = 0 ;
	virtual int Draw2(void* pVI, int drawMode) = 0 ; // nt add 2010/4/23
	virtual int Serialize(CArchive& ar) ;
} ;
////////////////////////////////////////////////////////////////

#endif