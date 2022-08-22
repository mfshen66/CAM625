/*	2010/3/30 nt
 *	the head file of tool revolve surface
 */
#ifndef _TRS_h_
#define _TRS_h_

////////////////////////////////////////////////////////////////
// TRS : ������ת��(��z����ת)
// ע�⣺��TRS���йؼ�����ֻ�õ���TRS->curve��xz����
//       TRS->curveһ�㶨��һ���ֲ�����ϵ��
typedef struct _trs TRS ;
struct _trs
{
	CURVE* curve ; // ����
	INTERVAL interval ;
	BOX3D box ;
	STRPT* strpt ;
	FACET* facet ;
	int n ; // ��ɢʱ��һ�ֶܷ��ٷ�, n>=3
} ;

/*
 *	TRS.cpp
 */
TRS* trsCreate(CURVE* curve, INTERVAL* interval) ;
int trsFree(TRS* trs) ;
int trsCalBox(TRS* trs) ;
int trsGetBox(TRS* trs, BOX3D* box) ;
int trsDisc(TRS* trs, double dTol, double dAng, int n) ;
int trsDraw(TRS* trs, void* pVI, int drawMode, int color) ;
int trsPick(TRS* trs, PINFO* pi) ; // return 0=error;1=picked,2=not picked
int trsSerialize(TRS* trs, CArchive& ar) ;
////////////////////////////////////////////////////////////////
#endif