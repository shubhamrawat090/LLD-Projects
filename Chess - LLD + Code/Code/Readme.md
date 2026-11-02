# Chess Game (C++)

## Compile

Run this command from the project's root directory:

```powershell
g++ -std=c++17 -Iinclude src/main.cpp src/Utils.cpp src/Piece.cpp src/Cell.cpp src/Board.cpp src/Move.cpp src/Player.cpp src/Game.cpp src/PieceFactory.cpp src/King.cpp src/Queen.cpp src/Bishop.cpp src/Knight.cpp src/Rook.cpp src/Pawn.cpp src/KingMovementStrategy.cpp src/QueenMovementStrategy.cpp src/BishopMovementStrategy.cpp src/KnightMovementStrategy.cpp src/RookMovementStrategy.cpp src/PawnMovementStrategy.cpp -o chess.exe
```

## Run

```powershell
.\chess.exe
```