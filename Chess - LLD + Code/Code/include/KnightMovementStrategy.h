#pragma once

#include "MovementStrategy.h"

class KnightMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override;
};