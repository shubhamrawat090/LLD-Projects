#pragma once

#include "Piece.h"
#include "KnightMovementStrategy.h"

class Knight : public Piece
{
public:
    Knight(bool isWhitePiece);

    char getSymbol() override;
};