/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : file terminal

**************************************************************************/
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>

#include "cfilelog.hpp"

CFileLog::CFileLog(const NVP_CHAR *szFileName)
{
    m_filefd = -1;
    memset(m_szFileName,0,sizeof(m_szFileName));
    
    if (szFileName)
    {
        strncpy(m_szFileName,szFileName,sizeof(m_szFileName) - 1);
    }      
}

CFileLog::~CFileLog()
{
    if (m_filefd > 0)
    {
        ::close(m_filefd);
    }
       
    m_filefd = -1;
}

/**************************************************************************
@brief     : open file for log
@function  : openFile
@param     :
@note      : 
@author    : sicheng.lin
**************************************************************************/

NVP_S32 CFileLog::openFile()
{
    m_filefd = open(m_szFileName,O_WRONLY | O_CREAT | O_APPEND | O_NDELAY,0777);
    
    if (m_filefd < 0)
    {
        fprintf(stderr, "open file error %s,error (%s:%d) \n!\n",m_szFileName,strerror(errno),errno);
        return NVP_FAILURE;
    }
           
    return NVP_SUCCESS;             
}

/**************************************************************************
@brief     : init terminal
@function  : init
@param     :
@note      : 
@author    : sicheng.lin
**************************************************************************/

NVP_S32 CFileLog::init()
{
    NVP_S32 slRet = NVP_SUCCESS;
    
    slRet = openFile();
    
    if (slRet != NVP_SUCCESS)
    {
        return NVP_FAILURE;
    }
    
    return NVP_SUCCESS;
}

/**************************************************************************
@brief     : log to file
@function  : log
@param     :
	ulogLevel         log leve type,  such as LL_ERR,LL_WARN ...
	format            c stype format ,like "%s %d"
    args              c vary type
@note      : 
@author    :  sicheng.lin 
**************************************************************************/

NVP_S32 CFileLog::log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args)
{
    NVP_S32 slRet;
    NVP_CHAR szBuf[M_MAX_MSG_LENGTH] = {0};
    
    if (ulogLevel >= LL_MAX)
    {
        fprintf(stderr,"ulogLevel(%u) > LL_MAX(%d) \n",ulogLevel,LL_MAX);
        return NVP_FAILURE;
    }
    
    slRet = snprintf(szBuf,sizeof(szBuf),"[ %-10s ] ",ppszLevStr[ulogLevel]);	
    slRet += vsnprintf(szBuf + slRet, sizeof(szBuf) - slRet,format,args); 
    
    if (slRet > 0 && m_filefd > 0)
    {
        if (::write(m_filefd,szBuf,slRet) < 0)
        {
            ::close(m_filefd);
            m_filefd = -1;
            
            fprintf(stderr,"write file error!\n");
            
            return NVP_FAILURE;
        }
    }
    
    return slRet;
}

/**************************************************************************
@brief     : close file
@function  : close
@param     :
@note      : 
@author    : sicheng.lin
**************************************************************************/

NVP_S32 CFileLog::close()
{
    if (m_filefd > 0)
    {
        ::close(m_filefd);
    }
    
    m_filefd = -1;
    
    return NVP_SUCCESS;
}
