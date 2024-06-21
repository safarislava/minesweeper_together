#ifndef SERVER_SERVERSOCKET_H
#define SERVER_SERVERSOCKET_H
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#pragma comment(lib, "ws2_32")

class SocketManager{
public:
    int serverSocket;
    std::vector<int> clientSockets;

    void init(){
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(1234);
        in_addr ip_to_num{};
        inet_pton(AF_INET, "192.168.31.216", &ip_to_num);
        serverAddress.sin_addr = ip_to_num;

        bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress));

        listen(serverSocket, SOMAXCONN);
    }
};

#endif //SERVER_SERVERSOCKET_H
