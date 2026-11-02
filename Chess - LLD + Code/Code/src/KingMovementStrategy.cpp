
#include "KingMovementStrategy.h"
#include "Board.h"
#include "Cell.h"
#include "Piece.h"
#include <cstdlib>

bool KingMovementStrategy::canMove(Board *board, Cell *start, Cell *end)
{
    if (board == nullptr || start == nullptr || end == nullptr)
        return false;

    int startRow = start->getRow();
    int startCol = start->getCol();

    int endRow = end->getRow();
    int endCol = end->getCol();

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    // King must move exactly one square in any direction.
    if (rowDiff > 1 || colDiff > 1)
        return false;

    // King cannot stay in the same cell.
    if (rowDiff == 0 && colDiff == 0)
        return false;

    return true;
}
