#include "logcapi.h"
#include "cdiagnose.hpp"

CDiagnose *pdiagnose = NULL;
NVP_U8  ucStart = 0;

void initLog()
{
    if(NULL == pdiagnose)
        pdiagnose = CDiagnose::getInstance();
    
    return;
}

void setTerminal(NVP_U32 ulTermType,const NVP_CHAR *szFile)
{
    if(NULL == pdiagnose)
    {
        fprintf(stderr,"call initLog first,please!\n");
        return;
    }
 
    pdiagnose->setTerminal(ulTermType,szFile);
    ucStart = 1;
    
    return;
}

void logPrint(NVP_U32 ulogLevel,const NVP_CHAR *format, ...)
{
    if(NULL == pdiagnose || 0 == ucStart )
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

void closeLog()
{
    ucStart = 0;
}
