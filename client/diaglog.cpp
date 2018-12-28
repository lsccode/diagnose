#include "diaglog.h"

CDiaglog* CDiaglog::pSelf = NULL;

CDiaglog::CDiaglog()
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serverLen = sizeof(serverAddr);
    
    m_fd = socket (AF_INET,SOCK_DGRAM,0);
    
    if(m_fd < 0)
    {
        fprintf(stderr,"socket error!\n");
    }
    
    if(connect(m_fd, (struct sockaddr *)&serverAddr, serverLen) < 0)
    {
        close(m_fd);
        fprintf(stderr,"connect error!\n");
    }
    fprintf(stderr,"connect (%s:%d)... \n",SERVER_ADDR,SERVER_PORT);
    
}

CDiaglog* CDiaglog::getInstance(void)
{
    if(NULL == pSelf)
        pSelf = new CDiaglog();
    
    return pSelf;
}

void CDiaglog::message(char *buf,int length)
{
    if(send(m_fd,buf,length,0) < 0)
    {
        fprintf(stderr,"send message error!\n");
    }
    return;
}
                       
void CDiaglog::destory(void)
{
    close(m_fd);
    if(pSelf)
        delete pSelf;
    pSelf = NULL;
}
