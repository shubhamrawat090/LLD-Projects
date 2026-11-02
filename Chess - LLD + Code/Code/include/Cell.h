#pragma once

class Piece;

class Cell
{
private:
    int row, col;
    Piece *piece;

public:
    Cell(int row, int col, Piece *piece);

    Piece *getPiece();

    void setPiece(Piece *piece);

    int getRow();

    int getCol();
};