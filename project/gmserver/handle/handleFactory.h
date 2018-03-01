#ifndef __HANDLE_FACTORY_H__
#define __HANDLE_FACTORY_H__

/**
    ��Ϣ�������������������ĳ��pb���������Ӧ�������
*/

#include "baseHandle.h"

class HandleFactory
{
public:
    static bool createHandle(const MessagePtr& message, BaseHandlePtr &handle, GmServer* gmserver);
};

#endif