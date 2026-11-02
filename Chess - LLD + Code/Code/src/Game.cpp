#include "Game.h"

#include "Board.h"
#include "Player.h"
#include "Move.h"
#include "Cell.h"
#include "Piece.h"
#include "King.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

Game::Game(Player *player1, Player *player2)
{
    this->player1 = player1;
    this->player2 = player2;

    this->board = Board::getInstance(8);
    this->isWhiteTurn = true;

    this->status = Status::ACTIVE;
    this->gameLog = {};
}

void Game::start()
{
    while (this->status == Status::ACTIVE)
    {
        system("cls");

        board->displayBoard();

        Player *currentPlayer = isWhiteTurn ? player1 : player2;

        cout << "\n"
             << currentPlayer->getName()
             << (isWhiteTurn ? " (White)" : " (Black)")
             << " to move.\n";

        string startPosition, endPosition;

        cout << "\nEnter starting position (e.g. e2): ";
        cin >> startPosition;

        if (toLowercase(startPosition) == "q")
            break;

        cout << "Enter destination position (e.g. e4): ";
        cin >> endPosition;

        int startRow, startCol;
        int endRow, endCol;

        if (!parsePosition(startPosition, startRow, startCol) ||
            !parsePosition(endPosition, endRow, endCol))
        {
            cout << "\nInvalid position! Please enter coordinates between a1 and h8.\n";
            system("pause");
            continue;
        }

        Cell *startCell = board->getCell(startRow, startCol);
        Cell *endCell = board->getCell(endRow, endCol);

        Move *move = new Move(startCell, endCell);

        bool success = makeMove(move, currentPlayer);

        delete move;

        if (!success)
        {
            system("pause");
        }
    }

    system("cls");
    board->displayBoard();

    cout << "\nGame Over!\n";
}

bool Game::makeMove(Move *move, Player *player)
{
    Piece *sourcePiece = move->getStartCell()->getPiece();

    if (sourcePiece == nullptr)
    {
        cout << "\nInvalid move: No piece at starting position.\n";
        return false;
    }

    if (sourcePiece->isWhite() != player->isWhiteSide())
    {
        cout << "\nInvalid move: You cannot move your opponent's piece.\n";
        return false;
    }

    if (!move->isValid())
    {
        cout << "\nInvalid move: You cannot capture your own piece.\n";
        return false;
    }

    if (!sourcePiece->canMove(
            this->board,
            move->getStartCell(),
            move->getEndCell()))
    {
        cout << "\nInvalid move: Piece cannot move to that position.\n";
        return false;
    }

    Piece *destinationPiece = move->getEndCell()->getPiece();

    if (dynamic_cast<King *>(destinationPiece) != nullptr)
    {
        this->status = isWhiteTurn
                           ? Status::WHITE_WIN
                           : Status::BLACK_WIN;

        return true;
    }

    if (destinationPiece != nullptr)
    {
        destinationPiece->setKilled(true);
    }

    gameLog.push_back(*move);

    move->getEndCell()->setPiece(sourcePiece);
    move->getStartCell()->setPiece(nullptr);

    isWhiteTurn = !isWhiteTurn;

    return true;
}