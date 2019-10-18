#ifndef GAME_H
#define GAME_H

#define BUFFER 256

void newGame(Settings* settings);
void displayBoard(char** board, int width, int height);
int hasWon(char** board, Settings* settings, char player, int x, int y);
void coordInput(int width, int height, int* x, int* y, char player);
char** createBoard(int width, int height);

#endif