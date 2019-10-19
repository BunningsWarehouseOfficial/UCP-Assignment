#ifndef GAME_H
#define GAME_H

#define BUFFER 256
#define MAX 38 /* Max board size */

/* PURPOSE:  */
typedef struct
{
    int turn;
    char player;
    int x;
    int y;
} Turn;

LinkedList* newGame(Settings* settings);
void displayBoard(char** board, int width, int height);

int hasWon(char** board, Settings* settings, char player, int x, int y);
int checkRow(char** board, char player, Settings* settings, int x, int y);
int checkColumn(char** board, char player, Settings* settings, int x, int y);
int checkDiagonals(char** board, char player, Settings* settings, int x, int y);

void coordInput(int width, int height, int* x, int* y, char player);
char** createBoard(int width, int height);

#endif