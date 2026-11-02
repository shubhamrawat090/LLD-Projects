#pragma once

#include "MovementStrategy.h"

class PawnMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override;
};