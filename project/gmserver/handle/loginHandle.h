#ifndef __LOGIN_HANLE_H__
#define __LOGIN_HANLE_H__

#include "baseHandle.h"

class LoginHandle : public BaseHandle 
{
public:
    LoginHandle(GmServer *gmserver, const MessagePtr& message) : 
                BaseHandle(gmserver, message) {}
    
    void execute();
};

#endif