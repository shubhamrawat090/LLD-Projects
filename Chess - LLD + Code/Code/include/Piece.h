#pragma once

#include "MovementStrategy.h"

class Piece
{
private:
    bool isWhitePiece;
    bool killed = false;

protected:
    MovementStrategy *movementStrategy;

public:
    Piece(bool isWhitePiece, MovementStrategy *movementStrategy);

    virtual char getSymbol() = 0;

    virtual ~Piece();

    bool isWhite();

    bool isKilled();

    void setKilled(bool killed);

    bool canMove(Board *board, Cell *startCell, Cell *endCell);
};