#pragma once

#include "MovementStrategy.h"

class BishopMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override;
};