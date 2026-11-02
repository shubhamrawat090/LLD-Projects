
#include "KnightMovementStrategy.h"
#include "Board.h"
#include "Cell.h"
#include "Piece.h"
#include <cstdlib>

bool KnightMovementStrategy::canMove(Board *board, Cell *start, Cell *end)
{
    if (board == nullptr || start == nullptr || end == nullptr)
        return false;

    int rowDiff = abs(end->getRow() - start->getRow());
    int colDiff = abs(end->getCol() - start->getCol());

    // Knight must move in an L-shape.
    return (rowDiff == 2 && colDiff == 1) ||
           (rowDiff == 1 && colDiff == 2);
}
