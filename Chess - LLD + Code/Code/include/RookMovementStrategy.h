#pragma once

#include "MovementStrategy.h"

class RookMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override;
};