#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H


class Cell {
    bool bombCell = false;
    bool openned = false, flag = false;

public:
    void setFlag(){
        flag = !flag;
    }

    void setOpen(){
        openned = true;
    }

    void setClosed(){
        openned = false;
    }

    bool isBombCell() const{
        return bombCell;
    }

    bool isOpenned() const{
        return openned;
    }

    bool isFlag() const{
        return flag;
    }

    void setBombCell(){
        bombCell = true;
    }

    void setEmptyCell(){
        bombCell = false;
    }
};


#endif //MINESWEEPER_CELL_H
