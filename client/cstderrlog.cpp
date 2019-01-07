/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : standard  error terminal

**************************************************************************/

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

/**************************************************************************
@brief     : log to standard error terminal
@function  : log
@param     :
	ulogLevel         log leve type,  such as LL_ERR,LL_WARN ...
	format            c stype format ,like "%s %d"
    args              c vary type
@note      : 
@author    :   sicheng.lin  
**************************************************************************/
NVP_S32 CStdErrLog::log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args)
{
    NVP_S32 slRet;
    NVP_CHAR szBuf[M_MAX_MSG_LENGTH] = {0};
    
    if(ulogLevel >= LL_MAX)
    {
        fprintf(stderr,"ulogLevel(%u) > LL_MAX(%d) \n",ulogLevel,LL_MAX);
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
