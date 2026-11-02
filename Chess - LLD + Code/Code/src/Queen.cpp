#include "Queen.h"

Queen::Queen(bool isWhitePiece)
    : Piece(isWhitePiece, new QueenMovementStrategy()) {}

char Queen::getSymbol()
{
    return isWhite() ? 'Q' : 'q';
}