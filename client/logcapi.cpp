/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : c stype encap

**************************************************************************/

#include "logcapi.h"
#include "cdiagnose.hpp"

static CDiagnose *s_pdiagnose = NULL;    //  log encap
static NVP_U8  s_ucStart = 0;            //  start flag,this flag must 1,or else no print message
static NVP_U32 s_ulLevel = 0;
/**************************************************************************
@brief     : Initialize the log function
@function  : initLog
@param     :
@note      : 
@author    :   sicheng.lin  
**************************************************************************/
void initLog()
{
    if (NULL == s_pdiagnose)
    {
        s_pdiagnose = CDiagnose::getInstance();
    }
    
    return;
}

/**************************************************************************
@brief     : set log terminal
@function  : setTerminal
@param     :
    ulTermType   terminal type
    szFile       file name
@note      : 
@author    :   sicheng.lin  
**************************************************************************/
void setTerminal(NVP_U32 ulTermType,const NVP_CHAR *szFile)
{
    if (NULL == s_pdiagnose)
    {
        fprintf(stderr,"call initLog first,please!\n");
        return;
    }
 
    s_pdiagnose->setTerminal(ulTermType,szFile);
    s_ucStart = 1;
    
    return;
}

/**************************************************************************
@brief     : set log level
@function  : setLevel
@param     :
    ulogLevel   log level
@note      : 
@author    :   sicheng.lin  
**************************************************************************/

void setLevel(NVP_U32 ulogLevel)
{
    s_ulLevel = ulogLevel;
    return;
}

/**************************************************************************
@brief     : print to concrete terminal
@function  : logPrint
@param     :
    ulogLevel   log level
    format      c style format
@note      : 
@author    :  sicheng.lin
@example   : ref main.c 
**************************************************************************/

void logPrint(NVP_U32 ulogLevel,const NVP_CHAR *format, ...)
{
    if (NULL == s_pdiagnose || 0 == s_ucStart )
    {
        fprintf(stderr,"call initLog and setTerminal first,please!\n");
        return;
    }
    
    if (ulogLevel > s_ulLevel)
    {
        return;
    }
    
    va_list args;
    va_start(args, format);
    s_pdiagnose->log(ulogLevel,format,args);
    va_end(args);
    
    return;
}

/**************************************************************************
@brief     : stop log
@function  : closeLog
@param     :
@note      : 
@author    :   sicheng.lin  
**************************************************************************/

void closeLog()
{
    s_ucStart = 0;
}
