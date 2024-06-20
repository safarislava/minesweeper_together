#ifndef MINESWEEPER_MOVE_H
#define MINESWEEPER_MOVE_H

class Move{
    int x, y;
    bool flag;

public:
    Move(int X = 0, int Y = 0, bool Flag = false){
        x = X;
        y = Y;
        flag = Flag;
    }

    int getX() const{
        return x;
    }

    int getY() const{
        return y;
    }

    bool isFlag() const{
        return flag;
    }

    void removeFlag(){
        flag = false;
    }
};

#endif //MINESWEEPER_MOVE_H
