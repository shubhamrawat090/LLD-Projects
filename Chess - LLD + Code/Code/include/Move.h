#pragma once

class Cell;

class Move
{
private:
    Cell *startCell;
    Cell *endCell;

public:
    Move(Cell *startCell, Cell *endCell);

    bool isValid();

    Cell *getStartCell();

    Cell *getEndCell();
};