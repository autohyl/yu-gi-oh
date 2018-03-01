#ifndef __HANDLE_FACTORY_H__
#define __HANDLE_FACTORY_H__

/**
    消息包派生工厂，用于针对某种pb生产出相对应处理的类
*/

#include "baseHandle.h"

class HandleFactory
{
public:
    static bool createHandle(const MessagePtr& message, BaseHandlePtr &handle, GmServer* gmserver);
};

#endif