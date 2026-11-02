
#include "RookMovementStrategy.h"
#include "Board.h"
#include "Cell.h"
#include "Piece.h"

bool RookMovementStrategy::canMove(Board *board, Cell *start, Cell *end)
{
    if (start == nullptr || end == nullptr || board == nullptr)
        return false;

    int startRow = start->getRow();
    int startCol = start->getCol();

    int endRow = end->getRow();
    int endCol = end->getCol();

    // Rook cannot remain in the same cell.
    if (startRow == endRow && startCol == endCol)
        return false;

    // Rook moves either horizontally or vertically.
    if (startRow != endRow && startCol != endCol)
        return false;

    int rowDirection = (endRow > startRow) ? 1 :
                       (endRow < startRow) ? -1 : 0;

    int colDirection = (endCol > startCol) ? 1 :
                       (endCol < startCol) ? -1 : 0;

    int currentRow = startRow + rowDirection;
    int currentCol = startCol + colDirection;

    // Check every intermediate cell.
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
