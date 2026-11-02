#pragma once

#include <string>

class Player
{
private:
    std::string name;
    bool whiteSide;

public:
    Player(std::string name, bool isWhiteSide);

    std::string getName();

    bool isWhiteSide();
};