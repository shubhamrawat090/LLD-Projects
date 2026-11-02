#include "Utils.h"
#include <cctype>

std::string toLowercase(std::string str)
{
    for (char &c : str)
    {
        c = static_cast<char>(
            std::tolower(static_cast<unsigned char>(c)));
    }

    return str;
}

bool parsePosition(std::string position, int &row, int &col)
{
    position = toLowercase(position);

    if (position.length() != 2)
        return false;

    if (position[0] < 'a' || position[0] > 'h' ||
        position[1] < '1' || position[1] > '8')
        return false;

    col = position[0] - 'a';
    row = position[1] - '1';

    return true;
}