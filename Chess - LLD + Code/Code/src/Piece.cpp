#include "Piece.h"

Piece::Piece(bool isWhitePiece, MovementStrategy *movementStrategy)
{
    this->isWhitePiece = isWhitePiece;
    this->movementStrategy = movementStrategy;
}

Piece::~Piece()
{
    delete movementStrategy;
}

bool Piece::isWhite()
{
    return isWhitePiece;
}

bool Piece::isKilled()
{
    return killed;
}

void Piece::setKilled(bool killed)
{
    this->killed = killed;
}

bool Piece::canMove(Board *board, Cell *startCell, Cell *endCell)
{
    return movementStrategy->canMove(board, startCell, endCell);
}