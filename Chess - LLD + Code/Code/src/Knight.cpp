#include "Knight.h"

Knight::Knight(bool isWhitePiece)
    : Piece(isWhitePiece, new KnightMovementStrategy()) {}

char Knight::getSymbol()
{
    return isWhite() ? 'N' : 'n';
}