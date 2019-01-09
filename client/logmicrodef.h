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
#define LL_ALERT  (0)   //  message should print alway,but not error,just key info
#define LL_ERR    (1)   //  message should print alway,must fix bug,if print error message           
#define LL_WARN   (2)   //  Print by level         
#define LL_NOTICE (3)   //  Print by level         
#define LL_INFO   (4)   //  Print by level           
#define LL_DEBUG  (5)   //  Print by level          

#define LL_MAX (LL_DEBUG + 1)

//  the max length of one message
#define M_MAX_MSG_LENGTH (128)
#define NVP_SUCCESS      (0)


#endif    //  CLIENT_LOGMICRODEF_H_
