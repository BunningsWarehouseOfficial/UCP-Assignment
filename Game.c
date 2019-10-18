/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 16/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FileManager.h"
#include "Game.h"

/* PURPOSE:  */
void newGame(Settings* settings)
{
    char** board;
    int ii, jj, ff, height, width, max, turn;
    char player;
    int end = 0; /* "boolean" */
    height = settings->height;
    width = settings->width;
    max = height * width; /* Used to test for tie */
    player = 'X';
    turn = 1;

    /* Creating a new blank board */
    board = (char**)malloc(height * sizeof(char*));
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
        printf("Turn %d, Player %c is picking\n", turn, player);
        displayBoard(board, width, height);
        printf("Place {%c} at tile: ", turn);
        printf("%d", max); /***/
        
        /***
        pick location prompt
        user enters coords
        add to board array
        switch player
        increment turn
        ***/
        end = 1;
    }

    for (ff = 0; ff < width; ff++)
    {
        free(board[ff]);
    }
    free(board);
}

/* PURPOSE:  */
void displayBoard(char** board, int width, int height)
{
    int aa, ii, jj;
    /* Allocating the space needed for repeated strings in board */
    char* barOuter = (char*)malloc((5 + (width) * 4) * sizeof(char));
    char* barInner = (char*)malloc((5 + (width) * 4) * sizeof(char));

    /* Creating strings for the board */
    strncpy(barOuter, "===", 4);
    strncpy(barInner, "||---", 6);
    for (aa = 0; aa < width - 1; aa++)
    {/* Extend top, bottom and middle bars for each tile in width */
        barOuter = strncat(barOuter, "====", 5);
        barInner = strncat(barInner, "----", 5);
    }
    barOuter = strncat(barOuter, "====\n", 6);
    barInner = strncat(barInner, "||\n", 4);

    /* Printing the board */
    printf("%s", barOuter);
    for (ii = 0; ii < height; ii++)
    {
        printf("||");
        for (jj = 0; jj < width; jj++)
        {
            printf(" %c |", board[ii][jj]);
        }
        printf("|\n");
        if (ii != height - 1) /* Don't print inner bar at end of board */
            printf("%s", barInner);
    }
    printf("%s", barOuter);

    free(barOuter);
    free(barInner);
}

int hasWon(char** board, int width, int height, char player)
{
    int hasWon = 1; /* "boolean" */ /***1 IS TEMP, SHOULD BE 0 ***/

    return hasWon;
}