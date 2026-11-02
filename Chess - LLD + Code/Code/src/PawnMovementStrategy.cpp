
#include "PawnMovementStrategy.h"
#include "Board.h"
#include "Cell.h"
#include "Piece.h"
#include <cstdlib>

bool PawnMovementStrategy::canMove(Board *board, Cell *start, Cell *end)
{
    if (board == nullptr || start == nullptr || end == nullptr)
        return false;

    Piece *pawn = start->getPiece();

    if (pawn == nullptr)
        return false;

    int startRow = start->getRow();
    int startCol = start->getCol();

    int endRow = end->getRow();
    int endCol = end->getCol();

    int rowDiff = endRow - startRow;
    int colDiff = abs(endCol - startCol);

    // White moves towards increasing rows.
    // Black moves towards decreasing rows.
    int direction = pawn->isWhite() ? 1 : -1;

    // Forward movement: destination must be empty.
    if (colDiff == 0)
    {
        if (end->getPiece() != nullptr)
            return false;

        // Move one square forward.
        if (rowDiff == direction)
            return true;

        // Move two squares forward from the starting position.
        int startingRow = pawn->isWhite() ? 1 : 6;

        if (startRow == startingRow && rowDiff == 2 * direction)
        {
            int intermediateRow = startRow + direction;

            Cell *intermediateCell =
                board->getCell(intermediateRow, startCol);

            return intermediateCell->getPiece() == nullptr;
        }

        return false;
    }

    // Diagonal capture: exactly one row forward and one column sideways.
    if (colDiff == 1 && rowDiff == direction)
    {
        Piece *target = end->getPiece();

        return target != nullptr &&
               target->isWhite() != pawn->isWhite();
    }

    return false;
}
