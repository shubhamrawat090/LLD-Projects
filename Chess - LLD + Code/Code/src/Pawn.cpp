#include "Pawn.h"

Pawn::Pawn(bool isWhitePiece)
    : Piece(isWhitePiece, new PawnMovementStrategy()) {}

char Pawn::getSymbol()
{
    return isWhite() ? 'P' : 'p';
}