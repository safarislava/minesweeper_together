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
    char buffer[1024]{};
    int clientSocket;

public:
    IPlayer(int &serverSocket){
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
        memset(buffer, 0, 1024);
        buffer[0] = 1;
        memcpy(buffer + 1, &sizeBoard, sizeof(sizeBoard));
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

        memset(buffer, 0, 1024);
        buffer[0] = 2;
        memcpy(buffer + 1, &transView, sizeof transView);
        send(clientSocket, buffer, sizeof buffer, 0);
    }

    void switchDoMove(){
        memset(buffer, 0, 1024);
        buffer[0] = 3;
        send(clientSocket, buffer, sizeof buffer, 0);
    }
};

#endif //MINESWEEPER_SERVER_PLAYERINTERFACE_H
