/*	2010/3/30 nt
 *	the head file of CTool
 */
#ifndef _Tool_h_
#define _Tool_h_

////////////////////////////////////////////////////////////////
// CTool : ����
/*	tool type
 */
enum EToolType2
{
	toolTypeUD = -1, // user defined
	toolTypeMill = 0, // ϳ��
	toolTypeDrill = 1,
	toolTypeLathe = 2
	// ...
} ;
//--------------------------------------------------------------
/*	tool subtype
 */
enum EToolSubType
{
	toolSubTypeUD = -1, // user defined
	toolSubTypeFlat = 0, // ƽ�׵�
	toolSubTypeBall = 1, // ��ͷ��
	toolSubTypeTorus = 2, // ���ε�
	toolSubTypeBarrel = 3, // ���ε�
	toolSubTypeCone = 4, // ׶��
	toolSubTypeBNose = 5, // ţ�ǵ�
	toolSubTypeCBall = 6, // ׶����ͷ��
	toolSubTypeCBNose = 7 // ׶��ţ�ǵ�
	// ...
} ;
//--------------------------------------------------------------
#define TOOL_MAXNUMPARAM 10
#define TOOL_MAXNUMTRS 32
/*	Usage:
 *		(1)CTool* pTool = new CTool() ;
 *		(2)pTool->CreateFlat(r, h) ;
 *		(3)pTool->Draw(pVI, drawMode) ;
 *		(4)delete pTool
 */
// nt modify 2010/9/22
class CTool : public CObj
{
public:
	int m_type ; // ����
	int m_subType ; // ������
	int m_ver ; // version
	double m_ds[TOOL_MAXNUMPARAM] ; // ���߳��Ȳ���
	double m_rs[TOOL_MAXNUMPARAM] ; // ���߰뾶����
	double m_as[TOOL_MAXNUMPARAM] ; // ���߽ǶȲ���
	double m_rOffset ; // �뾶����
	int m_roRegister ; // �뾶�����Ĵ���
	double m_zOffset ; // ���Ȳ���
	int m_zoRegister ; // ���Ȳ����Ĵ���
	int m_nBlade ; // ������
	int m_material ; // ���Ϻ�
	CStr m_name ; // ��������
	int m_no ; // ���ߺ�

	BOX3D m_box ;
	RFRAME m_lf ; // �������������ϵ
	double m_dTol ;
	double m_dAng ;
	int m_color ; // RGB
	int m_n ; // �ж��ٸ�TRS
	TRS* m_trss[TOOL_MAXNUMTRS] ; // TRS����

	HTREEITEM m_hItem ;
	
public:
	CTool() ;
	~CTool() ;

	int CreateFlat(double r, double h) ;
	int CreateBall(double r, double h) ;
	int CreateTorus(double r1,
			        double r2,
					double r3,
					double h1,
					double h2) ; // nt add 2010/6/28
	//...
	int Recreate() ; // nt add 2010/9/22
	CTool* Copy() ; // nt add 2010/9/22
	int GetType() ;
	int GetSubType() ;
	int GetNumOfTRS() ;
	TRS* GetTRS(int index) ;
	int AddProfile(CURVE* curve, INTERVAL* interval) ; // copy curve
	double GetDTol() ;
	int SetDTol(double dTol) ;
	double GetDAng() ;
	int SetDAng(double dAng) ;
	int GetLF(RFRAME* pLF) ;
	int SetLF(RFRAME* pLF) ;
	int GetName(CStr& name) ;
	int SetName(CStr& name) ;
	int GetName(CString& name) ; // nt add 2016/6/4
	int SetName(CString& name) ; // nt add 2016/6/4
	int GetNo() ;
	int SetNo(int no) ;
	HTREEITEM GetItem() ;
	void SetItem(HTREEITEM hItem) ;
	int GetColor() ;
	int SetColor(int color) ;
	int CalBox() ;
	int GetBox(BOX3D* box) ;
	int Disc() ;
	int Draw(void* pVI, int drawMode) ;
	int Pick(PINFO* pi) ; // return 0=error,1=picked,2=not picked
	int Save(FILE* fp) ; // nt add 2010/9/22
	int Load(FILE* fp) ; // nt add 2010/9/22
	int Serialize(CArchive& ar) ;
} ;
////////////////////////////////////////////////////////////////
#endif