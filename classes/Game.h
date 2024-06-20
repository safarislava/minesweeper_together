#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H
#include <iostream>
#include "Move.h"
#include "Board.h"
#include "IPlayer.h"


class Game {
    Board board;
    std::vector<IPlayer> players;

    void updateBoard() {
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

public:
    void start(){
        board.init(10);
        players.emplace_back();
    }

    void process(){
        for (IPlayer &player : players){
            player.sendSizeBoard(board);
        }
        board.addBombCells(40);

        while (true){
            for (IPlayer &player : players){
                updateBoard();
                std::vector<std::vector<char>> viewBoard = board.getView();
                for (IPlayer &player : players){
                    player.sendBoard(viewBoard);
                }

                Move move;
                player.receiveMove(move);
                if (isAvailableMove(move)) board.apply(move);
            }
        }
    }
};


#endif //MINESWEEPER_GAME_H
