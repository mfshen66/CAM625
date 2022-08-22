#pragma once

////////////////////////////////////////////////////////////////
// structure of boundary
typedef struct _bnd_cur_node BNDNODE ; // boundary curve
struct _bnd_cur_node
{
	CURVE* curve ;
	INTERVAL interval ;
	BOX3D box ;
	PNT3D vs[2] ;
} ;

/*
 *	SND.cpp
 */
BNDNODE* bndnodeCreate(CURVE* curve, INTERVAL* interval, BOX3D* box) ;
void bndnodeFree(BNDNODE* bndnode) ;
int bndnodeSnap(BNDNODE* bndnode, PNT3D p, double tol, PNT3D q, double* t, int* found) ;
//--------------------------------------------------------------
typedef struct _tr_sur_node TRNODE ; // trimmed surface node
struct _tr_sur_node
{
	SURFACE* surface ;
	BOXUV boxuv;
	FACET* facet ;
	BOX3D box ;
	PNT3D vs[4] ;
} ;

/*
 *	SND.cpp
 */
TRNODE* trnodeCreate(SURFACE* surface, FACET* facet, BOXUV* boxuv, BOX3D* box) ;
void trnodeFree(TRNODE* trnode) ;
int trnodeSnap(TRNODE* trnode, PNT3D p, double tol, PNT3D q, double uv[2], int* found) ;
//--------------------------------------------------------------
// ���÷���:
// (1)sndCreate() : ����ʼֵ
// (2)��������sndSetTr(),sndSetBnd() : ����
// (3)��������sndCal() : �����������
// (4)sndFree() : �ͷſռ�
//--------------------------------------------------------------
typedef struct _snd SND ; // trimmed surface nearest distance
struct _snd
{
	int nTr ; // �ü���������
	TRNODE** trs ;
	int nBnd ;
	BNDNODE** bnds ;
	double d ; // �ü������ʷֵĿռ����
	double r ; // �ռ䷶Χ���ڼ���ռ�㵽�ü�������������ʱ��Ҫ��õ������治����r
	double tol ; // �ж��Ƿ�Ϊ�������㷨����������
} ;

/*
 *	SND.cpp
 */
SND* sndCreate(int nTr, int nBnd, double d, double r, double tol) ;
int sndFree(SND* snd) ;
void sndSetTr(SND* snd, int i, SURFACE* surface, FACET* facet, BOXUV* boxuv, BOX3D* box) ;
void sndSetBnd(SND* snd, int i, CURVE* curve, INTERVAL* interval, BOX3D* box) ;
// p�ǿռ�һ�㣨Ҫ��õ��ڲü������Χ�е�һ����Χ�ڣ����ҳ�һ�����������*pgeo,
// q��*psur��һ�����p���, uv[0],uv[1]��q��*pgeo�ϵĲ���
// entityIsSurface(ENTITY* entity) ; // ID_NO:is not;ID_YES:is
int sndCal(SND* snd, PNT3D p, GEOMETRY** pgeo, PNT3D q, PNT2D uv) ;
////////////////////////////////////////////////////////////////
