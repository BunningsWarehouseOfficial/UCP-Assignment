#ifndef GAME_H
#define GAME_H

void newGame(Settings* settings);
void displayBoard(char** board, int width, int height);
int hasWon(char** board, int width, int height, char player);

#endif