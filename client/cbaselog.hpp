/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : log terminal template class

**************************************************************************/

#ifndef __LOG_BASE_H__
#define __LOG_BASE_H__

#include <stdarg.h>
#include "nvp_types.h"
#include "logmicrodef.h"


class CBaseLog
{
public:
    CBaseLog();
    virtual ~CBaseLog(){};
    
    // log init function,must first call it,children class must implement this function
    virtual NVP_S32 init() = 0;  
    
    // log function,used by format string,children class must implement this function
    virtual NVP_S32 log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args) = 0; 
    
    // log close function
    virtual NVP_S32 close() = 0;

protected:
    
    //  format string
    NVP_S32 format(NVP_CHAR *pszMsg,NVP_U32 ulMsgLenght,const NVP_CHAR* pszFormat, ...);
    
    //format string level 
    const NVP_CHAR *ppszLevStr[LL_MAX];
};

#endif
