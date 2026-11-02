#pragma once

#include "Piece.h"
#include "BishopMovementStrategy.h"

class Bishop : public Piece
{
public:
    Bishop(bool isWhitePiece);

    char getSymbol() override;
};