#include "gmserver.h"
#include "RegLua/RegLua.h"
#include <muduo/base/Logging.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/net/EventLoop.h>
#include <core/ConfigFileRead.h>
#include <core/phelper.h>

// using namespace muduo;
// using namespace muduo::net;

muduo::AsyncLogging* g_asyncLog = NULL;
void asyncOutput(const char* msg, int len)
{
    if (g_asyncLog != NULL)
    {
        g_asyncLog->append(msg, len);
        //std::cout << msg << std::endl;
    }
}

//加载脚本
int initScript(const char* scriptpath) {
	//注册任务，监听等
    struct lua_State *pLState = luaL_newstate();
    if (NULL == pLState)
    {
        LOG_ERROR <<  "luaL_newstate error.";
        return -1;
    }

    luaL_openlibs(pLState);
    Y_RegAll(pLState);

    string strLuaFile = scriptpath;
	strLuaFile += "start.lua";
    if (0 != luaL_dofile(pLState, strLuaFile.c_str()))
    {
    	LOG_ERROR << lua_tostring(pLState, -1);
        lua_close(pLState);
        return -1;
    }

    lua_close(pLState);

    return 0;
}

int main(int argc, char* argv[])
{
	int ch;
	bool bdaemon = false;
	while ((ch = getopt(argc, argv, "d")) != -1) {
		switch (ch) {
			case 'd':
				bdaemon = true;
				break;
		}
	}
	if (bdaemon) {
		if (daemon(1, 0) == -1) {
			LOG_ERROR << "dbserver run daemon failed";
		}
	}

	CConfigFileReader config("./config/server.conf");
	
	muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
    int kRollSize = 500 * 1000 * 1000;
	const char* logfilepath = config.GetConfigName("logdir");
    muduo::AsyncLogging log(logfilepath, kRollSize);
    log.start();
    g_asyncLog = &log;
    muduo::Logger::setOutput(asyncOutput);

	//加载脚本
	const char* scriptpath = config.GetConfigName("scriptdir");
	if (initScript(scriptpath) == -1) {
		LOG_ERROR << "initScript failed";
	}

  	LOG_INFO << "pid = " << getpid();

	muduo::string ip_address = config.GetConfigName("listenip");
	uint16_t ip_port = phelper::from_str<uint16_t>(config.GetConfigName("listenport"));

	//数据库服务器地址和端口
	muduo::string dbip_address = config.GetConfigName("dbserverip");
	uint16_t dbip_port = phelper::from_str<uint16_t>(config.GetConfigName("dbserverport"));

  	muduo::net::EventLoop loop;
  	muduo::net::InetAddress listenAddr(ip_address, ip_port);
	muduo::net::InetAddress DBAddr(dbip_address, dbip_port); 
  	GmServer server(&loop, listenAddr, DBAddr);
  	server.start();
	server.setTimer(1);
  	loop.loop();
}

