#ifndef _FILE_LOG_H__
#define _FILE_LOG_H__

#include "cbaselog.hpp"
#define M_MAX_FILE_NAME_LENGTH (64)

class CFileLog:public CBaseLog
{
public:
    CFileLog(NVP_CHAR *szFileName);
    ~CFileLog();
    virtual NVP_S32 init();
    virtual NVP_S32 log(NVP_U32 ulogLevel,const NVP_CHAR *format,va_list args);
    virtual NVP_S32 close();
    
private:
    NVP_S32 openFile();
private:
    NVP_S32 m_filefd;
    NVP_CHAR m_szFileName[M_MAX_FILE_NAME_LENGTH];
};

#endif
