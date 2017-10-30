#include "echo.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

// using namespace muduo;
// using namespace muduo::net;

//�ػ��������к���
bool daemo_run() {
	pid_t pid = fork();
	if (pid < 0) {
		std::cout << "fork error" << std::endl;
		return false;
	}
	else if (pid > 0) {
		exit(0);
	}

	//�����ļ�Ȩ������
	umask(0);

	pid_t sid = setsid();
	if (sid < 0) {
		std::cout << "setsid error" << std::endl;
		return false; 
	}
	//�л�����Ŀ¼
	if (chdir("/tmp") < 0) {
		std::cout << "chdir error" << std::endl;
		return false;
	}
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	int fd = open("/dev/null", O_RDWR, 0);
	//ʹ���ػ����̴�/dev/null��ʹ������ļ�������0��1��2��
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

  	LOG_INFO << "pid = " << getpid();
  	muduo::net::EventLoop loop;
  	muduo::net::InetAddress listenAddr(2007);
  	EchoServer server(&loop, listenAddr);
  	server.start();
  	loop.loop();
}

