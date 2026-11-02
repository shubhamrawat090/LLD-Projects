#include "PieceFactory.h"

#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "Utils.h"

#include <stdexcept>

Piece *PieceFactory::createPiece(
    std::string pieceType,
    bool isWhitePiece)
{
    pieceType = toLowercase(pieceType);

    if (pieceType == "king")
        return new King(isWhitePiece);

    if (pieceType == "queen")
        return new Queen(isWhitePiece);

    if (pieceType == "bishop")
        return new Bishop(isWhitePiece);

    if (pieceType == "knight")
        return new Knight(isWhitePiece);

    if (pieceType == "rook")
        return new Rook(isWhitePiece);

    if (pieceType == "pawn")
        return new Pawn(isWhitePiece);

    throw std::invalid_argument(
        "Unknown piece type: " + pieceType);
}