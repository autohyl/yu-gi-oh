#pragma once

#include <map>

extern "C"
{
#include "http_parser.h"
}

#include "http.h"
#include "httpparser.h"
#include "httprequest.h"

namespace net_http
{
    class HttpRequest;
    class HttpResponse;

    class HttpDataParser : public HttpParser
    {
    public:
        HttpDataParser();

        ~HttpDataParser();

        static void setMaxHeaderSize(size_t size) { ms_maxHeaderSize = size; }
        static void setMaxBodySize(size_t size) { ms_maxBodySize = size; }

        muduo::string getBody() const {
            return m_request.body;
        }

        muduo::string getHost() const {
            return m_request.host;
        }

        muduo::string getQuery() const {
            return m_request.query;
        }
    
    private:
        int onMessageBegin();
        int onUrl(const char* at, size_t length);
        int onHeader(const muduo::string& field, const muduo::string& value);
        int onHeadersComplete();
        int onBody(const char* at, size_t length);
        int onMessageComplete();
        int onUpgrade(const char* at, size_t length);
        int onError(const HttpError& error);
        
    private:
        HttpRequest m_request;
        static size_t ms_maxHeaderSize;
        static size_t ms_maxBodySize;
    };    
}

