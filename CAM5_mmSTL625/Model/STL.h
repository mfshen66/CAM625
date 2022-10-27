#ifndef _STL_h_
#define _STL_h_

#define EPS06 1e-6
#define STLTRI 60

#define TOLLENGTH 1e-6
#define TOLSQUARELENGTH 1e-12
#define TOLANGLE 1e-6

typedef struct {
	double   x,y,z;
} STLVECTOR;

typedef struct {
	double   x,y;
} POINT2D;

typedef STLVECTOR  STLPNT3D;
typedef struct VertexList   *VList;
typedef struct EdgeList     *EList;
typedef struct FaceList     *FList;
typedef struct FaceRelated  *FRelated;
typedef struct MTIPathOriginList    *POList;
typedef struct GridModel GM ; // nt add 2022/6/15

// smf add 2022/09/07
STLVECTOR vectorNormalize(STLVECTOR &iVector);
STLVECTOR operator- (STLPNT3D &iEnd, STLPNT3D &iBegin);
STLVECTOR operator- (STLVECTOR &iVector); // ����ȡ��
STLVECTOR operator+ (STLVECTOR &iVector1, STLVECTOR &iVector2);
STLVECTOR operator* (double iScalar, STLVECTOR &iVector);
double operator*(STLVECTOR & iVector1, STLVECTOR & iVector2);
STLVECTOR operator^ (STLVECTOR &iVectorU, STLVECTOR &iVectorV);
struct VertexList {
	STLPNT3D     Coord;		
	STLVECTOR    NormalVector;
	VList        Rchild;
	VList        Lchild;
	FRelated     FaceUsed;
	int          FaceNum;
	int			 flag ; // nt add 2022/6/17

	VList SchMinVert(double p[3], double& min) ;
};

struct EdgeList {
	VList         VertexUsed[2];
	EList         ENext;
	FRelated      FaceUsed;
	int           FaceNum;
	double		  FCircleTag;
	int			  FaceCircleTag;
};

struct FaceList : public CVO
{
	STLVECTOR   NormalVector;
	VList       VertexUsed[3];
	EList       EdgeUsed[3];
	FList       FNext;
	int         FaceNO;
	double		  FCircleTag;
	FaceList() ;
	~FaceList() ;
	int GetType() ;
	void GetVertPos(int k, double p[3]) ;
	void GetPos(double gc[3], double p[3]) ;
	int GetNumOfCV(FList f) ; // common vertex
	int IsAdj(FList f) ;
	FList GetAdj(int i, int j) ;
	FList GetAdjRayPass(double p[3], double dir[3], double tol) ; // nt add 2022/7/9
	EList GetEdge(int i, int j) ;
	VList SchMinVert(double p[3], double& min) ;
	int PlaneCut(double pivot[3], double normal[3], double p[3], double dir[3], double tol, double q[3], int& i, int& j);
	int IsIn(double p[3], double tol) ;
	int IsIn2(double p[3], double tol, double prj_p[3]) ; // nt add 2022/7/9 p��ͶӰ��Face�ڣ����߽磩
	void Prj(double p[3], double prj_p[3]) ;
	void GetBarycenter(double center[3]) ;
	int Draw(void* pVI, int drawMode) ;
	int Draw2(void* pVI, int drawMode) ;
};

// �߶���ƽ����
int mathSegmentIntPln(PNT3D iPntOfSegment1, PNT3D iPntOfSegment2,  // �߶ε������˵�
	PNT3D iPntOnPlane, VEC3D iNormPlane,  // ƽ��ķ�ʸ��ƽ����һ��
	double iTolLength, double iTolAngle,  // �����ݲ�Ƕ��ݲ�
	PNT3D* oPntsOfIntersection); // ���������ָ��

// ƽ������������
int mathPlnIntTri(
	PNT3D iPntOfTri1, PNT3D iPntOfTri2, PNT3D iPntOfTri3, // �����ε���������
	PNT3D iPntOnPlane, VEC3D iNormPlane,  // ƽ��ķ�ʸ��ƽ����һ��
	double iTolLength, double iTolAngle,  // �����ݲ�Ƕ��ݲ�
	PNT3D* oPntsOfIntersection, // ���������ָ��
	int *oIndexOfIntEdge, int &oNumOfIntEdge); // ��ƽ���ཻ�ıߵ���ż�����

int mathPlnIntTri(
	STLPNT3D iPntOfTri1, STLPNT3D iPntOfTri2, STLPNT3D iPntOfTri3, // �����ε���������
	STLPNT3D iPntOnPlane, STLVECTOR iNormPlane,  // ƽ��ķ�ʸ��ƽ����һ��
	double iTolLength, double iTolAngle,  // �����ݲ�Ƕ��ݲ�
	STLPNT3D* oPntsOfIntersection,  // ���������ָ��
	int *oIndexOfIntEdge, int &oNumOfIntEdge); // ��ƽ���ཻ�ıߵ���ż�����

int mathPlnIntTri(
	FList iTriangle, // ������
	STLPNT3D iPntOnPlane, STLVECTOR iNormPlane,  // ƽ��ķ�ʸ��ƽ����һ��
	double iTolLength, double iTolAngle,  // �����ݲ�Ƕ��ݲ�
	STLPNT3D* oPntsOfIntersection,  // ���������ָ��
	int *oIndexOfIntEdge, int &oNumOfIntEdge); // ��ƽ���ཻ�ıߵ���ż�����

// ������ƽ������
double mathSquareDist(PNT3D p1, PNT3D p2);
double mathSquareDist(STLPNT3D p1, STLPNT3D p2);

BOOL mathIsCoincidentPoint(STLPNT3D iPoint1, STLPNT3D iPoint2);
// �����ľ���
double mathDist(STLPNT3D p1, STLPNT3D p2);

void mathPrjPntPln(STLPNT3D iPoint, STLPNT3D iPointOfPlane, STLVECTOR iNormalOfPlane, STLPNT3D &oProjectPoint);

const double INVSQRT2 = 0.70710678118654752440;

struct MTIPathOriginList{//����ǰ·���ɷֶ�,�����·�����ɷֶ�
	int TNum;					//�������
	int DNum;					//�������
	STLPNT3D *PTrail;			//�ؼ���			POLYLINE
	STLPNT3D *PNTrail;			//�ؼ��㷨��
	FList *FTrail;				//�������Ƭ
	int *SNum;					//�ؼ�����Ŀ��
	int *ENum;					//�ؼ�����Ŀĩ
	POList PONext;

	POList Copy() ; // nt add 2022/7/10
	POList DirectOffset(double d) ; // nt add 2022/7/10
	// �����Թ���
	POList GeodesicOffsetNonFlexible(double iDistance, int iDir, double * oChordalHeight, POList &offset_2); // smf add 2022/7/27
	// ���Թ���
	POList GeodesicOffsetFlexible(double iDistance, int iDir, double *oChordalHeight); // smf add 2022/9/25
	void Draw() ;
	double Snap(GridModel* pGM, FList fs[2], double ps[2][3], double tol, int& I, double& t, int& perp) ;
	BOOL FindNextPoint(FRelated &ioFace, int &ioFaceNum, STLPNT3D &ioPointOnPlane, STLVECTOR iNormalOfPlane, STLVECTOR iOffsetDir);
	BOOL IsPointAVertex(STLPNT3D iPoint, FaceList* iFace, int oIndex);
	BOOL IsPointOnEdge(STLPNT3D iPoint, EList iEdge);
};

struct FaceRelated abstract {
	FList     Face;
	FRelated  FNext;
};

typedef struct Pog POG ;
struct Pog : public CObj // point on grid
{
	int type ;
	void* vef ;
	double p[3] ;

	Pog(int Type, void* Vef, double P[3]) ;
	~Pog() ;
} ;

typedef struct Pl PL ;
struct Pl
{
	COA pogs ;
	double arcLen ;

	Pl() ;
	~Pl() ;

	int CalArcLen() ;
	int Opt(double tol, double eps) ;
	void ReplaceBegin(double p[3]) ;
	void ReplaceEnd(double p[3]) ;
} ;

typedef struct Pp PP ; // point pair
struct Pp
{
	FList fs[2] ;
	double ps[2][3] ;
	int I ; // λ������, I<1��ʾ���point pair����Ч�ģ�������
	double t ; // [0., 1.)
	double d ; // geodesic distance
	int perp ; // nt add 2022/7/4 1=��ֱ, 0=����ֱ
} ;

typedef struct Gdinfo GDINFO ; // ��ؾ�����Ϣ
struct Gdinfo
{
	int ns[2] ; // ns[0]Ϊpolyline1�ڵ������ns[1]Ϊpolyline2�ڵ����
	// pps[0][0],pps[1][0]δ��
	PP* pps[2] ; // pps[0]��Ԫ��ʵ�ʸ���Ϊns[0]+1, pps[1]��Ԫ��ʵ�ʸ���Ϊns[1]+1
	double min ;
	double max ;
	int i ; // i>0, ��С������Ϊpps[0][i], ����Ϊpps[1][|i|]
	int I ; // I>0, ��������Ϊpps[0][I], ����Ϊpps[1][|I|]

	Gdinfo() ;
	~Gdinfo() ;
} ;

struct GridModel {
	VList   VRoot;
	EList   EHead;
	FList   FHead;
	int  VerNum;
	int  EdgeNum;
	int  FaceNum;
	POList	*POLHead;//�����ض�ǰ·��//���ɷֶ�
	double stl_xmin ;
	double stl_ymin ;
	double stl_zmin ;
	double stl_xmax ;
	double stl_ymax ;
	double stl_zmax ;
	int TraverseNum ;
	int MeshResulttag ;
	char MeshResult[10][256] ;
	char PointName[100], ModelName[100];
	STLPNT3D PBreak;
	char PreDataFileName[256];//�ݿ�,�����е�Path/Geometry/Trajectory
	double isag,istep,iangle,Plyangle,dval,gapValue;
	int TrailNumDum,FiberNum;
	int stlFaceTag;

	GridModel() ;
	BOOL stlCreateSTLTriangle(STLPNT3D p1, STLPNT3D p2, STLPNT3D p3);
	BOOL stlVectorNormal(STLVECTOR *v1);

	//���˹�ϵ����

	FList stlCreateFace(STLVECTOR *nv, STLPNT3D *p1, STLPNT3D *p2, STLPNT3D *p3,int tNum);
	FList stlFaceAlloc();
	VList stlCreateVertex(VList *root, STLPNT3D *pt);
	VList stlSortTree(STLPNT3D *pt, VList *t);
	VList stlVertexAlloc();
	EList stlCreateEdge(VList p1, VList p2);
	EList stlEdgeAlloc();
	void stlAddFace2Vertex(FList f, VList v);
	void stlAddFace2Edge(FList f, EList e);

	//2016.09Add

	BOOL stlCompareTwo3DPoint(STLPNT3D p3d1, STLPNT3D p3d2, double epsdis);//�������ƶȱȽ�
	int stlCompareTriangleVertex(STLPNT3D p1, STLPNT3D p2, STLPNT3D p3, STLPNT3D q1, STLPNT3D q2, STLPNT3D q3);//����Ƭ���

	STLPNT3D stlTwoVectorPlus(STLPNT3D p1,STLPNT3D p2);//���������p1+p2
	STLPNT3D stlTwoVectorMinus(STLPNT3D p1,STLPNT3D p2);//���������p1-p2
	STLPNT3D stlTwoVectorMultiply(STLPNT3D p1,double l1);//�����ӳ�p1*l1
	STLPNT3D stlTwoVectorDivide(STLPNT3D p1,double l1);//��������p1/l1
	//20170825 ADD DAT�ļ�����
	void stlDealInputFile();
	void stlReadFile(char *file);
	void stlReadSTLBinFile(char *file);
	void stlReadStlFile(char *file);
	void stlRead4Bytes(FILE *stlfile, char *c);
	void stlReadDatFile(char *file);
	void    GetInformationFromPath();//���̷�·����ȡ��Ϣ			��Ҫ���TXT�ļ�
	POList	stlPOLHeadAlloc();//�ض�ǰ·��
    FList stlGetFacetFromNum(int N);
	//void GetNormaVectorOnVertex(VList p) ;
	double stlDistanceTwoPoints(STLPNT3D p1, STLPNT3D p2) ;
	double  stlDistanceOneVector(STLPNT3D p1) ;
	
	STLPNT3D stlDistanceVectorTwoPoint(STLPNT3D p1, STLPNT3D p2);
	STLPNT3D stlTwoVectorProduct(STLPNT3D v1, STLPNT3D v2);
	STLPNT3D stlOPPNormalVector(STLPNT3D v) ;
	STLPNT3D CreateMTIPoint();
	STLPNT3D CreateMTIPoint(double ix,double iy,double iz);//��xyz����
	STLPNT3D CreateMTIPoint(double p1[]);//�����鴴��
	STLPNT3D CreateMTIPoint(double p1[],int iNbStart);
	double GetDistanceVertexToCoreOfTrangle(STLPNT3D p, FList face) ;

	void InitFlagAll() ;
	int CalGeodesicLineOne(FList f, double p1[3], double p2[3], PL** polyline) ;
	int CalGeodesicLineAdj(FList f1, double p1[3], FList f2, double p2[3], double tol, PL** polyline) ;
	int CalGeodesicLine(FList f1, double p1[3], FList f2, double p2[3], double tol, PL** polyline) ;
	FList Prj(FList f1, double p1[3], FList f2, double p2[3], double tol, double ptOnLine[3], double ptOnFace[3]) ; // nt add 2022/7/8	
	int CalGDInfo(POList polys[2], double tol, GDINFO** pGDI) ;
	FList Pick(PNT3D pos, VEC3D dir, double r, PNT3D p, double* pz, PNT3D gc) ;
	void Draw(void* pVI, int drawMode) ;

	int nPolyline ;
	Pl* polylines[100] ;
} ;


// 2022/10/10 smf add

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;
typedef int SElemType; /* SElemType���͸���ʵ������������������Ϊint */


/* ��ջ�ṹ */
typedef struct StackNode
{
	SElemType data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;


typedef struct
{
	LinkStackPtr top;
	int count;
}LinkStack;
#endif