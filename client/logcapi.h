/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : c stype encap

**************************************************************************/

#ifndef __LOG_API_H__
#define __LOG_API_H__

#include "logmicrodef.h"
#include <stdio.h>

#ifdef __cplusplus 
extern "C" { 
#endif

//  init log
void initLog();

// set terminal 
void setTerminal(NVP_U32 ulTermType,const NVP_CHAR *szFile);

// log print
void logPrint(NVP_U32 ulogLevel,const NVP_CHAR *format, ...);

// stop log
void closeLog();

// log micro fun,ref main.c
#define NVPLOG(loglevel,format,...) \
do{ \
    logPrint(loglevel,"/%s/%s/%d -- "format, __FILE__,__func__,__LINE__, ##__VA_ARGS__); \
} while(0)


#ifdef __cplusplus 
} 
#endif 

#endif
