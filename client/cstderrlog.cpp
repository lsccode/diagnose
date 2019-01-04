#include <stdio.h>
#include <stdarg.h>

#include "cstderrlog.hpp"

CStdErrLog::CStdErrLog()
{

}

CStdErrLog::~CStdErrLog()
{

}

NVP_S32 CStdErrLog::init()
{
    return NVP_SUCCEED;
}

NVP_S32 CStdErrLog::log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args)
{
    NVP_S32 slRet;
    NVP_CHAR szBuf[M_MAX_MSG_LENGTH] = {0};
    
    if(ulogLevel >= LL_MAX)
    {
        fprintf(stderr,"ulogLevel(%u) > LL_MAX(%u) \n",ulogLevel,LL_MAX);
        return NVP_FAILURE;
    }
    
    slRet = snprintf(szBuf,sizeof(szBuf),"[ %-10s ] ",ppszLevStr[ulogLevel]);	
    slRet += vsnprintf(szBuf + slRet, sizeof(szBuf) - slRet,format,args); 	  
    
    if(slRet > 0)
        fprintf(stderr,szBuf);
    
    return NVP_SUCCEED;
}

NVP_S32 CStdErrLog::close()
{
    return NVP_SUCCEED;
}
