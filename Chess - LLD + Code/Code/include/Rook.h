#pragma once

#include "Piece.h"
#include "RookMovementStrategy.h"

class Rook : public Piece
{
public:
    Rook(bool isWhitePiece);

    char getSymbol() override;
};