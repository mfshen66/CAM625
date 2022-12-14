#ifndef _STL_h_
#define _STL_h_

#define EPS06 1e-6
#define STLTRI 60

#define TOLLENGTH 1e-6
#define TOLSQUARELENGTH 1e-12
#define TOLANGLE 1e-6

#define INVERSQRT2 0.7071067811865475244

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
STLVECTOR operator- (STLVECTOR &iVector); // 向量取反
STLVECTOR operator+ (STLVECTOR &iVector1, STLVECTOR &iVector2);
STLVECTOR operator* (double iScalar, STLVECTOR &iVector);
double operator*(STLVECTOR & iVector1, STLVECTOR & iVector2);
STLVECTOR operator^ (STLVECTOR &iVectorU, STLVECTOR &iVectorV);

// smf add 2022/11/01
// 判断圆柱面上的点是否在延长段上:
// iCylBegin, iCylEnd: 圆柱轴线起止点
// iRadius: 圆柱半径
BOOLEAN mathIsPointOnExtension(PNT3D iPoint, PNT3D iCylBegin, PNT3D iCylEnd, double iRadius);

// smf add 2022/11/01
// 线段与圆柱段求交: 
// iSegmBegin, iSegmEnd: 线段的两个端点
// iCylBegin, iCylEnd: 圆柱轴线起止点
// iRadius: 圆柱半径
// oNumIntPnts: 交点个数
// oIntPnts: 交点数组
BOOLEAN mathIntSegmCyl(
	STLVECTOR iSegmBegin, STLVECTOR iSegmEnd,	//线段的两个端点
	STLVECTOR iCylBegin, STLVECTOR iCylEnd,		// 圆柱轴线的起止点
	double iRadius,								// 圆柱半径
	double iTol,								// 容差 
	int &oNumIntPnts,							// 交点个数
	STLVECTOR *oIntPnts);						// 交点数组

// 直线与圆柱求交
int mathIntLinCyl(PNT3D begin, VEC3D dir, PNT3D pivot, VEC3D axis, double r, double tol, double ang, PNT3D intpt1, PNT3D intpt2);
// 线段与圆柱求交
int mathIntSegmCyl(PNT3D begin, PNT3D end, PNT3D pivot, VEC3D axis, double r, double tol, int* pn, PNT3D p1, PNT3D p2, double* pt1, double* pt2);

void mathTransWorldVec3DByXYZ(VEC3D e1,
	VEC3D e2,
	VEC3D e3,
	VEC3D world_vector,
	VEC3D local_vector);
void mathTransLocalPnt3DByOXYZ(PNT3D origin,
	VEC3D e1,
	VEC3D e2,
	VEC3D e3,
	PNT3D local_point,
	PNT3D world_point);

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
	int IsIn2(double p[3], double tol, double prj_p[3]) ; // nt add 2022/7/9 p的投影在Face内（含边界）
	void Prj(double p[3], double prj_p[3]) ;
	void GetBarycenter(double center[3]) ;
	int Draw(void* pVI, int drawMode) ;
	int Draw2(void* pVI, int drawMode) ;
};

// 线段与平面求交
int mathSegmentIntPln(PNT3D iPntOfSegment1, PNT3D iPntOfSegment2,  // 线段的两个端点
	PNT3D iPntOnPlane, VEC3D iNormPlane,  // 平面的法矢及平面上一点
	double iTolLength, double iTolAngle,  // 长度容差及角度容差
	PNT3D* oPntsOfIntersection); // 交点数组的指针

// 平面与三角形求交
int mathPlnIntTri(
	PNT3D iPntOfTri1, PNT3D iPntOfTri2, PNT3D iPntOfTri3, // 三角形的三个顶点
	PNT3D iPntOnPlane, VEC3D iNormPlane,  // 平面的法矢及平面上一点
	double iTolLength, double iTolAngle,  // 长度容差及角度容差
	PNT3D* oPntsOfIntersection, // 交点数组的指针
	int *oIndexOfIntEdge, int &oNumOfIntEdge); // 与平面相交的边的序号及数量

int mathPlnIntTri(
	STLPNT3D iPntOfTri1, STLPNT3D iPntOfTri2, STLPNT3D iPntOfTri3, // 三角形的三个顶点
	STLPNT3D iPntOnPlane, STLVECTOR iNormPlane,  // 平面的法矢及平面上一点
	double iTolLength, double iTolAngle,  // 长度容差及角度容差
	STLPNT3D* oPntsOfIntersection,  // 交点数组的指针
	int *oIndexOfIntEdge, int &oNumOfIntEdge); // 与平面相交的边的序号及数量

int mathPlnIntTri(
	FList iTriangle, // 三角形
	STLPNT3D iPntOnPlane, STLVECTOR iNormPlane,  // 平面的法矢及平面上一点
	double iTolLength, double iTolAngle,  // 长度容差及角度容差
	STLPNT3D* oPntsOfIntersection,  // 交点数组的指针
	int *oIndexOfIntEdge, int &oNumOfIntEdge); // 与平面相交的边的序号及数量

// 两点间的平方距离
double mathSquareDist(PNT3D p1, PNT3D p2);
double mathSquareDist(STLPNT3D p1, STLPNT3D p2);

BOOL mathIsCoincidentPoint(STLPNT3D iPoint1, STLPNT3D iPoint2);
// 两点间的距离
double mathDist(STLPNT3D p1, STLPNT3D p2);

void mathPrjPntPln(STLPNT3D iPoint, STLPNT3D iPointOfPlane, STLVECTOR iNormalOfPlane, STLPNT3D &oProjectPoint);

const double INVSQRT2 = 0.70710678118654752440;

struct MTIPathOriginList{//排序前路径可分段,排序后路径不可分段
	int TNum;					//条数标记
	int DNum;					//段数标记
	STLPNT3D *PTrail;			//关键点			POLYLINE
	STLPNT3D *PNTrail;			//关键点法向
	FList *FTrail;				//相关三角片
	int *SNum;					//关键点数目起
	int *ENum;					//关键点数目末
	POList PONext;

	POList Copy() ; // nt add 2022/7/10
	POList DirectOffset(double d) ; // nt add 2022/7/10
	// 非柔性滚子
	POList GeodesicOffsetNonFlexible(
		double iDistance, 
		int iDir,  // 确保等距方向保持一致，iDir=1 或 iDir=-1.
		double * oChordalHeight); // smf add 2022/7/27
	// 柔性滚子
	POList GeodesicOffsetFlexible(
		double iDistance, 
		int iDir, // 确保等距方向保持一致，iDir=1 或 iDir=-1.
		double *oChordalHeight); // smf add 2022/9/25
	void Draw() ;
	double Snap(GridModel* pGM, FList fs[2], double ps[2][3], double tol, int& I, double& t, int& perp) ;
	BOOL FindNextPoint(FRelated &ioFace, int &ioFaceNum, STLPNT3D &ioPointOnPlane, STLVECTOR iNormalOfPlane, STLVECTOR iLastDir);
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
	int I ; // 位置索引, I<1表示这个point pair是无效的，不能用
	double t ; // [0., 1.)
	double d ; // geodesic distance
	int perp ; // nt add 2022/7/4 1=垂直, 0=不垂直
} ;

typedef struct Gdinfo GDINFO ; // 测地距离信息
struct Gdinfo
{
	int ns[2] ; // ns[0]为polyline1节点个数，ns[1]为polyline2节点个数
	// pps[0][0],pps[1][0]未用
	PP* pps[2] ; // pps[0]的元素实际个数为ns[0]+1, pps[1]的元素实际个数为ns[1]+1
	double min ;
	double max ;
	int i ; // i>0, 最小距离点对为pps[0][i], 否则为pps[1][|i|]
	int I ; // I>0, 最大距离点对为pps[0][I], 否则为pps[1][|I|]

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
	POList	*POLHead;//排序后截断前路径//不可分段
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
	char PreDataFileName[256];//暂空,存已有的Path/Geometry/Trajectory
	double isag,istep,iangle,Plyangle,dval,gapValue;
	int TrailNumDum,FiberNum;
	int stlFaceTag;

	GridModel() ;
	BOOL stlCreateSTLTriangle(STLPNT3D p1, STLPNT3D p2, STLPNT3D p3);
	BOOL stlVectorNormal(STLVECTOR *v1);

	//拓扑关系建立

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

	BOOL stlCompareTwo3DPoint(STLPNT3D p3d1, STLPNT3D p3d2, double epsdis);//两点相似度比较
	int stlCompareTriangleVertex(STLPNT3D p1, STLPNT3D p2, STLPNT3D p3, STLPNT3D q1, STLPNT3D q2, STLPNT3D q3);//三角片检测

	STLPNT3D stlTwoVectorPlus(STLPNT3D p1,STLPNT3D p2);//两向量求和p1+p2
	STLPNT3D stlTwoVectorMinus(STLPNT3D p1,STLPNT3D p2);//两向量求差p1-p2
	STLPNT3D stlTwoVectorMultiply(STLPNT3D p1,double l1);//向量延长p1*l1
	STLPNT3D stlTwoVectorDivide(STLPNT3D p1,double l1);//向量缩短p1/l1
	//20170825 ADD DAT文件处理
	void stlDealInputFile();
	void stlReadFile(char *file);
	void stlReadSTLBinFile(char *file);
	void stlReadStlFile(char *file);
	void stlRead4Bytes(FILE *stlfile, char *c);
	void stlReadDatFile(char *file);
	void    GetInformationFromPath();//从铺放路径获取信息			主要针对TXT文件
	POList	stlPOLHeadAlloc();//截断前路径
    FList stlGetFacetFromNum(int N);
	//void GetNormaVectorOnVertex(VList p) ;
	double stlDistanceTwoPoints(STLPNT3D p1, STLPNT3D p2) ;
	double  stlDistanceOneVector(STLPNT3D p1) ;
	
	STLPNT3D stlDistanceVectorTwoPoint(STLPNT3D p1, STLPNT3D p2);
	STLPNT3D stlTwoVectorProduct(STLPNT3D v1, STLPNT3D v2);
	STLPNT3D stlOPPNormalVector(STLPNT3D v) ;
	STLPNT3D CreateMTIPoint();
	STLPNT3D CreateMTIPoint(double ix,double iy,double iz);//从xyz创点
	STLPNT3D CreateMTIPoint(double p1[]);//从数组创点
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
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */


/* 链栈结构 */
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