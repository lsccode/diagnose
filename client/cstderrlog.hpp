/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : standard  error terminal

**************************************************************************/

#ifndef __STDERR_LOG_H__
#define __STDERR_LOG_H__

#include "cbaselog.hpp"

class CStdErrLog:public CBaseLog
{
public:
    CStdErrLog();
    ~CStdErrLog();
    virtual NVP_S32 init();
    virtual NVP_S32 log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args);
    virtual NVP_S32 close();

private:
  
};

#endif
