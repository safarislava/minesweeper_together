#include "classes/Game.h"

int main() {
    Game game;

    game.init();

    for (IPlayer &player : game.players){
        player.sendSizeBoard(game.board);
    }

    Move move;
    game.players[game.players.size()-1].receiveMove(move);
    move.removeFlag();
    if (game.isAvailableMove(move)) game.board.apply(move, true);

    while (!game.players.empty()){
        for (IPlayer &player : game.players){
            game.updateBoard();

            player.receiveMove(move);
            if (game.isAvailableMove(move)) game.board.apply(move);
        }
    }

    return 0;
}
