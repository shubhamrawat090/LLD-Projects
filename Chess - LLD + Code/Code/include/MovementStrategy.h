#pragma once

class Board;
class Cell;

class MovementStrategy
{
public:
    virtual bool canMove(
        Board *board,
        Cell *startCell,
        Cell *endCell) = 0;

    virtual ~MovementStrategy() = default;
};