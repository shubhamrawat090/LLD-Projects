#include "Board.h"

#include "Cell.h"
#include "Piece.h"
#include "PieceFactory.h"

#include <iostream>

using namespace std;

Board::Board(int rows)
{
    initializeBoard(rows);
}

void Board::initializeBoard(int rows)
{
    board.resize(rows, vector<Cell *>(rows, nullptr));

    // White pieces
    setPieceRow(0, true);
    setPawnRow(1, rows, true);

    // Black pieces
    setPieceRow(rows - 1, false);
    setPawnRow(rows - 2, rows, false);

    // Empty cells
    for (int row = 2; row < rows - 2; row++)
    {
        for (int col = 0; col < rows; col++)
        {
            board[row][col] = new Cell(row, col, nullptr);
        }
    }
}

void Board::setPieceRow(int row, bool isWhite)
{
    board[row][0] = new Cell(row, 0, PieceFactory::createPiece("rook", isWhite));
    board[row][1] = new Cell(row, 1, PieceFactory::createPiece("knight", isWhite));
    board[row][2] = new Cell(row, 2, PieceFactory::createPiece("bishop", isWhite));
    board[row][3] = new Cell(row, 3, PieceFactory::createPiece("queen", isWhite));
    board[row][4] = new Cell(row, 4, PieceFactory::createPiece("king", isWhite));
    board[row][5] = new Cell(row, 5, PieceFactory::createPiece("bishop", isWhite));
    board[row][6] = new Cell(row, 6, PieceFactory::createPiece("knight", isWhite));
    board[row][7] = new Cell(row, 7, PieceFactory::createPiece("rook", isWhite));
}

void Board::setPawnRow(int row, int rows, bool isWhite)
{
    for (int col = 0; col < rows; col++)
    {
        board[row][col] = new Cell(
            row, col,
            PieceFactory::createPiece("pawn", isWhite));
    }
}

Board *Board::getInstance(int rows)
{
    if (instance == nullptr)
    {
        instance = new Board(rows);
    }

    return instance;
}

Cell *Board::getCell(int row, int col)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return nullptr;

    return board[row][col];
}

void Board::displayBoard()
{
    cout << "\n    a   b   c   d   e   f   g   h\n";
    cout << "  +---+---+---+---+---+---+---+---+\n";

    for (int row = 7; row >= 0; row--)
    {
        cout << row + 1 << " |";

        for (int col = 0; col < 8; col++)
        {
            Piece *piece = board[row][col]->getPiece();

            if (piece == nullptr)
                cout << "   |";
            else
                cout << " " << piece->getSymbol() << " |";
        }

        cout << " " << row + 1 << "\n";
        cout << "  +---+---+---+---+---+---+---+---+\n";
    }

    cout << "    a   b   c   d   e   f   g   h\n\n";
}