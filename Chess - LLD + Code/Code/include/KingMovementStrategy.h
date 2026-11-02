#pragma once

#include "MovementStrategy.h"

class KingMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override;
};