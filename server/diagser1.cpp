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
#include <algorithm>
#include <map>
#include <string>

#define debug(format,...) \
    do{ \
    fprintf(stderr,"file( %s ), fun( %s ),line( %d ), "format, __FILE__,__func__,__LINE__, ##__VA_ARGS__); \
} \
while(0)

typedef struct tagMessageStatic
{
    unsigned long long enter;
    unsigned long long leave;
    unsigned long status;
}tMessageStatic;

#define STATUS_OK (0)
#define STATUS_FA (1)

typedef std::map<std::string,std::string> tMapKey;
typedef std::map<std::string,tMessageStatic*> tMapStatic;

int createUdpServer()
{
    int sockfd;
    struct sockaddr_in addr;
    
    sockfd = socket (AF_INET,SOCK_DGRAM,0);
    if(sockfd <0)
    {
        debug("socket");
        exit(1);
    }
    
    bzero(&addr, sizeof(addr) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0)
    {
        debug("bind");
        exit(1);
    }
    
    return sockfd;
}

int main(int argc, char *argv[])
{
    tMapStatic mapStatics;
    int slSocket = createUdpServer();
    if(slSocket < 0)
    {
        debug("create udp server error!\n");
        return -1;
    }
    while(1)
    {
        char szBuf[1024] = {0};
        char ver[16] = {0};
        char key[128] = {0};
        
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        if(recvfrom(slSocket,szBuf,sizeof(szBuf),0,(struct sockaddr *)&clientAddr,&clientLen) < 0)
        {
            debug("recv error,!");
            continue;
        }
        
        sscanf(szBuf,"%s %s",ver,key);
        tMessageStatic stStatic = {0};  
        std::string mapkey = key;
        tMapStatic::iterator iter = mapStatics.find(mapkey);
        
        if(!strcmp(ver,"enter"))
        {               
            stStatic.enter = 1;
        }
        else if(!strcmp(ver,"leave"))
        {
            stStatic.leave = 1;
        }
        else
        {
            debug("unknow ver(%s)\n",ver);
        }
        stStatic.status = STATUS_FA;
        
        
        if(iter != mapStatics.end())
        {
            tMessageStatic *pstStatic = iter->second;
            if(stStatic.enter)
            {               
                ++pstStatic->enter;
            }
            else if(stStatic.leave)
            {
                ++pstStatic->leave;
            }
            else
            {
                debug("unknow ver(%s)\n",ver);
            }
            
            pstStatic->status = stStatic.status;
            if(pstStatic->enter == pstStatic->leave)
                pstStatic->status = STATUS_OK;
            
        }
        else
        {
            debug("add new\n");
            //char *mapkey = (char *)calloc(1,strlen(key) + 1);
            
            tMessageStatic *pstStatic = (tMessageStatic *)calloc(1,sizeof(tMessageStatic));
            
            pstStatic->enter = stStatic.enter;
            pstStatic->leave = stStatic.leave;
            pstStatic->status = stStatic.status;
            //strcpy(mapkey,key);
            
            mapStatics.insert(std::make_pair(mapkey, pstStatic));            
        }
        
        for (tMapStatic::iterator iter = mapStatics.begin(); 
                iter != mapStatics.end(); ++iter) 
        {
            tMessageStatic *pstStatic = iter->second;
            std::string mapkey = iter->first;
            debug("%s enter(%llu) leave(%llu) \n",mapkey.c_str(),pstStatic->enter,pstStatic->leave);
        }
        
        debug("recv (%s:%d),mesage = %s\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port),szBuf);  
        debug("ver(%s),key(%s))!\n\n\n",ver,key);  
    }
    close(slSocket);
    
    return 0;
}
