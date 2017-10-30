//#define MUDUO_STD_STRING //for string at makefile

#include "general.h"

#include <muduo/base/Logging.h>

#include <boost/bind.hpp>

// using namespace muduo;
// using namespace muduo::net;

GeneralServer::GeneralServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr)
  : server_(loop, listenAddr, "GeneralServer"),
    dispatcher_(boost::bind(&GeneralServer::onUnknownMessage, this, _1, _2, _3)),
    codec_(boost::bind(&ProtobufDispatcher::onProtobufMessage, &dispatcher_, _1, _2, _3))
{
  dispatcher_.registerMessageCallback<generalmess::Heartbeat>(
      boost::bind(&GeneralServer::onHeartbeat, this, _1, _2, _3));
  server_.setConnectionCallback(
      boost::bind(&GeneralServer::onConnection, this, _1));
  //server_.setMessageCallback(
      //boost::bind(&ProtobufCodec::onMessage, &codec_, _1, _2, _3));
  server_.setMessageCallback(
      boost::bind(&GeneralServer::onMessage, this, _1, _2, _3));
}

void GeneralServer::onUnknownMessage(const muduo::net::TcpConnectionPtr& conn,
                      const MessagePtr& message,
                      muduo::Timestamp)
{
  LOG_INFO << "onUnknownMessage: " << message->GetTypeName();
  conn->shutdown();
}

void GeneralServer::onHeartbeat(const muduo::net::TcpConnectionPtr& conn,
              const HeartbeatPtr& message,
              muduo::Timestamp)
{
  LOG_INFO << "onHeartbeat: " << message->GetTypeName();
  conn->shutdown();
}

void GeneralServer::start()
{
  server_.start();
}

void GeneralServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
  LOG_INFO << "GeneralServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
}

void GeneralServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
  muduo::string msg(buf->retrieveAllAsString());
  LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
           << "data received at " << time.toString();
  //conn->send(msg);
  LOG_INFO << "========================================";

  const char* data = msg.c_str();

  unsigned char value = data[0];

  LOG_INFO << "first value: " << value;

  uint32_t net_length = 0;
	uint32_t net_bodylen = 0;
	int len = 1;
	memcpy(&net_length, data+len, 4);
	len += 4;
	memcpy(&net_bodylen, data+len, 4);
	len += 4;
	uint32_t length = ntohl(net_length);
	uint32_t bodylen = ntohl(net_bodylen);

	if (length != bodylen + 10)
	{
		LOG_INFO << "length != bodylen + 10";
    return ;
	}

	//char * tmp_buf=data+len; 
	//need decry
	//de(tmp_buf,bodylen);

	muduo::string request_buff;
	request_buff.assign(data+len, bodylen);

  //protobuf test
  Heartbeat heartbeat;
  if (heartbeat.ParseFromString(request_buff)) {
    LOG_INFO << "Get Heartbeat - recode: " << heartbeat.recode() << " seq: " << heartbeat.seq(); 
  }
  else {
    LOG_INFO << "ParseFromString msg failure!!!";
  }
  //end
}

void GeneralServer::setTimer(double delay) {
  delay_ = delay;
  muduo::net::EventLoop* loop_ = server_.getLoop();
  loop_->runAfter(delay, boost::bind(&GeneralServer::check_time_out, this));
}

void GeneralServer::check_time_out() {
  LOG_INFO << "check_time_out";
  muduo::net::EventLoop* loop_ = server_.getLoop();
  loop_->runAfter(delay_, boost::bind(&GeneralServer::check_time_out, this));
}

