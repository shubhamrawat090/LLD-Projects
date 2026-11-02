#pragma once

#include "Piece.h"
#include "KingMovementStrategy.h"

class King : public Piece
{
public:
    King(bool isWhitePiece);

    char getSymbol() override;
};