#ifndef _DLoop_h_
#define _DLoop_h_

////////////////////////////////////////////////////////////////
// DCURVE��ɢ���ߵķ�ʸ���������Ȼ��ʸ
#define DLOOP_MAX 100000

typedef struct _dloop DLOOP ;
struct _dloop
{
	DLOOP* prev ;
	DLOOP* next ;
	int n ;
	DCURVE** dcurves ; // ������Ȼ������β����, ��Ӧ�Ĳ����������ڲ����������⻷��ʱ�룬�ڻ�˳ʱ��
} ;

/*
 *	DLoop.cpp
 */
DLOOP* dloopCreate(int n) ;
void dloopFree(DLOOP* dloop) ;
void dloopsFree(DLOOP* loops) ;
int dloopIsClose(DLOOP* dloop, double tol) ;
int dloopsIsClose(DLOOP* loops, double tol) ;
int dloopsCut(DLOOP* loops, DCURVE* tool, double tol, int res, DLOOP** lps, int* error) ;
////////////////////////////////////////////////////////////////

#endif