#pragma once

#include "Piece.h"
#include "PawnMovementStrategy.h"

class Pawn : public Piece
{
public:
    Pawn(bool isWhitePiece);

    char getSymbol() override;
};