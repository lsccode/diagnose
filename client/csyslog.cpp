/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : sys log terminal

**************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

#include "csyslog.hpp"

CSysLog::CSysLog()
{
    szLogLevel[LL_ERR]    = LOG_ERR;
    szLogLevel[LL_WARN]   = LOG_WARNING;
    szLogLevel[LL_NOTICE] = LOG_NOTICE;
    szLogLevel[LL_INFO]   = LOG_INFO;
    szLogLevel[LL_DEBUG]  = LOG_DEBUG;
}
CSysLog::~CSysLog()
{
    closelog();
}

/**************************************************************************
@brief     : call syslog
@function  : init
@param     :
@note      : 
@author    : sicheng.lin??
**************************************************************************/

NVP_S32 CSysLog:: init()
{

    openlog("User Log", LOG_PID | LOG_NDELAY, LOG_USER);
    
    return NVP_SUCCEED;
}

/**************************************************************************
@brief     : log to sys log
@function  : log
@param     :
	ulogLevel         log leve type,  such as LL_ERR,LL_WARN ...
	format            c stype format ,like "%s %d"
    args              c vary type
@note      : 
@author    :   sicheng.lin  
**************************************************************************/

NVP_S32 CSysLog::log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args)
{
    NVP_S32 slRet;
    NVP_CHAR szBuf[M_MAX_MSG_LENGTH] = {0};
    
    if(ulogLevel >= LL_MAX)
    {
        syslog(LOG_ERR,"ulogLevel(%u) > LL_MAX(%u) \n",ulogLevel,LL_MAX);
        return NVP_FAILURE;
    }
    
    slRet = snprintf(szBuf,sizeof(szBuf),"[ %-10s ] ",ppszLevStr[ulogLevel]);	
    slRet += vsnprintf(szBuf + slRet, sizeof(szBuf) - slRet,format,args);
    
    if(slRet > 0)
        syslog(szLogLevel[ulogLevel],szBuf);
	
    return slRet;
}

/**************************************************************************
@brief     : close sys log
@function  : log
@param     :
@note      : 
@author    :   sicheng.lin  
**************************************************************************/
NVP_S32 CSysLog::close()
{   
    closelog();
    
    return NVP_SUCCEED;
}
