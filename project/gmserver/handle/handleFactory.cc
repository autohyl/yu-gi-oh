#include <muduo/base/Logging.h>
#include "handleFactory.h"
#include "loginHandle.h"
#include <string>

bool HandleFactory::createHandle(const MessagePtr& message, BaseHandlePtr &handle, GmServer* gmserver)
{
    bool ret = true;
    std::string typeName = message->GetTypeName();
    if (typeName == "gmserver.LoginInfo")
        handle.reset(new LoginHandle(gmserver, message));
    else {
        LOG_ERROR << "error GetTypeName";
        ret = false;
    }   
    return ret;
}