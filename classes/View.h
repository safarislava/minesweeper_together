#ifndef MINESWEEPER_GAMEVIEW_H
#define MINESWEEPER_GAMEVIEW_H
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>

const char CLOSED = '-';
const char BOMB = '*';
const char FLAG = '+';


class View{
    const int width = 800;
    const int height = 600;
    int cellSize;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    std::map<std::string, SDL_Texture*> textures;

    std::vector<std::vector<char>> board;

    SDL_Texture* LoadImage(const std::string& file){
        SDL_Surface *loadedImage = nullptr;
        SDL_Texture *texture = nullptr;
        loadedImage = SDL_LoadBMP(file.c_str());
        if (loadedImage != nullptr){
            texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
            SDL_FreeSurface(loadedImage);
        }
        else
            std::cout << SDL_GetError() << std::endl;
        return texture;
    }

    void ApplySurface(int x, int y, int w, int h, SDL_Texture *tex, SDL_Renderer *rend){
        SDL_Rect pos{.x=x, .y=y, .w = w, .h = h};
        SDL_RenderCopy(rend, tex, nullptr, &pos);
    }

public:
    void setFlagCell(int x, int y){
        if (!(0 <= x and x <= board.size()) or !(0 <= y and y <= board.size())) return;

        if (board[y][x] == CLOSED) board[y][x] = FLAG;
        else if (board[y][x] == FLAG) board[y][x] = CLOSED;
    }

    void setBoard(std::vector<std::vector<char>> &newBoard){
        for (int y = 0; y < board.size(); y++){
            for (int x = 0; x < board.size(); x++){
                if (!(board[y][x] == FLAG and newBoard[y][x] == CLOSED)){
                    board[y][x] = newBoard[y][x];
                }
            }
        }

        cellSize = height / static_cast<int>(board.size());
    }

    void update(){
        SDL_RenderClear(renderer);
        ApplySurface(0, 0, width, height, textures["Background"], renderer);

        for (int y = 0; y < board.size(); y++){
            for (int x = 0; x < board.size(); x++){
                std::string state;
                if (board[y][x] == CLOSED) state = "Closed";
                else if (board[y][x] == FLAG) state = "Flag";
                else if (board[y][x] == BOMB) state = "Bomb";
                else state = board[y][x];

                ApplySurface(cellSize * x, cellSize * y, cellSize, cellSize, textures["Cell" + state], renderer);
            }
        }

        SDL_RenderPresent(renderer);
    }

    void init(int sizeBoard){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        window = SDL_CreateWindow("Minesweeper Together", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (window == nullptr){
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr){
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return;
        }

        textures["Cell0"] = LoadImage("../res/images/Cell0.bmp");
        textures["Cell1"] = LoadImage("../res/images/Cell1.bmp");
        textures["Cell2"] = LoadImage("../res/images/Cell2.bmp");
        textures["Cell3"] = LoadImage("../res/images/Cell3.bmp");
        textures["Cell4"] = LoadImage("../res/images/Cell4.bmp");
        textures["Cell5"] = LoadImage("../res/images/Cell5.bmp");
        textures["Cell6"] = LoadImage("../res/images/Cell6.bmp");
        textures["Cell7"] = LoadImage("../res/images/Cell7.bmp");
        textures["Cell8"] = LoadImage("../res/images/Cell8.bmp");
        textures["CellBomb"] = LoadImage("../res/images/CellBomb.bmp");
        textures["CellClosed"] = LoadImage("../res/images/CellClosed.bmp");
        textures["CellExploded"] = LoadImage("../res/images/CellExploded.bmp");
        textures["CellFlag"] = LoadImage("../res/images/CellFlag.bmp");
        textures["Background"] = LoadImage("../res/images/Background.bmp");

        board.assign(sizeBoard, std::vector<char>(sizeBoard, '-'));
    }

    void exit(){
        for (auto &texture : textures) {
            SDL_DestroyTexture(texture.second);
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void getCellCoordinate(int &x, int &y, int px, int py){
        x = px / cellSize;
        y = py / cellSize;
    }
};

#endif //MINESWEEPER_GAMEVIEW_H
