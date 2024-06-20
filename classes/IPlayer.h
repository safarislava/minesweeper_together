#ifndef MINESWEEPER_SERVER_PLAYERINTERFACE_H
#define MINESWEEPER_SERVER_PLAYERINTERFACE_H

#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#pragma comment(lib, "ws2_32")
#include "Move.h"


class IPlayer{
    char buffer[1024];
    int clientSocket;

public:
    IPlayer(){
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(1234);
        in_addr ip_to_num{};
        inet_pton(AF_INET, "192.168.31.216", &ip_to_num);
        serverAddress.sin_addr = ip_to_num;

        bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress));

        listen(serverSocket, SOMAXCONN);

        clientSocket = accept(serverSocket, nullptr, nullptr);
    }

    void receiveMove(Move &move){
        while (true){
            int status = recv(clientSocket, buffer, sizeof buffer, 0);

            if (status >= 0){
                memcpy(&move, buffer, sizeof move);
                return;
            }
        }
    }

    void sendSizeBoard(Board &board){
        int sizeBoard = board.getSizeBoard();
        memcpy(buffer, &sizeBoard, sizeof sizeBoard);
        send(clientSocket, buffer, sizeof buffer, 0);
    }

    void sendBoard(std::vector<std::vector<char>> &boardView){
        int sizeBoard = boardView.size();
        char transView[sizeBoard][sizeBoard];
        for (int i = 0; i < sizeBoard; i++){
            for (int j = 0; j < sizeBoard; j++){
                transView[i][j] = boardView[i][j];
            }
        }

        int size = sizeof transView;
        memcpy(buffer, &transView, size);
        send(clientSocket, buffer, sizeof buffer, 0);
    }
};

#endif //MINESWEEPER_SERVER_PLAYERINTERFACE_H
