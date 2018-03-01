#pragma once

#include <vector>
#include <stdint.h>
#include <sstream>
#include <muduo/base/Types.h>

namespace net_http
{
    class StringUtil
    {
    public:
        static std::vector<muduo::string> split(const muduo::string& src, const muduo::string& delim, size_t maxParts = size_t(-1));
        static uint32_t hash(const muduo::string& str);

        static muduo::string lower(const muduo::string& src);
        static muduo::string upper(const muduo::string& src);

        static muduo::string lstrip(const muduo::string& src);
        static muduo::string rstrip(const muduo::string& src);
        static muduo::string strip(const muduo::string& src);

        static muduo::string hex(const muduo::string& src);
        static muduo::string hex(const uint8_t* src, size_t srcLen);

        static muduo::string base64Encode(const muduo::string& src);
        static muduo::string base64Decode(const muduo::string& src);

        static muduo::string md5Bin(const muduo::string& src);
        static muduo::string md5Hex(const muduo::string& src);

        static muduo::string sha1Bin(const muduo::string& src);
        static muduo::string sha1Hex(const muduo::string& src);

        template<typename T>
        static muduo::string toString(const T& in)
        {
            std::stringstream str;
            str << in;
            return str.str();    
        }

        static muduo::string toString(const char* in)
        {
            return muduo::string(in);    
        }

        static muduo::string toString(const muduo::string& in)
        {
            return muduo::string(in);
        }
    };    
}

