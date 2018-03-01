#ifndef __BASE_HANDLE_H__
#define __BASE_HANDLE_H__

#include <google/protobuf/message.h>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

class GmServer;

class BaseHandle 
{
public:
    //BaseHandle () {}
    BaseHandle (GmServer *gmserver, const MessagePtr& messageptr) : 
                gmserver_(gmserver),
                message_(messageptr) {}
    virtual ~BaseHandle() {}

    virtual void execute() = 0;

private:
    GmServer *gmserver_;
    MessagePtr message_;
};

typedef boost::shared_ptr<BaseHandle> BaseHandlePtr;

#endif