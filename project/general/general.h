#ifndef MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H
#define MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H

#include "codec.h"
#include "dispatcher.h"
#include "General.pb.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace generalmess;

typedef boost::shared_ptr<generalmess::Heartbeat> HeartbeatPtr;

// RFC 862
class GeneralServer
{
 public:
  GeneralServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr);

  void start();  // calls server_.start();

 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn);

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time);

  void onUnknownMessage(const muduo::net::TcpConnectionPtr& conn,
                        const MessagePtr& message,
                        muduo::Timestamp);

  void onHeartbeat(const muduo::net::TcpConnectionPtr& conn,
                const HeartbeatPtr& message,
                muduo::Timestamp);

  void check_time_out();//定时器回调方法

public:
  void setTimer(double delay);//设置定时器

  muduo::net::TcpServer server_;
  ProtobufDispatcher dispatcher_;
  ProtobufCodec codec_;
  double delay_;//定时器回调时间
};

#endif  // MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H
