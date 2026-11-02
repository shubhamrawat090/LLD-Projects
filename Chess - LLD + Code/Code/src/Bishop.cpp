#include "Bishop.h"

Bishop::Bishop(bool isWhitePiece)
    : Piece(isWhitePiece, new BishopMovementStrategy()) {}

char Bishop::getSymbol()
{
    return isWhite() ? 'B' : 'b';
}