#include "logcapi.h"

int main(int argc,char *argv[])
{
    int i = 0;
    initLog();
    setTerminal(M_TERM_STD,NULL);    
    NVPLOG(LL_ERR,"this is just test\n");    
    NVPLOG(LL_WARN,"this is just test %d\n",i);  
    NVPLOG(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");   
    NVPLOG(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");    
    NVPLOG(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG"); 
    
    setTerminal(M_TERM_SYS,NULL);    
    NVPLOG(LL_ERR,"this is just test\n");    
    NVPLOG(LL_WARN,"this is just test %d\n",i);  
    NVPLOG(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");   
    NVPLOG(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");    
    NVPLOG(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG");
    
    setTerminal(M_TERM_FILE,"debug.log");    
    NVPLOG(LL_ERR,"this is just test\n");    
    NVPLOG(LL_WARN,"this is just test %d\n",i);  
    NVPLOG(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");   
    NVPLOG(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");    
    NVPLOG(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG");
    
    setTerminal(M_TERM_NET,NULL);    
    NVPLOG(LL_ERR,"this is just test\n");    
    NVPLOG(LL_WARN,"this is just test %d\n",i);  
    NVPLOG(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");   
    NVPLOG(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");    
    NVPLOG(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG");
    
    return 0;
}
