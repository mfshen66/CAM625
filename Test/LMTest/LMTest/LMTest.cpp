// LMTest.cpp: 主项目文件。

#include "stdafx.h"

////////////////////////////////////////////////////////////////
//  Example program that shows how to use levmar in order to fit the three-
//  parameter exponential model x_i = p[0]*exp(-p[1]*i) + p[2] to a set of
//  data measurements; example is based on a similar one from GSL.
//
//  Copyright (C) 2008-11 Manolis Lourakis (lourakis at ics forth gr)
//  Institute of Computer Science, Foundation for Research & Technology - Hellas
//  Heraklion, Crete, Greece.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
// random number in [0,1]
double rand01()
{
	return (double)rand()/RAND_MAX ;
}
//--------------------------------------------------------------
// structure for passing user-supplied data to the objective function and its Jacobian
typedef struct _lmd LMD ;
struct _lmd
{
	int n ; // number of point
	double (*ps)[3] ; // point array which need fitting
} ;

LMD* lmdCreate(int n)
{
	LMD* lmd = (LMD*)malloc(sizeof(LMD)) ;

	if( lmd == NULL )
		return NULL ;
	lmd->n = n ;
	lmd->ps = NULL ;
	if( n > 0 )
		lmd->ps = (double(*)[3])malloc(n*sizeof(double[3])) ;

	return lmd ;
}

void lmdFree(LMD* lmd)
{
	if( lmd )
	{
		if( lmd->ps )
			//free(lmd->ps) ;
			delete []lmd->ps ;
		//free(lmd) ;
		delete lmd ;
	}

	return ;
}
//--------------------------------------------------------------
// model to be fitted to measurements
// model g(p) = sum (fi(p)-xi)^2, i from 0 to n-1
// F(p) = (f0(p), f1(p), ..., fn-1(p)'
void func(double* p, double* x, int m, int n, void* data)
{
	int i ;
	double dx, dy, r2 = p[2]*p[2] ; // r*r
	LMD* d = (LMD*)data ;

	for( i = 0 ; i < n ; i++ )
	{
		dx = p[0]-d->ps[i][0] ;
		dy = p[1]-d->ps[i][1] ;
		x[i]=dx*dx+dy*dy-r2 ;
	}

	return ;
}

// Jacobian matrix:
// | df0/dp[0]   df0/dp[1]   ... df0/dp[m-1]   |
// | df1/dp[0]   df1/dp[1]   ... df1/dp[m-1]   |
// ...
// | dfn-1/dp[0] dfn-1/dp[1] ... dfn-1/dp[m-1] |
void df(double* p, double* jac, int m, int n, void* data)
{   
	int i, I ;
	LMD* d = (LMD*)data ;

	// fill Jacobian row by row
	for( i = I = 0 ; i < n; i++ )
	{
		jac[I++] = 2*(p[0]-d->ps[i][0]) ;
		jac[I++] = 2*(p[1]-d->ps[i][1]) ;
		jac[I++] = -2*p[2] ;
	}

	return ;
}
//--------------------------------------------------------------
int main()
{
	int i, n = 40, m = 3, rt ; // 40 measurements, 3 parameters
	//double p[3], x[40], opts[5], info[10] ;
	double *p, *x, *opts, *info, r, a ; // nt add 2022/3/6
	LMD* data ;

	// nt add 2022/3/6, 原因是用数组，在debug时有问题，非debug运行好像正常!
	p = (double*)malloc(m*sizeof(double)) ;
	x = (double*)malloc(n*sizeof(double)) ;
	opts = (double*)malloc(5*sizeof(double)) ;
	info = (double*)malloc(10*sizeof(double)) ;
	data = lmdCreate(n) ;

	INIT_RANDOM(0) ;
	r = 100. ;
	for( i = 0 ; i < n ; i++ )
	{
		a = PI2*rand01() ;
		data->ps[i][0] = r*cos(a)+0.01*rand01() ;
		data->ps[i][1] = r*sin(a)+0.01*rand01() ;
		x[i] = 0. ;
	}

	// initial parameters estimate:
	p[0] = 10. ;
	p[1] = 20. ;
	p[2] = 15. ;

	// optimization control parameters
	opts[0] = LM_INIT_MU ; // 1.e-3
	opts[1] = 1e-15 ;
	opts[2] = 1e-15 ;
	opts[3] = 1e-20 ;
	opts[4] = LM_DIFF_DELTA ; 

	// invoke the optimization function
	rt = dlevmar_der(func, df, p, x, m, n, 1000, opts, info, NULL, NULL, data) ;
	//ret=dlevmar_dif(func, p, x, m, n, 1000, opts, info, NULL, NULL, &data) ;
	printf("Levenberg-Marquardt returned in %g iter, reason %g, sumsq %g [%g]\n", info[5], info[6], info[1], info[0]);
	printf("Best fit parameters: %.7g %.7g %.7g\n", p[0], p[1], p[2]);

	// nt add 2022/3/6
	lmdFree(data) ;
	free(p) ;
	free(x) ;
	free(opts) ;
	free(info) ;
	system("pause");

	return 1 ;
}
