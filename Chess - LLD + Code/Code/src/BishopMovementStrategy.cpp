#include <cstdlib>
#include "BishopMovementStrategy.h"
#include "Board.h"
#include "Cell.h"
#include "Piece.h"

bool BishopMovementStrategy::canMove(
    Board *board,
    Cell *start,
    Cell *end)
{
    if (board == nullptr || start == nullptr || end == nullptr)
        return false;

    int startRow = start->getRow();
    int startCol = start->getCol();

    int endRow = end->getRow();
    int endCol = end->getCol();

    // Bishop cannot stay in the same cell.
    if (startRow == endRow && startCol == endCol)
        return false;

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    // Bishop must move diagonally.
    if (rowDiff != colDiff)
        return false;

    int rowDirection = (endRow > startRow) ? 1 : -1;
    int colDirection = (endCol > startCol) ? 1 : -1;

    // Converts 1-indexed row/col to 0-indexed in the right direction
    int currentRow = startRow + rowDirection;
    int currentCol = startCol + colDirection;

    // Check intermediate cells for blocking pieces.
    while (currentRow != endRow && currentCol != endCol)
    {
        Cell *currentCell = board->getCell(currentRow, currentCol);

        // In b/w, if there is a piece then stop
        if (currentCell->getPiece() != nullptr)
            return false;

        // Move 1 step, both row + col, in right direction
        currentRow += rowDirection;
        currentCol += colDirection;
    }

    return true;
}