#include <muduo/base/Logging.h>
#include "httprequest.h"
#include "httpresponse.h"
#include "httpparser.h"
#include "httpdataparser.h"

using namespace muduo;

namespace net_http
{
    size_t HttpDataParser::ms_maxHeaderSize = 80 * 1024;
    size_t HttpDataParser::ms_maxBodySize = 10 * 1024 * 1024;

    HttpDataParser::HttpDataParser()
        : HttpParser(HTTP_REQUEST)
    {
        
    }

    HttpDataParser::~HttpDataParser()
    {
        LOG_INFO << "HttpDataParser destroyed";
    }

    int HttpDataParser::onMessageBegin()
    {
        m_request.clear();
        return 0;    
    }

    int HttpDataParser::onUrl(const char* at, size_t length)
    {
        m_request.url.append(at, length);
        return 0;
    }

    int HttpDataParser::onHeader(const string& field, const string& value)
    {        
        if(m_parser.nread >= ms_maxHeaderSize)
        {
            m_errorCode = 413;
            return -1;         
        }
    
        //LOG_INFO << "HttpDataParser::onHeader: " << field << " " << value;
        m_request.headers.insert(make_pair(field, value));    
        return 0;
    }

    int HttpDataParser::onBody(const char* at, size_t length)
    {
        if(m_request.body.size() + length > ms_maxBodySize)
        {
            m_errorCode = 413;
            return -1;    
        }

        //LOG_INFO << "HttpDataParser::onBody: " << at;

        m_request.body.append(at, length);    
        return 0;
    }

    int HttpDataParser::onHeadersComplete()
    {
        m_request.majorVersion = m_parser.http_major;
        m_request.minorVersion = m_parser.http_minor;
        
        m_request.method = (http_method)m_parser.method;

        m_request.parseUrl();

        return 0;    
    }

    int HttpDataParser::onMessageComplete()
    {
        if(!m_parser.upgrade)
        {
            
        }
        return 0;     
    }

    int HttpDataParser::onUpgrade(const char* at, size_t length)
    {
        
        return 0;    
    }

    int HttpDataParser::onError(const HttpError& error)
    {
        
        return 0;    
    }

}
