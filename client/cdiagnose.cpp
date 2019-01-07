#include "cdiagnose.hpp"
#include "cfilelog.hpp"
#include "cnetlog.hpp"
#include "cstderrlog.hpp"
#include "csyslog.hpp"

CDiagnose* CDiagnose::pcSelf = NULL;

CDiagnose::CDiagnose()
{
    pcBaseLog = NULL;
}

//  Logging functions do not need to consider multithreading during initialization,
//  Therefore, the mutex is omitted, please note
CDiagnose* CDiagnose::getInstance(NVP_VOID)
{
    if(NULL == pcSelf)
        pcSelf = new CDiagnose();
    
    return pcSelf;
}

//  Logging functions do not need to consider multithreading during initialization,
//  Therefore, the mutex is omitted, please note
NVP_S32 CDiagnose::setTerminal(NVP_U32 ulTermType,const NVP_CHAR *szFile)
{
    NVP_S32 slRet = NVP_SUCCEED;
    
    if(NULL != this->pcBaseLog)
        delete this->pcBaseLog;
    
    this->pcBaseLog = NULL;
    
    switch(ulTermType)
    {
        case M_TERM_FILE:
        {
            if(szFile == NULL)
            {
                slRet = NVP_FAILURE;
                fprintf(stderr,"file name must have a file name\n");
            }
            else
            {
                this->pcBaseLog = new CFileLog(szFile);
            }     
        }break;
        
        case M_TERM_NET:
        {
            this->pcBaseLog = new CNetLog();
        }break;
        
        case M_TERM_SYS:
        {
            this->pcBaseLog = new CSysLog();
        }break;
        
        case M_TERM_STD:
        {
            this->pcBaseLog = new CStdErrLog();
        }break;        
        
        default:
        {
            fprintf(stderr,"unKnown term type\n");
            slRet = NVP_FAILURE;
        }break;
    }
    
    if(this->pcBaseLog)
    {
        this->pcBaseLog->init();
    }
    else
    {
        fprintf(stderr,"create terminam error!\n");
        slRet = NVP_FAILURE;
    }
    
    return slRet;

}

NVP_VOID CDiagnose::log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args)
{
    if( NULL == this->pcBaseLog )
    {
        return;
    }
    
    this->pcBaseLog->log(ulogLevel,format,args);
    
    return;
}
