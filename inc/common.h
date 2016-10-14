/***************************************************************************
*     Copyright (c) 2016 by Fan.Xi.  All Rights Reserved.
****************************************************************************
* File:  common.h
* Author:  Fan Xi <xifan2012@gmail.com>
* Description: 
*
**********************************History***********************************
*     when              who                      what, where, why
* ------------    ---------------    ---------------------------------------
*  2016/10/12      Fan.Xi             Create Module.
*
****************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG    /* The marco to open debug information. */
#define SUCCESS 0
#define FAIL -1

/* Refer to Linux about the version format. (major.minor.revision | 2.6.18) */
#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define REVISION_VERSION 1

typedef unsigned char byte;
typedef unsigned int u_int;

#endif /* _COMMON_H_ */
