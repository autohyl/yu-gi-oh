#pragma once

#include <string>
#include <map>

#include "http.h"

namespace net_http
{
    class HttpResponse
    {
    public:
        HttpResponse();

        HttpResponse(int code, const Headers_t& headers = Headers_t(), const muduo::string& body = "");
        ~HttpResponse();    

        void clear()
        {
            statusCode = 200;
            body.clear();
            headers.clear();    
        }

        void setContentType(const muduo::string& contentType);
        void setKeepAlive(bool on);

        void enableDate();

        //generate http response text
        muduo::string dump();
   
        int statusCode;
        muduo::string body;
        
        Headers_t headers;
    };
    
}

