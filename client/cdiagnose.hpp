#ifndef __DIAGNOSE_H__
#define __DIAGNOS_H__

#include <stdio.h>
#include <stdarg.h>
#include "cbaselog.hpp"

#define M_TERM_FILE (0)
#define M_TERM_NET  (1)
#define M_TERM_SYS  (2)
#define M_TERM_STD  (3)

class CDiagnose
{
private:
    CDiagnose(NVP_VOID);   

public:
    static CDiagnose* getInstance(NVP_VOID);
    
public:
    NVP_S32 setTerminal(NVP_U32 ulTermType,NVP_CHAR *szFile = NULL);
    NVP_VOID log(NVP_U32 ulogLevel,const NVP_CHAR *format, ...); 
    
private:
    CBaseLog *pcBaseLog;
    
private:
    static CDiagnose *pcSelf;
};

#endif
