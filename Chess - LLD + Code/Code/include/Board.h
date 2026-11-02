#pragma once

#include <vector>

class Cell;

class Board
{
private:
    inline static Board *instance = nullptr;

    std::vector<std::vector<Cell *>> board;

    Board(int rows);

    void initializeBoard(int rows);

    void setPieceRow(int row, bool isWhite);

    void setPawnRow(int row, int rows, bool isWhite);

public:
    static Board *getInstance(int rows);

    Cell *getCell(int row, int col);

    void displayBoard();
};