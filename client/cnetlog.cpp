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

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT (9638)
#define M_CFG_FILE "/etc/netlog.cfg"

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
    if(m_fd > 0)
        ::close(m_fd);
    m_fd = -1;
}

NVP_S32 CNetLog::getCfgIP()
{
    FILE *fp = fopen(M_CFG_FILE,"a+");
    
    if(NULL == fp)
    {
        return NVP_FAILURE;
    }
    memset(m_szIP,0,sizeof(m_szIP));
    
    if(fgets(m_szIP,sizeof(m_szIP),fp) == NULL)
    {
        fclose(fp);
        return NVP_FAILURE;
    }
    
    fclose(fp); 
    
    return NVP_SUCCEED;

}

NVP_S32 CNetLog::init()
{ 
    m_fd = socket (AF_INET,SOCK_DGRAM,0);
    
    if(m_fd < 0)
    {
        fprintf(stderr,"socket error!\n");
        return NVP_FAILURE;
    }
    
    if(getCfgIP() != NVP_SUCCEED)
    {
        fprintf(stderr,"get config ip error!\n");
        return NVP_FAILURE;
    }
    
    // redirect ip 
    m_serverAddr.sin_addr.s_addr = inet_addr(m_szIP);
    
    return NVP_SUCCEED;
}

NVP_S32 CNetLog::log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args)
{
    NVP_S32 slRet;
    NVP_CHAR szBuf[M_MAX_MSG_LENGTH] = {0};
    
    if(ulogLevel >= LL_MAX)
    {
        fprintf(stderr,"ulogLevel(%u) > LL_MAX(%u) \n",ulogLevel,LL_MAX);
        return NVP_FAILURE;
    }
    
    slRet = snprintf(szBuf,sizeof(szBuf),"[ %-10s ] ",ppszLevStr[ulogLevel]);	
    slRet += vsnprintf(szBuf + slRet, sizeof(szBuf) - slRet,format,args);  
    
    if(slRet > 0 && m_fd > 0)
    {
        if(sendto(m_fd,szBuf,slRet,0,(struct sockaddr *)&m_serverAddr,m_serverLen) < 0)
        {
            if(getCfgIP() != NVP_SUCCEED)
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

NVP_S32 CNetLog::close()
{
    if(m_fd > 0)
        ::close(m_fd);
    m_fd = -1;
    
    return NVP_SUCCEED;
}
