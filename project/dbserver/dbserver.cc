#include "dbserver.h"
#include "comm.h"
#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
#include <stdio.h>

DBServer::DBServer(EventLoop* loop,
                       const InetAddress& listenAddr)
  : server_(loop, listenAddr, "DBServer")
{
    server_.setConnectionCallback(
        boost::bind(&DBServer::onConnection, this, _1));
    server_.setMessageCallback(
        boost::bind(&DBServer::onMessage, this, _1, _2, _3));
}


void DBServer::init_database(CConfigFileReader &config) {
	try {
		muduo::string dbserver = config.GetConfigName("dbserver");
		muduo::string dbuser = config.GetConfigName("dbuser");
		muduo::string dbpassword = config.GetConfigName("dbpassword");
		muduo::string dbname = config.GetConfigName("dbname");
		mysql.Connect(dbserver.c_str(), dbuser.c_str(), dbpassword.c_str(), dbname.c_str());
	}catch(CCommonException &e){
        LOG_ERROR << e.GetErrMsg();
    }
}

void DBServer::start(CConfigFileReader &config)
{
	init_database(config);
    server_.start();
}

void DBServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "DBServer - " << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");
}

void DBServer::onMessage(const TcpConnectionPtr& conn,
                           Buffer* buf,
                           Timestamp time)
{
	#if 0
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
            << "content: " << msg << ", "
            << "data received at " << time.toString();
	#endif

	LOG_DEBUG << "onMessage conn_empty: " << conn->getContext().empty();
	
	unpacket(buf, conn);
}

void DBServer::packetByString(int id, const string& msg, const TcpConnectionPtr& conn)
{
	assert(msg.size() <= kMaxPacketLen);
	Buffer buf;
	buf.append(msg);
	packet(id, &buf, conn);
}

void DBServer::packet(int id, Buffer* buf, const TcpConnectionPtr& conn)
{
	size_t len = buf->readableBytes();
	LOG_DEBUG << "packet " << len;
	assert(len <= kMaxPacketLen);
	uint8_t header[kHeaderLen] = {
		static_cast<uint8_t>(len),
		static_cast<uint8_t>(id & 0xFF),
		static_cast<uint8_t>((id & 0xFF00) >> 8)
	};
	buf->prepend(header, kHeaderLen);
	if (conn)
	{
		conn->send(buf);
	}
}

void DBServer::unpacket(Buffer* buf, const TcpConnectionPtr& conn)
{
	while (buf->readableBytes() > kHeaderLen)
	{
		int len = static_cast<uint8_t>(*buf->peek());
		if (buf->readableBytes() < len + kHeaderLen)
		{
			break;
		}
		else
		{
			int id = static_cast<uint8_t>(buf->peek()[1]);
			id |= (static_cast<uint8_t>(buf->peek()[2]) << 8);

			if (id != 0)
			{
				//if (conn->getContext().empty())
				{
					conn->setContext(id);
				}
				muduo::string cmd(buf->peek() + kHeaderLen, len);
				LOG_INFO << "unpacket cmd " << cmd << " conn_id: " << id;
				handleRequest(cmd, conn);
			}
			else
			{
				#if 0
				muduo::string cmd(buf->peek() + kHeaderLen, len);
				LOG_INFO << "unpacket cmd " << cmd;
				handleRequest(cmd, conn);
				#endif
			}
			buf->retrieve(len + kHeaderLen);
		}
	}
}

void DBServer::handleRequest(const muduo::string& msg, const TcpConnectionPtr& conn) {
	Json::Value jsonRequest;
    Json::Reader reader;
    if(reader.parse(msg, jsonRequest) == false) {
		//·¢ËÍ´íÎóretcode
		LOG_ERROR << "json parse failed";
		return ;
	}

	CMD cmd = (CMD)jsonRequest["cmd"].asInt();

	switch (cmd) {
		case QUERY_USER_INFO:
			process_query_user(jsonRequest, conn);
			break;
		default:
			LOG_ERROR << "cmd error";
	}
}

void DBServer::sendMsg(const Json::Value &jsonResponse, const TcpConnectionPtr& conn)
{
	Json::FastWriter writer;
    muduo::string msg = writer.write(jsonResponse);
	if (!conn->getContext().empty())
	{
		int id = boost::any_cast<int>(conn->getContext());
		assert(id > 0 && id <= kMaxConns);
		packetByString(id, msg, conn);
	}
}

void DBServer::process_query_user(const Json::Value& jsonRequest, const TcpConnectionPtr& conn) 
{
	muduo::string userId = jsonRequest["userId"].asString();
	muduo::string userPwd = jsonRequest["userPwd"].asString();

	RETCODE retcode_rsp;

	Json::Value jsonResponse;
	jsonResponse["cmd"] = QUERY_USER_INFO;

	char sql[1024];
	snprintf(sql, sizeof(sql), "select ISUSED, ISFORBID, USERID, PASSWORD, LOGINID from LOGIN where LOGINID = '%s'", userId.c_str());
	LOG_DEBUG << "sql: " << sql;
	try {
        mysql.Query(sql);
        char** row = mysql.FetchRow();
        
		if (row == NULL) {
			retcode_rsp = USER_NOT_EXIT;
		}
		else {
			int isused = strtoul(row[0], NULL, 10);
			int isforbid = strtoul(row[1], NULL, 10);
			string pwd = row[3];
	
			if (isused != 0) {
				retcode_rsp = USER_ACCOUNT_IDINUSED;
			}
			else if (isforbid != 0) {
				retcode_rsp = USER_ACCOUNT_IDINFORBID;
			}
			else if (pwd != userPwd) {
				retcode_rsp = USER_ACCOUNT_PWDERROR;
			}
			else {
				retcode_rsp = USER_LOG_SUCESS;
			}
		}

    } catch (CMysqlException &e) {
        LOG_ERROR << e.GetErrMsg();
    }

	jsonResponse["retcode"] = retcode_rsp;
	sendMsg(jsonResponse, conn);
}
