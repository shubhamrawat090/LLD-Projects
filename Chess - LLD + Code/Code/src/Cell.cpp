#include "Cell.h"

Cell::Cell(int row, int col, Piece *piece)
{
    this->row = row;
    this->col = col;
    this->piece = piece;
}

Piece *Cell::getPiece()
{
    return piece;
}

void Cell::setPiece(Piece *piece)
{
    this->piece = piece;
}

int Cell::getRow()
{
    return row;
}

int Cell::getCol()
{
    return col;
}