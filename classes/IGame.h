#ifndef MINESWEEPER_GAMEINTERFACE_H
#define MINESWEEPER_GAMEINTERFACE_H

#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32")
#include "Move.h"


class IGame{
    SOCKET clientSocket;
    char buffer[1024]{};

public:
    IGame() {
        WSAData wsaData{};
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(1234);
        in_addr ip_to_num{};
        ip_to_num.S_un.S_un_b.s_b1 = 192;
        ip_to_num.S_un.S_un_b.s_b2 = 168;
        ip_to_num.S_un.S_un_b.s_b3 = 31;
        ip_to_num.S_un.S_un_b.s_b4 = 216;
        ip_to_num.S_un.S_un_w.s_w1 = 192;
        ip_to_num.S_un.S_un_w.s_w2 = 256;
        ip_to_num.S_un.S_addr = 3625953472;
        serverAddress.sin_addr = ip_to_num;

        // TODO проверка подключения
        connect(clientSocket, (struct sockaddr*) &serverAddress,sizeof(serverAddress));
    }

    void sendMove(Move move){
        memcpy(buffer, &move, sizeof move);
        send(clientSocket, buffer, sizeof buffer, 0);
    }

    void receiveSizeBoard(int &sizeBoard){
        while (true){
            int status = recv(clientSocket, buffer, sizeof buffer, 0);
            if (status >= 0){
                memcpy(&sizeBoard, buffer, sizeof sizeBoard);
                return;
            }
        }
    }

    void receiveBoard(std::vector<std::vector<char>> &boardView, int sizeBoard){
        boardView.assign(sizeBoard, std::vector<char>(sizeBoard));
        char transView[sizeBoard][sizeBoard];

        while (true){
            int status = recv(clientSocket, buffer, sizeof buffer, 0);
            if (status >= 0){
                int size = sizeof transView;
                memcpy(&transView, buffer, size);

                for (int i = 0; i < sizeBoard; i++){
                    for (int j = 0; j < sizeBoard; j++){
                        boardView[i][j] = transView[i][j];
                    }
                }
                return;
            }
        }
    }
};

#endif //MINESWEEPER_GAMEINTERFACE_H
