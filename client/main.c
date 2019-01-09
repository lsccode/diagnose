/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : test log function

**************************************************************************/

#include "logcapi.h"

int main(int argc,char *argv[])
{
    initLog();
    setTerminal(M_TERM_STD,NULL);
    setLevel(LL_INFO);
    NLALERT("log level %s (%d)\n","alert",LL_ALERT);
    NLERROR("log level %s (%d)\n","error",LL_ERR);    
    NLWARN("log level %s (%d)\n","warn",LL_WARN);  
    NLNOTICE("log level %s (%d)\n","notice",LL_NOTICE);   
    NLINFO("log level %s (%d)\n","info",LL_INFO);    
    NLDEBUG("log level %s (%d)\n","debug",LL_DEBUG);     
    
    setTerminal(M_TERM_SYS,NULL);  
    setLevel(LL_NOTICE);
    NLALERT("log level %s (%d)\n","alert",LL_ALERT);
    NLERROR("log level %s (%d)\n","error",LL_ERR);    
    NLWARN("log level %s (%d)\n","warn",LL_WARN);  
    NLNOTICE("log level %s (%d)\n","notice",LL_NOTICE);   
    NLINFO("log level %s (%d)\n","info",LL_INFO);    
    NLDEBUG("log level %s (%d)\n","debug",LL_DEBUG);
    
    setTerminal(M_TERM_FILE,"debug.log");
    setLevel(LL_WARN);
    NLALERT("log level %s (%d)\n","alert",LL_ALERT);
    NLERROR("log level %s (%d)\n","error",LL_ERR);    
    NLWARN("log level %s (%d)\n","warn",LL_WARN);  
    NLNOTICE("log level %s (%d)\n","notice",LL_NOTICE);   
    NLINFO("log level %s (%d)\n","info",LL_INFO);    
    NLDEBUG("log level %s (%d)\n","debug",LL_DEBUG);
    
    setTerminal(M_TERM_NET,NULL); 
    setLevel(LL_ERR);
    NLALERT("log level %s (%d)\n","alert",LL_ALERT);
    NLERROR("log level %s (%d)\n","error",LL_ERR);    
    NLWARN("log level %s (%d)\n","warn",LL_WARN);  
    NLNOTICE("log level %s (%d)\n","notice",LL_NOTICE);   
    NLINFO("log level %s (%d)\n","info",LL_INFO);    
    NLDEBUG("log level %s (%d)\n","debug",LL_DEBUG);
    
    return 0;
}
