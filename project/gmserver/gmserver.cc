//#define MUDUO_STD_STRING //for string at makefile

#include "gmserver.h"
#include "comm.h"
#include <muduo/base/Logging.h>
#include <boost/bind.hpp>

//using namespace json;

// using namespace muduo;
// using namespace muduo::net;

GmServer::GmServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr,
					   const muduo::net::InetAddress& dbAddr)
  : server_(loop, listenAddr, "GmServer"),
  	dbclient_(loop, dbAddr, "DBClient"),
    dispatcher_(boost::bind(&GmServer::onUnknownMessage, this, _1, _2, _3), this),
    codec_(boost::bind(&ProtobufDispatcher::onProtobufMessage, &dispatcher_, _1, _2, _3)),
    pLState_(luaL_newstate()), respond_(pLState_)
{
	initTask();
	dispatcher_.registerMessageCallback<gmserver::Heartbeat>(
		boost::bind(&GmServer::onHeartbeat, this, _1, _2, _3));
	dispatcher_.registerMessageCallback<gmserver::LoginInfo>(
		boost::bind(&GmServer::onLogin, this, _1, _2, _3));
	server_.setConnectionCallback(
		boost::bind(&GmServer::onConnection, this, _1));
	server_.setMessageCallback(
		boost::bind(&ProtobufCodec::onMessage, &codec_, _1, _2, _3));
	dbclient_.setConnectionCallback(
        boost::bind(&GmServer::onDBConnection, this, _1));
    dbclient_.setMessageCallback(
        boost::bind(&GmServer::onDBMessage, this, _1, _2, _3));
    dbclient_.enableRetry();

	#if 0
	server_.setMessageCallback(
		boost::bind(&GmServer::onMessage, this, _1, _2, _3));
	#endif
}

void GmServer::start()
{
	dbclient_.connect();
  	server_.start();
}

void GmServer::initTask() {
	luaL_openlibs(pLState_);
	Y_RegAll(pLState_);
	muduo::string strLuaFile = "script/echo.lua";
	if (0 != luaL_dofile(pLState_, strLuaFile.c_str()))
	{
		const char *pErr = lua_tostring(pLState_, -1);
		LOG_INFO << pErr;
	}
	respond_ = luabridge::getGlobal(pLState_, "echo");
}

void GmServer::onUnknownMessage(const muduo::net::TcpConnectionPtr& conn,
                      const MessagePtr& message,
                      muduo::Timestamp)
{
	LOG_INFO << "onUnknownMessage: " << message->GetTypeName();
	conn->shutdown();
}

void GmServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << "GmServer - " << conn->peerAddress().toIpPort() << " -> "
			<< conn->localAddress().toIpPort() << " is "
			<< (conn->connected() ? "UP" : "DOWN");
	if (conn->connected())
    {
		int id = -1;
		if (!availIds_.empty())
		{
			id = availIds_.front();
			availIds_.pop();
			clientConns_[id] = conn;
		}

		if (id <= 0)
		{
			// no client id available
			conn->shutdown();
		}
		else
		{
			conn->setContext(id);
		}
    }
    else
    {
		if (!conn->getContext().empty())
		{
			int id = boost::any_cast<int>(conn->getContext());
			assert(id > 0 && id <= kMaxConns);

			if (dbclientConn_)
			{
				// put client id back for reusing
				availIds_.push(id);
				clientConns_.erase(id);
			}
			else
			{
				assert(availIds_.empty());
				assert(clientConns_.empty());
			}
		}
    }
}

void GmServer::send_to_DB(const TcpConnectionPtr& conn, const string& msg)
{
	assert(msg.size() <= kMaxPacketLen);
	int id = boost::any_cast<int>(conn->getContext());
	Buffer buf;
	buf.append(msg);
	sendDBPacket(id, &buf);
}

void GmServer::sendDBPacket(int id, Buffer* buf)
{
	size_t len = buf->readableBytes();
	LOG_DEBUG << "sendDBPacket " << len;
	assert(len <= kMaxPacketLen);
	uint8_t header[kHeaderLen] = {
		static_cast<uint8_t>(len),
		static_cast<uint8_t>(id & 0xFF),
		static_cast<uint8_t>((id & 0xFF00) >> 8)
	};
	buf->prepend(header, kHeaderLen);
	if (dbclientConn_)
	{
		dbclientConn_->send(buf);
	}
}

void GmServer::onDBConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "DBServer " << conn->localAddress().toIpPort() << " -> "
				<< conn->peerAddress().toIpPort() << " is "
				<< (conn->connected() ? "UP" : "DOWN");

	if (conn->connected())
	{
		dbclientConn_ = conn;
		assert(availIds_.empty());
		for (int i = 1; i <= kMaxConns; ++i)
		{
			availIds_.push(i);
		}
	}
	else
	{
		dbclientConn_.reset();
		for (std::map<int, TcpConnectionPtr>::iterator it = clientConns_.begin();
			it != clientConns_.end();
			++it)
		{
			it->second->shutdown();
		}
		clientConns_.clear();
		while (!availIds_.empty())
		{
			availIds_.pop();
		}
	}
}

void GmServer::onDBMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp)
{
	parse_DB_message(buf);
}

void GmServer::parse_DB_message(Buffer* buf)
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
				std::map<int, TcpConnectionPtr>::iterator it = clientConns_.find(id);
				if (it != clientConns_.end())
				{
					//it->second->send(buf->peek() + kHeaderLen, len);
					string msg(buf->peek() + kHeaderLen, len);
					LOG_INFO << "parse_DB_message msg " << msg << " conn_id: " << id;
					handleResponse(msg, it->second);
				}
			}
			else
			{
				#if 0
				string cmd(buf->peek() + kHeaderLen, len);
				LOG_INFO << "parse_DB_message cmd " << cmd;
				doCommand(cmd);
				#endif
			}
			buf->retrieve(len + kHeaderLen);
		}
	}
}

void GmServer::send_to_client(const string& msg, const TcpConnectionPtr& conn) {
	Buffer buf;
	buf.append(msg);
	if (conn)
	{
		conn->send(&buf);
	}
}

void GmServer::handleResponse(const string& msg, const TcpConnectionPtr& conn)
{
	Json::Value jsonResponse; 
	Json::Reader reader;
    if(reader.parse(msg, jsonResponse) == false) {
		//发送错误retcode
		LOG_ERROR << "json parse failed";
		return ;
	}
	CMD cmd = (CMD)jsonResponse["cmd"].asInt();

	switch (cmd) {
		case QUERY_USER_INFO:
			do_rsp_login(jsonResponse, conn);
			break;
		default:
			LOG_ERROR << "cmd error";
	}
}

void GmServer::setTimer(double delay) {
	delay_ = delay;
	muduo::net::EventLoop* loop_ = server_.getLoop();
	loop_->runAfter(delay, boost::bind(&GmServer::check_time_out, this));
}

void GmServer::check_time_out() {
	LOG_INFO << "check_time_out";
	muduo::net::EventLoop* loop_ = server_.getLoop();
	loop_->runAfter(delay_, boost::bind(&GmServer::check_time_out, this));
}

void GmServer::onHeartbeat(const muduo::net::TcpConnectionPtr& conn,
              const HeartbeatPtr& message,
              muduo::Timestamp)
{
	LOG_INFO << "onHeartbeat: " << message->GetTypeName();
	conn->shutdown();
}

void GmServer::onLogin(const muduo::net::TcpConnectionPtr& conn,
              const LoginInfoPtr& message,
              muduo::Timestamp)
{
	LOG_INFO << "onLogin: " << message->GetTypeName();
	LOG_INFO << "user_id: " << message->user_id() 
			 << " user_pwd: " << message->user_pwd()
			 << " conn_id: " << boost::any_cast<int>(conn->getContext());
	//通知数据库服务器查询信息
	Json::Value jsonRequest;
	jsonRequest["cmd"] = QUERY_USER_INFO;
	jsonRequest["userId"] = message->user_id();
	jsonRequest["userPwd"] = message->user_pwd();
	Json::FastWriter writer;
    string strMessage = writer.write(jsonRequest);

	send_to_DB(conn, strMessage);
}

void GmServer::do_rsp_login(Json::Value jsonResponse, const TcpConnectionPtr& conn)
{
	Json::Value retcode_value = jsonResponse["retcode"];
	if (retcode_value != Json::nullValue) {
		string err_msg;
		RETCODE retcode = (RETCODE)jsonResponse["retcode"].asInt();
		switch (retcode) {
			case USER_NOT_EXIT:
				err_msg = "user not exit";
				break;
			case USER_LOG_SUCESS:
				err_msg = "log sucess";
				break;
			default:
				LOG_ERROR << "cmd error";
		}
		send_to_client(err_msg, conn);
		//登录失败,关闭连接
		if (retcode < 0)
			conn->shutdown();
		LOG_ERROR << err_msg;
	} 
}

