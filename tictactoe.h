/// Acts as an interface for the tic-tac-toe program.
/// Defines necessary functions to play the game.
/// @author Dan Beiter

#ifndef TACTACTOE_H
#define TICTACTOE_H

// structure used for maintaining the game board.
// a is top left, e is middle, etc.
typedef struct Board_S {
    char a; char b; char c;
    char d; char e; char f;
    char g; char h; char i;
} Board;

/// displayRules displays the basics of playing tic-tac-toe.
static void displayRules();


/// displayInstructions displays how to play this C-based version of tic-tac-toe.
static void displayInstructions();


/// wonGame checks the current board to see if the player or CPU has won.
/// @param board: the current representation of the game board
/// @param symbol: 'x' for player, 'o' for CPU
/// @return: true if the game has been won, false otherwise
static bool wonGame(Board board, char symbol);


/// beginNewGame allows to user to play a game from start-to-finish against the CPU.
/// @param difficulty: 1 for easy CPU, 2 for normal
static void beginNewGame(int difficulty);

#endif // TACTACTOE_H
