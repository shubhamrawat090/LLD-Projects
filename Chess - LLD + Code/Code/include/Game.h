#pragma once

#include <vector>

#include "Status.h"
#include "BoardGames.h"
#include "Move.h"

class Board;
class Player;

class Game : BoardGames
{
private:
    Board *board;

    Player *player1;
    Player *player2;

    bool isWhiteTurn;

    std::vector<Move> gameLog;

    Status status;

public:
    Game(Player *player1, Player *player2);

    void start();

    bool makeMove(Move *move, Player *player);
};