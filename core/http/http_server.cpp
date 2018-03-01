#include "httpdataparser.h"
#include "httpresponse.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

using namespace std;

char _recvbuf[2048];
char _sendbuf[2048];

int main() {

    sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8001);
    server_addr.sin_family = AF_INET;

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    int sock_reuse=1; 
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&sock_reuse, sizeof(sock_reuse)); 

    bind(listenfd, (sockaddr*)&server_addr, sizeof(server_addr));

    listen(listenfd, 5);

    socklen_t cilent_len = sizeof(client_addr);

    while (1) {
        int clientfd = accept(listenfd, (sockaddr*)&client_addr, &cilent_len);
        cout << "clientfd: " << clientfd << endl;

        net_http::HttpDataParser http_parser;

        int n = read(clientfd, _recvbuf, sizeof(_recvbuf));

        http_parser.execute(_recvbuf, strlen(_recvbuf));

        //cout << "recv: " << _recvbuf << "len: " << strlen(_recvbuf) << endl;

        cout << "-----------------body: " << http_parser.getBody() << endl;

        net_http::HttpResponse resp;
        resp.statusCode = 200;
        resp.setContentType("text/html");
        resp.setKeepAlive(true);
        resp.enableDate();
    
        resp.body.append("first"); 
        resp.body.append("Hello World");

        muduo::string dump = resp.dump();

        n = send(clientfd, dump.c_str(), dump.length(), 0);
        cout << "send n: " << dump << endl;

        //cout << "host: " << http_parser.getHost() << endl;

        close(clientfd);
    }

    close(listenfd);

    return 0;
}