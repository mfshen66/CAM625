/*	2010/3/13 nt
 *	implementation file of cut surface algorithm
 */
#include "StdAfx.h"
#include "CutSur.h"

////////////////////////////////////////////////////////////////
// cut surface
// 2010/3/13 nt
// create CURSUR
CUTSUR* cutsurCreate(SURFACE* surface,
					 BOXUV* boxuv,
					 BOX3D* box,
					 SURFACE* cut1,
					 BOXUV* boxuv1,
					 BOX3D* box1,
					 SURFACE* cut2,
					 BOXUV* boxuv2,
					 BOX3D* box2,
					 double tol)
{
	CUTSUR* cutsur ;
	cutsur = new CUTSUR ;
	cutsur->surface = surface ;
	if( boxuv )
		cutsur->boxuv = *boxuv ;
	if( box )
		cutsur->box = *box ;
	cutsur->n = 0 ;
	if( cut1 )
		(cutsur->n)++ ;
	cutsur->cut1 = cut1 ;
	if( box1 )
		cutsur->box1 = *box1 ;
	if( boxuv1 )
		cutsur->boxuv1 = *boxuv1 ;
	if( cut2 )
		(cutsur->n)++ ;
	cutsur->cut2 = cut2 ;
	if( boxuv2 )
		cutsur->boxuv2 = *boxuv2 ;
	if( box2 )
		cutsur->box2 = *box2 ;

	// nt add 2010/3/15
	cutsur->cutcur1 = NULL ;
	cutsur->intv1.t1 = 0. ;
	cutsur->intv1.t2 = 1. ;
	cutsur->cutcur2 = NULL ;
	cutsur->intv2.t1 = 0. ;
	cutsur->intv2.t2 = 1. ;

	cutsur->tol = tol ;
	cutsur->stepu = 1.e-3 ;
	cutsur->stepv = 1.e-3 ;
	cutsur->step  = 1.e-3 ;
	cutsur->uvflag = -1 ;
	cutsur->uv = 0. ;
	cutsur->isocur = NULL ;
	cutsur->interval.t1 = 0. ;
	cutsur->interval.t2 = 1. ;
	cutsur->nSection = 0 ;
	cutsur->ss = NULL ;
	cutsur->m = 0 ;
	cutsur->bss[0] = NULL ;
	cutsur->bss[1] = NULL ;
	cutsur->bss[2] = NULL ;

	return cutsur ;
}

int cutsurFree(CUTSUR* cutsur)
{
	int k ;

	if( cutsur )
	{
		if( cutsur->cutcur1 )
			entityFree(cutsur->cutcur1) ;
		if( cutsur->cutcur2 )
			entityFree(cutsur->cutcur2) ;
		if( cutsur->isocur )
			entityFree(cutsur->isocur) ;
		if( cutsur->ss )
			delete [](cutsur->ss) ;
		for( k = 0 ; k < cutsur->m ; k++ )
		{
			if( cutsur->bss[k] )
				bssurFree(cutsur->bss[k]) ;
		}
		delete cutsur ;
		return ERSUCSS ;
	}
	else
		return ERUNSUC ;
}
//--------------------------------------------------------------
// nt add 2010/3/15
int cutsurCut(CUTSUR* cutsur)
{
	return ERSUCSS ;
}
//--------------------------------------------------------------
SURFACE* cutsurGetCutSur(CUTSUR* cutsur, int k, BOXUV* boxuv)
{
	if( k < 1 )
	{
		*boxuv = cutsur->boxuv1 ;
		return cutsur->cut1 ; // �и���k
	}
	else
	{
		*boxuv = cutsur->boxuv2 ;
		return cutsur->cut2 ; // �и���k
	}
}

CURVE* cutsurGetCutCur(CUTSUR* cutsur, int k, INTERVAL* interval)
{
	if( k < 1 )
	{
		*interval = cutsur->intv1 ;
		return cutsur->cutcur1 ; // �и���k
	}
	else
	{
		*interval = cutsur->intv2 ;
		return cutsur->cutcur2 ; // �и���k
	}
}

// 2010/3/13 nt
int cutsurEstimateStep(CUTSUR* cutsur)
{
	int exact ;
	double a1 = 0., a2 = 0., a, d ;
	PNT3D p, q ;
	VEC3D du, dv, ds, dt ;
	BSSUR* nurbs ;

	if( cutsur ||
		cutsur->surface )
	{
		if( surfaceToNurbs(cutsur->surface, // get NURBS approximation
						   &(cutsur->boxuv),
						   &nurbs,
						   &exact) != ERSUCSS )
			return ERUNSUC ;
		if( bssurGetMaxiStepLin(nurbs, 
								cutsur->tol,
								&(cutsur->stepu),
								&(cutsur->stepv)) != ERSUCSS )
		{
			bssurFree(nurbs) ;
			return ERUNSUC ;
		}

		// ����Ƿ�u��v�ߵ���
		surfaceEvalDer1O(cutsur->surface,
						 0.5*(cutsur->boxuv.min[0]+cutsur->boxuv.max[0]),
						 0.5*(cutsur->boxuv.min[1]+cutsur->boxuv.max[1]),
						 p,
						 du,
						 dv) ;
		mathUniVec(du, MIN_DBL) ;
		mathUniVec(dv, MIN_DBL) ;
		bssurEvalDer1O(nurbs, 0.5, 0.5, q, ds, dt) ;
		mathUniVec(ds, MIN_DBL) ;
		mathUniVec(dt, MIN_DBL) ;
		a = mathGetAngleUnit(du, ds) ;
		if( a > 0.5*PI1 )
			a = PI1-a ;
		a1 += a ;
		a = mathGetAngleUnit(dv, dt) ;
		if( a > 0.5*PI1 )
			a = PI1-a ;
		a1 += a ;
		a = mathGetAngleUnit(du, dt) ;
		if( a > 0.5*PI1 )
			a = PI1-a ;
		a2 += a ;
		a = mathGetAngleUnit(dv, ds) ;
		if( a > 0.5*PI1 )
			a = PI1-a ;
		a2 += a ;
		if( a1 > a2 ) // ����u��v
		{
			d = cutsur->stepu ;
			cutsur->stepu = cutsur->stepv ;
			cutsur->stepv = d ;
		}

		return ERSUCSS ;
	}
	else
		return ERUNSUC ;
}

// Ҫ��stepu��stepv��uvflag�Ѿ�����
int cutsurCalNumOfSection(CUTSUR* cutsur)
{
	int i ;

	if( cutsur ||
		cutsur->surface )
	{
		cutsur->step = cutsur->uvflag<1?cutsur->stepu:cutsur->stepv ;
		cutsur->nSection = (int)ceil(1./mathMAX(cutsur->step, 1.e-6))+2 ;
		if( cutsur->nSection < 3 )
			return ERUNSUC ;
		cutsur->step = (cutsur->boxuv.max[cutsur->uvflag]-
			            cutsur->boxuv.min[cutsur->uvflag])/
			           (cutsur->nSection-1) ;
		if( cutsur->step < MIN_DBL )
			return ERUNSUC ;
		if( cutsur->ss )
			delete [](cutsur->ss) ;
		cutsur->ss = new double[cutsur->nSection][2] ;
		for( i = 0 ; i < cutsur->nSection ; i++ )
		{
			cutsur->ss[i][0] = MAX_DBL ;
			cutsur->ss[i][1] = MAX_DBL ;
		}
		return ERSUCSS ;
	}
	else
		return ERUNSUC ;
}
//--------------------------------------------------------------
// ����uvflag��uv����isocur
int cutsurMakeIsocur(CUTSUR* cutsur)
{
	PNT3D dege_p ;

	if( cutsur )
	{
		if( cutsur->isocur ) // if already exist, release it first
		{
			entityFree(cutsur->isocur) ;
			cutsur->isocur = NULL ;
		}
		if( surfaceGetIsoCurve(cutsur->surface, // ����һ���Ȳ�����
							   cutsur->uvflag,
							   cutsur->uv,
							   &(cutsur->isocur), 
							   &(cutsur->interval),
							   dege_p) == ERSUCSS &&
			cutsur->isocur )
			return ERSUCSS ;
		else
			return ERUNSUC ;
	}
	else
		return ERUNSUC ;
}

int cutsurFreeIsocur(CUTSUR* cutsur)
{
	if( cutsur &&
		cutsur->isocur )
	{
		entityFree(cutsur->isocur) ;
		cutsur->isocur = NULL ;
	}
	return ERSUCSS ;
}
//--------------------------------------------------------------
/*	2010/3/12 nt
 *	Ҫ���Ѿ�������˵Ȳ�����isocur
 *	����cutsur->isocur/cutcur1(or 2)������
 *	cutsur->uvflag = 0(u=����) or 1(v=����)
 *  k=0:cut1
 *	k=1:cut2
 *	intpt->uv[0] : cutsur->cutcur1(or 2)�ĳ�ʼ����
 *	intpt->st[0] : cutsur->isocur�ĳ�ʼ����
 */
int cutsurIttIso(CUTSUR* cutsur, 
				 int k, 
				 INTPT* intpt)
{
	int tan ;
	if( k < 1 )
		return curveItt(cutsur->cutcur1, // cutcur1/isocur
						cutsur->isocur,
						MIN_LEN,
						MIN_ANG,
						intpt->p,
						&(intpt->uv[0]),
						&(intpt->st[0]),
						&tan) ;
	else
		return curveItt(cutsur->cutcur2,  // cutcur2/isocur
						cutsur->isocur,
						MIN_LEN,
						MIN_ANG,
						intpt->p,
						&(intpt->uv[0]),
						&(intpt->st[0]),
						&tan) ;
}
//--------------------------------------------------------------
// 2010/3/13 nt
// ȡ���и�����ĵȲ����ߣ��ü������ɽ����ߣ�
// ע��Ҫ���Ѿ������stepu��stepv
int cutsurMakeSections(CUTSUR* cutsur)
{
	int i, k, uvflag, ok ;
	INTPT* intpts = NULL ;
	INTERVAL interval ;
	CURVE* cutcur ;

	if( cutsur == NULL ||
		cutsur->surface == NULL ||
		cutsur->cut1 == NULL )
		return ERUNSUC ;

	// �ֱ𰴲���u��v=����ȥ���Բü�����
	ok = 0 ; // ��δ�ü������ɽ�����
	for( uvflag = 0 ; uvflag < 2 ; uvflag++ )
	{
		cutsur->uvflag = uvflag ;
		if( cutsurCalNumOfSection(cutsur) != ERSUCSS )
			return ERUNSUC ;

		// ���������ָ���
		for( k = 0 ; k < 2 ; k++ )
		{
			cutcur = cutsurGetCutCur(cutsur, k, &interval) ; // �ָ���
			if( cutcur == NULL )
				break ;
			// ȡ����surface��һ���߽���, boxuv.min[uvflag]
			cutsur->uv = cutsur->boxuv.min[uvflag] ;
			if( cutsurMakeIsocur(cutsur) != ERSUCSS ) //|| // ȡһ���߽���
				//curveInt(cutcur, // ����߽���ָ���cutcur1(2)������
				//		 &interval,
				//		 cutsur->isocur, 
				//		 &(cutsur->interval),
				//		 &intpts) != ERSUCSS )
				return ERUNSUC ;
			if( intpts )
			{
				if( intpts->next == NULL ) // �õ�Ψһһ������
				{
					cutsur->ss[0][k] = intpts->st[0] ;
					for( i = 1 ; i < cutsur->nSection ; i++ )
					{
						cutsur->uv += cutsur->step ;
						if( cutsurMakeIsocur(cutsur) != ERSUCSS )
							return ERUNSUC ;
						if( cutsurIttIso(cutsur, // isocur/cut1��cut2
										 k,
										 intpts) != IDCNVGN )
							break ;
						cutsur->ss[i][k] = intpts->st[0] ;
					}
					if( i < cutsur->nSection ) // fail to find all
					{
						for( i = 0 ; i < cutsur->nSection ; i++ )
							cutsur->ss[i][k] = MAX_DBL ;
					}
					else
						ok++ ; // �Ѿ��ü���һ��������
				}
				mathFreBDChns(intpts) ;
				intpts = NULL ;
			}
		}
		if( ok > 0 )
			return ERSUCSS ; // found
	}

	return ERSUCSS ;
}

// nt add 2010/3/14
// ������cutsurMakeSections()�ٵ��ô˺���
// ʹss[i][0]<ss[i][1]
int cutsurOrder(CUTSUR* cutsur)
{
	int i ;
	double t ;

	for( i = 0 ; i < cutsur->nSection ; i++ )
	{
		if( cutsur->ss[i][0] > cutsur->ss[i][1] )
		{
			t = cutsur->ss[i][0] ;
			cutsur->ss[i][0] = cutsur->ss[i][1] ;
			cutsur->ss[i][1] = t ;
		}
	}

	return ERSUCSS ;
}
//--------------------------------------------------------------
// 2010/3/14 nt
// in the following example, uvflag = 1
//           ----|----------|------ i=nSection-1
//           ----|----------|------
//           .
//  v        .
//  |        .
//  --->u    ----|----------|------ i=1
// boxuv.min ----|----------|------ i=0
//            k=0     k=1      k=2
//              cut1       cut2
//             ss[][0]    ss[][1]
int cutsurGetInterval(CUTSUR* cutsur, 
					  int k, 
					  int i, 
					  INTERVAL* interval)
{
	if( cutsur &&
		k >= 0 &&
		k <= 2 &&
		i >= 0 &&
		i < cutsur->nSection &&
		interval )
	{
		if( k == 0 )
		{
			interval->t1 = cutsur->boxuv.min[1-cutsur->uvflag] ;
			interval->t2 = cutsur->ss[i][0] ;
		}
		else
		if( k == 1 )
		{
			interval->t1 = cutsur->ss[i][0] ;
			if( cutsur->cut2 ) // nt modify 2016/7/12 ����cut2ΪNULL
				interval->t2 = cutsur->ss[i][1] ;
			else
				interval->t2 = cutsur->boxuv.max[1 - cutsur->uvflag];
		}
		else
		{
			interval->t1 = cutsur->ss[i][1] ;
			interval->t2 = cutsur->boxuv.max[1-cutsur->uvflag] ;
		}
		if( interval->t2-interval->t1 < MIN_DBL )
			return ERUNSUC ;
		return ERSUCSS ;
	}
	else
		return ERUNSUC ;
}

/*	2010/3/14 nt
 *	��������������Χ�����������Ȳ����߹����������
 *	uvflag=0:ȡu=�����ĵȲ����ߣ�
 *	uvflag=1:ȡv=�����ĵȲ����ߣ�
 *	ע����Щ�Ʋ������ڲ������ǵȼ���
 *	ss[i][0]��ss[i][1]��ʾ��i���Ȳ����ߵ������ָ���Ӧ�Ĳ���ֵ
 *	ss[i][1]=MAX_DBL��ʾ�޴˷ָ��
 *	����������ٷ�������NURBS����
 *	Ҫ���Ѿ�������cutsurMakeSections()��cutsurOrder()
 *	���Ϊ:
 *		(1)cutsur->bss[0],
 *		(2)cutsur->bss[1],
 *		(3)cutsur->bss[2].
 */
int cutsurMakeLoft(CUTSUR* cutsur)
{
	return ERUNSUC ;
}
//--------------------------------------------------------------
// 2010/3/14 nt
int cutsurMake(CUTSUR* cutsur)
{
	if( cutsurCut(cutsur) != ERSUCSS ||
		cutsurEstimateStep(cutsur) != ERSUCSS ||
		cutsurMakeSections(cutsur) != ERSUCSS ||
		cutsurOrder(cutsur) != ERSUCSS ||
		cutsurMakeLoft(cutsur) != ERSUCSS )
		return ERUNSUC ;
	else
		return ERSUCSS ;
}
////////////////////////////////////////////////////////////////
