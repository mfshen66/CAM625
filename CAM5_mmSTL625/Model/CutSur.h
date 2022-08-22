#ifndef _CUTSUR_h_
#define _CUTSUR_h_

////////////////////////////////////////////////////////////////
// ���÷���:
// (1)cutsurCreate() : ����ʼֵ
// (2)cutsurMake() : ����ָ�����
// (3)cutsurFree() : �ͷſռ�
//--------------------------------------------------------------
typedef struct _cutsur CUTSUR ;
struct _cutsur
{
	SURFACE* surface ; // ���и������
	BOXUV boxuv ; // of surface
	BOX3D box ; // nt add 2010/3/15
	int n ; // 1 or 2 : �����и����������
	SURFACE* cut1 ; // �����и������1
	BOXUV boxuv1 ;
	BOX3D box1 ; // nt add 2010/3/15
	SURFACE* cut2 ; // �����и������2
	BOXUV boxuv2 ;
	BOX3D box2 ; // nt add 2010/3/15

	// nt add 2010/3/15
	CURVE* cutcur1 ; // intersection curve of surface/cut1
	INTERVAL intv1 ;
	CURVE* cutcur2 ; // intersection curve of surface/cut2
	INTERVAL intv2 ;

	double tol ; // ����ָ�����ľ���
	// stepu��stepv��������boxuv��ָ���ķ�Χ�������������Χ
	// ��[0,1]x[0,1]
	double stepu ; // ���ڵ�u=�����Ȳ������ڲ������ڵļ��
	double stepv ; // ���ڵ�v=�����Ȳ������ڲ������ڵļ��
	double step ; // ������surface��������
	int uvflag ; // 0(u=constant) or 1(v=constant)
	double uv ; // u or v
	CURVE* isocur ; // ��Ӧuvflag��uv��surface�ĵȲ�����
	INTERVAL interval ; // isocur��interval
	int nSection ;
	double (*ss)[2] ; // surface�Ĳ������ֱ��Ӧ��cut1��cut2
	int m ; // �õ�NURBS������
	BSSUR* bss[3] ;
} ;

/*
 *	CutSur.cpp
 */
CUTSUR* cutsurCreate(SURFACE* surface,
					 BOXUV* boxuv,
					 BOX3D* box,
					 SURFACE* cut1,
					 BOXUV* boxuv1,
					 BOX3D* box1,
					 SURFACE* cut2,
					 BOXUV* boxuv2,
					 BOX3D* box2,
					 double tol) ;
int cutsurFree(CUTSUR* cutsur) ;
int cutsurMake(CUTSUR* cutsur) ;
////////////////////////////////////////////////////////////////

#endif