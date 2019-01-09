/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : c stype encap

**************************************************************************/

#ifndef CLIENT_LOGCAPI_H_
#define CLIENT_LOGCAPI_H_

#include "logmicrodef.h"
#include <stdio.h>

#ifdef __cplusplus 
extern "C" { 
#endif 

//  init log
void initLog();

// set terminal 
void setTerminal(NVP_U32 ulTermType,const NVP_CHAR *szFile);

// set level
void setLevel(NVP_U32 ulogLevel);

// log print
void logPrint(NVP_U32 ulogLevel,const NVP_CHAR *format, ...);

// stop log
void closeLog();

// log micro fun,ref main.c
#define NVPLOG(loglevel,format,...) \
do{ \
    logPrint(loglevel,"/%s/%s/%d -- "format, __FILE__,__func__,__LINE__, ##__VA_ARGS__); \
} while (0)

//  NL means NVPLOG
#define NLALERT(format,...) NVPLOG(LL_ALERT,format, ##__VA_ARGS__)
#define NLERROR(format,...) NVPLOG(LL_ERR,format, ##__VA_ARGS__)
#define NLWARN(format,...) NVPLOG(LL_WARN,format, ##__VA_ARGS__)
#define NLNOTICE(format,...) NVPLOG(LL_NOTICE,format, ##__VA_ARGS__)
#define NLINFO(format,...) NVPLOG(LL_INFO,format, ##__VA_ARGS__)
#define NLDEBUG(format,...) NVPLOG(LL_DEBUG,format, ##__VA_ARGS__)

#ifdef __cplusplus 
} 
#endif  

#endif   //  CLIENT_LOGCAPI_H_
