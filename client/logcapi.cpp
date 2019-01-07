/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : c stype encap

**************************************************************************/

#include "logcapi.h"
#include "cdiagnose.hpp"

CDiagnose *pdiagnose = NULL;    //  log encap
NVP_U8  ucStart = 0;            //  start flag,this flag must 1,or else no print message

/**************************************************************************
@brief     : Initialize the log function
@function  : initLog
@param     :
@note      : 
@author    :   sicheng.lin  
**************************************************************************/
void initLog()
{
    if (NULL == pdiagnose)
        pdiagnose = CDiagnose::getInstance();
    
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
    if (NULL == pdiagnose)
    {
        fprintf(stderr,"call initLog first,please!\n");
        return;
    }
 
    pdiagnose->setTerminal(ulTermType,szFile);
    ucStart = 1;
    
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
    if (NULL == pdiagnose || 0 == ucStart )
    {
        fprintf(stderr,"call initLog and setTerminal first,please!\n");
        return;
    }
    
    va_list args;
    va_start(args, format);
    pdiagnose->log(ulogLevel,format,args);
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
    ucStart = 0;
}
