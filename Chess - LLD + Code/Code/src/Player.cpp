#include "Player.h"

Player::Player(std::string name, bool isWhiteSide)
{
    this->name = name;
    this->whiteSide = isWhiteSide;
}

std::string Player::getName()
{
    return name;
}

bool Player::isWhiteSide()
{
    return whiteSide;
}