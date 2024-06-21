#include "classes/View.h"
#include "classes/IGame.h"
#include <future>
#undef main


int main() {
    IGame game;
    View view;
    SDL_Event e;
    bool quit = false;
    bool doMove = false;
    int sizeBoard;

    game.receiveManager(view, sizeBoard, doMove);
    view.init(sizeBoard);

    std::future<void> receiving = std::async([&quit, &game, &view, &sizeBoard, &doMove]{
        while (!quit){
            game.receiveManager(view, sizeBoard, doMove);
        }
    });

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                if (doMove) {
                    bool isFlag = e.button.button == SDL_BUTTON_RIGHT;
                    int x, y;
                    view.getCellCoordinate(x, y, e.button.x, e.button.y);
                    game.sendMove({x, y, isFlag});
                }
            }

        }
        view.update();
    }

    view.exit();

    return 0;
}
