#ifndef __DIAGNOSE_H__
#define __DIAGNOS_H__

#include <stdio.h>
#include <stdarg.h>
#include "cbaselog.hpp"

class CDiagnose
{
private:
    CDiagnose(NVP_VOID);   

public:
    static CDiagnose* getInstance(NVP_VOID);
    
public:
    NVP_S32 setTerminal(NVP_U32 ulTermType,const NVP_CHAR *szFile = NULL);
    NVP_VOID log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args); 
    
private:
    CBaseLog *pcBaseLog;
    
private:
    static CDiagnose *pcSelf;
};

#endif
