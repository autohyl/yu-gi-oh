/**
  *数据库服务器
  *负责查询数据库功能
*/

#ifndef Y_DBSERVER_H
#define Y_DBSERVER_H

#include <muduo/net/TcpServer.h>
#include <core/ConfigFileRead.h>
#include "database/cmysql.h"
#include "json/json.h"

using namespace muduo;
using namespace muduo::net;

const int 		kMaxConns = 10;  // 65535
const size_t 	kMaxPacketLen = 255;
const size_t 	kHeaderLen = 3;

class DBServer
{
public:
    DBServer(EventLoop* loop,
              const InetAddress& listenAddr);

    void start(CConfigFileReader &config);  // calls server_.start();

private:
	void init_database(CConfigFileReader &config);
	
    void onConnection(const TcpConnectionPtr& conn);

    void onMessage(const TcpConnectionPtr& conn,
                  Buffer* buf,
                  Timestamp time);

    void packetByString(int id, const string& msg, const TcpConnectionPtr& conn);
    void packet(int id, Buffer* buf, const TcpConnectionPtr& conn);   
    void unpacket(Buffer* buf, const TcpConnectionPtr& conn);       
    void handleRequest(const muduo::string& msg, const TcpConnectionPtr& conn);     

    void sendMsg(const Json::Value &jsonResponse, const TcpConnectionPtr& conn);

    void process_query_user(const Json::Value& jsonRequest, const TcpConnectionPtr& conn);

    TcpServer server_;
    CMysql mysql;
};

#endif
