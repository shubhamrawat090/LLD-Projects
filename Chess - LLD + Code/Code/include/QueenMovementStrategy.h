#pragma once

#include "MovementStrategy.h"

class QueenMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override;
};