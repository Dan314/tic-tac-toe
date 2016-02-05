/// Provides functions outlined in tictactoe.h interface.
/// @author Dan Beiter

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include "tictactoe.h"


static void displayRules() {
    int stall = 0;
    printf("In tic-tac-toe, the goal is to get 3-in-a-row on the board\n");
    printf("\tbefore your opponent does.\n");
    stall++;
    usleep(4000000);
    printf("The 3-in-a-row can be horizontally, vertically, or diagonally.\n");
    stall++;
    usleep(4000000);
    printf("Be sure to block your opponent if they can get 3-in-a-row\n");
    printf("\ton the next move!\n");
    stall++;
    usleep(4000000);
    printf("\n");
}



static void displayInstructions() {
    int stall = 0;
    printf("1 2 3\n4 5 6\n7 8 9\n");
    printf("These numbers correspond to where you would put an 'x'.\n");
    stall++;
    usleep(5500000);
    printf("For example, to put an 'x' in the upper-right corner, type 3 and hit enter.\n");
    stall++;
    usleep(4000000);
    printf("You cannot put an 'x' where there is already an 'x' or an 'o'!\n");
    stall++;
    usleep(4000000);
    printf("At any time, press 'q' and hit enter to exit the game.\n");
    stall++;
    usleep(4000000);
}



static bool wonGame(Board board, char symbol) {
    if( (board.a == symbol) && (board.b == symbol) && (board.c == symbol) ) {return true;}
    if( (board.d == symbol) && (board.e == symbol) && (board.f == symbol) ) {return true;}
    if( (board.g == symbol) && (board.h == symbol) && (board.i == symbol) ) {return true;}
    if( (board.a == symbol) && (board.d == symbol) && (board.g == symbol) ) {return true;}
    if( (board.b == symbol) && (board.e == symbol) && (board.h == symbol) ) {return true;}
    if( (board.c == symbol) && (board.f == symbol) && (board.i == symbol) ) {return true;}
    if( (board.a == symbol) && (board.e == symbol) && (board.i == symbol) ) {return true;}
    if( (board.c == symbol) && (board.e == symbol) && (board.g == symbol) ) {return true;}
    return false;
}



static void beginNewGame(int difficulty) {
    int turn_number = 0;
    char buffer[1];
    Board board = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

    bool occupied[9];
    for(int index = 0; index < 9; index++) {
        occupied[index] = false;
    }

    while(true) {
        turn_number++;
        while(true) {
            for(unsigned int bufIndex = 0; bufIndex < sizeof(buffer); bufIndex++) {
                memset(&buffer[bufIndex], 0, sizeof(buffer[bufIndex]));  // empty buffer
            }
            char * ptr;
            printf("Please enter a number (1-9): > ");
            fgets(buffer, 15, stdin);
            if(buffer[0] == 'q') {
                printf("Thanks for Playing! :)");
                exit(EXIT_SUCCESS);
            }
            else if(buffer[0] == '0') {
                printf("Invalid Choice.\n");
                continue;
            }
            else if(isdigit(buffer[0])) {
                int user_entered_num = (int) strtol(buffer, &ptr, 10);
                if(!occupied[user_entered_num - 1]) {
                    occupied[user_entered_num - 1] = true;
                    break;
                }
            }
        }

        char * ptr;
        int user_position = (int) strtol(buffer, &ptr, 10);
        switch(user_position) {
            case 1: board.a = 'x';
                break;
            case 2: board.b = 'x';
                break;
            case 3: board.c = 'x';
                break;
            case 4: board.d = 'x';
                break;
            case 5: board.e = 'x';
                break;
            case 6: board.f = 'x';
                break;
            case 7: board.g = 'x';
                break;
            case 8: board.h = 'x';
                break;
            case 9: board.i = 'x';
                break;
            default: break;
        }

        printf("Current Board: \n");
        printf("%c %c %c\n%c %c %c\n%c %c %c\n", board.a, board.b, board.c,
               board.d, board.e, board.f, board.g, board.h, board.i);
        if(wonGame(board, 'x')) {
            printf("Nice Job - you won the game!\n");
            return;
        }
        if(turn_number == 5) {
            printf("This game is officially a draw. Well played, grasshopper.\n");
            return;
        }

        printf("Computer now choosing Move...\n");
        int comp_move = 0;
        if(difficulty == 1) {                       // easy
            comp_move = user_position - 1;
            while(occupied[comp_move]) {
                comp_move = (rand() % 9);
            }
        }
        else {                                      // normal
            if(!occupied[4]) {comp_move = 4;}
            // start of horizontal 3-in-a-row checks:
            else if( (board.a != '-') && (board.a == board.b) && (!occupied[2]) ) {comp_move = 2;}
            // 1. if the top-left and top-center squares are both either 'x' or 'o'
            // and the top-right square is empty, move there.
            else if( (board.a != '-') && (board.a == board.c) && (!occupied[1]) ) {comp_move = 1;}
            // 2. if the top-left and top-right squares are both either 'x' or 'o'
            // and the top-center square is empty, move there.
            else if( (board.b != '-') && (board.b == board.c) && (!occupied[0]) ) {comp_move = 0;}
            // and so on
            else if( (board.d != '-') && (board.d == board.e) && (!occupied[5]) ) {comp_move = 5;}
            else if( (board.d != '-') && (board.d == board.f) && (!occupied[4]) ) {comp_move = 4;}
            else if( (board.e != '-') && (board.e == board.f) && (!occupied[3]) ) {comp_move = 3;}
            else if( (board.g != '-') && (board.g == board.h) && (!occupied[8]) ) {comp_move = 8;}
            else if( (board.g != '-') && (board.g == board.i) && (!occupied[7]) ) {comp_move = 7;}
            else if( (board.h != '-') && (board.h == board.i) && (!occupied[6]) ) {comp_move = 6;}
            // start of vertical 3-in-a-row checks:
            else if( (board.a != '-') && (board.a == board.d) && (!occupied[6]) ) {comp_move = 6;}
            else if( (board.a != '-') && (board.a == board.g) && (!occupied[3]) ) {comp_move = 3;}
            else if( (board.d != '-') && (board.d == board.g) && (!occupied[0]) ) {comp_move = 0;}
            else if( (board.b != '-') && (board.b == board.e) && (!occupied[7]) ) {comp_move = 7;}
            else if( (board.b != '-') && (board.b == board.h) && (!occupied[4]) ) {comp_move = 4;}
            else if( (board.e != '-') && (board.e == board.h) && (!occupied[1]) ) {comp_move = 1;}
            else if( (board.c != '-') && (board.c == board.f) && (!occupied[8]) ) {comp_move = 8;}
            else if( (board.c != '-') && (board.c == board.i) && (!occupied[5]) ) {comp_move = 5;}
            else if( (board.f != '-') && (board.f == board.i) && (!occupied[2]) ) {comp_move = 2;}
            // start of diagonal 3-in-a-row checks:
            else if( (board.a != '-') && (board.a == board.e) && (!occupied[8]) ) {comp_move = 8;}
            else if( (board.a != '-') && (board.a == board.i) && (!occupied[4]) ) {comp_move = 4;}
            else if( (board.e != '-') && (board.e == board.i) && (!occupied[0]) ) {comp_move = 0;}
            else if( (board.b != '-') && (board.b == board.e) && (!occupied[6]) ) {comp_move = 6;}
            else if( (board.b != '-') && (board.b == board.g) && (!occupied[4]) ) {comp_move = 4;}
            else if( (board.e != '-') && (board.e == board.g) && (!occupied[2]) ) {comp_move = 2;}

            else {                    // if all else fails, choose a randomized move
                comp_move = user_position - 1;
                while(occupied[comp_move]) {
                    comp_move = (rand() % 9);
                }
            }
        }
        occupied[comp_move] = true;

        usleep(4000000);
        printf("Computer chooses move #%d\n", comp_move + 1);
        switch(comp_move + 1) {
            case 1: board.a = 'o';
                break;
            case 2: board.b = 'o';
                break;
            case 3: board.c = 'o';
                break;
            case 4: board.d = 'o';
                break;
            case 5: board.e = 'o';
                break;
            case 6: board.f = 'o';
                break;
            case 7: board.g = 'o';
                break;
            case 8: board.h = 'o';
                break;
            case 9: board.i = 'o';
                break;
            default: break;
        }

        printf("Current Board: \n");
        printf("%c %c %c\n%c %c %c\n%c %c %c\n", board.a, board.b, board.c,
               board.d, board.e, board.f, board.g, board.h, board.i);
        if(wonGame(board, 'o')) {
            printf("The computer won this round.\n");
            return;
        }
    }
}



int main(int argc, char* argv[]) {
    printf("Choose your difficulty: (e)asy or (n)ormal.\n");
    char buffer[1];
    int difficulty;
    bool entered_command = false, play_again = true;
    for(unsigned int bufIndex = 0; bufIndex < sizeof(buffer); bufIndex++) {
        memset(&buffer[bufIndex], 0, sizeof(buffer[bufIndex]));  // empty buffer
    }

    while( (buffer[0] != 'e') && (buffer[0] != 'n') ) {
        if(entered_command) {printf("Invalid Command.\n");}
        printf("> ");
        for(unsigned int bufIndex = 0; bufIndex < sizeof(buffer); bufIndex++) {
            memset(&buffer[bufIndex], 0, sizeof(buffer[bufIndex]));  // empty buffer
        }
        fgets(buffer, 15, stdin);
        entered_command = true;
    }

    if(buffer[0] == 'e') {difficulty = 1;}
    else {difficulty = 2;}
    for(unsigned int bufIndex = 0; bufIndex < sizeof(buffer); bufIndex++) {
        memset(&buffer[bufIndex], 0, sizeof(buffer[bufIndex]));  // empty buffer
    }
    printf("Welcome to tic-tac-toe! You'll play as 'x'.\n");
    printf("If you need to hear the rules for the game, press r and hit enter.\n");
    printf("Otherwise, press s and hit enter to start a new game.\n");
    entered_command = false;

    while( (buffer[0] != 'r') && (buffer[0] != 's') ) {
        if(entered_command) {printf("Invalid Command.\n");}
        printf("> ");
        for(unsigned int bufIndex = 0; bufIndex < sizeof(buffer); bufIndex++) {
            memset(&buffer[bufIndex], 0, sizeof(buffer[bufIndex]));  // empty buffer
        }
        fgets(buffer, 15, stdin);
        entered_command = true;
    }

    if(buffer[0] == 'r') {
        displayRules();
        printf("Now starting game.\n");
    }

    displayInstructions();
    while(play_again) {
        beginNewGame(difficulty);
        entered_command = false;
        buffer[0] = 'i';

        while( (buffer[0] != 'y') && (buffer[0] != 'n') ) {
            if(entered_command) {printf("Invalid Command.\n");}
            printf("Play Again? (y)es/(n)o > ");
            for(unsigned int bufIndex = 0; bufIndex < sizeof(buffer); bufIndex++) {
                memset(&buffer[bufIndex], 0, sizeof(buffer[bufIndex]));  // empty buffer
            }
            fgets(buffer, 15, stdin);
            entered_command = true;
        }
        if(buffer[0] == 'n') {play_again = false;}
    }
    return 0;
}
