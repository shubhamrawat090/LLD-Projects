#include "Rook.h"

Rook::Rook(bool isWhitePiece)
    : Piece(isWhitePiece, new RookMovementStrategy()) {}

char Rook::getSymbol()
{
    return isWhite() ? 'R' : 'r';
}