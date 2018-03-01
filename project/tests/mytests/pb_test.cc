#define _GNU_SOURCE 1
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <zlib.h>
#include "GmServer.pb.h"
#include "net.h"

#define BUFFER_SIZE 64

using namespace std;
using namespace gmserver;

#if 0
void onMessage(const muduo::net::TcpConnectionPtr& conn,
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
	
		try {
		respond("hello lua");
		} catch (const luabridge::LuaException& e) {
		LOG_ERROR<< e.what();
		}
	}
	else {
		LOG_INFO << "ParseFromString msg failure!!!";
	}
	//end
}
#endif

void fillEmptyBuffer(string &buff, const google::protobuf::Message& message) {
    const string& typeName = message.GetTypeName();
    cout << "typeName: " << typeName << endl;
    int32_t nameLen = static_cast<int32_t>(typeName.size()+1);

    char _data[1024];
    memset(_data, '\0', sizeof _data);

    int32_t index = 4;
    uint32_t netlen = htonl(nameLen);
    memcpy(_data + index, (const void*)&netlen, sizeof netlen);
    index += sizeof netlen;

    memcpy(_data + index, typeName.c_str(), nameLen);
    index += nameLen;

    //cout << "netlen: " << sizeof netlen << " nameLen: " << sizeof nameLen << endl;

    int byte_size = message.ByteSize();

    uint8_t* start = reinterpret_cast<uint8_t*>(_data + index);
    uint8_t* end = message.SerializeWithCachedSizesToArray(start);
    if (end - start != byte_size)
    {
        cout << "end - start != byte_size" << endl;
    }

    index += byte_size;

    int32_t checkSum = static_cast<int32_t>(::adler32(1,reinterpret_cast<const Bytef*>(_data + 4),index - 4));
    uint32_t sumnetlen = htonl(checkSum);
    memcpy(_data + index, (const void*)&sumnetlen, sizeof sumnetlen);
    index += sizeof sumnetlen;

    assert(index - 4 == sizeof nameLen + nameLen + byte_size + sizeof checkSum);
    uint32_t len = htonl(index - 4);
    memcpy(_data, (const void*)&len, sizeof len);

    buff.assign(_data, index);
}

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
			LoginInfo loginInfo;
			cout << "desc: " << loginInfo.GetDescriptor() << endl;
			loginInfo.set_user_id("yulin");
			loginInfo.set_user_pwd("haha");
            
            string sendbuff;
            fillEmptyBuffer(sendbuff, loginInfo);
			send(sockfd, sendbuff.c_str(), sendbuff.size(), 0);
		}
	}
	
	close(sockfd);
	return 0;
}
