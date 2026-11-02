#include <cstdlib>
#include "QueenMovementStrategy.h"
#include "Board.h"
#include "Cell.h"
#include "Piece.h"

bool QueenMovementStrategy::canMove(Board *board, Cell *start, Cell *end)
{
    if (board == nullptr || start == nullptr || end == nullptr)
        return false;

    int startRow = start->getRow();
    int startCol = start->getCol();

    int endRow = end->getRow();
    int endCol = end->getCol();

    // Queen cannot stay in the same cell.
    if (startRow == endRow && startCol == endCol)
        return false;

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    // Queen must move horizontally, vertically, or diagonally.
    bool isHorizontal = (startRow == endRow);
    bool isVertical = (startCol == endCol);
    bool isDiagonal = (rowDiff == colDiff);

    if (!isHorizontal && !isVertical && !isDiagonal)
        return false;

    int rowDirection = (endRow > startRow) ? 1 : (endRow < startRow) ? -1
                                                                     : 0;

    int colDirection = (endCol > startCol) ? 1 : (endCol < startCol) ? -1
                                                                     : 0;

    int currentRow = startRow + rowDirection;
    int currentCol = startCol + colDirection;

    // Check all intermediate cells.
    while (currentRow != endRow || currentCol != endCol)
    {
        Cell *currentCell = board->getCell(currentRow, currentCol);

        if (currentCell->getPiece() != nullptr)
            return false;

        currentRow += rowDirection;
        currentCol += colDirection;
    }

    return true;
}