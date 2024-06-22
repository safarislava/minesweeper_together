#include "classes/Game.h"

int main() {
    Game game;

    game.init();
    game.addPlayer();
    //game.addPlayer();

    for (IPlayer &player : game.players){
        player.sendSizeBoard(game.board);
    }
    game.updateBoard();

    Move move;
    IPlayer playerFirst = game.players[game.players.size() - 1];
    playerFirst.switchDoMove(); // true

    playerFirst.receiveMove(move);
    while (!game.isAvailableMove(move)){
        playerFirst.receiveMove(move);
    }

    move.removeFlag();
    game.board.apply(move, true);
    game.updateBoard();

    playerFirst.switchDoMove(); // false

    while (!game.players.empty()){
        for (IPlayer &player : game.players){
            player.switchDoMove(); // true

            auto availableMove = [&game, &player, &move]{
                player.receiveMove(move);
                while (!game.isAvailableMove(move)){
                    player.receiveMove(move);
                }
            };

            availableMove();
            while (move.isFlag()){
                game.board.apply(move);
                game.updateBoard();
                availableMove();
            }
            game.board.apply(move);
            game.updateBoard();

            player.switchDoMove(); // false
        }
    }

    return 0;
}
