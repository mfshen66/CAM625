/*	2021/7/2 nt
 *	implementation file of discrete loop
 */
#include "StdAfx.h"
#include "DCurve.h"
#include "DLoop.h"

////////////////////////////////////////////////////////////////
/*	2021/7/2 nt
 *	create DLOOP
 */
DLOOP* dloopCreate(int n)
{
	DLOOP* dloop = NULL ;

	dloop = (DLOOP*)malloc(sizeof(DLOOP)) ;
	dloop->prev = NULL ;
	dloop->next = NULL ;
	dloop->n = n ;
	if( n > 0 )
		dloop->dcurves = (DCURVE**)malloc(sizeof(DCURVE*)*n) ;
	else
		dloop->dcurves = NULL ;

	return dloop ;
}

void dloopFree(DLOOP* dloop)
{
	int i ;

	if( dloop )
	{
		if( dloop->dcurves )
		{
			for( i = 0 ; i < dloop->n ; i++ )
			{
				if( dloop->dcurves[i] )
					dcurveFree(dloop->dcurves[i]) ;
			}
			free(dloop->dcurves) ;
		}
		free(dloop) ;
	}

	return ;
}

void dloopsFree(DLOOP* loops)
{
	DLOOP* temp ;

	while(loops)
	{
		temp = loops->next ;
		dloopFree(loops) ;
		loops = temp ;
	}

	return ;
}

int dloopIsClose(DLOOP* dloop, double tol)
{
	int i ;
	double d ;
	PNT3D b, e ;

	for( i = 0 ; i < dloop->n ; i++ )
	{
		dcurveGetEndPt(dloop->dcurves[i>0?(i-1):(dloop->n-1)], e) ;
		dcurveGetBeginPt(dloop->dcurves[i], b) ;
		d = mathDist(b, e) ;
		if( d > tol )
			return ID_NO ;
	}

	return ID_YES ;
}

int dloopsIsClose(DLOOP* loops, double tol)
{
	DLOOP* temp ;

	for( temp = loops ; temp ; temp = temp->next )
	{
		if( dloopIsClose(temp, tol) == ID_NO )
			return ID_NO ;
	}

	return ID_YES ;
}

// ����DLOOP
// ���������
//     dcurves: DCURVE����
//     seed: ��seedΪ��һ��DCURVE��ʼ����
//	   tol: �жϵ��غϵ��ݲ�
// ���������
//     error: ������
// ����:
//     DLOOP: ��������DCURVE���ɵĻ�
//	   *error:0=����,1=�������,2=��ʸ����,3=�˻�,4=���պ�,5=�������ѭ������
// ע�⣺
//     1)seed����dcurves��
//     2)�����dcurves��������������seed����ص�DCURVE��ɻ����أ�������ص�
//     DCURVEҪ��dcurves�з�����������û��������, ��dcurves��seed�����޸ġ�
//     ���ͷ�,
//     3)seed : b---->e ��������Ϊ ->
DLOOP* dloopFind(DCURVE** dcurves, DCURVE* seed, double tol, int* error)
{
	int dL, n = 1 ;
	double min, a ;
	PNT3D b, e, B ;
	VEC2D v ;
	VEC3D X, Y, Z, V ;
	DCURVE* dcurve = NULL, *tail = NULL, *found ;
	DLOOP* dloop = NULL ;

	if( error )
		*error = 0 ;
	if( seed == NULL )
	{
		if( error )
			(*error) |= 1 ; // �������
		return NULL ;
	}
	if( dcurveIsClose(seed, tol) == ID_YES )
	{
		dloop = dloopCreate(1) ;
		dloop->dcurves[0] = seed ;
		return dloop ;
	}
	if( dcurves == NULL )
	{
		if( error )
			(*error) |= 1 ; // �������
		return NULL ;
	}
	dcurveGetBeginPt(seed, b) ;
	seed->next = NULL ;
	tail = seed ; // seed is head

	for( dL = 0 ; dL < DLOOP_MAX ; dL++ )
	{
		dcurveGetEndTangent(tail, e, X) ;
		if( mathDist(b, e) < tol)
			break ;
		memcpy(Z, tail->ns[tail->np-1], sizeof(VEC3D)) ;
		mathPrjVecPln(X, Z, X) ;
		if( mathUniVec(X, MIN_DBL) != ERSUCSS ) // x axis
		{
			if( error )
				(*error) |= 2 ; // ��ʸ����
			goto ExceExit ;
		}
		mathVProduct(Z, X, Y) ;
		if( mathUniVec(Y, MIN_DBL) != ERSUCSS ) // y axis
		{
			if( error )
				(*error) |= 2 ; // ��ʸ����
			goto ExceExit ;
		}

		found = NULL ;
		min = MAX_DBL ;
		for( dcurve = *dcurves ; dcurve ; dcurve = dcurve->next )
		{
			if( tail->flag != 0 && tail->flag == -dcurve->flag ) // ��Ե�
				continue ;
			dcurveGetBeginTangent(dcurve, B, V) ; // dcurve�����
			if( mathDist(e, B) < tol )
			{
				mathPrjVecPln(V, Z, V) ;
				if( mathUniVec(V, MIN_DBL) != ERSUCSS )
				{
					if( error )
						(*error) |= 2 ; // ��ʸ����
					goto ExceExit ;
				}
				v[0] = V[0]*X[0]+V[1]*X[1]+V[2]*X[2] ;
				v[1] = V[0]*Y[0]+V[1]*Y[1]+V[2]*Y[2] ;
				a = mathGetAngleX2D(v) ;
				if( fabs(a-PI1) < MIN_ANG )
				{
					if( error )
						(*error) |= 4 ; // �˻�
					goto ExceExit ;
				}
				a = a<PI1?PI1-a:(3*PI1-a) ;
				if( min > a )
				{
					found = dcurve ;
					min = a ;
				}
			}
		}
		if( found )
		{
			*dcurves = (DCURVE*)mathDelItemInSDChns(found, *dcurves) ;
			tail->next = found ;
			found->next = NULL ;
			tail = found ;
			n++ ;
		}
		else
			goto ExceExit ;
	}
	if( dL >= DLOOP_MAX )
	{
		if( error )
			(*error) |= 8 ; // ������������
		goto ExceExit ;
	}

	dloop = dloopCreate(n) ;
	for( n = 0, tail = seed ; tail ; tail = tail->next, n++ )
		dloop->dcurves[n] = tail ;
	return dloop ;

ExceExit:
	*dcurves = (DCURVE*)mathInsSDChnsAtHead(seed->next, *dcurves) ;
	return NULL ;
}

// ��DCURVE�ü�DLOOP
// �������:
//     loops: DLOOP����
//     tool: ���ڲü�loops��DCURVE
//     tol: ���غ��ݲ�
//     res:res&1=1����tool���Ļ�,res&2=1����tool�Ҳ�Ļ�
// �������:
//     *lps: DLOOP����
//	   *error: (*error)&1=�������
//			   (*error)&2=��ʸ����
//			   (*error)&4=�˻�
//		       (*error)&8=������������
//			   (*error)&64=�޽���
//			   (*error)&128=�󽻴���
// ����:
//	   ERUNSUC=ʧ��,ERSUCSS=�ɹ�
// ע��:
//     1)δ�޸ġ��ͷ�loops��tool
//     2)���⴦��tool�Ǳպϵ����
//     3)lps�������ɵ�
int dloopsCut(DLOOP* loops,
			  DCURVE* tool,
			  double tol,
			  int res,
			  DLOOP** lps,
			  int* error)
{
	int i, rt = ERUNSUC, flag = 1, E ;
	double s ;
	DCURVE* all = NULL, *dcurve, *seed ;
	DLOOP* dloop ;
	INTPT* intpts = NULL, *intpt = NULL ;
	DCTRIM dct ;

	if( loops == NULL ||
		tool == NULL ||
		lps == NULL ||
		error == NULL )
		return ERUNSUC ;
	*lps = NULL ;
	*error = 0 ;

	// trim loops, �߽���ɢ�����ڽ��㴦�ü���С��
	for( dloop = loops ; dloop ; dloop = dloop->next )
	{
		for( i = 0 ; i < dloop->n ; i++ )
		{
			dcurveTrim(dloop->dcurves[i], tool, tol, &dct) ; // trim dcurve
			if( dct.error != 0 )
				(*error) |= dct.error ; // �󽻴���
			if( dct.dcurves )
				all = (DCURVE*)mathInsSDChnsAtHead(dct.dcurves, all) ;
			else
			{
				dcurve = dcurveCopy(dloop->dcurves[i]) ;
				all = (DCURVE*)mathInsItemInSDChns(dcurve, all) ;
			}
			if( dct.intpts )
				intpts = (INTPT*)mathInsBDChnsAtHead(dct.intpts, intpts) ;
			dctrimInit(&dct) ;
		}
	}
	if( all == NULL ||
		intpts == NULL )
	{
		(*error) |= 64 ; // �޽���
		goto ExceExit ;
	}

	// trim tool, tool�ڽ��㴦�ü���С��
	for( intpt = intpts ; intpt ; intpt = intpt->next ) // swap uv and st
		memcpy(intpt->uv, intpt->st, sizeof(double[2])) ;
	intptFilter(&intpts, tol) ;
	if(	intpts == NULL )
	{
		(*error) |= 64 ; // �޽���
		goto ExceExit ;
	}
	intpt = intpts ;
	// ���ܿ��Ļ�պϵ���������Ǵӵ�һ�����㿪ʼ
	s = intpt->uv[0] ;
	for( intpt = intpt->next ; intpt ; intpt = intpt->next, flag++ )
	{
		if( res&1 )
		{
			dcurve = dcurveMake(tool, s, intpt->uv[0], tol) ;
			dcurve->flag = flag ;
			dcurve->next = all ;
			all = dcurve ;
		}
		if( res&2 )
		{
			dcurve = dcurveCopy(dcurve) ;
			dcurveRev(dcurve, 0) ;
			dcurve->flag = -flag ;
			dcurve->next = all ;
			all = dcurve ;
		}
		s = intpt->uv[0] ;
	}
	if( dcurveIsClose(tool, tol) == ID_YES ) // �պϵ��������Ҫ����һ������
	{
		if( res&1 )
		{
			dcurve = dcurveMake(tool, s, intpts->uv[0], tol) ;
			dcurve->flag = flag ;
			dcurve->next = all ;
			all = dcurve ;
		}
		if( res&2 )
		{
			dcurve = dcurveCopy(dcurve) ;
			dcurveRev(dcurve, 0) ;
			dcurve->flag = -flag ;
			dcurve->next = all ;
			all = dcurve ;
		}
	}

	// link loop
	while(1)
	{
		for( seed = NULL, dcurve = all ; dcurve ; dcurve = dcurve->next )
		{
			if( dcurve->flag == 0 ) // DCURVE from loops,����tool��ȡDCURVE
			{
				all = (DCURVE*)mathDelItemInSDChns(dcurve, all) ;
				seed = dcurve ;
				break ;
			}
		}
		if( seed == NULL )
			break ;
		dloop = dloopFind(&all, seed, tol, &E) ;
		if( E > 0 )
			(*error) |= E ;
		if( dloop )
			*lps = (DLOOP*)mathInsItemInBDChns(dloop, *lps) ;
		else
			dcurveFree(seed) ;
	}
	rt = ERSUCSS ;
	
ExceExit:
	if( intpts )
		mathFreBDChns(intpts) ;
	if( all )
		dcurvesFree(all) ;

	return rt ;
}
////////////////////////////////////////////////////////////////
