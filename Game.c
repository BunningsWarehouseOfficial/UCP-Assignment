/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 16/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include "Game.h"

/* PURPOSE:  */
void newGame(Settings* settings)
{
    int ii, jj, height, width, max, turn;
    char player;
    int end = 0; /* "boolean" */
    height = settings->height;
    width = settings->width;
    max = heigth * width; /* Used to test for tie */
    player = 'X';
    turn = 1;

    /* Creating a new blank board */
    char** board = (char**)malloc(height * sizeof(char*));
    for (ii = 0; ii < height; ii++)
    {
        board[ii] = (char*)malloc(width * sizeof(char));
        for (jj = 0; jj < width; jj++)
        {/* Initialising to space characters, allowing for easier printing */
            board[ii][jj] = ' ';
        }
    }

    while (end == 0)
    {
        printf("Turn %d, player %c is picking", turn, player);
        displayBoard(board, width, height);
        /***
        pick location prompt
        user enters coords
        add to board array
        switch player
        increment turn
        ***/
    }
}

/* PURPOSE:  */
void displayBoard(char** board, int width, int height)
{
    int aa, ii, jj;

    char* barOuter = "===";
    char* barInner = "||";
    for (aa = 0; aa < width - 1; aa++)
    {/* Extend top, bottom and middle bars for each tile in width */
        barOuter = strncat(barOuter, "====", 5);
        barInner = strncat(barInner, "----", 5);
    }
    barOuter = strncat(barOuter, "====\n", 5);
    barInner = strncat(BarInner, "||\n", 3);

    printf("")
    printf("%s", barOuter);
    for (ii = 0; ii < height; ii++)
    {
        printf("||");
        for (jj = 0; jj < width; jj++)
        {
            printf(" %c |", board[ii][jj]);
        }
        printf("|\n");
    }
    printf("%s", barOuter);
}

int hasWon(char** board, int width, int height, char player)
{
    int hasWon = 1; /* "boolean" */ /***1 IS TEMP, SHOULD BE 0 ***/

    return hasWon;
}