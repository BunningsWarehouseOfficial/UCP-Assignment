/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 20/10/2019
   Purpose: Handles the actual gameplay for MNK Tic Tac Toe. This involves
            creating, managing, displaying and adding to a new game board, as
            well as creating and managing the log entry for this new game.
            Player moves are handled here and any victories or ties are also
            determined here.                                                  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "FileManager.h"
#include "Game.h"

/* PURPOSE:
Starts a brand new Tic Tac Toe game using the current game settings. It creates
and manages the board and also manages generating the necessary logs for this
game. The enirety of the actual Tic Tac Toe gameplay is handled by this
function as it handles displaying the board, placing new tiles, checking for a
winner and checking for a tie. */
LinkedList* newGame(Settings* settings)
{
    LinkedList* game;
    char** board;
    char player;
    int ff, height, width, max, turnNo, x, y;
    int end = 0;

    game = createLinkedList();
    height = settings->height;
    width = settings->width;
    max = height * width; /* Used to test for a tie */
    player = 'X'; /* X always goes first */
    turnNo = 1;

    board = createBoard(width, height);
    while (end == 0)
    {
        printf("\nTurn %d, Player %c\n", turnNo, player);
        displayBoard(board, width, height);
        
        coordInput(width, height, &x, &y, player); /* Retrieving user input */
        if (board[y][x] == 'X' || board[y][x] == 'O')
        {
            printf("Error: That tile has already been filled!\n");
        }
        else
        {/* Placing player letter in selected tile when valid */
            Turn* turn = (Turn*)malloc(sizeof(Turn));
            board[y][x] = player;
            /* Recording the turn for the logs */
            turn->turn = turnNo;
            turn->player = player;
            turn->x = x;
            turn->y = y;
            insertLast(game, turn);

            end = hasWon(board, settings, player, x, y); /* Check for winner */
            if (turnNo == max && end != 1)
            {/* Checking for a tie */
                printf("\n");
                displayBoard(board, width, height); /* Show the full board */
                printf("The game is a tie!\n");
                end = 2;
            }

            if (end == 1)
            {/* Informing the users of a winner */
                printf("\n");
                displayBoard(board, width, height); /* Show the winning board */
                printf("Player %c won the game!\n", player);
            }

            if (player == 'X') /* Switching to next player */
                player = 'O';
            else
                player = 'X';
            turnNo++;
        }
    }

    /* Freeing the board */
    for (ff = 0; ff < height; ff++)
    {
        free(board[ff]);
    }
    free(board);
    return game;
}

/* PURPOSE:
Translates the literal board that is stored in a two dimensional array into a
visual representation of the board that is somewhat pleasing aesthetically so
that it can be printed to the terminal for the user to track the game. */
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

/* PURPOSE:
Checks the board for any patterns that would indicate that the player who just
placed a new tile has won the game or not depending on the win condition defined
by the settings struct. */
int hasWon(char** board, Settings* settings, char player, int x, int y)
{
    int hasWon = 0; /* "boolean" */

    hasWon = checkRow(board, player, settings, x, y);
    if (hasWon == 0)
    {
        hasWon = checkColumn(board, player, settings, x, y);
        if (hasWon == 0)
        {
            hasWon = checkDiagonals(board, player, settings, x, y);
        }
    }
    return hasWon;
}

/* PURPOSE:
Checks for tiles of the same type as the player in the same row as where the
player just placed a tile. */
int checkRow(char** board, char player, Settings* settings, int x, int y)
{
    int numLetter, coord, hasWon;
    char letter;
    hasWon = 0;
    numLetter = 1;
    
    /* Check left side */
    letter = player;
    coord = x - 1;
    while (coord >= 0 && letter == player)
    {
        letter = board[y][coord];
        if (letter == player)
            numLetter++;

        coord--;
    }
    
    /* Check right side */
    letter = player;
    coord = x + 1;
    while (coord < settings->width && letter == player)
    {
        letter = board[y][coord];
        if (letter == player)
            numLetter++;

        coord++;
    }
    
    if (numLetter >= settings->winCondition)
        hasWon = 1;
    return hasWon;
}

/* PURPOSE:
Checks for tiles of the same type as the player in the same column as where the
player just placed a tile. */
int checkColumn(char** board, char player, Settings* settings, int x, int y)
{
    int numLetter, coord, hasWon;
    char letter;
    hasWon = 0;
    numLetter = 1;
    
    /* Check bottom side */
    letter = player;
    coord = y - 1;
    while (coord >= 0 && letter == player)
    {
        letter = board[coord][x];
        if (letter == player)
            numLetter++;
        
        coord--;
    }

    /* Check top side */
    letter = player;
    coord = y + 1;
    while (coord < settings->height && letter == player)
    {
        letter = board[coord][x];
        if (letter == player)
            numLetter++;
        
        coord++;
    }
    
    if (numLetter >= settings->winCondition)
        hasWon = 1;
    return hasWon;
}

/* PURPOSE:
Checks for tiles of the same type as the player in both of the diagonals that
extend out from where the player just placed a tile. */
int checkDiagonals(char** board, char player, Settings* settings, int x, int y)
{
    int numLetter, xCoord, yCoord, hasWon, width, height, w;
    char letter;
    width = settings->width;
    height = settings->height;
    w = settings->winCondition;
    hasWon = 0;
    numLetter = 1;
    
    /* Check top left diagonal */
    letter = player;
    xCoord = x - 1;
    yCoord = y - 1;
    while (xCoord >= 0 && yCoord >= 0 && letter == player)
    {
        letter = board[yCoord][xCoord];
        if (letter == player)
            numLetter++;
        xCoord--;
        yCoord--;
    }
    
    /* Check bottom right diagonal */
    letter = player;
    xCoord = x + 1;
    yCoord = y + 1;
    while (xCoord < width && yCoord < height && letter == player)
    {
        letter = board[yCoord][xCoord];
        if (letter == player)
            numLetter++;
        xCoord++;
        yCoord++;
    } 

    if (numLetter >= w)
        hasWon = 1;
    else
    {
        numLetter = 1;
        /* Check top right diagonal */
        letter = player;
        xCoord = x + 1;
        yCoord = y - 1;
        while (xCoord < width && yCoord >= 0 && letter == player)
        {
            letter = board[yCoord][xCoord];
            if (letter == player)
                numLetter++;
            xCoord++;
            yCoord--;
        }

        /* Check bottom left diagonal */
        letter = player;
        xCoord = x - 1;
        yCoord = y + 1;
        while (xCoord >= 0 && yCoord > height && letter == player)
        {
            letter = board[yCoord][xCoord];
            if (letter == player)
                numLetter++;
            xCoord--;
            yCoord++;
        }

        if (numLetter >= w)
            hasWon = 1;
    }
    return hasWon;
}

/* PURPOSE:
Handles user input for the game itself, determining the coordinates in which
the current player would like to place their tile. Ensures that the user's
input is both valid and within the correct range. */
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

/* PURPOSE:
Creates a new board for this game by allocating memory on the heap for a two
dimensional array of characters with a size determined by the current game
dimensions as defined by the settings struct (but imported individually). */
char** createBoard(int width, int height)
{
    int ii, jj;
    char** board;

    /* Creating array of arrays (y dimension) */
    board = (char**)malloc(height * sizeof(char*));
    for (ii = 0; ii < height; ii++)
    {
        /* Creating array for each element of previous array (x dimension) */
        board[ii] = (char*)malloc(width * sizeof(char));
        for (jj = 0; jj < width; jj++)
        {/* Initialising as space characters, allows for easier printing */
            board[ii][jj] = ' ';
        }
    }
    return board;
}