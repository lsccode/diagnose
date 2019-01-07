/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : sys log terminal

**************************************************************************/

#ifndef __SYS_LOG_H__
#define __SYS_LOG_H__

#include "cbaselog.hpp"

class CSysLog:public CBaseLog
{
public:    
    CSysLog();
    ~CSysLog();
    virtual NVP_S32 init();
    virtual NVP_S32 log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args);
    virtual NVP_S32 close();

private:   
    NVP_CHAR szLogLevel[LL_MAX];

};

#endif 
