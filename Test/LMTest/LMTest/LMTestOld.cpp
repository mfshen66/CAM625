// LMTest.cpp: 主项目文件。

#include "stdafx.h"

////////////////////////////////////////////////////////////////////////////////////
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
//
////////////////////////////////////////////////////////////////////////////////////

/* Gaussian noise with mean m and variance s, uses the Box-Muller transformation */
double gNoise(double m, double s)
{
	double r1, r2, val;

	r1=((double)rand())/(double)(RAND_MAX);
	r2=((double)rand())/(double)(RAND_MAX);

	val=sqrt(-2.0*log(r1))*cos(2.0*M_PI*r2);

	val=s*val+m;

	return val;
}

/* structure for passing user-supplied data to the objective function and its Jacobian */
struct xtradata
{
	char msg[128];

    /* more can be added here... */
};

/* model to be fitted to measurements: x_i = p[0]*exp(-p[1]*i) + p[2], i=0...n-1 */
void expfunc(double *p, double *x, int m, int n, void *data)
{
	int i;
	struct xtradata *dat;

	dat=(struct xtradata *)data;
	/* user-supplied data can now be accessed as dat->msg, etc */

	for(i=0; i<n; ++i)
	{
		x[i]=p[0]*exp(-p[1]*i) + p[2];
	}
}

/* Jacobian of expfunc() */
void jacexpfunc(double *p, double *jac, int m, int n, void *data)
{   
	int i, j ;
	struct xtradata *dat;

	dat=(struct xtradata *)data;
	/* user-supplied data can now be accessed as dat->msg, etc */
  
	/* fill Jacobian row by row */
	for(i=j=0; i<n; ++i)
	{
		jac[j++]=exp(-p[1]*i);
		jac[j++]=-p[0]*i*exp(-p[1]*i);
		jac[j++]=1.0;
	}
}

int main()
{
	int i, n=40, m=3, ret ; // 40 measurements, 3 parameters
	//double p[3], x[40], opts[5], info[10] ;
	double *p, *x, *opts, *info ; // nt add 2022/3/6
	struct xtradata data ;

	// nt add 2022/3/6, 原因是用数组，在debug时有问题，非debug运行好像正常!
	p = (double*)malloc(m*sizeof(double)) ;
	x = (double*)malloc(n*sizeof(double)) ;
	opts = (double*)malloc(5*sizeof(double)) ;
	info = (double*)malloc(10*sizeof(double)) ;

	/* generate some measurement using the exponential model with
	* parameters (5.0, 0.1, 1.0), corrupted with zero-mean
	* Gaussian noise of s=0.1
	*/
	INIT_RANDOM(0);
	x[0] = 1. ;
	for(i=0; i<n; ++i)
		x[i]=(5.0*exp(-0.1*i) + 1.0) + gNoise(0.0, 0.1);

	/* initial parameters estimate: (1.0, 0.0, 0.0) */
	p[0]=1.0; p[1]=0.0; p[2]=0.0;

	/* optimization control parameters; passing to levmar NULL instead of opts reverts to defaults */
	opts[0]=LM_INIT_MU; opts[1]=1E-15; opts[2]=1E-15; opts[3]=1E-20;
	opts[4]=LM_DIFF_DELTA; // relevant only if the finite difference Jacobian version is used 

	/* example of user-supplied data */
	strcpy_s(data.msg, 128, "Hello there!");

	/* invoke the optimization function */
	ret=dlevmar_der(expfunc, jacexpfunc, p, x, m, n, 1000, opts, info, NULL, NULL, (void *)&data); // with analytic Jacobian
	//ret=dlevmar_dif(expfunc, p, x, m, n, 1000, opts, info, NULL, NULL, (void *)&data); // without Jacobian
	printf("Levenberg-Marquardt returned in %g iter, reason %g, sumsq %g [%g]\n", info[5], info[6], info[1], info[0]);
	printf("Best fit parameters: %.7g %.7g %.7g\n", p[0], p[1], p[2]);

	// nt add 2022/3/6
	free(p) ;
	free(x) ;
	free(opts) ;
	free(info) ;

	return 1 ;
}
