#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>

using namespace std;

class Board;
class Cell;
class Piece;

string toLowercase(string str);

// Common Interface for the move strategies
class MovementStrategy
{
public:
    virtual bool canMove(Board *board, Cell *startCell, Cell *endCell) = 0;

    virtual ~MovementStrategy() = default;
};

// Abstract Class
class Piece
{
private:
    bool isWhitePiece;
    bool killed = false;
    MovementStrategy *movementStrategy;

public:
    Piece(bool isWhitePiece, MovementStrategy *movementStrategy)
    {
        this->isWhitePiece = isWhitePiece;
        this->movementStrategy = movementStrategy;
    }

    virtual ~Piece()
    {
        delete movementStrategy;
    }

    // returns piece type
    bool isWhite()
    {
        return isWhitePiece;
    }

    // returns whether a player has been killed or not
    bool isKilled()
    {
        return killed;
    }

    // modifies piece status upon being killed
    void setKilled(bool killed)
    {
        this->killed = killed;
    }

    bool canMove(Board *board, Cell *startBlock, Cell *endBlock)
    {
        return movementStrategy->canMove(board, startBlock, endBlock);
    }
};

// Individual Movement Strategies - START
class KingMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override
    {
        // TODO: King movement logic
        return true;
    }
};

class QueenMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override
    {
        // TODO: Queen movement logic
        return true;
    }
};

class BishopMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override
    {
        // TODO: Bishop movement logic
        return true;
    }
};

class KnightMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override
    {
        // TODO: Knight movement logic
        return true;
    }
};

class RookMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override
    {
        // TODO: Rook movement logic
        return true;
    }
};

class PawnMovementStrategy : public MovementStrategy
{
public:
    bool canMove(Board *board, Cell *startCell, Cell *endCell) override
    {
        // TODO: Pawn movement logic
        return true;
    }
};
// Individual Movement Strategies - END

// Individual Pieces - START
class King : public Piece
{
public:
    King(bool isWhitePiece)
        : Piece(isWhitePiece, new KingMovementStrategy()) {}
};

class Queen : public Piece
{
public:
    Queen(bool isWhitePiece)
        : Piece(isWhitePiece, new QueenMovementStrategy()) {}
};

class Bishop : public Piece
{
public:
    Bishop(bool isWhitePiece)
        : Piece(isWhitePiece, new BishopMovementStrategy()) {}
};

class Knight : public Piece
{
public:
    Knight(bool isWhitePiece)
        : Piece(isWhitePiece, new KnightMovementStrategy()) {}
};

class Rook : public Piece
{
public:
    Rook(bool isWhitePiece)
        : Piece(isWhitePiece, new RookMovementStrategy()) {}
};

class Pawn : public Piece
{
public:
    Pawn(bool isWhitePiece)
        : Piece(isWhitePiece, new PawnMovementStrategy()) {}
};
// Individual Pieces - END

string toLowercase(string str)
{
    for (char &c : str)
    {
        c = static_cast<char>(
            tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

// Piece Factory - responsible for creation of pieces
class PieceFactory
{
public:
    static Piece *createPiece(string pieceType, bool isWhitePiece)
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

        throw invalid_argument("Unknown piece type: " + pieceType);
    }
};

class Cell
{
private:
    int row, col;
    string label;
    Piece *piece;

public:
    Cell(int row, int col, Piece *piece)
    {
        this->row = row;
        this->col = col;
        this->piece = piece;
    }

    Piece *getPiece()
    {
        return piece;
    }

    // Puts piece on a cell
    void setPiece(Piece *piece)
    {
        this->piece = piece;
    }
};

class Move
{
private:
    Cell *startCell;
    Cell *endCell;

public:
    Move(Cell *startCell, Cell *endCell)
        : startCell(startCell), endCell(endCell) {}

    // Validate the move
    bool isValid()
    {
        Piece *sourcePiece = startCell->getPiece();

        if (sourcePiece == nullptr)
            return false;

        Piece *destinationPiece = endCell->getPiece();

        // Empty destination is allowed
        if (destinationPiece == nullptr)
            return true;

        // Cannot capture your own piece
        return sourcePiece->isWhite() != destinationPiece->isWhite();
    }

    Cell *getStartCell()
    {
        return startCell;
    }

    Cell *getEndCell()
    {
        return endCell;
    }
};

// SIGLETON PATTERN OF BOARD
class Board
{
private:
    inline static Board *instance = nullptr;
    vector<vector<Cell *>> board;

    // private constructor
    Board(int rows)
    {
        initializeBoard(rows);
    }

    void initializeBoard(int rows)
    {
        board.resize(rows, vector<Cell *>(rows));

        // Setting white pieces using PieceFactory
        setPieceRow(0, true);
        setPawnRow(1, rows, true);

        // Setting black pieces using PieceFactory
        setPieceRow(rows - 1, false);
        setPawnRow(rows - 2, rows, false);

        // Defining rest of the cells having no pieces
        for (int row = 2; row < rows - 2; row++)
        {
            for (int col = 0; col < rows; col++)
            {
                board[row][col] = new Cell(row, col, nullptr);
            }
        }
    }

    // Set major pieces for a given row
    void setPieceRow(int row, bool isWhite)
    {
        board[row][0] = new Cell(row, 0, PieceFactory::createPiece("rook", isWhite));
        board[row][1] = new Cell(row, 1, PieceFactory::createPiece("knight", isWhite));
        board[row][2] = new Cell(row, 2, PieceFactory::createPiece("bishop", isWhite));
        board[row][3] = new Cell(row, 3, PieceFactory::createPiece("queen", isWhite));
        board[row][4] = new Cell(row, 4, PieceFactory::createPiece("king", isWhite));
        board[row][5] = new Cell(row, 5, PieceFactory::createPiece("bishop", isWhite));
        board[row][6] = new Cell(row, 6, PieceFactory::createPiece("knight", isWhite));
        board[row][7] = new Cell(row, 7, PieceFactory::createPiece("rook", isWhite));
    }

    void setPawnRow(int row, int rows, bool isWhite)
    {
        for (int j = 0; j < rows; j++)
        {
            board[row][j] = new Cell(row, j, PieceFactory::createPiece("pawn", isWhite));
        }
    }

public:
    static Board *getInstance(int rows)
    {
        if (instance == nullptr)
        {
            instance = new Board(rows);
        }
        return instance;
    }

    Cell *getCell(int row, int col)
    {
        if (row < 0 || row >= 8 || col < 0 || col >= 8)
            return nullptr;

        return board[row][col];
    }
};

enum class Status
{
    ACTIVE,
    SAVED,
    BLACK_WIN,
    WHITE_WIN,
    STALEMATE
};

class Player
{
private:
    string name;
    bool isWhiteSide;

public:
    Player(string name, bool isWhiteSide)
    {
        this->name = name;
        this->isWhiteSide = isWhiteSide;
    }

    string getName()
    {
        return name;
    }

    bool isWhiteSide()
    {
        return isWhiteSide;
    }
};

class BoardGames
{
    /*
        This interface illustrates how a large game company can manage multiple types
        of games, including board games, non-board games. Tic Tac Toe is an example
        of a game that is a child of the BoardGames interface.
    */
};

class Game : BoardGames
{
private:
    Board *board;
    // Assuming player1 is always WHITE
    Player *player1;
    // Assuming player2 is always BLACK
    Player *player2;

    bool isWhiteTurn;
    vector<Move *> gameLog;
    Status status;

public:
    // Constructor to initialize the game with two players
    Game(Player *player1, Player *player2)
    {
        this->player1 = player1;
        this->player2 = player2;

        this->board = Board::getInstance(8); // Initialize the board with 8 rows
        this->isWhiteTurn = true;

        this->status = Status::ACTIVE;
        this->gameLog = {};
    }

    void start()
    {
        while (this->status == Status::ACTIVE)
        {
            int startRow, startCol, endRow, endCol;

            cout << "\n"
                 << (isWhiteTurn ? "White" : "Black")
                 << "'s turn\n";

            cout << "Enter starting position (row col): ";
            cin >> startRow >> startCol;

            cout << "Enter destination position (row col): ";
            cin >> endRow >> endCol;

            Cell *startCell = board->getCell(startRow, startCol);
            Cell *endCell = board->getCell(endRow, endCol);

            if (startCell == nullptr || endCell == nullptr)
            {
                cout << "Invalid board position!\n";
                continue;
            }

            Move *move = new Move(startCell, endCell);

            makeMove(move, isWhiteTurn ? player1 : player2);
        }

        cout << "Game Over!\n";
    }

    void makeMove(Move *move, Player *player)
    {
        // Initial check for a valid move
        // To check if source and destination don't contain the same color pieces
        if (move->isValid())
        {
            Piece *sourcePiece = move->getStartCell()->getPiece();

            // Check if the source piece can be moved or not
            if (sourcePiece->canMove(this->board, move->getStartCell(), move->getEndCell()))
            {
                Piece *destinationPiece = move->getEndCell()->getPiece();

                // Check if the destination cell contains some piece
                if (destinationPiece != nullptr)
                {
                    // If the destination cell contains King and currently white is playing
                    //     --> White wins
                    if (dynamic_cast<King *>(destinationPiece) != nullptr && isWhiteTurn)
                    {
                        this->status = Status::WHITE_WIN;
                        return;
                    }

                    // If the destination cell contains King and currently Black is playing
                    //     --> Black wins
                    if (dynamic_cast<King *>(destinationPiece) != nullptr && !isWhiteTurn)
                    {
                        this->status = Status::BLACK_WIN;
                        return;
                    }

                    // Set the destination piece as killed
                    destinationPiece->setKilled(true);
                }

                // Adding the valid move to the game logs
                gameLog.push_back(move);
                // Moving the source piece to the destination cell
                move->getEndCell()->setPiece(sourcePiece);
                // Setting the source cell to null (means it doesn't have any piece)
                move->getStartCell()->setPiece(nullptr);

                // Toggling the turn
                isWhiteTurn = !isWhiteTurn;
            }
        }
    }
};

int main()
{
    // Create Players
    Player *player1 = new Player("Player1", true);  // White
    Player *player2 = new Player("Player2", false); // Black

    // Initialize game
    Game *chessGame = new Game(player1, player2);

    // Start the game
    chessGame->start();

    return 0;
}