/**************************************************************************

Copyright   : NEXTVPU
Author      : sicheng.lin
Date        : 2019-01-07
Description : micro def

**************************************************************************/

#ifndef CLIENT_LOGMICRODEF_H_
#define CLIENT_LOGMICRODEF_H_

#include "nvp_types.h"

//  terminal type ,include file ,net,syslog,standard error
#define M_TERM_FILE (0)
#define M_TERM_NET  (1)
#define M_TERM_SYS  (2)
#define M_TERM_STD  (3)

//  LL means log level
#define LL_ERR    (0)              
#define LL_WARN   (1)          
#define LL_NOTICE (2)           
#define LL_INFO  (3)             
#define LL_DEBUG   (4)            

#define LL_MAX (5)

//  the max length of one message
#define M_MAX_MSG_LENGTH (128)


#endif    //  CLIENT_LOGMICRODEF_H_
