#include "dbserver.h"
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

  	LOG_INFO << "pid = " << getpid();
	muduo::string ip_address = config.GetConfigName("listenip");
	uint16_t ip_port = phelper::from_str<uint16_t>(config.GetConfigName("listenport"));
  	EventLoop loop;
  	InetAddress listenAddr(ip_address, ip_port);
  	DBServer server(&loop, listenAddr);
  	server.start(config);
  	loop.loop();
}

