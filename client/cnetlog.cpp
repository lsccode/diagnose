/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : net log terminal

**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

#include "cnetlog.hpp"

CNetLog::CNetLog()
{
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(SERVER_PORT);
    m_serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    m_serverLen = sizeof(m_serverAddr);
    m_fd = -1;
    memset(m_szIP,0,sizeof(m_szIP));
}

CNetLog::~CNetLog()
{
    if (m_fd > 0)
        ::close(m_fd);
    m_fd = -1;
}

/**************************************************************************
@brief     : get log server's ip
@function  : getCfgIP
@param     :
@note      : 
@author    : sicheng.lin 
**************************************************************************/

NVP_S32 CNetLog::getCfgIP()
{
    FILE *fp = fopen(M_CFG_FILE,"a+");
    
    if (NULL == fp)
    {
        return NVP_FAILURE;
    }
    memset(m_szIP,0,sizeof(m_szIP));
    
    if (fgets(m_szIP,sizeof(m_szIP),fp) == NULL)
    {
        fclose(fp);
        return NVP_FAILURE;
    }
    
    fclose(fp); 
    
    return NVP_SUCCEED;

}

/**************************************************************************
@brief     : init socket
@function  : init
@param     :
@note      : 
@author    : sicheng.lin??
**************************************************************************/

NVP_S32 CNetLog::init()
{ 
    m_fd = socket (AF_INET,SOCK_DGRAM,0);
    
    if (m_fd < 0)
    {
        fprintf(stderr,"socket error!\n");
        return NVP_FAILURE;
    }
    
    if (getCfgIP() != NVP_SUCCEED)
    {
        //  udp socket,if  no ip config,then wait user config netlog.cfg, therefore keep socket fd
        fprintf(stderr,"get config ip error!\n");
        return NVP_FAILURE;
    }
    
    // redirect ip 
    m_serverAddr.sin_addr.s_addr = inet_addr(m_szIP);
    
    return NVP_SUCCEED;
}

/**************************************************************************
@brief     : log to net udp server
@function  : log
@param     :
	ulogLevel         log leve type,  such as LL_ERR,LL_WARN ...
	format            c stype format ,like "%s %d"
    args              c vary type
@note      : 
@author    :   sicheng.lin  
**************************************************************************/

NVP_S32 CNetLog::log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args)
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
    
    if (slRet > 0 && m_fd > 0)
    {
        if (sendto(m_fd,szBuf,slRet,0,(struct sockaddr *)&m_serverAddr,m_serverLen) < 0)
        {
            if (getCfgIP() != NVP_SUCCEED)
            {
                fprintf(stderr,"get config ip error!\n");
                return NVP_FAILURE;
            }            
            m_serverAddr.sin_addr.s_addr = inet_addr(m_szIP);
            fprintf(stderr,"send message error!\n");
            
            return NVP_FAILURE;
        }
    }
    
    return NVP_SUCCEED;
}

/**************************************************************************
@brief     : disconncect from server
@function  : close
@param     :
@note      : 
@author    : sicheng.lin??
**************************************************************************/

NVP_S32 CNetLog::close()
{
    if (m_fd > 0)
        ::close(m_fd);
    m_fd = -1;
    
    return NVP_SUCCEED;
}

