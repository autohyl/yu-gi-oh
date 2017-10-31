#include "general.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

//守护进程运行函数
bool daemo_run() {
	pid_t pid = fork();
	if (pid < 0) {
		std::cout << "fork error" << std::endl;
		return false;
	}
	else if (pid > 0) {
		exit(0);
	}

	//设置文件权限掩码
	umask(0);

	pid_t sid = setsid();
	if (sid < 0) {
		std::cout << "setsid error" << std::endl;
		return false; 
	}
	//切换工作目录
	/**if (chdir("/tmp") < 0) {
		std::cout << "chdir error" << std::endl;
		return false;
	}*/
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	int fd = open("/dev/null", O_RDWR, 0);
	//使得守护进程打开/dev/null，使其具有文件描述符0、1、2。
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
	}
	if (fd > 2)
		close(fd);
	return true;
}

//加载脚本
void initScript() {

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
	if (bdaemon)
		daemo_run();

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
  	muduo::net::EventLoop loop;
  	muduo::net::InetAddress listenAddr(ip_address, ip_port);
  	GeneralServer server(&loop, listenAddr);
  	server.start();
	server.setTimer(1);
  	loop.loop();
}

