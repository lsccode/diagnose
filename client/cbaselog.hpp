#ifndef __LOG_BASE_H__
#define __LOG_BASE_H__

#include <stdarg.h>

#include "nvp_types.h"
#include "logmicrodef.h"
//  LL means log level

#define M_VSTR_FORMAT(buf,length,format,level,ret) \
do{ \
    ret = snprintf(szBuf,length,"[ %s ]",level); \
    va_list args; \
    va_start(args, format);	\
    ret += vsnprintf(buf + ret, length - ret,format,args); \
    va_end(args); \
}while(0)

class CBaseLog
{
public:
    CBaseLog();
    virtual ~CBaseLog(){};
    virtual NVP_S32 init() = 0;
    virtual NVP_S32 log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args) = 0;
    virtual NVP_S32 close() = 0;

protected:
    NVP_S32 formatMsg(NVP_CHAR *pszMsg,NVP_U32 ulMsgLenght,const NVP_CHAR* pszFormat, ...);
    const NVP_CHAR *ppszLevStr[LL_MAX];
};

#endif
