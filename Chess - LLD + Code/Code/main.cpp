#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <cstdlib>

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

    virtual char getSymbol() = 0;

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

    char getSymbol() override
    {
        return isWhite() ? 'K' : 'k';
    }
};

class Queen : public Piece
{
public:
    Queen(bool isWhitePiece)
        : Piece(isWhitePiece, new QueenMovementStrategy()) {}

    char getSymbol() override
    {
        return isWhite() ? 'Q' : 'q';
    }
};

class Bishop : public Piece
{
public:
    Bishop(bool isWhitePiece)
        : Piece(isWhitePiece, new BishopMovementStrategy()) {}

    char getSymbol() override
    {
        return isWhite() ? 'B' : 'b';
    }
};

class Knight : public Piece
{
public:
    Knight(bool isWhitePiece)
        : Piece(isWhitePiece, new KnightMovementStrategy()) {}

    char getSymbol() override
    {
        return isWhite() ? 'N' : 'n';
    }
};

class Rook : public Piece
{
public:
    Rook(bool isWhitePiece)
        : Piece(isWhitePiece, new RookMovementStrategy()) {}

    char getSymbol() override
    {
        return isWhite() ? 'R' : 'r';
    }
};

class Pawn : public Piece
{
public:
    Pawn(bool isWhitePiece)
        : Piece(isWhitePiece, new PawnMovementStrategy()) {}

    char getSymbol() override
    {
        return isWhite() ? 'P' : 'p';
    }
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

bool parsePosition(string position, int &row, int &col)
{
    // Convert input to lowercase
    position = toLowercase(position);

    // Validate input length
    if (position.length() != 2)
        return false;

    // Validate file (a-h) and rank (1-8)
    if (position[0] < 'a' || position[0] > 'h' ||
        position[1] < '1' || position[1] > '8')
        return false;

    col = position[0] - 'a';
    row = position[1] - '1';

    return true;
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

    void displayBoard()
    {
        cout << "\n    a   b   c   d   e   f   g   h\n";
        cout << "  +---+---+---+---+---+---+---+---+\n";

        for (int row = 7; row >= 0; row--)
        {
            cout << row + 1 << " |";

            for (int col = 0; col < 8; col++)
            {
                Piece *piece = board[row][col]->getPiece();

                if (piece == nullptr)
                {
                    cout << "   |";
                }
                else
                {
                    cout << " " << piece->getSymbol() << " |";
                }
            }

            cout << " " << row + 1 << "\n";
            cout << "  +---+---+---+---+---+---+---+---+\n";
        }

        cout << "    a   b   c   d   e   f   g   h\n\n";
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
    bool whiteSide;

public:
    Player(string name, bool isWhiteSide)
    {
        this->name = name;
        this->whiteSide = isWhiteSide;
    }

    string getName()
    {
        return name;
    }

    bool isWhiteSide()
    {
        return whiteSide;
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
    vector<Move> gameLog;
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
            // Clear terminal screen
            system("cls");

            // Display current board
            board->displayBoard();

            // Display current player's turn
            Player *currentPlayer = isWhiteTurn ? player1 : player2;

            cout << "\n"
                 << currentPlayer->getName()
                 << (isWhiteTurn ? " (White)" : " (Black)")
                 << " to move.\n";

            string startPosition, endPosition;

            cout << "\nEnter starting position (e.g. e2): ";
            cin >> startPosition;

            // Allow user to quit
            if (toLowercase(startPosition) == "q")
                break;

            cout << "Enter destination position (e.g. e4): ";
            cin >> endPosition;

            // Convert chess notation into board coordinates
            int startRow, startCol;
            int endRow, endCol;

            if (!parsePosition(startPosition, startRow, startCol) ||
                !parsePosition(endPosition, endRow, endCol))
            {
                cout << "\nInvalid position! Please enter coordinates between a1 and h8.\n";
                system("pause");
                continue;
            }

            // Retrieve corresponding cells
            Cell *startCell = board->getCell(startRow, startCol);
            Cell *endCell = board->getCell(endRow, endCol);

            // Create move
            Move *move = new Move(startCell, endCell);

            // Execute move
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

    bool makeMove(Move *move, Player *player)
    {
        // Get source piece
        Piece *sourcePiece = move->getStartCell()->getPiece();

        // Check whether source cell contains a piece
        if (sourcePiece == nullptr)
        {
            cout << "\nInvalid move: No piece at starting position.\n";
            return false;
        }

        // Check whether the piece belongs to the current player
        if (sourcePiece->isWhite() != player->isWhiteSide())
        {
            cout << "\nInvalid move: You cannot move your opponent's piece.\n";
            return false;
        }

        // Validate source and destination
        if (!move->isValid())
        {
            cout << "\nInvalid move: You cannot capture your own piece.\n";
            return false;
        }

        // Check whether the piece can move to the destination
        if (!sourcePiece->canMove(
                this->board,
                move->getStartCell(),
                move->getEndCell()))
        {
            cout << "\nInvalid move: Piece cannot move to that position.\n";
            return false;
        }

        Piece *destinationPiece = move->getEndCell()->getPiece();

        // Check if the destination contains the opponent's King
        if (dynamic_cast<King *>(destinationPiece) != nullptr)
        {
            this->status = isWhiteTurn
                               ? Status::WHITE_WIN
                               : Status::BLACK_WIN;

            return true;
        }

        // Capture destination piece if present
        if (destinationPiece != nullptr)
        {
            destinationPiece->setKilled(true);
        }

        // Store move in game log
        gameLog.push_back(*move);

        // Move the piece
        move->getEndCell()->setPiece(sourcePiece);
        move->getStartCell()->setPiece(nullptr);

        // Switch turn
        isWhiteTurn = !isWhiteTurn;

        return true;
    }
};

int main()
{
    Player *player1 = new Player("Player1", true);
    Player *player2 = new Player("Player2", false);

    Game *chessGame = new Game(player1, player2);

    chessGame->start();

    delete chessGame;
    delete player1;
    delete player2;

    return 0;
}