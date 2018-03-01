#pragma once

#include <stdint.h>

#include "http.h"

namespace net_http
{
    class HttpUtil
    {
    public:
        static const muduo::string& codeReason(int code);
        static const char* methodStr(uint8_t method);
    
        static muduo::string escape(const muduo::string& src);
        static muduo::string unescape(const muduo::string& src);
 
        //http header key is Http-Head-Case format
        static muduo::string normalizeHeader(const muduo::string& src);
    };
}

