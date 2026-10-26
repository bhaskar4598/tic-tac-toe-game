# Tic Tac Toe (C++ Console Game)

A console-based Tic Tac Toe game in C++ that demonstrates core programming concepts such as loops, arrays and conditional logic.

## Features
- Player vs Player and Player vs Computer modes
- Board is redrawn dynamically after every move
- Win and draw detection (all 8 winning lines checked with an array)
- Input validation (invalid or already-taken positions are rejected)
- Replay option with a running scoreboard
- Simple computer AI: win if possible, block the opponent, take centre, else random

## How to play
Positions are numbered 1-9:
```
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
```

## How to run
```bash
g++ -std=c++14 main.cpp -o tictactoe
./tictactoe        # Windows: tictactoe.exe
```

## Concepts used
Arrays (1D board, 2D winning lines), loops, if/else conditions, functions, `rand()` for computer moves.
