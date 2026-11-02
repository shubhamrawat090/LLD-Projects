#include "Move.h"

#include "Cell.h"
#include "Piece.h"

Move::Move(Cell *startCell, Cell *endCell)
    : startCell(startCell), endCell(endCell) {}

bool Move::isValid()
{
    Piece *sourcePiece = startCell->getPiece();

    if (sourcePiece == nullptr)
        return false;

    Piece *destinationPiece = endCell->getPiece();

    // Empty destination is allowed
    if (destinationPiece == nullptr)
        return true;

    // Cannot capture your own piece
    return sourcePiece->isWhite() != destinationPiece->isWhite();
}

Cell *Move::getStartCell()
{
    return startCell;
}

Cell *Move::getEndCell()
{
    return endCell;
}