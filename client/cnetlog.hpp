#ifndef __NET_LOG_H__
#define __NET_LOG_H__

#include <sys/socket.h>
#include <netinet/in.h>

#include "cbaselog.hpp"
#define M_MAX_IP_ADDR_LEN (32) // just ipv4

class CNetLog:public CBaseLog
{
public:
    CNetLog();
    ~CNetLog();
    virtual NVP_S32 init();
    virtual NVP_S32 log(NVP_U32 ulogLevel,const NVP_CHAR *format, va_list args);
    virtual NVP_S32 close();
    
private:
    NVP_S32 getCfgIP();
    
private:
    int m_fd;
    socklen_t m_serverLen;
    struct sockaddr_in m_serverAddr;
    NVP_CHAR m_szIP[M_MAX_IP_ADDR_LEN];
};



#endif
