#include "diaglog.h"
#include "cdiagnose.hpp"
int main()
{
    //MESSAGE_ENTER("");
    //MESSAGE_LEAVE("");  
    
    
    CDiagnose *pdiagnose = CDiagnose::getInstance();
    
    int i = 0;
    
    pdiagnose->setTerminal(M_TERM_STD);
    
    pdiagnose->log(LL_ERR,"this is just test\n");
    
    pdiagnose->log(LL_WARN,"this is just test %d\n",i);
    
    pdiagnose->log(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");
    
    pdiagnose->log(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");
    
    pdiagnose->log(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG");
    
    
    pdiagnose->setTerminal(M_TERM_SYS);
    
    pdiagnose->log(LL_ERR,"this is just test\n");
    
    pdiagnose->log(LL_WARN,"this is just test %d\n",i);
    
    pdiagnose->log(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");
    
    pdiagnose->log(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");
    
    pdiagnose->log(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG");
    
    
    pdiagnose->setTerminal(M_TERM_FILE,"debuglog");
    
    pdiagnose->log(LL_ERR,"this is just test\n");
    
    pdiagnose->log(LL_WARN,"this is just test %d\n",101);
    
    pdiagnose->log(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");
    
    pdiagnose->log(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");
    
    pdiagnose->log(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG");
    
    pdiagnose->setTerminal(M_TERM_NET);
    
    pdiagnose->log(LL_ERR,"this is just test\n");
    
    pdiagnose->log(LL_WARN,"this is just test %d\n",101);
    
    pdiagnose->log(LL_NOTICE,"this is just test %d,%s\n",++i, "OK","NOTICE");
    
    pdiagnose->log(LL_INFO,"this is just test %d,%s,%s\n",++i, "OK", "INFO");
    
    pdiagnose->log(LL_DEBUG,"this is just test %d,%s,%s\n",++i, "OK","DEBUG");
    
}

