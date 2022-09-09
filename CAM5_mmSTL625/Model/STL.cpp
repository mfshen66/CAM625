#include "StdAfx.h"
#include "STL.h"
#include <vector>

using namespace std;

//==============================================================
/*	1997/4/22 nt
 *	在2D平面上判断原点是否在一个三角形内
 *	return IDIN: in ; IDOUT: not in; IDDEGE, degenerate
 */
int mathChkOriInTri2D(double p1[2],
					  double p2[2],
					  double p3[2],
					  double tol)
{
	int ks[3], i = 0 ;
	double xs[6] ; 

	if( (p1[0] >  tol && p2[0] >  tol && p3[0] >  tol) ||
		(p1[0] < -tol && p2[0] < -tol && p3[0] < -tol) ||
		(p1[1] >  tol && p2[1] >  tol && p3[1] >  tol) ||
		(p1[1] < -tol && p2[1] < -tol && p3[1] < -tol) )
		return IDOUT ;

	ks[0] = fabs(p1[1]) < tol ? 0 : p1[1] > 0.0 ? 1 : -1 ;
	ks[1] = fabs(p2[1]) < tol ? 0 : p2[1] > 0.0 ? 1 : -1 ;
	ks[2] = fabs(p3[1]) < tol ? 0 : p3[1] > 0.0 ? 1 : -1 ;
	if( ks[0] == 0 ) xs[i++] = p1[0] ;
	if( ks[1] == 0 ) xs[i++] = p2[0] ;
	if( ks[2] == 0 ) xs[i++] = p3[0] ;
	if( i >= 3 )
		return IDDEGE ;
	if( ks[0] * ks[1] < 0 )
		xs[i++] = p1[0]+p1[1]*(p2[0]-p1[0])/(p1[1]-p2[1]) ;
	if( ks[1] * ks[2] < 0 )
		xs[i++] = p2[0]+p2[1]*(p3[0]-p2[0])/(p2[1]-p3[1]) ;
	if( ks[2] * ks[0] < 0 )
		xs[i++] = p3[0]+p3[1]*(p1[0]-p3[0])/(p3[1]-p1[1]) ;
	
	if( i == 2 )
	{
		if( xs[0]*xs[1] < 0.0 ||
			fabs(xs[0]) < tol ||
			fabs(xs[1]) < tol )
			return IDIN ;
	}

	return IDOUT ;
}

/*	1997/5/5 nt
 *	计算一个点相对于2D三角形的重心坐标
 */
int mathCalTri2DGCP(PNT2D p1,
					PNT2D p2,
					PNT2D p3,
					PNT2D p,
					PNT3D gc)
{
	double a11, a12, a21, a22, delta ;

	a11 = p1[0]-p3[0] ;
	a12 = p2[0]-p3[0] ;
	a21 = p1[1]-p3[1] ;
	a22 = p2[1]-p3[1] ;
	if( fabs(delta = a11*a22-a12*a21) < 1e-20 )
		return ERUNSUC ;
	gc[0] = ((p3[1]-p[1])*a12-(p3[0]-p[0])*a22)/delta ;
	gc[1] = ((p3[0]-p[0])*a21-(p3[1]-p[1])*a11)/delta ;
	gc[2] = 1.0-gc[0]-gc[1] ;

	return ERSUCSS ;
}

/*	2016/8 nt
 *  将p投影到三角形上，再按二维情况计算重心坐标
 */
int mathCalTriGCPX(PNT3D p1, PNT3D p2, PNT3D p3, VEC3D normal, PNT3D p, PNT3D gc)
{
	PNT2D q1, q2, q3, q ;
	PNT3D O ;
	VEC3D v, X, Y ;

	O[0] = (p1[0] + p2[0] + p3[0]) / 3;
	O[1] = (p1[1] + p2[1] + p3[1]) / 3;
	O[2] = (p1[2] + p2[2] + p3[2]) / 3;
	mathGetXYFromZ(normal, X, Y);

	mathGetVec(O, p1, v);
	q1[0] = mathOProduct(X, v); // to local coordinate frame lf
	q1[1] = mathOProduct(Y, v);

	mathGetVec(O, p2, v);
	q2[0] = mathOProduct(X, v); // to local coordinate frame lf
	q2[1] = mathOProduct(Y, v);

	mathGetVec(O, p3, v);
	q3[0] = mathOProduct(X, v); // to local coordinate frame lf
	q3[1] = mathOProduct(Y, v);

	mathGetVec(O, p, v);
	q[0] = mathOProduct(X, v); // to local coordinate frame lf
	q[1] = mathOProduct(Y, v);

	mathCalTri2DGCP(q1, q2, q3, q, gc);

	return ERSUCSS;
}

/*  1997/2/8 nt
 *	计算点与线段的最近距离和与该点最近的线段上点的参数,参数在0.0,1.0之间
 */
double mathGetPntSegmNDT(PNT3D p, PNT3D begin, PNT3D end, double* pt)
{
    VEC3D v1, v2 ;
    double A, B, C ;

    *pt = 0.0 ;
    v1[0] = end[0]-begin[0] ;
	v1[1] = end[1]-begin[1] ;
	v1[2] = end[2]-begin[2] ;
    v2[0] = begin[0]-p[0] ;
	v2[1] = begin[1]-p[1] ; 
	v2[2] = begin[2]-p[2] ;
    A = v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2] ;
    B = v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2] ;
    C = v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2] ;
    if( A > 1e-20 )
    {
        pt[0] = - B/A ;
        if( pt[0] > 1.0 )
        {
			C += (A+2.0*B) ; 
			pt[0] = 1.0 ; 
		}
        else
        if( pt[0] > 0.0 )
			C += B*pt[0] ;
        else
            pt[0] = 0.0 ;
    }

    return sqrt(C) ;
}

// 线段：from begin to end
// *perp = 1 : 最近点与p的连线垂直与线段; *perp = 0, 表示不垂直
// 是否垂直的判断依据：垂足是否在线段上，容差为tol
double mathGetPntSegmNDTPerp(PNT3D p, PNT3D begin, PNT3D end, double tol, double* pt, int* perp)
{
    VEC3D v1, v2 ;
    double A, B, C ;

    *pt = 0. ;
	*perp = 1 ;
    v1[0] = end[0]-begin[0] ;
	v1[1] = end[1]-begin[1] ;
	v1[2] = end[2]-begin[2] ;
    v2[0] = begin[0]-p[0] ;
	v2[1] = begin[1]-p[1] ; 
	v2[2] = begin[2]-p[2] ;
    A = v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2] ;
    B = v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2] ;
    C = v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2] ;
    if( A > 1e-20 )
    {
        pt[0] = - B/A ;
        if( pt[0] > 1. )
        {
			C += (A+2.*B) ;
			if( (pt[0]-1.)*sqrt(A) > tol )
				*perp = 0 ;
			pt[0] = 1.0 ;
		}
        else
        if( pt[0] >= 0. )
			C += B*pt[0] ;
        else // pt[0] < 0.
		{
			if( -pt[0]*sqrt(A) > tol )
				*perp = 0 ;
            pt[0] = 0. ;
		}
    }

    return sqrt(C) ;
}

int mathChkPntSegmX(PNT3D p, PNT3D begin, PNT3D end, double tol)
{
    VEC3D v1, v2 ;
    double A, B, C, t ;

    if( mathMIN(begin[0], end[0]) > p[0] + tol || //chk box intersection
        mathMAX(begin[0], end[0]) + tol < p[0] ||
        mathMIN(begin[1], end[1]) > p[1] + tol ||
        mathMAX(begin[1], end[1]) + tol < p[1] ||
        mathMIN(begin[2], end[2]) > p[2] + tol ||
        mathMAX(begin[2], end[2]) + tol < p[2] )
        return IDOUT ;

    v1[0] = end[0]-begin[0] ;
	v1[1] = end[1]-begin[1] ;
	v1[2] = end[2]-begin[2] ;
    v2[0] = begin[0]-p[0] ;
	v2[1] = begin[1]-p[1] ;
	v2[2] = begin[2]-p[2] ;
    A = v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2] ;
    B = v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2] ;
    C = v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2] ;
    if( A > 1e-20 )
    {
        t = -B/A ;
        if( t > 1.0 )
			C += (A+2.0*B) ;
        else
        if( t > 0.0 )
			C += B*t ;
    }

	C = sqrt(fabs(C)) ;
    if( C < tol )
		return IDIN ;
	else
		return IDOUT ;
}

int mathGetTriNormal(PNT3D p1, PNT3D p2, PNT3D p3, VEC3D normal)
{
    int k ;
    VEC3D v1, v2 ;

    for( k = 0 ; k < 3 ; k++ )
    {
        v1[k] = p2[k]-p1[k] ;
        v2[k] = p3[k]-p2[k] ;
    }
    mathVProduct(v1, v2, normal) ;
    if( mathUniVec(normal, 1e-50) != ERSUCSS )
        return ERUNSUC ;

    return ERSUCSS ;
}
//==============================================================
Pog::Pog(int Type, void* Vef, double P[3])
{
	type = Type ;
	vef = Vef ;
	memcpy(p, P, sizeof(double[3])) ;
}

Pog::~Pog()
{
}
//==============================================================
Pl::Pl()
{
	arcLen = 0. ;
}

Pl::~Pl()
{
	int i, n = pogs.GetSize() ;

	for( i = 0 ; i < n ; i++ )
		delete pogs[i] ;
	pogs.RemoveAll() ;

	return ;
}

int Pl::CalArcLen()
{
	int i, n = pogs.GetSize() ;

	if( n < 2 )
		return 0 ; // error
	arcLen = 0. ;

	for( i = 1 ; i < n ; i++ )
		arcLen += mathDist(((POG*)pogs[i-1])->p, ((POG*)pogs[i])->p) ;
	
	return 1 ;
}

FList GetFaceOfTwoEdge(EList e1, EList e2)
{
	FRelated r1, r2 ;

	for( r1 = e1->FaceUsed ; r1 ; r1 = r1->FNext )
	{
		for( r2 = e2->FaceUsed ; r2 ; r2 = r2->FNext )
			if( r1->Face == r2->Face )
				return r1->Face ;
	}

	return NULL ;
}

int Pl::Opt(double tol, double eps)
{
	int i, n = pogs.GetSize(), dL ;
	double* A, *B, v[3], d, *p1, *p2, q1[3], q2[3], h1, h2, h, q[3], oldAL ;
	POG* pog ;
	EList e ;

	CalArcLen() ;
	for( dL = 0 ; dL < 1000 ; dL++ )
	{
		oldAL = arcLen ;
		for( i = 1 ; i < n-1 ; i++ ) // for inner node
		{
			pog = (POG*)pogs[i] ;
			if( ((POG*)pogs[i-1])->type == 1 && // on edge
				((POG*)pogs[i+1])->type == 1 && // on edge
				GetFaceOfTwoEdge((EList)(((POG*)pogs[i-1])->vef), 
								 (EList)(((POG*)pogs[i+1])->vef)) )
			{
				pogs.RemoveAt(i) ;
				delete pog ;
				n-- ;
				i-- ;
			}
			else
			if( pog->type == 1 )
			{
				e = (EList)pog->vef ;
				A = &e->VertexUsed[0]->Coord.x ;
				B = &e->VertexUsed[1]->Coord.x ;
				mathGetVec(A, B, v) ; // v = B-A
				d = mathVecLen(v) ;
				if( d > tol )
				{
					v[0] /= d ;
					v[1] /= d ;
					v[2] /= d ;
					p1 = ((POG*)pogs[i-1])->p ;
					p2 = ((POG*)pogs[i+1])->p ;
					mathPrjPntLin(p1, A, v, q1) ;
					mathPrjPntLin(p2, A, v, q2) ;
					h1 = mathDist(p1, q1) ;
					h2 = mathDist(p2, q2) ;
					if( (h = h1+h2) < 1e-10 )
						mathMidPnt(q1, q2, q) ;
					else
						mathMixPnt(q1, q2, h2/h, h1/h, q) ;
					h = (q[0]-A[0])*v[0]+(q[1]-A[1])*v[1]+(q[2]-A[2])*v[2] ;
					if( h < tol ) // A
					{
						memcpy(pog->p, A, sizeof(double[3])) ;
						pog->vef = e->VertexUsed[0] ;
						pog->type = 0 ;
					}
					else
					if( h > d-tol ) // B
					{
						memcpy(pog->p, B, sizeof(double[3])) ;
						pog->vef = e->VertexUsed[1] ;
						pog->type = 0 ;
					}
					else // on AB
						memcpy(pog->p, q, sizeof(double[3])) ;
				}
			}
		}
		CalArcLen() ;
		if( fabs(arcLen-oldAL) < eps )
			break ;
	}

	return 1 ;
}

void Pl::ReplaceBegin(double p[3])
{
	int n = pogs.GetSize() ;

	if( n < 2 )
		return ;
	POG* pog = (POG*)pogs[0] ;
	if( pog )
		memcpy(pog->p, p, sizeof(double[3])) ;

	return ;
}

void Pl::ReplaceEnd(double p[3])
{
	int n = pogs.GetSize() ;

	if( n < 2 )
		return ;
	POG* pog = (POG*)pogs[n-1] ;
	if( pog )
		memcpy(pog->p, p, sizeof(double[3])) ;

	return ;
}
//==============================================================
Gdinfo::Gdinfo()
{
	ns[0] = 0 ;
	ns[1] = 0 ;
	pps[0] = NULL ;
	pps[1] = NULL ;
	min = 1e50 ;
	max = -1e50 ;
	i = 0 ;
	I = 0 ;
}

Gdinfo::~Gdinfo()
{
	delete []pps[0] ;
	delete []pps[1] ;
}
//==============================================================
void MTIPathOriginList::Draw()
{
	int i, n = 0 ;

	for( i = 1 ; i <= DNum ; i++ )
		n += (ENum[i]-SNum[i]+1) ;

	glBegin(GL_LINE_STRIP) ;
	for( i = 1 ; i <= n ; i++ )
		glVertex3dv(&PTrail[i].x) ;
	glEnd() ;

	return ;
}

// nt add 2022/7/10
POList MTIPathOriginList::Copy()
{
	int i, n = 0 ;
	POList copy ;

	copy = (POList)malloc(sizeof(struct MTIPathOriginList)) ;
	if( copy == NULL )
		return NULL ;
	for( i = 1 ; i <= DNum ; i++ )
		n += (ENum[i]-SNum[i]+1) ;
	copy->PTrail = (STLPNT3D*)malloc(sizeof(STLPNT3D)*(n+1)) ;
	memcpy(copy->PTrail, PTrail, sizeof(STLPNT3D)*(n+1)) ;
	copy->PNTrail = (STLPNT3D*)malloc(sizeof(STLPNT3D)*(n+1)) ;
	memcpy(copy->PNTrail, PNTrail, sizeof(STLPNT3D)*(n+1)) ;
	copy->FTrail = (FList*)malloc(sizeof(FList)*(n+1)) ;
	memcpy(copy->FTrail, FTrail, sizeof(FList)*(n+1)) ;
	copy->TNum = TNum ;
	copy->DNum = DNum ;
	copy->SNum = (int*)malloc(sizeof(int)*(DNum+1)) ;
	memcpy(copy->SNum, SNum, sizeof(int)*(DNum+1)) ;
	copy->ENum = (int*)malloc(sizeof(int)*(DNum+1)) ;
	memcpy(copy->ENum, ENum, sizeof(int)*(DNum+1)) ;
	copy->PONext = NULL ;

	return copy ;
}

// nt add 2022/7/10
POList MTIPathOriginList::DirectOffset(double d)
{
	int i, n = 0 ;
	POList offset ;

	offset = Copy() ;
	for( i = 1 ; i <= DNum ; i++ )
		n += (ENum[i]-SNum[i]+1) ;
	for( i = 1 ; i <= n ; i++ )
	{
		mathEvalLin(&PTrail[i].x, &PNTrail[i].x, d, &offset->PTrail[i].x) ;
	}

	return offset ;
}

// 非柔性滚子工作时的测地距离
// smf add 2022/7/27
POList MTIPathOriginList::GeodesicOffsetNonFlexible(double iDistance, int iDir, double * oChordalHeight)
{
	int i, n = 0;
	POList offset;
	double distance_square = iDistance * iDistance; // 用距离的平方进行比较和计算

	offset = Copy(); // 先复制一条当前曲线

	for (i = 1; i <= DNum; i++)
		n += (ENum[i] - SNum[i] + 1); // 计算需要等距的点数？？？
	for (i = 1; i <= n; i++)
	{
		// 测地方向
		STLVECTOR vec_tangent, vec_tangent1, vec_tangent2 ;

		if (i == 1)
			vec_tangent = PTrail[i + 1] - PTrail[i];
		else if (i == n)
			vec_tangent = PTrail[i] - PTrail[i - 1];
		else
		{
			vec_tangent1 = PTrail[i] - PTrail[i - 1];
			vectorNormalize(vec_tangent1);
			vec_tangent2 = PTrail[i + 1] - PTrail[i];
			vectorNormalize(vec_tangent2);
			vec_tangent = 0.5 * (vec_tangent1 + vec_tangent2);
		}
		vec_tangent = vectorNormalize(vec_tangent);
		// 关键点法矢方向
		STLVECTOR vec_normal = PNTrail[i];
		STLVECTOR vec_offset;

		vec_offset = vec_tangent ^ vec_normal;
		vec_offset = vectorNormalize(vec_offset);
		if (iDir == -1)
			vec_offset = -vec_offset;

		offset->PTrail[i] = PTrail[i] + iDistance * vec_offset;

		// 计算弓高
		// 平面与三角形求交
		
		//double threshold_height = 100;


	}

	return offset;
}


// 柔性滚子工作时的测地距离
// smf add 2022/9/25
POList MTIPathOriginList::GeodesicOffsetFlexible(double d, int dir)
{
	int i, n = 0;
	POList offset;
	double distance_square = d * d; // 用距离的平方进行比较和计算

	offset = Copy(); // 先复制一条当前曲线

	for (i = 1; i <= DNum; i++)
		n += (ENum[i] - SNum[i] + 1); // 计算需要等距的点数？？？
	for (i = 1; i < n; i++)
	{
		// 测地方向
		STLVECTOR v;
		v.x = PTrail[i + 1].x - PTrail[i].x;
		v.y = PTrail[i + 1].y - PTrail[i].y;
		v.z = PTrail[i + 1].z - PTrail[i].z;
		// 关键点法矢方向
		STLVECTOR norm = PNTrail[i];
		// 以测地方向为法向量且过该点的平面与当前三角片的邻接三角片求交，累计距离达到d。可能遇到模型边界。
		double sumSquareDistance = 0.;
		while (sumSquareDistance < distance_square)
		{
			double delta = 0.;
			sumSquareDistance += delta;
		}
	}

	return offset;
}

//==============================================================
VList VertexList::SchMinVert(double p[3], double& min)
{
	VList v, V = NULL ;
	FList f ;
	FRelated r ;

	for( r = FaceUsed ; r ; r = r->FNext )
	{
		f = r->Face ;
		if( f )
		{
			v = f->SchMinVert(p, min) ;
			if( v )
				V = v ;
		}
	}

	return V ;
}
//==============================================================
FaceList::FaceList()
{
}

FaceList::~FaceList()
{
}

int FaceList::GetType()
{
	return 60 ;
}

int FaceList::GetNumOfCV(FList f)
{
	int i, j, n = 0 ;

	for( i = 0 ; i < 3 ; i++ )
	{
		for( j = 0 ; j < 3 ; j++ )
		{
			if( VertexUsed[i] == f->VertexUsed[j] )
			{
				n++ ;
				break ;
			}
		}
	}

	return n ;
}

int FaceList::IsAdj(FList f)
{
	return GetNumOfCV(f) == 2 ? 1 : 0 ;
}

void FaceList::GetVertPos(int k, double p[3])
{
	memcpy(p, &VertexUsed[k%3]->Coord.x, sizeof(double[3])) ;

	return ;
}

void FaceList::GetPos(double gc[3], double p[3])
{
	p[0] = gc[0]*VertexUsed[0]->Coord.x+
		   gc[1]*VertexUsed[1]->Coord.x+
		   gc[2]*VertexUsed[2]->Coord.x ;
	p[1] = gc[0]*VertexUsed[0]->Coord.y+
		   gc[1]*VertexUsed[1]->Coord.y+
		   gc[2]*VertexUsed[2]->Coord.y ;
	p[2] = gc[0]*VertexUsed[0]->Coord.z+
		   gc[1]*VertexUsed[1]->Coord.z+
		   gc[2]*VertexUsed[2]->Coord.z ;

	return ;
}

FList FaceList::GetAdj(int i, int j)
{
	int k ;
	FRelated r ;
	EList e ;

	for( k = 0 ; k < 3 ; k++ )
	{
		e = EdgeUsed[k] ;
		if( (e->VertexUsed[0] == VertexUsed[i] &&
			 e->VertexUsed[1] == VertexUsed[j]) ||
			(e->VertexUsed[0] == VertexUsed[j] &&
			 e->VertexUsed[1] == VertexUsed[i]) )
		{
			for( r = e->FaceUsed ; r ; r = r->FNext )
			{
				if( r->Face != this )
					return r->Face ;
			}
		}
	}

	return NULL ;
}

EList FaceList::GetEdge(int i, int j)
{
	int k ;
	EList e ;

	for( k = 0 ; k < 3 ; k++ )
	{
		e = EdgeUsed[k] ;
		if( (e->VertexUsed[0] == VertexUsed[i%3] &&
			 e->VertexUsed[1] == VertexUsed[j%3]) ||
			(e->VertexUsed[0] == VertexUsed[j%3] &&
			 e->VertexUsed[1] == VertexUsed[i%3]) )
			return e ;
	}

	return NULL ; // error
}

VList FaceList::SchMinVert(double p[3], double& min)
{
	int k, I = -1 ;
	double d ;

	for( k = 0 ; k < 3 ; k++ )
	{
		if( VertexUsed[k]->flag == 0 ) // unused only
		{
			d = mathDist(&VertexUsed[k]->Coord.x, p) ;
			if( min > d )
			{
				min = d ;
				I = k ;
			}
		}
	}

	return I<0?NULL:VertexUsed[I] ;
}

void FaceList::GetBarycenter(double center[3])
{
	center[0] = (VertexUsed[0]->Coord.x+VertexUsed[1]->Coord.x+VertexUsed[2]->Coord.x)/3 ;
	center[1] = (VertexUsed[0]->Coord.y+VertexUsed[1]->Coord.y+VertexUsed[2]->Coord.y)/3 ;
	center[2] = (VertexUsed[0]->Coord.z+VertexUsed[1]->Coord.z+VertexUsed[2]->Coord.z)/3 ;

	return ;
}

void FaceList::Prj(double p[3], double prj_p[3])
{
	int k ;
	double gc[3], s = 0. ;

	mathCalTriGCPX(&VertexUsed[0]->Coord.x, 
				   &VertexUsed[1]->Coord.x,
				   &VertexUsed[2]->Coord.x,
				   &NormalVector.x,
				   p,
				   gc) ;
	for( k = 0 ; k < 3 ; k++ )
	{
		if( gc[k] < 0. )
			gc[k] = 0. ;
		s += gc[k] ;
	}
	if( s < 1e-50 )
	{
		memcpy(prj_p, p, sizeof(double[3])) ;
		return ; // error
	}
	for( k = 0 ; k < 3 ; k++ )
		gc[k] /= s ;
	
	prj_p[0] = gc[0]*VertexUsed[0]->Coord.x+
			   gc[1]*VertexUsed[1]->Coord.x+
			   gc[2]*VertexUsed[2]->Coord.x ;
	prj_p[1] = gc[0]*VertexUsed[0]->Coord.y+
			   gc[1]*VertexUsed[1]->Coord.y+
			   gc[2]*VertexUsed[2]->Coord.y ;
	prj_p[2] = gc[0]*VertexUsed[0]->Coord.z+
			   gc[1]*VertexUsed[1]->Coord.z+
			   gc[2]*VertexUsed[2]->Coord.z ;

	return ;
}

// 输入：
//		pivot:平面上一点
//		normal:平面法矢
//		p:三角形内或其边上一点
//		dir:单位方向，指向测地线的终点
//		tol:点重合容差
// 输出：
//		q是三角形边上一点或三角形顶点
//		i==j表示q就是顶点i
//		i!=j表示q在边上，该边的顶点为i和j
// 功能:
//		平面切三角形得到三角形边上一点q，保证q-p与dir同向
// return 0=not found q, 1=found q
int FaceList::PlaneCut(double pivot[3], 
					   double normal[3], 
					   double p[3], 
					   double dir[3], 
					   double tol, 
					   double q[3], 
					   int& i, 
					   int& j)
{
	int k, m ;
	double* vs[3], hs[3], h, d1, d2, ps[3][3], Q[3], max = 0. ; // tol

	i = j = -1 ;

	for( k = 0 ; k < 3 ; k++ )
	{
		vs[k] = &VertexUsed[k]->Coord.x ;
		hs[k] = mathDistPntPlnSide(vs[k], pivot, normal) ; // original use p
	}
	
	for( k = 0 ; k < 3 ; k++ )
	{
		m = k<2?k+1:0 ;
		if( fabs(hs[k]) < tol &&
			fabs(hs[j]) < tol )
		{
			d1 = mathOProduct2(dir, p, vs[k]) ;
			d2 = mathOProduct2(dir, p, vs[m]) ;
			if( d1 >= d2 && d1 > 0. ) // nt modify 2022/7/8 old tol
			{
				memcpy(q, vs[k], sizeof(double[3])) ;
				i = j = k ;
				return 1 ;
			}
			if( d2 >= d1 && d2 > 0. ) // nt modify 2022/7/8 old tol
			{
				memcpy(q, vs[m], sizeof(double[3])) ;
				i = j = m ;
				return 1 ;
			}
			return 0 ;
		}
	}

	for( k = 0 ; k < 3 ; k++ )
		mathPrjPntPln(vs[k], pivot, normal, ps[k]) ; // original use p
	for( k = 0 ; k < 3 ; k++ )
	{
		m = k<2?k+1:0 ;
		if( hs[k]*hs[m] < 0. )
		{
			h = hs[k]-hs[m] ;
			mathMixPnt(ps[k], ps[m], -hs[m]/h, hs[k]/h, Q) ;
			h = mathOProduct2(dir, p, Q) ;
			if( max < h )
			{
				memcpy(q, Q, sizeof(double[3])) ;
				i = k ;
				j = m ;
				max = h ;
			}
		}
	}

	for( k = 0 ; k < 3 ; k++ )
	{
		if( fabs(hs[k]) < tol )
		{
			h = mathOProduct2(dir, p, vs[k]) ;
			if( max < h )
			{
				memcpy(q, vs[k], sizeof(double[3])) ;
				i = j = k ;
				return 1 ;
			}
		}
	}

	return i<0?0:1 ;
}

// 返回：
//		-1=退化
//		0=not in triangle
//		1=in interior
//		2=on edge
//		3=coincident with vertex
int FaceList::IsIn(double p[3], double tol)
{
	double *A, *B, *C, q[3], d, AB[3], AC[3], v[3], center[3], s, t ;

	GetBarycenter(center) ;
	mathPrjPntPln(p, center, &NormalVector.x, q) ;
	d = mathDist(p, q) ;
	if( d > tol )
		return 0 ;

	A = &VertexUsed[0]->Coord.x ;
	B = &VertexUsed[1]->Coord.x ;
	C = &VertexUsed[2]->Coord.x ;
	if( mathDist(p, A) < tol || // p is coincident with one vertex
		mathDist(p, B) < tol ||
		mathDist(p, C) < tol )
		return 3 ;

	if( mathChkPntSegmX(p, A, B, tol) == IDIN || // p is on one edge
		mathChkPntSegmX(p, B, C, tol) == IDIN ||
		mathChkPntSegmX(p, C, A, tol) == IDIN )
		return 2 ;

	mathGetVec(A, B, AB) ;
	mathGetVec(A, C, AC) ;
	mathVProduct(AB, &NormalVector.x, v) ; // v perpendicular to AB
	d = mathOProduct(AC, v) ;
	if( fabs(d) < 1e-50 )
		return -1 ; // degenerate
	t = mathOProduct2(v, A, p)/d ;
	if( t < 0. || t > 1. )
		return 0 ;
	mathVProduct(AC, &NormalVector.x, v) ; // v perpendicular to AC
	d = mathOProduct(AB, v) ;
	if( fabs(d) < 1e-50 )
		return -1 ; // degenerate
	s = mathOProduct2(v, A, p)/d ;
	if( s < 0. || s > 1. )
		return 0 ;
	if( s+t < 1. )
		return 1 ;
	else
		return 0 ;
}

int FaceList::IsIn2(double p[3], double tol, double prj_p[3])
{
	double center[3], q[3] ;

	GetBarycenter(center) ;
	mathPrjPntPln(p, center, &NormalVector.x, q) ;
	if( prj_p )
		memcpy(prj_p, q, sizeof(double[3])) ;
	
	return IsIn(q, tol) ;
}

int FaceList::Draw(void* pVI, int drawMode)
{
	return 1 ;
}

int FaceList::Draw2(void* pVI, int drawMode)
{
	MATERIAL material ;
	if( drawMode == dmNormal )
		materialGet2(&material, 9) ;
	else
	if( drawMode == dmPrompt )
		materialGet2(&material, 1) ;
	else
	if( drawMode == dmSelect )
		materialGet2(&material, 41) ;
	materialSet(&material) ;

	viLighting(pVI, 1) ;
	viAddDefaultLight(pVI) ;	
	glBegin(GL_TRIANGLES) ;
		glNormal3dv(&NormalVector.x) ;
		glVertex3dv(&VertexUsed[0]->Coord.x) ;
		glNormal3dv(&NormalVector.x) ;
		glVertex3dv(&VertexUsed[1]->Coord.x) ;
		glNormal3dv(&NormalVector.x) ;
		glVertex3dv(&VertexUsed[2]->Coord.x) ;
	glEnd() ;
	viLighting(pVI, 0) ;
	
	return 1 ;
}
//==============================================================
GridModel::GridModel()
{
	VRoot = NULL ;
	EHead = NULL ;
	FHead = NULL ;
	VerNum = 0 ;
	EdgeNum = 0 ;
	FaceNum = 0 ;
	POLHead = NULL ;//排序后截断前路径//不可分段
	stl_xmin = 1e100 ;
	stl_ymin = 1e100 ;
	stl_zmin = 1e100 ;
	stl_xmax = -1e100 ;
	stl_ymax = -1e100 ;
	stl_zmax = -1e100 ;
	TraverseNum = 0 ;
	MeshResulttag  = 0 ;
	// nt add 2022/6/17
	nPolyline = 0 ;
}

void GridModel::InitFlagAll()
{
	EList e ;

	for( e = EHead ; e ; e = e->ENext )
	{
		if( e->VertexUsed[0] )
			e->VertexUsed[0]->flag = 0 ;
		if( e->VertexUsed[1] )
			e->VertexUsed[1]->flag = 0 ;
	}

	return ;
}

void GridModel::Draw(void* pVI, int drawMode)
{
	MATERIAL material ;
	if( drawMode == dmNormal )
		materialGet2(&material, 9) ;
	else
	if( drawMode == dmPrompt )
		materialGet2(&material, 1) ;
	else
	if( drawMode == dmSelect )
		materialGet2(&material, 41) ;
	materialSet(&material) ;

	FList f ;
	glBegin(GL_TRIANGLES) ;
	for( f = FHead ; f ; f = f->FNext )
	{
		glNormal3dv(&f->NormalVector.x) ;
		glVertex3dv(&f->VertexUsed[0]->Coord.x) ;
		glNormal3dv(&f->NormalVector.x) ;
		glVertex3dv(&f->VertexUsed[1]->Coord.x) ;
		glNormal3dv(&f->NormalVector.x) ;
		glVertex3dv(&f->VertexUsed[2]->Coord.x) ;
	}
	glEnd() ;

	int i, j, n ;
	POG* pog ;
	glLineWidth(2.f) ;
	for( i = 0 ; i < nPolyline ; i++ )
	{
		n = polylines[i]->pogs.GetSize() ;
		glBegin(GL_LINE_STRIP) ;
			for( j = 0 ; j < n ; j++ )
			{
				pog = (POG*)polylines[i]->pogs[j] ;
				glVertex3dv(pog->p) ;
			}
		glEnd() ;
	}

	for( i = 1 ; i <= TrailNumDum ; i++ )
	{
		POLHead[i]->Draw() ;
	}

	return ;
}

FList GridModel::Pick(PNT3D pos, 
					  VEC3D dir,
					  double r, 
					  PNT3D p, // 输入输出参数
					  double* pz, // 输入输出参数
					  PNT3D gc)
{
	int k ;
	double z ;
	PNT2D ps[3], ori={0.,0.} ;
	PNT3D q ;
	VEC3D X, Y, v ;
	BOX3D box ;
	FList f, picked = NULL ;

	box.min[0] = stl_xmin ;
	box.min[1] = stl_ymin ;
	box.min[2] = stl_zmin ;
	box.max[0] = stl_xmax ;
	box.max[1] = stl_ymax ;
	box.max[2] = stl_zmax ;


	if( mathChkBoxLinInt(&box, pos, dir, r) == IDINT )
	{
		mathGetXYFromZ(dir, X, Y) ;
		for( f = FHead ; f ; f = f->FNext )
		{
			for( k = 0 ; k < 3 ; k++ )
			{
				v[0] = f->VertexUsed[k]->Coord.x-pos[0] ;
				v[1] = f->VertexUsed[k]->Coord.y-pos[1] ;
				v[2] = f->VertexUsed[k]->Coord.z-pos[2] ;
				ps[k][0] = v[0]*X[0]+v[1]*X[1]+v[2]*X[2] ;
				ps[k][1] = v[0]*Y[0]+v[1]*Y[1]+v[2]*Y[2] ;
			}
			if( mathChkOriInTri2D(ps[0], ps[1], ps[2], r) == IDIN )
			{
				mathCalTri2DGCP(ps[0], ps[1], ps[2], ori, gc) ;
				q[0] = f->VertexUsed[0]->Coord.x*gc[0]+
					   f->VertexUsed[1]->Coord.x*gc[1]+
					   f->VertexUsed[2]->Coord.x*gc[2] ;
				q[1] = f->VertexUsed[0]->Coord.y*gc[0]+
					   f->VertexUsed[1]->Coord.y*gc[1]+
					   f->VertexUsed[2]->Coord.y*gc[2] ;
				q[2] = f->VertexUsed[0]->Coord.z*gc[0]+
					   f->VertexUsed[1]->Coord.z*gc[1]+
					   f->VertexUsed[2]->Coord.z*gc[2] ;
				v[0] = q[0]-pos[0] ;
				v[1] = q[1]-pos[1] ;
				v[2] = q[2]-pos[2] ;
				z = v[0]*dir[0]+v[1]*dir[1]+v[2]*dir[2] ;
				if( *pz > z )
				{
					memcpy(p, q, sizeof(PNT3D)) ;
					picked = f ;
					*pz = z ;
				}
			}
		}
	}

	return picked ;
}

int GridModel::CalGeodesicLineOne(FList f, 
							      double p1[3], 
							      double p2[3], 
							      PL** polyline)
{
	*polyline = new Pl() ;
	(*polyline)->arcLen = mathDist(p1, p2) ;
	(*polyline)->pogs.Add(new Pog(2, f, p1)) ;
	(*polyline)->pogs.Add(new Pog(2, f, p2)) ;

	return 1 ; // success
}

int GridModel::CalGeodesicLineAdj(FList f1, 
							      double p1[3], 
							      FList f2, 
							      double p2[3], 
							      double tol, 
							      PL** polyline)
{
	int i, j, n = 0, is[2], type = 0 ;
	double A[3], B[3], v[3], d, q[3], q1[3], q2[3], h1, h2, h ;
	void* vef = NULL ;

	for( i = 0 ; i < 3 ; i++ )
	{
		for( j = 0 ; j < 3 ; j++ )
		{
			if( f1->VertexUsed[i] == f2->VertexUsed[j] )
			{
				is[n] = i ;
				n++ ;
				break ;
			}
		}
		if( n == 2 )
			break ;
	}
	if( n != 2 )
		return 0 ; // error

	f1->GetVertPos(is[0], A) ;
	f1->GetVertPos(is[1], B) ;
	mathGetVec(A, B, v) ; // v = B-A
	d = mathVecLen(v) ;
	if( d < tol )
	{
		vef = f1->VertexUsed[is[0]] ; // A
		mathMidPnt(A, B, q) ;
		type = 2 ;
	}
	else
	{
		v[0] /= d ;
		v[1] /= d ;
		v[2] /= d ;
		mathPrjPntLin(p1, A, v, q1) ;
		mathPrjPntLin(p2, A, v, q2) ;
		h1 = mathDist(p1, q1) ;
		h2 = mathDist(p2, q2) ;
		if( (h = h1+h2) < 1e-10 )
			mathMidPnt(q1, q2, q) ;
		else
			mathMixPnt(q1, q2, h2/h, h1/h, q) ;

		h = (q[0]-A[0])*v[0]+(q[1]-A[1])*v[1]+(q[2]-A[2])*v[2] ;
		if( h > tol )
		{
			if( h > d-tol )
				vef = f1->VertexUsed[is[1]] ; // B
			else // on AB
			{
				vef = f1->GetEdge(is[0], is[1]) ;
				type = 1 ;
			}
		}
		else
			vef = f1->VertexUsed[is[0]] ; // A
	}

	*polyline = new Pl() ;
	(*polyline)->arcLen = mathDist(p1, q)+mathDist(q, p2) ;
	(*polyline)->pogs.Add(new Pog(2, f1, p1)) ;
	(*polyline)->pogs.Add(new Pog(type, vef, q)) ;
	(*polyline)->pogs.Add(new Pog(2, f2, p2)) ;

	return 1 ; // success
}

// nt add 2022/7/9
// 找被射线穿过的邻面
FList FaceList::GetAdjRayPass(double p[3], double dir[3], double tol)
{
	int k, n ;
	double v1[3], v2[3], q[3], d ;
	VList v ;
	EList e ;
	FList F ;
	FRelated r ;

	n = IsIn(p, tol) ;
	if( n == 0 )
	{
		for( k = 0 ; k < 3 ; k++ )
		{
			e = EdgeUsed[k] ;
			for( r = e->FaceUsed ; r ; r = r->FNext )
			{
				F = r->Face ;
				if( F != this )
				{
					F->Prj(p, q) ;
					if( F->IsIn(q, tol) > 0 )
						return F ;
				}
			}
		}
	}
	else
	if( n == 2 ) // p on edge
	{
		for( k = 0 ; k < 3 ; k++ )
		{
			e = EdgeUsed[k] ;
			for( r = e->FaceUsed ; r ; r = r->FNext )
			{
				F = r->Face ;
				if( F != this &&
					F->IsIn(p, tol) > 0 )
					return F ;
			}
		}
	}
	else
	if( n == 3 ) // p on vertex
	{
		for( k = 0 ; k < 3 ; k++ )
		{
			v = VertexUsed[k] ;
			if( mathDist(p, &v->Coord.x) < tol )
			{
				for( r = v->FaceUsed ; r ; r = r->FNext )
				{
					F = r->Face ;
					if( F != this )
					{
						if( F->VertexUsed[0] == v )
						{
							mathGetVec(p, &F->VertexUsed[1]->Coord.x, v1) ;
							mathGetVec(p, &F->VertexUsed[2]->Coord.x, v2) ;
						}
						else
						if( F->VertexUsed[1] == v )
						{
							mathGetVec(p, &F->VertexUsed[0]->Coord.x, v1) ;
							mathGetVec(p, &F->VertexUsed[2]->Coord.x, v2) ;
						}
						else
						{
							mathGetVec(p, &F->VertexUsed[0]->Coord.x, v1) ;
							mathGetVec(p, &F->VertexUsed[1]->Coord.x, v2) ;
						}
						mathVProduct(v1, dir, v1) ;
						mathVProduct(v2, dir, v2) ;
						d = mathOProduct(v1, v2) ;
						if( d <= 0. )
							return F ;
					}
				}
			}
		}
	}
	else
		return this ; // p在三角形内或外(error)

	return NULL ;
}

int GridModel::CalGeodesicLine(FList f1, 
							   double p1[3], 
							   FList f2, 
							   double p2[3], 
							   double tol, 
							   PL** polyline)
{
	int i, j, dL ;
	double p[3], q[3], dir[3], vec[3], pivot[3], normal[3], h1, h2, q1[3], q2[3] ;
	FRelated r ;
	VList v, v1, v2 ;
	EList e ;
	FList f, F, oldf ;

	*polyline = NULL ;
	if( f1 == f2 )
		return CalGeodesicLineOne(f1, p1, p2, polyline) ;
	else
	if( f1->IsAdj(f2) )
		return CalGeodesicLineAdj(f1, p1, f2, p2, tol, polyline) ;

	f1->Prj(p1, q1) ; // nt add 2022/7/9
	f2->Prj(p2, q2) ; // nt add 2022/7/9

	mathMidPnt(&f1->NormalVector.x, &f2->NormalVector.x, vec) ; // 平均法矢
	if( mathGetVecUnit(q1, q2, dir) != ERSUCSS || // direction from p1 to p2
		mathUniVec(vec, 1e-10) != ERSUCSS )
		return 0 ;
	mathVProduct(vec, dir, normal) ;
	if( mathUniVec(normal, 1e-10) != ERSUCSS )
		return 0 ;

	*polyline = new Pl() ;
	(*polyline)->pogs.Add(new Pog(2, f1, p1)) ; // add start point
	
	f = f1 ;
	mathMidPnt(q1, q2, pivot) ;
	memcpy(p, q1, sizeof(double[3])) ;
	// nt add 2022/7/9 当f不适合做初始跟踪时，选择其合适的邻面
	if( f->PlaneCut(pivot, normal, p, dir, tol, q, i, j) != 1 )
		f = f->GetAdjRayPass(p, dir, tol) ;
	if( f == NULL )
		return 0 ;
	// end

	for( dL = 0 ; dL < FaceNum ; dL++ )
	{
		if( f->PlaneCut(pivot, normal, p, dir, tol, q, i, j) != 1 )
			goto ExceExit ;
		if( i != j ) // q on edge
		{
			e = f->GetEdge(i, j) ;
			if( e == NULL )
				goto ExceExit ;
			(*polyline)->pogs.Add(new Pog(1, e, q)) ;
			f = f->GetAdj(i, j) ;
		}
		else // q on vertex
		{
			v = f->VertexUsed[i] ;
			if( v == NULL )
				goto ExceExit ;
			(*polyline)->pogs.Add(new Pog(0, v, q)) ;
			oldf = f ;
			for( r = v->FaceUsed ; r ; r = r->FNext )
			{
				F = r->Face ;
				if( F != oldf )
				{
					if( F->VertexUsed[0] == v )
					{
						v1 = F->VertexUsed[1] ;
						v2 = F->VertexUsed[2] ;
					}
					else
					if( F->VertexUsed[1] == v )
					{
						v1 = F->VertexUsed[0] ;
						v2 = F->VertexUsed[2] ;
					}
					else
					{
						v1 = F->VertexUsed[0] ;
						v2 = F->VertexUsed[1] ;
					}
					h1 = mathDistPntPlnSide(&(v1->Coord.x), pivot, normal) ;
					h2 = mathDistPntPlnSide(&(v2->Coord.x), pivot, normal) ;
					if( h1*h2 <= 0. )
					{
						f = F ;
						break ;
					}
				}
			}
			if( f == oldf ) // not found F, not update f
				goto ExceExit ;
		}
		memcpy(p, q, sizeof(double[3])) ;

		if( f == NULL )
			goto ExceExit ;
		if( f == f2 )
			break ;
	}
	if( dL >= FaceNum )
		goto ExceExit ;
	(*polyline)->pogs.Add(new Pog(2, f2, p2)) ; // add end point
	(*polyline)->Opt(tol, tol) ;

	return 1 ;
ExceExit:
	if( *polyline )
		delete *polyline ;
	*polyline = NULL ;

	return 0 ; // error
}
/*{
	int dL ;
	double min ;
	VList v ;

	*polyline = NULL ;
	if( f1 == f2 )
		return CalGeodesicLineOne(f1, p1, p2, polyline) ;
	else
	if( f1->IsAdj(f2) )
		return CalGeodesicLineAdj(f1, p1, f2, p2, tol, polyline) ;

	InitFlagAll() ;
	*polyline = new Pl() ;
	(*polyline)->pogs.Add(new Pog(2, f1, p1)) ; // add start point

	min = 1e50 ;
	if( (v = f1->SchMinVert(p2, min)) == NULL )
		return 0 ; // error
	for( dL = 0 ; dL < VerNum ; dL++ )
	{
		v->flag = 1 ;
		(*polyline)->pogs.Add(new Pog(0, v, &v->Coord.x)) ;
		if( v == f2->VertexUsed[0] || // end search initial path
			v == f2->VertexUsed[1] ||
			v == f2->VertexUsed[2] )
			break ;

		min = 1e50 ;
		if( (v = v->SchMinVert(p2, min)) == NULL )
			goto ExceExit ;
	}
	if( dL >= VerNum )
		goto ExceExit ;
	(*polyline)->pogs.Add(new Pog(2, f2, p2)) ; // add end point

	return 1 ;
ExceExit:
	if( *polyline )
		delete *polyline ;
	*polyline = NULL ;

	return 0 ; // error
}*/

// p1在f1上，p2在f2上
// ptOnLine在p1,p2的连线上
// 将ptOnLine投影到网格的某个Face上，输出投影点, 返回该Face
FList GridModel::Prj(FList f1, 
					 double p1[3], 
					 FList f2, 
					 double p2[3], 
					 double tol, 
					 double ptOnLine[3],
				     double ptOnFace[3])
{
	int i, j, dL ;
	double p[3], q[3], dir[3], vec[3], pivot[3], normal[3], h1, h2 ;
	FRelated r ;
	VList v, v1, v2 ;
	EList e ;
	FList f, F, oldf ;

	if( f1->IsIn2(ptOnLine, tol, ptOnFace) > 0 )
		return f1 ;
	else
	if( f2->IsIn2(ptOnLine, tol, ptOnFace) > 0 )
		return f2 ;
	
	mathMidPnt(&f1->NormalVector.x, &f2->NormalVector.x, vec) ; // 平均法矢
	if( mathGetVecUnit(p1, p2, dir) != ERSUCSS || // direction from p1 to p2
		mathUniVec(vec, 1e-10) != ERSUCSS )
		return NULL ;
	mathVProduct(vec, dir, normal) ;
	if( mathUniVec(normal, 1e-10) != ERSUCSS )
		return NULL ;
	
	f = f1 ;
	mathMidPnt(p1, p2, pivot) ;
	memcpy(p, p1, sizeof(double[3])) ;
	for( dL = 0 ; dL < FaceNum ; dL++ )
	{
		if( f->PlaneCut(pivot, normal, p, dir, tol, q, i, j) != 1 )
			return NULL ;
		if( i != j ) // q on edge
		{
			e = f->GetEdge(i, j) ;
			if( e == NULL )
				return NULL ;
			f = f->GetAdj(i, j) ;
		}
		else // q on vertex
		{
			v = f->VertexUsed[i] ;
			if( v == NULL )
				return NULL ;
			oldf = f ;
			for( r = v->FaceUsed ; r ; r = r->FNext )
			{
				F = r->Face ;
				if( F != oldf )
				{
					if( F->VertexUsed[0] == v )
					{
						v1 = F->VertexUsed[1] ;
						v2 = F->VertexUsed[2] ;
					}
					else
					if( F->VertexUsed[1] == v )
					{
						v1 = F->VertexUsed[0] ;
						v2 = F->VertexUsed[2] ;
					}
					else
					{
						v1 = F->VertexUsed[0] ;
						v2 = F->VertexUsed[1] ;
					}
					h1 = mathDistPntPlnSide(&(v1->Coord.x), pivot, normal) ;
					h2 = mathDistPntPlnSide(&(v2->Coord.x), pivot, normal) ;
					if( h1*h2 <= 0. )
					{
						f = F ;
						break ;
					}
				}
			}
			if( f == oldf ) // not found F, not update f
				return NULL ;
		}
		memcpy(p, q, sizeof(double[3])) ;

		if( f == NULL )
			return NULL ;
		if( f == f2 )
			break ;
		if( f->IsIn2(ptOnLine, tol, ptOnFace) > 0 )
			return f ;
	}

	return NULL ;
}

int GridModel::CalGDInfo(POList polys[2], double tol, GDINFO** pGDI)
{
	int i, k, n ;
	GDINFO* gdi ;
	PP* pp ;

	*pGDI = NULL ;
	gdi = new GDINFO() ;
	gdi->min = 1e50 ;
	gdi->max = -1e50 ;
	gdi->i = 0 ;
	gdi->I = 0 ;

	for( k = 0 ; k < 2 ; k++ )
	{
		for( n = 0, i = 1 ; i <= polys[k]->DNum ; i++ )
			n += (polys[k]->ENum[i]-polys[k]->SNum[i]+1) ;
		gdi->ns[k] = n ;
		gdi->pps[k] = new PP[n+1] ;
		gdi->pps[k][0].I = -1 ; // set invalid
	
		for( i = 1 ; i <= n ; i++ )
		{
			if( i == 2 && k == 1 )
				i = i ;
			pp = &gdi->pps[k][i] ;
			pp->fs[0] = polys[k]->FTrail[i] ; // 面
			memcpy(pp->ps[0], &polys[k]->PTrail[i].x, sizeof(double[3])) ; // 点
			// nt modify 2022/7/4 add pp->perp
			pp->d = polys[1-k]->Snap(this, pp->fs, pp->ps, tol, pp->I, pp->t, pp->perp) ;
			if( pp->I > 0 &&
				pp->perp == 1 ) // nt add 2022/7/4 只用垂直的情况更新min,max!!!
			{
				if( gdi->min > pp->d )
				{
					gdi->min = pp->d ;
					gdi->i = k?-i:i ;
				}
				if( gdi->max < pp->d )
				{
					gdi->max = pp->d ;
					gdi->I = k?-i:i ;
				}
			}
		}
	}
	*pGDI = gdi ;

	return 1 ;
}
//==============================================================
/*	2022/6/18 nt
 *	功能：计算点到polyline的最近距离
 *	输入：
 *		pGM : GridModel
 *		fs[0] : Flist which ps[0] is on
 *		ps[0] : a point on the grid
 *		tol : 点重合容差
 *	输出:
 *		ps[1] : a point on this polyline
 *		fs[1] : FList which ps[1] is on
 *		I : index of PTrail
 *		t : [0.,1.), ps[1] = (1-t)*PTrail[i]+t*PTrail[i+1], i is the return value
 *		perp : 1=垂直,0=非垂直
 *	返回:
 *		最近距离
 *	nt modify 2022/7/9 use Prj()
 */
double MTIPathOriginList::Snap(GridModel* pGM, 
							   FList fs[2], 
							   double ps[2][3], 
							   double tol, 
							   int& I, 
							   double& t,
							   int& perp)
{
	int i, n = 0, PERP ;
	double min = 1e50, d, s, q[3] ;
	Pl* polyline = NULL ;

	fs[1] = NULL ;
	t = 0. ;
	I = 0 ;
	perp = 0 ; // nt add 2022/7/4, 0 or 1

	// 点的下标从1到n
	for( i = 1 ; i <= DNum ; i++ )
		n += (ENum[i]-SNum[i]+1) ; // i段实际点数=ENum[i]-SNum[i]+1

	if( n < 2 )
		return -1. ; // error

	for( i = 1 ; i < n ; i++ )
	{
		//d = mathGetPntSegmNDT(ps[0], &PTrail[i].x, &PTrail[i+1].x, &s) ;
		// nt modify 2022/7/4
		d = mathGetPntSegmNDTPerp(ps[0], &PTrail[i].x, &PTrail[i+1].x, tol, &s, &PERP) ;
		if( (PERP == perp && min > d) || // nt add 2022/7/4, 尽量保留垂直的结果
			PERP > perp )
		{
			mathMixPnt(&PTrail[i].x, &PTrail[i+1].x, 1.-s, s, ps[1]) ;
			min = d ;
			t = s ;
			I = i ;
			perp = PERP ;
		}
	}
	if( I < 1 ) // I一定<n
		return -1. ; // error

	// nt add 2022/7/9
	fs[1] = pGM->Prj(FTrail[I], &PTrail[I].x, FTrail[I+1], &PTrail[I+1].x, tol, ps[1], q) ;
	if( fs[1] == NULL )
		return -1. ; // error=ps[1]投影不在网格面上
	if( min < tol )
		return min ;

	if( pGM->CalGeodesicLine(fs[0], ps[0], fs[1], q, tol, &polyline) < 1 ||
		polyline == NULL )
	{
		fs[1] = NULL ;
		t = 0. ;
		I = 0 ;
		return -1. ; // error
	}

	polyline->ReplaceEnd(ps[1]) ; // nt add 2022/7/9
	polyline->CalArcLen() ;
	d = polyline->arcLen ;
	// release polyline
	delete polyline ;
	//pGM->polylines[pGM->nPolyline] = polyline ; // debug only
	//(pGM->nPolyline)++ ; // debug only

	return d ;
}
//==============================================================
BOOL GridModel::stlVectorNormal(STLVECTOR *v1)
{
	double alph =stlDistanceOneVector(*v1);
	if ( alph < 1.e-4) {
		return FALSE;
	}
	*v1 = stlTwoVectorDivide(*v1,alph);
	return TRUE;
}

FList GridModel::stlGetFacetFromNum(int N)
{
	FList f = FHead;
	for (int i = 1;i <= FaceNum; i ++)
	{
		if (f ->FaceNO == N)return f;
		else if(f->FNext != NULL)f = f->FNext;
	}
	return f;
}

BOOL GridModel::stlCreateSTLTriangle(STLPNT3D p1, STLPNT3D p2, STLPNT3D p3)
{
	STLVECTOR v1, v2, nv;

	v1 = stlTwoVectorMinus(p2,p1);
	if ( !stlVectorNormal(&v1) ) {
		return FALSE;
	}

	v2 = stlTwoVectorMinus(p3,p2);
	if ( !stlVectorNormal(&v2) ) {
		return FALSE;
	}


	nv = stlTwoVectorProduct(v1,v2);
	if ( !stlVectorNormal(&nv) ) {
		STLVECTOR v3 = stlTwoVectorMinus(p1,p3);
		if ( !stlVectorNormal(&v3) ) {
			return FALSE;
		}
		nv = stlTwoVectorProduct(v3,v1);
		if ( !stlVectorNormal(&nv) ) {
			return FALSE;
		}
	}

	stlCreateFace(&nv, &p1, &p2, &p3,-1);

	return TRUE;
}

FList GridModel::stlCreateFace(STLVECTOR *nv, STLPNT3D *p1, STLPNT3D *p2, STLPNT3D *p3,int tNum)
{
	FList p, temp;

	if (fabs(p1->x-p2->x) < EPS06 && fabs(p1->y-p2->y) < EPS06 && fabs(p1->z-p2->z) < EPS06 ||
		fabs(p1->x-p3->x) < EPS06 && fabs(p1->y-p3->y) < EPS06 && fabs(p1->z-p3->z) < EPS06 ||
		fabs(p3->x-p2->x) < EPS06 && fabs(p3->y-p2->y) < EPS06 && fabs(p3->z-p2->z) < EPS06 ) {
		return NULL;
	}

	FaceNum++;
	p = stlFaceAlloc();
	//默认p1,p2,p3,nv呈右手法则
	/*p->NormalVector.x=nv->x;
	p->NormalVector.y=nv->y;
	p->NormalVector.z=nv->z;*/
	// nt add 2022/7/9
	mathGetTriNormal(&p1->x, &p2->x, &p3->x, &p->NormalVector.x) ; 
	if( mathOProduct(&nv->x, &p->NormalVector.x) < 0. )
	{
		p->NormalVector.x = -p->NormalVector.x ;
		p->NormalVector.y = -p->NormalVector.y ;
		p->NormalVector.z = -p->NormalVector.z ;
	}
	// end

	if(tNum == -1)p->FaceNO = FaceNum;
	else p->FaceNO = tNum;

	p->VertexUsed[0]=stlCreateVertex(&VRoot,p1);
	p->VertexUsed[1]=stlCreateVertex(&VRoot,p2);
	p->VertexUsed[2]=stlCreateVertex(&VRoot,p3);

	p->EdgeUsed[0]=stlCreateEdge(p->VertexUsed[0],p->VertexUsed[1]);
	p->EdgeUsed[1]=stlCreateEdge(p->VertexUsed[1],p->VertexUsed[2]);
	p->EdgeUsed[2]=stlCreateEdge(p->VertexUsed[2],p->VertexUsed[0]);
	
	stlAddFace2Vertex(p,p->VertexUsed[0]);
	stlAddFace2Vertex(p,p->VertexUsed[1]);
	stlAddFace2Vertex(p,p->VertexUsed[2]);

	p->EdgeUsed[0]->FaceCircleTag = 0;
	p->EdgeUsed[1]->FaceCircleTag = 0;
	p->EdgeUsed[2]->FaceCircleTag = 0;

	stlAddFace2Edge(p,p->EdgeUsed[1]);
	stlAddFace2Edge(p,p->EdgeUsed[0]);
	stlAddFace2Edge(p,p->EdgeUsed[2]);

	if(FHead == NULL) {
		FHead = p;
	}
	else {
		temp = FHead;
		FHead = p;
		FHead->FNext = temp;
	}

	return p;
}

FList GridModel::stlFaceAlloc()
{
	FList p;

	//p = (FList)malloc(sizeof(struct FaceList));
	p = new FaceList() ; // nt add 2022/6/15
	if (p==NULL) {
		exit(1);
	}
	p->FCircleTag = 0.0;
	p->FaceNO = -1;
	p->FNext = NULL;
	return p;
}

// nt modify 2022/6/15
VList GridModel::stlCreateVertex(VList *root, STLPNT3D *pt)
{
	STLPNT3D q ;

	q.x = /*0.001**/pt->x ;
	q.y = /*0.001**/pt->y ;
	q.z = /*0.001**/pt->z ;

	if(q.x < stl_xmin) 
		stl_xmin = (double)(q.x);
	if(q.x > stl_xmax) 
		stl_xmax = (double)(q.x);
	if(q.y < stl_ymin) 
		stl_ymin = (double)(q.y);
	if(q.y > stl_ymax) 
		stl_ymax = (double)(q.y);
	if(q.z < stl_zmin) 
		stl_zmin = (double)(q.z);
	if(q.z > stl_zmax) 
		stl_zmax = (double)(q.z);

	return stlSortTree(&q,root);
}

VList GridModel::stlSortTree(STLPNT3D *pt, VList *t)  //二叉排序树
{
	VList	 p,p1;  //p作为遍历节点使用,p1作为返回指针使用 
	int	   Bool;
	if(*t == NULL)  //树为空
	{
		*t = p1 = stlVertexAlloc();
		p1->Coord = *pt; 
		VerNum++;
	} 
	else   //树不为空
	{
		p = *t;  //p作为遍历节点使用
		Bool = 1; 
		do 
		{
			if (pt->z < p->Coord.z)   //如果需要插入的z值小于当前节点的z值,插入左子树
			{
				if(p->Lchild != NULL)  //左子树不空
				{
					p = p->Lchild;
				}
				else 
				{
					p1 = stlVertexAlloc();
					p1->Coord = *pt; 
					p->Lchild = p1;
					VerNum++;
					Bool = 0;
				}
			}
			else if(pt->z > p->Coord.z) 
			{
				if(p->Rchild != NULL) 
				{
					p = p->Rchild;
				}
				else 
				{
					p1 = stlVertexAlloc();
					p1->Coord = *pt; 
					p->Rchild = p1;
					VerNum++;
					Bool = 0;
				}
			}
			else 
			{
				if(pt->x == p->Coord.x && pt->y == p->Coord.y)  //完全相同
				{
					p1 = p;
					Bool = 0;
				}
				else   //插入左子树
				{
					if(p->Lchild != NULL) 
					{
						p = p->Lchild;
					}
					else 
					{
						p1 = stlVertexAlloc();
						p1->Coord = *pt; 
						p->Lchild = p1;
						VerNum++;
						Bool = 0;
					}
				}
			}
		}
		while(Bool);
	}
	return p1;
}

VList GridModel::stlVertexAlloc()
{
	VList p;
	p = (VList)malloc(sizeof(struct VertexList));
	if (p==NULL) 
	{
		exit(1);
	}
	p->Lchild = NULL;
	p->Rchild = NULL;
	p->FaceUsed = NULL;
	p->FaceNum = 0;
	return p;
}
EList GridModel::stlCreateEdge(VList p1, VList p2)
{
	EList   e, e_new;
	FRelated fr1, fr2;
	int    i, j, k;
	fr1 = p1->FaceUsed;
	fr2 = p2->FaceUsed;
	if(fr1 != NULL && fr2 != NULL) 
	{
		for(i=0; i< p1->FaceNum; i++) 
		{
			fr2 = p2->FaceUsed;
			for(j=0; j<p2->FaceNum; j++) 
			{
				if(fr1->Face == fr2->Face) //如果两个点相关联的面相同
				{
					for(k=0; k<3; k++) 
					{
						e = fr1->Face->EdgeUsed[k];
						if (e->VertexUsed[0]==p2 && e->VertexUsed[1]==p1) 
							return e;
						else if (e->VertexUsed[0]==p1 && e->VertexUsed[1]==p2) 
							return e;
					}
				}
				fr2 = fr2->FNext;
			}
			fr1 = fr1->FNext;
		} 
	}
	e_new = stlEdgeAlloc();
	e_new->VertexUsed[0] = p1;
	e_new->VertexUsed[1] = p2;
	e = EHead;
	EHead = e_new;
	EHead->ENext = e;
	EdgeNum++;
	return EHead;
}

EList GridModel::stlEdgeAlloc()
{
	EList p;
	p = (EList)malloc(sizeof(struct EdgeList));
	if (p==NULL) 
	{
		exit(1);
	}
	p->ENext = NULL;
	p->FaceUsed = NULL;
	p->FaceNum = 0;
	p->FaceCircleTag = 0;
	p->FCircleTag = 0.0;
	return p;
}

void GridModel::stlAddFace2Vertex(FList f, VList v)
{
	FRelated fr, fnew;
	fnew = (FRelated)malloc(sizeof(struct FaceRelated));
	if (fnew==NULL) 
	{
		exit(1);
	}
	fnew->Face = f;
	if (v->FaceUsed == NULL) 
	{
		v->FaceUsed = fnew;
		fnew->FNext = NULL;
	}
	else 
	{
		fr = v->FaceUsed;
		v->FaceUsed = fnew;
		fnew->FNext = fr;
	}
	(v->FaceNum)++;
}

void GridModel::stlAddFace2Edge(FList f, EList e)
{
	FRelated fr,fnew;
	fnew = (FRelated)malloc(sizeof(struct FaceRelated));
	if (fnew==NULL) 
	{
		exit(1);
	}
	fnew->Face = f;
	if (e->FaceUsed == NULL) 
	{
		e->FaceUsed = fnew;
		fnew->FNext = NULL;
	}
	else 
	{
		fr = e->FaceUsed;
		e->FaceUsed = fnew;
		fnew->FNext = fr;
	}
	(e->FaceNum)++;
}

BOOL GridModel::stlCompareTwo3DPoint(STLPNT3D p3d1, STLPNT3D p3d2, double epsdis)
{
	BOOL equaled = FALSE;
	if (fabs(p3d1.x - p3d2.x) < epsdis)
	{
		if (fabs(p3d1.y - p3d2.y) < epsdis)
		{
			if (fabs(p3d1.z - p3d2.z) < epsdis)
			{
				equaled = TRUE;
			}
		}
	}
	return equaled;
}

double GridModel::stlDistanceTwoPoints(STLPNT3D p1, STLPNT3D p2)
{
	double dd = stlDistanceOneVector(stlTwoVectorMinus(p1,p2));
	return dd;
}

int GridModel::stlCompareTriangleVertex(STLPNT3D p1, STLPNT3D p2, STLPNT3D p3, STLPNT3D q1, STLPNT3D q2, STLPNT3D q3)
{
	STLPNT3D  v1, v2, v3;
	v1 = stlTwoVectorMinus(p1,q1);
	v2 = stlTwoVectorMinus(p2,q1);
	v3 = stlTwoVectorMinus(p3,q1);
	int  flag = 0;
	if (stlDistanceOneVector(v1)< 0.1 ) {
		flag++;
		v2 = stlTwoVectorMinus(p2,q2);
		v3 = stlTwoVectorMinus(p3,q3);
		if ( stlDistanceOneVector(v2)< 0.1 ) {
			flag++;
			if ( stlDistanceOneVector(v3) < 0.1 ) {
				flag++;
			}
		}
		else {
			v2 = stlTwoVectorMinus(p3,q2);
			v3 = stlTwoVectorMinus(p2,q3);
			if ( stlDistanceOneVector(v2) < 0.1 ) {
				flag++;
				if ( stlDistanceOneVector(v3)< 0.1 ) {
					flag++;
				}
			}
		}
	}
	else if ( stlDistanceOneVector(v2) < 0.1 ) {
		flag++;
		v1 = stlTwoVectorMinus(p1,q2);
		v3 = stlTwoVectorMinus(p3,q3);
		if ( stlDistanceOneVector(v1)< 0.1 ) {
			flag++;
			if (stlDistanceOneVector(v3) < 0.1 ) {
				flag++;
			}
		}
		else {
			v1 = stlTwoVectorMinus(p3,q2);
			v3 = stlTwoVectorMinus(p1,q3);
			if (stlDistanceOneVector(v1) < 0.1 ) {
				flag++;
				if (stlDistanceOneVector(v3) < 0.1 ) {
					flag++;
				}
			}
		}
	}
	else if (stlDistanceOneVector(v3) < 0.1 ) {
		flag++;
		v1 = stlTwoVectorMinus(p1,q2);
		v2 = stlTwoVectorMinus(p2,q3);
		if ( stlDistanceOneVector(v2) < 0.1 ) {
			flag++;
			if (stlDistanceOneVector(v1) < 0.1 ) {
				flag++;
			}
		}
		else {
			v1 = stlTwoVectorMinus(p1,q3);
			v2 = stlTwoVectorMinus(p2,q2);
			if (stlDistanceOneVector(v2) < 0.1 ) {
				flag++;
				if ( stlDistanceOneVector(v1) < 0.1 ) {
					flag++;
				}
			}
		}
	}
	return flag;
}
STLPNT3D GridModel::stlTwoVectorPlus(STLPNT3D p1,STLPNT3D p2)
{
	STLPNT3D PTemp = p1;
	PTemp.x = p1.x + p2.x;	PTemp.y = p1.y + p2.y;	PTemp.z = p1.z + p2.z;
	return PTemp;
}
STLPNT3D GridModel::stlTwoVectorMinus(STLPNT3D p1,STLPNT3D p2)
{
	STLPNT3D PTemp = p1;
	PTemp.x = p1.x - p2.x;	PTemp.y = p1.y - p2.y;	PTemp.z = p1.z - p2.z;
	return PTemp;
}
STLPNT3D GridModel::stlTwoVectorMultiply(STLPNT3D p1,double l1)
{
	STLPNT3D PTemp = p1;
	PTemp.x = p1.x * l1;	PTemp.y = p1.y * l1;	PTemp.z = p1.z * l1;
	return PTemp;
}
STLPNT3D GridModel::stlTwoVectorDivide(STLPNT3D p1,double l1)
{
	STLPNT3D PTemp = PBreak;
	if(fabs( l1 ) > 1.e-9)
	{
		PTemp.x = p1.x / l1;	PTemp.y = p1.y / l1;	PTemp.z = p1.z / l1;
	}
	return PTemp;
}
//计算某向量长度
double  GridModel::stlDistanceOneVector(STLPNT3D p1)
{
	return (sqrt(fabs(p1.x*p1.x +p1.y*p1.y +p1.z*p1.z)));
}

POList GridModel::stlPOLHeadAlloc()
{
	POList T;
	T = (POList)malloc(sizeof(struct MTIPathOriginList)) ;
	if( T == NULL )
	{
		exit(1) ;
	}
	T->PTrail = NULL ;
	T->PNTrail = NULL ;
	T->FTrail = NULL ;
	T->TNum = 0 ;
	T->DNum = 1 ;
	T->SNum = NULL ;
	T->ENum = NULL ;
	T->PONext = NULL ;

	return T ;
}

void  GridModel::GetInformationFromPath()//从铺放路径获取信息			主要针对TXT文件
{
	FILE * ffpem;
	int NumTemp;
	int it = 0;
	double d ; // nt add 2022/6/18
	char str[300],*ret, *ip;
	if(fopen_s(&ffpem, PreDataFileName,"r") != 0) {
		printf("Error: Path file open failed\n");
		MessageBox(NULL, L"数据文件不存在,请检查！", L"提示", MB_OK);
		exit(1);
	}
label:
	ret = fgets(str,300,ffpem);
	if (ret != NULL)
	{
		if (strstr(str,"iSag=")!= NULL)
		{
			ip = strstr(str,"iSag=")+5;
			sscanf_s(ip,"%le",&isag);
			ip = strstr(str,"iAngle=")+5;
			sscanf_s(ip,"%le",&iangle);
			ip = strstr(str,"iStep=")+6;
			sscanf_s(ip,"%le",&istep);
		}
		else if (strstr(str,"AngelStart=")!=NULL)
		{
			ip = strstr(str,"AngelStart=")+11;
			sscanf_s(ip,"%le",&Plyangle);
		}
		else if (strstr(str,"MeshDATAFile=")!= NULL)
		{
			ip = strstr(str,"_DATA")+5;
			//sprintf_s(FileResultName,DataFileFullPath);
			//strcat_s(FileResultName,ip);
			//stlReadStlFile(FileResultName);
		}
		else if (strstr(str,"Width=")!= NULL)
		{
			ip = strstr(str,"Width=")+6;
			sscanf_s(ip,"%le",&dval);
			ip = strstr(str,"Gap=")+4;
			sscanf_s(ip,"%le",&gapValue);
			ip = strstr(str,"TapNums=")+8;
			sscanf_s(ip,"%d",&FiberNum);
		}
		else if (strstr(str,"ModelName=")!= NULL)
		{
			ip = strstr(str,"ModelName=")+10;
			//sscanf_s(ip,"%s",&ModelName);
		}
		else if (strstr(str,"Element=")!= NULL)
		{
			ip = strstr(str,"Element=")+8;
			sscanf_s(ip,"%s",&PointName, 100);
		}
		else if (strstr(str,"TotalNum=")!= NULL)
		{
			ip = strstr(str,"TotalNum=")+9;
			sscanf_s(ip,"%d",&TrailNumDum);
		}
		else if (strstr(str,"NormalTag=")!= NULL)
		{
			ip = strstr(str,"NormalTag=")+10;
			sscanf_s(ip,"%d",&stlFaceTag);
		}
		else if (strstr(str,"Output Start")!= NULL)
		{
			POLHead = new POList[TrailNumDum+1];
			ret = fgets(str,300,ffpem);
label2:
			if (strstr(str,"tiaoshu=")!= NULL)
			{
				it++;
				ip = strstr(str,"tiaoshu=")+8;
				sscanf_s(ip,"%d",&NumTemp);
				POLHead[NumTemp] = stlPOLHeadAlloc();
				POLHead[NumTemp]->TNum = NumTemp;
				POLHead[NumTemp]->ENum = new int[2];
				POLHead[NumTemp]->SNum = new int[2];
				POLHead[NumTemp]->ENum[1] = 0;
				POLHead[NumTemp]->SNum[1] = 1;
				ip = strstr(str,"dianshu=")+8;
				int PointNumTemp;
				sscanf_s(ip,"%d",&PointNumTemp);
				POLHead[NumTemp]->PNTrail = new STLPNT3D[PointNumTemp+1];
				POLHead[NumTemp]->PTrail = new STLPNT3D[PointNumTemp+1];
				POLHead[NumTemp]->FTrail = new FList[PointNumTemp+1];
label3:
				ret = fgets(str,300,ffpem);
				if (strstr(str,"x=")!= NULL)
				{
					int FaceTemp;
					POLHead[NumTemp]->ENum[1]++;
					ip = strstr(str,"x=")+2;
					sscanf_s(ip,"%le",&d);
					POLHead[NumTemp]->PTrail[POLHead[NumTemp]->ENum[1]].x = /*0.001**/d ;
					ip = strstr(str,"y=")+2;
					sscanf_s(ip,"%le",&d);
					POLHead[NumTemp]->PTrail[POLHead[NumTemp]->ENum[1]].y = /*0.001**/d ;
					ip = strstr(str,"z=")+2;
					sscanf_s(ip,"%le",&d);
					POLHead[NumTemp]->PTrail[POLHead[NumTemp]->ENum[1]].z = /*0.001**/d ;

					ip = strstr(str,"Nx=")+3;
					sscanf_s(ip,"%le",&POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]].x);
					ip = strstr(str,"Ny=")+3;
					sscanf_s(ip,"%le",&POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]].y);
					ip = strstr(str,"Nz=")+3;
					sscanf_s(ip,"%le",&POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]].z);
					ip = strstr(str,"FaceNum=")+8;
					sscanf_s(ip,"%d",&FaceTemp);

					if (POLHead[NumTemp]->ENum[1] > 2 && stlDistanceTwoPoints(POLHead[NumTemp]->PTrail[POLHead[NumTemp]->ENum[1]],POLHead[NumTemp]->PTrail[POLHead[NumTemp]->ENum[1]-1]) < TOLLENGTH)//20210106
					{
						POLHead[NumTemp]->PTrail[POLHead[NumTemp]->ENum[1]-1] = POLHead[NumTemp]->PTrail[POLHead[NumTemp]->ENum[1]] ;
						POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]-1] = POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]] ;
						POLHead[NumTemp]->ENum[1]--;
					}
					//if(POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]].z < 0) 
					//	POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]] = stlOPPNormalVector(POLHead[NumTemp]->PNTrail[POLHead[NumTemp]->ENum[1]]);
					if(FHead != NULL)
					{
						POLHead[NumTemp]->FTrail[POLHead[NumTemp]->ENum[1]] = stlGetFacetFromNum(FaceTemp);

					}
					goto label3;
				}
				ret = fgets(str,300,ffpem);
				goto label2;
			}
			if(strstr(str,"Output End") != NULL) {
				TrailNumDum = it;
				fclose(ffpem);
				ffpem = NULL;
				return;
			}
			else {
				goto label2;
			}
		}
		if(strstr(str,"Output End") != NULL) {
			TrailNumDum = it;
			fclose(ffpem);
			ffpem = NULL;
			return;
		}
		else {
			goto label;
		}
	}
	if(strstr(str,"Output End") != NULL) {
		TrailNumDum = it;
		fclose(ffpem);
		ffpem = NULL;
		return;
	}
	else {
		goto label;
	}
}
void GridModel::stlDealInputFile()
{
	int flag = 0;
	FILE *file;

	char buf[300];
	errno_t err;
	err = fopen_s(&file, ModelName, "rb");
	if (strstr(ModelName,"stl") != NULL)
	{
		flag = 1;
		fread(buf, 1, 255,file);
		char* c;
		for(int i = 0; i < 255; i ++)
		{
			c = strstr(buf + i,"facet normal");  //search substring "facet normal"
			if (c != NULL) 
			{
				flag = 2;   //find "facet normal", then flag =2,stl文件为字符文件
				break;
			}
		}
	}
	else if (strstr(ModelName,"dat") != NULL)
	{
		flag = 3;
	}
	fclose(file);
	if (flag != 0)
	{
		if(flag == 1)
		{
			stlReadSTLBinFile(ModelName); //二进制stl文件
		}
		else if(flag == 2)
		{
			stlReadStlFile(ModelName);   //字符stl文件
		} 
		else if(flag == 3)
		{
			stlReadDatFile(ModelName);		//有限元网格Dat文件
		}
	}
}
void GridModel::stlReadFile(char *filename)
{
	int flag = 0;
	FILE *file;

	char buf[300];
	errno_t err;
	err = fopen_s(&file, filename, "rb");
	int FileEx = 1;
	if(err != 0){
		MessageBox(NULL, L"文件不存在，请检查输入条件。", L"提示", MB_OK);
		FileEx = 0;
	}
	if (strstr(filename,"stl") != NULL)
	{
		flag = 1;
		fread(buf, 1, 255,file);
		char* c;
		for(int i = 0; i < 255; i ++)
		{
			c = strstr(buf + i,"facet normal");  //search substring "facet normal"
			if (c != NULL) 
			{
				flag = 2;   //find "facet normal", then flag =2,stl文件为字符文件
				break;
				file = NULL;
			}
		}
	}
	else if (strstr(filename,"dat") != NULL)
	{
		flag = 3;
	}
	fclose(file);
	file = NULL;

	if (flag != 0)
	{
		if(flag == 1)
		{
			stlReadSTLBinFile(filename); //二进制stl文件
		}
		else if(flag == 2)
		{
			stlReadStlFile(filename);   //字符stl文件
		} 
		else if(flag == 3)
		{
			stlReadDatFile(filename);		//有限元网格Dat文件
		}
		TraverseNum = 0;
		//GetNormaVectorOnVertex(VRoot);//获取顶点处法向 nt comment 2022/6/14
	}
}
/*void GridModel::GetNormaVectorOnVertex(VList p)
{
	if (p)
	{
		TraverseNum ++;
		FRelated ff = p->FaceUsed;
		int FNum = p->FaceNum;
		FList f = ff->Face;
		double *dTemp = new double[FNum+1]; 
		double dEnd = 0;
		STLPNT3D NormalV = CreateMTIPoint();
		STLPNT3D NormalV2 = CreateMTIPoint();
		for (int i =1; i <= FNum;i++)
		{
			dTemp[i] = GetDistanceVertexToCoreOfTrangle(p->Coord,ff ->Face);
			if(dTemp[i] >= 0)
			{
				NormalV2 =  stlTwoVectorDivide(ff ->Face->NormalVector,dTemp[i]);
				NormalV =stlTwoVectorPlus(NormalV,NormalV2);
				dEnd += 1.0 / dTemp[i];
			}
			if(ff->FNext != NULL)
				ff = ff ->FNext;
		}
		if(FNum == 1)
			dEnd = 1.0;
		p->NormalVector = stlTwoVectorMultiply(NormalV,dEnd);
		stlVectorNormal(&(p->NormalVector));
		if(dTemp != NULL)delete [] dTemp;
			dTemp = NULL;
		GetNormaVectorOnVertex(p->Lchild);
		GetNormaVectorOnVertex(p->Rchild);
	}
	else if(TraverseNum >= VerNum-1)
	{
		return ;
	}
}*/
void GridModel::stlReadSTLBinFile(char *filename)
{
	FILE *stlfile;

	STLVECTOR nv;
	STLPNT3D  p1,p2,p3;

	union 
	{
		long int i4;
		char   c[4];
		float   r;
	} buf;

	errno_t err;

	err = fopen_s(&stlfile, filename, "rb");
	if ( err != 0 ) {
		return;
	}

	fseek(stlfile,0L,SEEK_SET); //move point to the beginning
	if(stlfile == NULL) 
	{
		printf("Error: STL file open failed\n");
		exit(1);
	}

	for(int i=0; i<80; i++)  
	{
		char c = getc(stlfile); 
		printf("%c",c);
	}
	printf("\n");

	buf.c[0] = getc(stlfile); //get the total number of the facet
	buf.c[1] = getc(stlfile);
	buf.c[2] = getc(stlfile);
	buf.c[3] = getc(stlfile);
	int NumberTotal = buf.i4;  //total number of facet
	//NumberTotal = 400000;
	int step = (int)(NumberTotal/20);

	char str[133];
	strcpy_s(str,"正在打开模型, 请等待");

	for(int i=0; i<NumberTotal; i++) 
	{
		if (i%step == 0) 
		{
			strcat_s(str, ".");
		}

		stlRead4Bytes(stlfile,&buf.c[0]);  //get the vector of the facet    
		nv.x = buf.r; 
		stlRead4Bytes(stlfile,&buf.c[0]);    
		nv.y = buf.r; 
		stlRead4Bytes(stlfile,&buf.c[0]);    
		nv.z = buf.r; 

		stlRead4Bytes(stlfile,&buf.c[0]);  //get the points of the facet    
		p1.x = buf.r;
		stlRead4Bytes(stlfile,&buf.c[0]);    
		p1.y = buf.r;
		stlRead4Bytes(stlfile,&buf.c[0]);    
		p1.z = buf.r;

		stlRead4Bytes(stlfile,&buf.c[0]);    
		p2.x = buf.r;
		stlRead4Bytes(stlfile,&buf.c[0]);    
		p2.y = buf.r;
		stlRead4Bytes(stlfile,&buf.c[0]);    
		p2.z = buf.r;

		stlRead4Bytes(stlfile,&buf.c[0]);    
		p3.x = buf.r;
		stlRead4Bytes(stlfile,&buf.c[0]);    
		p3.y = buf.r; 
		stlRead4Bytes(stlfile,&buf.c[0]);    
		p3.z = buf.r;

		char c = getc(stlfile); 
		c = getc(stlfile); 

		STLPNT3D vp1, vp2;
		vp1 = CreateMTIPoint();
		vp2 = nv;
		nv = stlTwoVectorMinus(vp2,vp1);
		stlVectorNormal(&nv);
		stlCreateFace(&nv,&p1,&p2,&p3,-1);   //生成一个三角片面,nv为法向量,p为三个顶点坐标

	}
	fclose(stlfile);
	stlfile = NULL;
}

void GridModel::stlRead4Bytes(FILE *stlfile, char *c)
{
	c[0] = getc(stlfile);
	c[1] = getc(stlfile);
	c[2] = getc(stlfile);
	c[3] = getc(stlfile);
}
void GridModel::stlReadStlFile(char *file)
{
	FILE		*stlfile;
	STLPNT3D  p1,p2,p3,nv;
	int			tttNum;
	char    str[256]; // nt modify 2022/7/8 old 80
	char    *ret, *ip;

	if(fopen_s(&stlfile, file,"r") != 0) {
		printf("Error: STL file open failed\n");
		exit(1);
	}
	MeshResulttag = 0;
label:
	ret = fgets(str,256,stlfile);
	if ( ret != NULL ) {
		if(strstr(str,"##") != NULL)
		{
			//ip = strstr(str,"%%");
			sscanf_s(str,"%s",&MeshResult[MeshResulttag], 256);
			MeshResulttag ++;
		}
		if ( strstr(str,"facet normal") != NULL ) {
			ip = strstr(str,"normal") + 6;
			sscanf_s(ip,"%le %le %le",&nv.x,&nv.y,&nv.z);
			if (strstr(str,"FaceNum = ") != NULL)
			{
				ip = strstr(str,"FaceNum = ") + 10;
				sscanf_s(ip,"%d",&tttNum);
			}
			else
				tttNum = -1;
			
			while(1)
			{
				ret = fgets(str,256,stlfile);
				if( strstr(str,"outer loop") != NULL ) // nt add 2022/7/8
					break ;
			}
			ret = fgets(str,256,stlfile);
			ip = strstr(str,"vertex") + 6;
			sscanf_s(ip,"%le %le %le",&p1.x,&p1.y,&p1.z);
			ret = fgets(str,256,stlfile);
			ip = strstr(str,"vertex") + 6;
			sscanf_s(ip,"%le %le %le",&p2.x,&p2.y,&p2.z);
			ret = fgets(str,256,stlfile);
			ip = strstr(str,"vertex") + 6;
			sscanf_s(ip,"%le %le %le",&p3.x,&p3.y,&p3.z);

			stlCreateFace(&nv,&p1,&p2,&p3,tttNum);    
			goto label;
		}
		else if(strstr(str,"endsolid") != NULL) {
			fclose(stlfile);
			stlfile = NULL;
			return;
		}
		else {
			goto label;
		}
	}
	stlfile = NULL;
}

void GridModel::stlReadDatFile(char *file)
{
	FILE		*datfile;
	STLPNT3D  p1,p2,p3,nv;
	char    str[80];
	char    *ret,*ip;
	int     temp[5],temp1;
	STLPNT3D *PTemp;
	int i = 1;

	//获取点数,确定点数组大小
	if(fopen_s(&datfile, file,"r") != 0) {
		printf("Error: dat file open failed\n");
		exit(1);
	}
label2:	
	ret = fgets(str,80,datfile);
	if ( ret != NULL ) {
		if ( strstr(str,"GRID*") != NULL ) {
			ret = fgets(str,80,datfile);
			ret = fgets(str,80,datfile);
			i ++;
			goto label2;
		}
		else if (strstr(str,"ELEMENTS") != NULL )
			fclose(datfile);
		else 
			goto label2;	
	}

	fclose(datfile);

	PTemp = new STLPNT3D[i];
	
	//重新打开文档,开始拓扑关系建立
	if(fopen_s(&datfile, file,"r") != 0) {
		printf("Error: dat file open failed\n");
		exit(1);
	}
	
	i = 1;
label1:
	ret = fgets(str,80,datfile);
	if ( ret != NULL ) {
		if ( strstr(str,"GRID*") != NULL ) {

			ip = strstr(str,"GRID*") + 5;
			sscanf_s(ip,"%d %le %le",&temp1,&p1.x,&p1.y);
			ret = fgets(str,80,datfile);
			ret = fgets(str,80,datfile);
 			sscanf_s(ip,"%d %le",&temp1,&p1.z);
			PTemp[i] = p1;

 			i ++;

			goto label1;

			}
			else if (strstr(str,"ELEMENTS") != NULL )
				goto labell;
			else
				goto label1;
		}	
	
labell:
	ret = fgets(str,80,datfile);
	if (ret != NULL)
	{
		if (strstr(str,"CTRIA3") != NULL)//从面开始拓扑入手
		{
			ip =strstr(str,"CTRIA3") + 6;
			sscanf_s(ip,"%d %d %d %d %d",&temp[0],&temp[1],&temp[2],&temp[3],&temp[4]);

			p1 = PTemp[temp[2]];
			p2 = PTemp[temp[3]];
			p3 = PTemp[temp[4]];

			STLPNT3D l1,l2;
			l1 = stlDistanceVectorTwoPoint(p1,p2);
			l2 = stlDistanceVectorTwoPoint(p1,p3);
			nv = stlTwoVectorProduct(l1,l2);
			stlVectorNormal(&nv);
			nv = stlOPPNormalVector(nv);
			stlCreateFace(&nv,&p1,&p2,&p3,-1); 
			goto labell;
		}
		else if(strstr(str,"ENDDATA") != NULL) {
			fclose(datfile);

			delete PTemp;
      PTemp = NULL;

			return;
		}
		else {
			goto labell;
		}
	}
}

//返回两点方向向量并单位化
STLPNT3D GridModel::stlDistanceVectorTwoPoint(STLPNT3D p1,STLPNT3D p2)
{
	STLPNT3D PTemp = stlTwoVectorMinus(p2,p1);
	if (!stlVectorNormal(&PTemp))
	{
		PTemp = CreateMTIPoint();
	}//return PBreak;
	return PTemp;
}
///////////////////////////////////////////////////////////////////////////////////////
// Function: 计算两向量叉积
// Input:		 L1  L2  两向量
// Return:  叉积
///////////////////////////////////////////////////////////////////////////////////////
STLPNT3D  GridModel::stlTwoVectorProduct(STLPNT3D L1,STLPNT3D L2)
{
	STLPNT3D P = PBreak;
	P.x = L1.y * L2.z - L1.z * L2.y;	
	P.y = L1.z * L2.x - L1.x * L2.z;		
	P.z = L1.x * L2.y - L1.y * L2.x;
	return P;
}
STLPNT3D GridModel::stlOPPNormalVector(STLPNT3D p1)
{
	p1 = stlTwoVectorMinus(CreateMTIPoint(), p1);
	return p1;
}
STLPNT3D GridModel::CreateMTIPoint()//创建默认点
{
	STLPNT3D pTemp;
	pTemp = CreateMTIPoint(0.,0.,0.);
	return pTemp;
}
STLPNT3D GridModel::CreateMTIPoint(double ix,double iy,double iz)//从xyz创点
{
	STLPNT3D pTemp;
	pTemp.x = ix;	pTemp.y = iy;	pTemp.z = iz;
	return pTemp;
}
STLPNT3D GridModel::CreateMTIPoint(double p1[])//从数组创点
{
	STLPNT3D pTemp;
	pTemp = CreateMTIPoint(p1[0],p1[1],p1[2]);
	return pTemp;
}
STLPNT3D GridModel::CreateMTIPoint(double p1[],int iNbStart)//从数组创点
{
	STLPNT3D pTemp;
	pTemp = CreateMTIPoint(p1[iNbStart+0],p1[iNbStart+1],p1[iNbStart+2]);
	return pTemp;
}

STLVECTOR vectorNormalize(STLVECTOR &iVector)
{
	STLVECTOR vector_normal = { 0. };
	double norm = iVector.x * iVector.x + iVector.y *iVector.y + iVector.z*iVector.z;
	if (norm <= TOLSQUARELENGTH)
		return vector_normal; // too short!
	if (fabs(norm - 1.) < TOLSQUARELENGTH)
		return iVector; // 已是单位向量，不需要单位化
	norm = 1./sqrt(norm);
	vector_normal.x = iVector.x * norm;
	vector_normal.y = iVector.y * norm;
	vector_normal.z = iVector.z * norm;

	return vector_normal;
}

STLVECTOR operator-(STLPNT3D &iBegin, STLPNT3D &iEnd)
{
	STLVECTOR v;
	v.x = iEnd.x - iBegin.x;
	v.y = iEnd.y - iBegin.y;
	v.z = iEnd.z - iBegin.z;
	return v;
}

STLVECTOR operator-(STLVECTOR &iVector)
{
	STLVECTOR oVector;
	oVector.x = -iVector.x;
	oVector.y = -iVector.y;
	oVector.z = -iVector.z;
	return oVector;
}

STLVECTOR operator+(STLVECTOR &iVector1, STLVECTOR &iVector2)
{
	STLVECTOR v;
	v.x = iVector1.x + iVector2.x;
	v.y = iVector1.y + iVector2.y;
	v.z = iVector1.z + iVector2.z;
	return v;
}


STLVECTOR operator*(double iScalar, STLVECTOR & iVector)
{
	STLVECTOR v;
	v.x = iScalar * iVector.x;
	v.y = iScalar * iVector.y;
	v.z = iScalar * iVector.z;
	return v;
}

double operator*(STLVECTOR & iVector1, STLVECTOR & iVector2)
{
	double res = 0.;
	res = iVector1.x*iVector2.x + iVector1.y*iVector2.y + iVector1.z*iVector2.z;
	return res;
}

STLVECTOR operator^(STLVECTOR &iVectorU, STLVECTOR &iVectorV)
{
	VEC3D v1, v2, rtvec;
	memcpy(v1, &iVectorU, sizeof(PNT3D));
	memcpy(v2, &iVectorV, sizeof(PNT3D));

	mathVProduct(v1, v2, rtvec);

	STLVECTOR vector_w;
	memcpy(&vector_w, rtvec, sizeof(PNT3D));

	return vector_w;
}


// 线段与平面求交
// smf add 2022/9/06
int mathSegmentIntPln(PNT3D iPntOfSegment1, PNT3D iPntOfSegment2,  // 线段的两个端点
	PNT3D iPntOnPlane, VEC3D iNormPlane,  // 平面的法矢及平面上一点
	double iTolLength, double iTolAngle,  // 长度容差及角度容差
	PNT3D* oPntsOfIntersection) // 交点数组的指针
{
	int num_intersection_pnts = -1; // 初始化

	double distToPlane1 = mathDistPntPlnSide(iPntOfSegment1, iPntOnPlane, iNormPlane);
	double distToPlane2 = mathDistPntPlnSide(iPntOfSegment2, iPntOnPlane, iNormPlane);

	if (distToPlane1 * distToPlane2 > TOLSQUARELENGTH) // 线段在平面的一侧，无交
	{
		num_intersection_pnts = 0;
		return num_intersection_pnts;
	}

	if (fabs(distToPlane1) < TOLLENGTH &&
		fabs(distToPlane2) < TOLLENGTH) // 线段在平面上，两个交点
	{
		num_intersection_pnts = 2;
		memcpy(oPntsOfIntersection[0], iPntOfSegment1, sizeof(PNT3D));
		memcpy(oPntsOfIntersection[1], iPntOfSegment2, sizeof(PNT3D));
		return num_intersection_pnts;
	}

	PNT3D p;
	VEC3D v, v1;
	if (mathGetVecUnit(iPntOfSegment1, iPntOfSegment2, v1) == 0)
	{
		num_intersection_pnts = 0; // 两点十分靠近，0个交点？？？
		return num_intersection_pnts;
	}
	double acos_alpha = 0.;
	double dist = 0.;
	acos_alpha = mathOProduct(v1, iNormPlane);
	if (acos_alpha < 0) // 线段方向向量与平面法线夹角，并判断是否同向
	{
		v1[0] *= -1;
		v1[1] *= -1;
		v1[2] *= -1;
		memcpy(p, iPntOfSegment1, sizeof(PNT3D));
		dist = distToPlane1;
	}
	else
	{
		memcpy(p, iPntOfSegment2, sizeof(PNT3D));
		dist = distToPlane2;
	}
	memcpy(v, v1, sizeof(VEC3D));

	num_intersection_pnts = 1;

	acos_alpha = fabs(acos_alpha);
	double tmp = dist / acos_alpha;
	for (size_t i = 0; i < 3; i++)
	{
		oPntsOfIntersection[0][i] = p[i] - v[i] * tmp; // 计算线-面交点坐标
	}

	return num_intersection_pnts;
}

int mathPlnIntTri(
	PNT3D iPntOfTri1, PNT3D iPntOfTri2, PNT3D iPntOfTri3, // 三角形的三个顶点
	PNT3D iPntOnPlane, VEC3D iNormPlane,  // 平面上一点及平面的法矢
	double iTolLength, double iTolAngle,  // 长度容差及角度容差
	PNT3D* oPntsOfIntersection) // 交点数组的指针
{
	int num_intersection_pnts = -1; // 初始化

	num_intersection_pnts = 0;

	PNT3D iPntsOfTri[3];
	memcpy(iPntsOfTri[0], iPntOfTri1, sizeof(PNT3D));
	memcpy(iPntsOfTri[1], iPntOfTri2, sizeof(PNT3D));
	memcpy(iPntsOfTri[2], iPntOfTri3, sizeof(PNT3D));

	double distToPlane[3];
	for (size_t i = 0; i < 3; i++)
		distToPlane[i] = mathDistPntPlnSide(iPntsOfTri[i], iPntOnPlane, iNormPlane);

	// 判断三点是否都在平面上
	if (fabs(distToPlane[0]) <= iTolLength &&
		fabs(distToPlane[1]) <= iTolLength &&
		fabs(distToPlane[2]) <= iTolLength)
	{
		num_intersection_pnts = 3; // 三点都在平面上
		memcpy(oPntsOfIntersection[0], iPntOfTri1, sizeof(PNT3D));
		memcpy(oPntsOfIntersection[1], iPntOfTri2, sizeof(PNT3D));
		memcpy(oPntsOfIntersection[2], iPntOfTri3, sizeof(PNT3D));
		return num_intersection_pnts;
	}

	// 判断三点是否在平面同侧
	if ((distToPlane[0] < -iTolLength &&
		distToPlane[1] < -iTolLength &&
		distToPlane[2] < -iTolLength) ||
		(distToPlane[0] > iTolLength &&
		distToPlane[1] > iTolLength &&
		distToPlane[2] > iTolLength))
	{
		num_intersection_pnts = 0; // 三点在平面同侧，无交
		return num_intersection_pnts;
	}
	for (size_t i = 0; i < 3; i++)
	{
		VEC3D v;
		int num_int_pnts = 0;
		if (num_int_pnts = mathGetVecUnit(iPntsOfTri[i], iPntsOfTri[(i + 1) % 3], v) == 0) // 线段长度过短
		{
			continue;
		}

		PNT3D int_pnts[2] = {};
		// 线段(三角形的边)与平面求交
		num_int_pnts = mathSegmentIntPln(iPntsOfTri[i], iPntsOfTri[(i + 1) % 3],
									 	 iPntOnPlane, iNormPlane,  // 平面上一点及平面的法矢
										 iTolLength, iTolAngle,  // 长度容差及角度容差
										 int_pnts); // 交点数组

		//检查是否有重合的交点，去重
		for (size_t j = 0; j < num_int_pnts; j++)
		{
			if (num_intersection_pnts == 0)
			{
				memcpy(oPntsOfIntersection[0], int_pnts[j], sizeof(PNT3D));
				num_intersection_pnts++;
			}
			else
			{
				int k = 0;
				for (k = 0; k < num_intersection_pnts; k++)
				{
					if (mathSquareDist(int_pnts[j], oPntsOfIntersection[k]) <= TOLSQUARELENGTH) // 是重合点
					{
						k = 0;
						break;
					}
				}
				if (k == num_intersection_pnts) // 不是重合点
				{
					// 保存不重合的交点
					memcpy(oPntsOfIntersection[num_intersection_pnts], int_pnts[j], sizeof(PNT3D));
					num_intersection_pnts++;
				}
			}
		}
	}
	return num_intersection_pnts;
}

int mathPlnIntTri(
	STLPNT3D iSTLPntOfTri1, STLPNT3D iSTLPntOfTri2, STLPNT3D iSTLPntOfTri3, // 三角形的三个顶点
	STLPNT3D iSTLPntOnPlane, STLVECTOR iSTLNormPlane,  // 平面的法矢及平面上一点
	double iTolLength, double iTolAngle,  // 长度容差及角度容差
	STLPNT3D* oSTLPntsOfIntersection) // 交点数组的指针
{
	PNT3D iPntOfTri1, iPntOfTri2, iPntOfTri3, // 三角形的三个顶点
		iPntOnPlane;
	VEC3D iNormPlane;  // 平面的法矢及平面上一点
	PNT3D oPntsOfIntersection[3];

	memcpy(iPntOfTri1, &iSTLPntOfTri1, sizeof(PNT3D));
	memcpy(iPntOfTri2, &iSTLPntOfTri2, sizeof(PNT3D));
	memcpy(iPntOfTri3, &iSTLPntOnPlane, sizeof(PNT3D));
	memcpy(iPntOnPlane, &iSTLPntOfTri1, sizeof(PNT3D));
	int res = mathPlnIntTri(
		iPntOfTri1, iPntOfTri2, iPntOfTri3, // 三角形的三个顶点
		iPntOnPlane, iNormPlane,  // 平面的法矢及平面上一点
		iTolLength, iTolAngle,  // 长度容差及角度容差
		oPntsOfIntersection); // 交点数组的指针
	memcpy(oSTLPntsOfIntersection, oPntsOfIntersection, 3 * sizeof(PNT3D));
	return res;
}

double mathSquareDist(PNT3D p1, PNT3D p2)
{
	double squareDist = 0.;
	for (size_t i = 0; i < 3; i++)
	{
		double delta = p1[i] - p2[i];
		squareDist += delta * delta;
	}
	return squareDist;
}
