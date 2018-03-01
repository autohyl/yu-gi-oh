#pragma once

#include <muduo/base/Types.h>
#include <map>
#include <memory>
#include <strings.h>

extern "C"
{
struct http_parser;    
}

namespace net_http
{

    class HttpParser;

    const int TNET_HTTP_ERROR = 599;

    class HttpError
    {
    public:
        HttpError(int code = 200, const muduo::string& m = muduo::string())
            : statusCode(code)
            , message(m)
        {}    

        //200 for no error
        int statusCode;
        muduo::string message;
    };
    
    enum WsEvent
    { 
        Ws_OpenEvent,
        Ws_CloseEvent, 
        Ws_MessageEvent,
        Ws_PongEvent,    
        Ws_ErrorEvent,
    };


    typedef std::shared_ptr<HttpParser> HttpParser_t;

    enum RequestEvent
    {
        Request_Upgrade, 
        Request_Complete,
        Request_Error,   
    };
    
    //Request_Upgrade: context is &StackBuffer
    //Request_Complete: context is 0
    //Request_Error: context is &HttpError

    enum ResponseEvent
    {
        Response_Complete,
        Response_Error,    
    };

    struct CaseKeyCmp
    {
        bool operator() (const muduo::string& p1, const muduo::string& p2) const
        {
            return strcasecmp(p1.c_str(), p2.c_str()) < 0;
        }    
    };

    typedef std::multimap<muduo::string, muduo::string, CaseKeyCmp> Headers_t;
    typedef std::multimap<muduo::string, muduo::string> Params_t;
}
