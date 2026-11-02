#pragma once

#include "Piece.h"
#include "QueenMovementStrategy.h"

class Queen : public Piece
{
public:
    Queen(bool isWhitePiece);

    char getSymbol() override;
};