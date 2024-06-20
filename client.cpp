#include "classes/View.h"
#include "classes/IGame.h"
#include <future>
#undef main

int main() {
    IGame game;
    View view;
    view.init();

    int sizeBoard;
    game.receiveSizeBoard(sizeBoard);

    std::future<void> receivingBoard = std::async([&game, &view, &sizeBoard]{
        while (true){
            std::vector<std::vector<char>> boardView;
            game.receiveBoard(boardView, sizeBoard);
            view.setBoard(boardView);
        }
    });

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                bool isFlag = e.button.button == SDL_BUTTON_RIGHT;
                int px = e.button.x, py = e.button.y;
                int x = px  / 100, y = py / 100;
                game.sendMove({x, y, isFlag});
            }
        }
        view.update();
    }

    receivingBoard.get();
    view.exit();

    return 0;
}
