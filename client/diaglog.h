#ifndef __DIAGLOG_H__
#define __DIAGLOG_H__

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

#include "serverinfo.h"

class CDiaglog
{
private:
    CDiaglog(void);   
    int m_fd;
    socklen_t serverLen;
    struct sockaddr_in serverAddr;

private:
    static CDiaglog *pSelf;

public:
    static CDiaglog* getInstance(void);
    
public:
    void message(char *buf,int length);
    void destory(void);
};


#if 0
#define MESSAGE(format,...) \
do{ \
    char buf[1024] = {0};\
    CDiaglog *pLog = CDiaglog::getInstance();\
    int i = snprintf(buf,sizeof(buf), "%s %s %d "format,__FILE__,__func__,__LINE__,##__VA_ARGS__);\
    pLog->message(buf,i);\
}while(0)

#define MESSAGE_ENTER(format,...) \
do{ \
    char buf[1024] = {0};\
    CDiaglog *pLog = CDiaglog::getInstance();\
    int i = snprintf(buf,sizeof(buf),"enter %s_%s %d " format,__FILE__,__func__,__LINE__,##__VA_ARGS__);\
    pLog->message(buf,i);\
}while(0)

#define MESSAGE_LEAVE(format,...) \
do{ \
    char buf[1024] = {0};\
    CDiaglog *pLog = CDiaglog::getInstance();\
    int i = snprintf(buf,sizeof(buf),"leave %s_%s %d " format,__FILE__,__func__,__LINE__,##__VA_ARGS__);\
    pLog->message(buf,i);\
}while(0)

#else
#define MESSAGE(format,...)
#define MESSAGE_ENTER(format,...)
#define MESSAGE_LEAVE(format,...)
#endif

#endif
