/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 17/10/2019
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
    char player;
    int ff, height, width, max, turn, x, y;
    int end = 0;
    height = settings->height;
    width = settings->width;
    max = height * width; /* Used to test for tie */
    player = 'X'; /* X always goes first */
    turn = 1;

    board = createBoard(width, height);
    while (end == 0)
    {
        printf("\nTurn %d, Player %c is picking\n", turn, player);
        displayBoard(board, width, height);
        
        coordInput(width, height, &x, &y, player); /* Retrieving user input */
        if (board[y][x] == 'X' || board[y][x] == 'O')
        {
            printf("Error: That tile has already been filled!\n");
        }
        else
        {/* Placing player letter in selected tile when valid */
            board[y][x] = player;

            if (turn == max)
            {
                printf("\n");
                displayBoard(board, width, height); /* Show the full board */
                printf("The game is a tie!\n");
                end = 2;
            }
            else
            {
                end = hasWon(board, width, height, player);
            }

            if (player == 'X') /* Switching to next player */
                player = 'O';
            else
                player = 'X';
            turn++;
        }
    }
    if (end == 1)
        printf("Player %c won the game!\n", player);

    for (ff = 0; ff < width; ff++)
    {/* Freeing the board */
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

/* PURPOSE:  */
int hasWon(char** board, int width, int height, char player)
{
    int hasWon = 0; /* "boolean" */ /***1 IS TEMP, SHOULD BE 0 ***/

    return hasWon;
}

/* PURPOSE:  */
void coordInput(int width, int height, int* x, int* y, char player)
{
    int valid, input;
    char temp[BUFFER]; /* Used for input */
    
    do
    {    
        valid = 1;
        printf("Place {%c} at tile: ", player);
        fgets(temp, BUFFER, stdin);
        input = sscanf(temp, "%d %d\n", x, y);
        if (input != 2)
        {/* Checking that user's input is 2 numbers */
            printf("Error: Invalid coordinates, please enter two numbers "
                    "separated by a space\n");
            valid = 0;
        }
        else if (*x < 0 || *y < 0)
        {/* Checking for negative input */
            printf("Error: Coordinates can't be negative\n");
            valid = 0;
        }
        else if (*x >= width || *y >= height)
        {/* Checking that input is inside the board */
            printf("Error: Coordinates entered are out of bounds\n");
            valid = 0;
        }
    }
    while (valid == 0);
}

/* PURPOSE:  */
char** createBoard(int width, int height)
{
    int ii, jj;
    char** board;

    board = (char**)malloc(height * sizeof(char*));
    for (ii = 0; ii < height; ii++)
    {
        board[ii] = (char*)malloc(width * sizeof(char));
        for (jj = 0; jj < width; jj++)
        {/* Initialising as space characters, allows for easier printing */
            board[ii][jj] = ' ';
        }
    }
    return board;
}