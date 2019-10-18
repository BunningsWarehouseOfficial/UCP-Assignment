#ifndef GAME_H
#define GAME_H

#define BUFFER 256

void newGame(Settings* settings);
void displayBoard(char** board, int width, int height);
int hasWon(char** board, int width, int height, char player);
void coordInput(int width, int height, int* x, int* y, char player);
char** createBoard(int width, int height);

#endif