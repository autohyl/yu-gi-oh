#pragma once

#include <string>
#include <map>
#include <stdint.h>

extern "C"
{
#include "http_parser.h"
}

#include "http.h"

namespace net_http
{
    class HttpRequest
    {
    public:
        HttpRequest();
        ~HttpRequest();

        void clear();
        void parseUrl();
        muduo::string dump();

        muduo::string url;
        muduo::string body;

        muduo::string schema;
        
        muduo::string host;
        muduo::string path;
        muduo::string query;

        Headers_t headers;

        Params_t params;
        
        unsigned short majorVersion;
        unsigned short minorVersion;

        http_method method;

        uint16_t port;

        void parseQuery();
    };
        
}

