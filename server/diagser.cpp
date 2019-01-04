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
    unsigned long long last;
    unsigned long long recent;
    unsigned long long diff;
    char szRecentAccessTime[32];  
}tMessageStatic;

#define STATUS_OK (0)
#define STATUS_FA (1)

typedef std::map<std::string,std::string> tMapKey;
typedef std::map<std::string,tMessageStatic*> tMapStatic;

void getLocalTimeStr(char *str)
{
    struct timeval    tv; 
//    struct timezone tz;
    struct tm         *lt;
    gettimeofday(&tv, NULL); 
    
    lt = localtime(&tv.tv_sec);
    int ret = sprintf(str,"%04d%02d%02d-%02d%02d%02d.%ld",
                      lt->tm_year+1900,lt->tm_mon+1,lt->tm_mday,
                      lt->tm_hour,lt->tm_min,lt->tm_sec,tv.tv_usec);
    str[ret] = 0;
    return;
}

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
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0)
    {
        debug("bind");
        exit(1);
    }
    
    debug("create udp server at (%s:%d)\n",0,SERVER_PORT);
    
    return sockfd;
}

int main(int argc, char *argv[])
{
    tMapStatic mapStatics;
    tMapKey mapKey;
    int slSocket = createUdpServer();
    if(slSocket < 0)
    {
        debug("create udp server error!\n");
        return -1;
    }
    unsigned step = 0;
    
    while(1)
    {
        char szBuf[1024] = {0};
        char ver[16] = {0};
        char key[128] = {0};
        tMessageStatic stStatic = {0};  
        
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        if(recvfrom(slSocket,szBuf,sizeof(szBuf),0,(struct sockaddr *)&clientAddr,&clientLen) < 0)
        {
            debug("recv error,!");
            continue;
        }
#if 1
        getLocalTimeStr(stStatic.szRecentAccessTime);
        fprintf(stderr,"%s \n",szBuf);
#else       
        sscanf(szBuf,"%s %s",ver,key);
        std::string mapkey = key;
        
        tMapKey::iterator iterkey = mapKey.find(mapkey);
        
        if(iterkey != mapKey.end())
        {
            mapkey = iterkey->second;
        }
        else
        {
            char temp[128] = {0};
            snprintf(temp,sizeof(temp),"%s_%d",key,++step);
            std::string strkey = mapkey;
            mapkey = temp;
            mapKey.insert(std::make_pair(strkey, mapkey)); 
        }

        
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
        stStatic.last   = 0;
        stStatic.recent = time(NULL);
        stStatic.diff   = stStatic.recent - stStatic.last;
        getLocalTimeStr(stStatic.szRecentAccessTime);
        
        if(iter != mapStatics.end())
        {
            tMessageStatic *pstStatic = iter->second;
            pstStatic->enter  += stStatic.enter;
            pstStatic->leave  += stStatic.leave;
            pstStatic->last   = pstStatic->recent;
            pstStatic->recent = stStatic.recent;
            pstStatic->diff   = pstStatic->recent - pstStatic->last;
            getLocalTimeStr(pstStatic->szRecentAccessTime);
            pstStatic->status = stStatic.status;
            if(pstStatic->enter == pstStatic->leave)
                pstStatic->status = STATUS_OK;           
        }
        else
        {
            debug("add new\n");
            //char *mapkey = (char *)calloc(1,strlen(key) + 1);
            
            tMessageStatic *pstStatic = (tMessageStatic *)calloc(1,sizeof(tMessageStatic));
            
            pstStatic->enter  = stStatic.enter;
            pstStatic->leave  = stStatic.leave;            
            pstStatic->last   = pstStatic->recent;
            pstStatic->recent = stStatic.recent;
            pstStatic->diff   = pstStatic->recent - pstStatic->last;
            getLocalTimeStr(pstStatic->szRecentAccessTime);
            pstStatic->status = stStatic.status;
            
            mapStatics.insert(std::make_pair(mapkey, pstStatic));            
        }
        
        
        
        for (tMapStatic::iterator iter = mapStatics.begin(); 
                iter != mapStatics.end(); ++iter) 
        {
            tMessageStatic *pstStatic = iter->second;
            std::string mapkey = iter->first;
            
            const char *strstatus = "NO";
            if(pstStatic->status == STATUS_OK)
                strstatus = "YES";
           
            if(pstStatic->status != STATUS_OK)
                fprintf(stderr,
                        "%s enter(%llu) leave(%llu) last(%u) recent(%u) diff(%u) time(%s) status (%s)\n",
                        mapkey.c_str(),
                        pstStatic->enter,
                        pstStatic->leave,                        
                        pstStatic->last,
                        pstStatic->recent,
                        pstStatic->diff,
                        pstStatic->szRecentAccessTime,
                        strstatus
                       );
        }
#endif
          
    }
    close(slSocket);
    
    return 0;
}
