#ifndef __COMM_H__
#define __COMM_H__

//定义一些类型枚举

enum CMD 
{
    CMD_BASE = 10000,
    QUERY_USER_INFO = CMD_BASE + 1
};

enum RETCODE 
{
    SUCESS_BASE = 20000,
    USER_LOG_SUCESS = SUCESS_BASE + 1,

    FAILED_BASE = -20000,
    USER_NOT_EXIT = FAILED_BASE - 1,
    USER_ACCOUNT_IDINUSED = FAILED_BASE - 2,
    USER_ACCOUNT_IDINFORBID = FAILED_BASE - 3,
    USER_ACCOUNT_PWDERROR = FAILED_BASE - 4
};

enum PACKAGE_ID
{
    //无效包
    ERROR_PACK = -1,
    
    //心跳包
    HEARTBEAT_PACK = 0,

    //登录包
    LOGIN_PACK = 1
};

#endif