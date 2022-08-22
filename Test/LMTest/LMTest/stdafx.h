// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

// TODO:  在此处引用程序需要的其他头文件
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#include "include\levmar.h"
#ifdef _cplusplus
extern "C"{
#include "include\f2c.h"
#include "include\clapack.h"
}
#endif

#ifndef LM_DBL_PREC
#error Example program assumes that levmar has been compiled with double precision, see LM_DBL_PREC!
#endif

#define PI2 3.141592653589793

// the following macros concern the initialization of a random number generator for adding noise
#undef REPEATABLE_RANDOM /* #define this for repeatable program behavior across runs */

// 定义宏:GETPID
#ifdef _MSC_VER // MSVC
#include <process.h>
#define GETPID  _getpid
#elif defined(__GNUC__) // GCC
#include <sys/types.h>
#include <unistd.h>
#define GETPID  getpid
#else
#warning Do not know the name of the function returning the process id
#define GETPID  0
#endif /* _MSC_VER */

// 定义宏:INIT_RANDOM(seed)
#ifdef REPEATABLE_RANDOM
#define INIT_RANDOM(seed) srandom(seed)
#else
#define INIT_RANDOM(seed) srand((int)GETPID()) // seed unused
#endif