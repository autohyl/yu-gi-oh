#define _GNU_SOURCE 1
#include "net.h"
#include "General.pb.h"
#include <string>

using namespace std;
using namespace generalmess;

#define BUFFER_SIZE 64

int main(int argc, char* argv[]) {
	
	if (argc <= 2) {
		printf("usage: %s ip_address port_number\n", basename(argv[0]));
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0);
	if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0){
		printf("connection failed\n");
		close(sockfd);
		return 1;
	}

	pollfd fds[2];
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[0].revents = 0;
	fds[1].fd = sockfd;
	fds[1].events = POLLIN | POLLRDHUP;
	fds[1].revents = 0;

	char read_buf[BUFFER_SIZE];
	int pipefd[2];
	int ret = pipe(pipefd);
	assert(ret != -1);

	while (1) {
		ret = poll(fds, 2, -1);
		if (ret < 0) {
			printf("poll failure\n");
			break;
		}

		if (fds[1].revents & POLLRDHUP) {
			printf("server close the connection\n");
			break;
		}
		else if (fds[1].revents & POLLIN) {
			memset(read_buf, '\0', BUFFER_SIZE);
			recv(fds[1].fd, read_buf, BUFFER_SIZE - 1, 0);
			printf("%s\n", read_buf);
		}

		if (fds[0].revents & POLLIN) {
			ret = splice(0, NULL, pipefd[1], NULL, 32768,
							SPLICE_F_MORE | SPLICE_F_MOVE);
			/**ret = splice(pipefd[0], NULL, sockfd, NULL, 32768,
							SPLICE_F_MORE | SPLICE_F_MOVE);*/
			Heartbeat heartbeat;
			heartbeat.set_recode(0);
			heartbeat.set_seq(1);
			string msg;
			if (!heartbeat.SerializeToString(&msg)) {
				printf("encode failed!!!\n");
				return 0;
			}
			const uint32_t BUF_SIZE = 1<<24;
			char* _sendbuf = new char[BUF_SIZE];;
			unsigned bodylen = msg.size();
			unsigned length = 1 + 4 + 4 + bodylen + 1;

			unsigned net_length = htonl(length);
			unsigned net_bodylen = htonl(bodylen);
			int len = 0;
			char* data = _sendbuf;
			data[0] = 0x05;
			len += 1;
			memcpy(data + len, &net_length, 4);
			len += 4;
			memcpy(data + len, &net_bodylen, 4);
			len += 4;

			//need encriy
			char* tmp_data;	
			tmp_data = new char[bodylen + 1];
			msg.copy(tmp_data, bodylen, 0);
			//en(tmp_data,bodylen);
			memcpy(data + len, tmp_data, bodylen);
			//end
			
			len += bodylen;
			data[len] = 0x06;
			send(sockfd, _sendbuf, length, 0);
			delete[] tmp_data;
			delete[] _sendbuf;
		}
	}
	
	close(sockfd);
	return 0;
}
