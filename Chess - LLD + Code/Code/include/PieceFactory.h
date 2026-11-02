#pragma once

#include <string>

class Piece;

class PieceFactory
{
public:
    static Piece *createPiece(std::string pieceType, bool isWhitePiece);
};