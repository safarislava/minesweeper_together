#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include <vector>
#include <random>
#include "Cell.h"
#include "Move.h"


class Board {
    std::vector<std::vector<Cell>> content;
    std::vector<std::vector<int>> countBombsAround;
    int sizeBoard;
    int countBombs = 0;

public:
    void init(int size){
        sizeBoard = size;
        content.resize(sizeBoard, std::vector<Cell>(sizeBoard));
        countBombsAround.resize(sizeBoard, std::vector<int>(sizeBoard));
    }

    void apply(Move move, bool isFirstMove = false){
        if (move.isFlag()){
            content[move.getY()][move.getX()].setFlag();
            return;
        }

        if (content[move.getY()][move.getX()].isBombCell()){
            content[move.getY()][move.getX()].setOpen();
        }

        if (isFirstMove){
            content[move.getY()][move.getX()].setOpen();
            addBombCells(40);
            content[move.getY()][move.getX()].setClosed();
        }

        openCellsWithoutBombs(move.getX(), move.getY());
    }

    void openCellsWithoutBombs(int x, int y){
        if (content[y][x].isBombCell() or content[y][x].isOpenned()) return;
        content[y][x].setOpen();

        for (int i = -1; i <= 1; i += 2){
            if (0 <= x + i  and x + i < sizeBoard){
                openCellsWithoutBombs(x + i, y);
            }
        }

        for (int i = -1; i <= 1; i += 2){
            if (0 <= y + i  and y + i < sizeBoard){
                openCellsWithoutBombs(x, y + i);
            }
        }
    }

    void addBombCells(int countNewBombs){
        countBombs += countNewBombs;

        std::random_device rd;
        std::mt19937 randomGenerator(rd());
        std::uniform_int_distribution<int> distribution(0, sizeBoard);

        int countAddedBombs = 0;
        while (countAddedBombs != countNewBombs){
            int x = distribution(randomGenerator) % sizeBoard, y = distribution(randomGenerator) % sizeBoard;
            if (!content[y][x].isBombCell() and !content[y][x].isOpenned()){
                content[y][x].setBombCell();
                countAddedBombs++;

                // update array counting of bombs around after adding new bomb
                for (int j = std::max(y-1, 0); j <= std::min(y+1, sizeBoard-1); j++){
                    for (int i = std::max(x-1, 0); i <= std::min(x+1, sizeBoard-1); i++){
                        countBombsAround[j][i]++;
                    }
                }
            }
        }
    }

    bool isAvailableCellForOpen(int x, int y){
        return !content[y][x].isOpenned() and !content[y][x].isFlag();
    }

    bool isAvailableCellForFlag(int x, int y){
        return !content[y][x].isOpenned();
    }

    int getSizeBoard() const{
        return sizeBoard;
    }

    std::vector<std::vector<char>> getView(){
        std::vector<std::vector<char>> view;

        for (int y = 0; y < sizeBoard; y++){
            view.emplace_back();
            for (int x = 0; x < sizeBoard; x++){
                char s = '-';
                if (content[y][x].isFlag()) s = '+';
                else {
                    if (content[y][x].isOpenned()) {
                        if (content[y][x].isBombCell()) s = '*';
                        else s = countBombsAround[y][x] + '0';
                    }
                }
                view[y].push_back(s);
            }
        }

        return view;
    }
};


#endif //MINESWEEPER_BOARD_H