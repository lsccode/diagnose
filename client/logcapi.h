#ifndef __LOG_API_H__
#define __LOG_API_H__

#include "logmicrodef.h"
#include <stdio.h>

#ifdef __cplusplus 
extern "C" { 
#endif

void initLog();
void setTerminal(NVP_U32 ulTermType,const NVP_CHAR *szFile);
void logPrint(NVP_U32 ulogLevel,const NVP_CHAR *format, ...);
void closeLog();


#define NVPLOG(loglevel,format,...) \
do{ \
    logPrint(loglevel,"/%s/%s/%d -- "format, __FILE__,__func__,__LINE__, ##__VA_ARGS__); \
} while(0)


#ifdef __cplusplus 
} 
#endif 

#endif
