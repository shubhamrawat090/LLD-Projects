#include <iostream>

#include "Game.h"
#include "Player.h"

using namespace std;

int main()
{
    // Create Players
    Player *player1 = new Player("Player1", true);
    Player *player2 = new Player("Player2", false);

    // Initialize Game
    Game *chessGame = new Game(player1, player2);

    // Start Game
    chessGame->start();

    // Cleanup
    delete chessGame;
    delete player1;
    delete player2;

    return 0;
}