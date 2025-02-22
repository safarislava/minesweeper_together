#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H
#include <iostream>
#include <future>
#include "Move.h"
#include "Board.h"
#include "IPlayer.h"
#include "SocketManager.h"


class Game {
public:
    Board board;
    SocketManager socketManager;
    std::vector<IPlayer> players;

    void init(){
        board.init(10);
        socketManager.init();
    }

    void addPlayer(){
        IPlayer player(socketManager.serverSocket);
        players.emplace_back(player);
    }

    void updateBoard() {
        std::vector<std::vector<char>> boardView = board.getView();
        for (IPlayer &player : players){
            player.sendBoard(boardView);
        }
    }

    void printBoard(){
        std::vector<std::vector<char>> boardView = board.getView();
        for (int y = 0; y < boardView.size(); y++){
            for (int x = 0; x < boardView.size(); x++){
                std::cout << boardView[y][x] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    bool isAvailableMove(Move move){
        if (!(move.getX() >= 0 and move.getX() < board.getSizeBoard() and
              move.getY() >= 0 and move.getY() < board.getSizeBoard())){
            std::cout << "Unavailable move : Invalid coordinate\n";
            return false;
        }

        if (move.isFlag()){
            if (!board.isAvailableCellForFlag(move.getX(), move.getY())){
                std::cout << "Unavailable move : Don't empty cell\n";
                return false;
            }
        }
        else{
            if (!board.isAvailableCellForOpen(move.getX(), move.getY())){
                std::cout << "Unavailable move : Don't empty cell\n";
                return false;
            }
        }

        return true;
    }
};


#endif //MINESWEEPER_GAME_H
