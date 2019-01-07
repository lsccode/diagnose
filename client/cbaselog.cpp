/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : log terminal template class

**************************************************************************/
#include "cbaselog.hpp"
#include <stdio.h>
#include <stdarg.h>

CBaseLog::CBaseLog()
{
    /*
        log level string define
    */
    ppszLevStr[LL_ERR]    = "NVP_ERR";
    ppszLevStr[LL_WARN]   = "NVP_WARN";
    ppszLevStr[LL_NOTICE] = "NVP_NOTICE";
    ppszLevStr[LL_INFO]   = "NVP_INFO";
    ppszLevStr[LL_DEBUG]  = "NVP_DEBUG";
    ppszLevStr[LL_MAX]    = NULL;

}
/**************************************************************************
@brief     : format string
@function  : format
@param     :
	pszMsg         input string buf
	ulMsgLenght    input string buf length?
	pszFormat      c style formatting input
@note      :
@author    : sicheng.lin
**************************************************************************/
NVP_S32 CBaseLog::format(NVP_CHAR *pszMsg,NVP_U32 ulMsgLenght,const NVP_CHAR* pszFormat, ...)
{	
    NVP_S32 slRet;
	
    va_list args; 
	va_start(args, pszFormat);
	
    slRet = vsnprintf(pszMsg, ulMsgLenght, pszFormat, args); 
	
    va_end(args);
	
	return slRet;
}

