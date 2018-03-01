/**
  *ͨ�÷�����
  *�����¼,�����˺�,�������ط������ȹ���
*/

#ifndef Y_GMSERVER_H
#define Y_GMSERVER_H

#include "codec.h"
#include "dispatcher.h"
#include "GmServer.pb.h"
#include "RegLua/RegLua.h"
#include "json/json.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <queue>

using namespace gmserver;
using namespace muduo;
using namespace muduo::net;

const int 		kMaxConns = 10;  // 65535
const size_t 	kMaxPacketLen = 255;
const size_t 	kHeaderLen = 3;

typedef boost::shared_ptr<gmserver::Heartbeat> HeartbeatPtr;
typedef boost::shared_ptr<gmserver::LoginInfo> LoginInfoPtr;

class GmServer
{
public:
	GmServer(EventLoop* loop,
             		const InetAddress& listenAddr, const InetAddress& dbAddr);

	~GmServer() {
		if (pLState_ != NULL) {
			lua_close(pLState_);
			pLState_ = NULL;
		}
	}

  	void start();  // calls server_.start();

private:
	void onConnection(const TcpConnectionPtr& conn);

	#if 0
	void onMessage(const muduo::net::TcpConnectionPtr& conn,
					muduo::net::Buffer* buf,
					muduo::Timestamp time);
	#endif

	//�����ݿ�����������Ľӿ�
	void onDBConnection(const TcpConnectionPtr& conn);
	void onDBMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp);
	void parse_DB_message(Buffer* buf);
	void send_to_DB(const TcpConnectionPtr& conn, const string& msg);
	void sendDBPacket(int id, Buffer* buf);
	void handleResponse(const string& cmd, const TcpConnectionPtr& conn);
	//end

	void send_to_client(const string& msg, const TcpConnectionPtr& conn);

	void onUnknownMessage(const TcpConnectionPtr& conn,
							const MessagePtr& message,
							Timestamp);

	void onHeartbeat(const TcpConnectionPtr& conn,
					const HeartbeatPtr& message,
					Timestamp);

	void onLogin(const TcpConnectionPtr& conn,
				const LoginInfoPtr& message,
				Timestamp);

	void do_rsp_login(Json::Value jsonResponse, const TcpConnectionPtr& conn);

	void check_time_out();//��ʱ���ص�����

	void initTask();

public:
	void setTimer(double delay);//���ö�ʱ��

	TcpServer server_;
	TcpClient dbclient_; //�����������ݿ�
	ProtobufDispatcher dispatcher_;
	ProtobufCodec codec_;

	// MutexLock mutex_;
	TcpConnectionPtr dbclientConn_;
	std::map<int, TcpConnectionPtr> clientConns_;
	std::queue<int> availIds_;

	double delay_;//��ʱ���ص�ʱ��
	
	struct lua_State *pLState_;
	luabridge::LuaRef respond_;
};

#endif
