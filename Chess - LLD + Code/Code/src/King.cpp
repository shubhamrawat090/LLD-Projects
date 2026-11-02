#include "King.h"

King::King(bool isWhitePiece)
    : Piece(isWhitePiece, new KingMovementStrategy()) {}

char King::getSymbol()
{
    return isWhite() ? 'K' : 'k';
}