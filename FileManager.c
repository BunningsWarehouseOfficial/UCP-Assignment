/* Filename:           FileManager.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 19/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LinkedList.h"
#include "FileManager.h"
#include "Game.c"

/* PURPOSE:  */
void loadSettings(Settings* settings, char* filename)
{
    FILE *f;
    int valid = 1; /* "boolean" */
    
    /* Base case: settings file is either invalid or not read properly */
    settings->width = -1;
    settings->height = -1;
    settings->winCondition = -1; /* -1 represents base case */
    f = fopen(filename, "r");

    if (f == NULL)
    {/* Checking for initial open error */
        perror("Error opening settings file");
        valid = 0;
    }
    else
    {
        char c;
        int v, width, height, winCondition, line;
        int upper, lower; /* "booleans" */
        int ii = 0; /* Counting number of lines read with ii */
        width = height = winCondition = 0;

        line = fscanf(f, "%c=%d\n", &c, &v);
        while (valid == 1 && line != EOF)
        {
            upper = (c != 'M' && c != 'N' && c != 'K');
            lower = (c != 'm' && c != 'n' && c != 'k');
            if (line != 2 || (upper && lower))
            {/* Catching any formatting errors */
                printf("Error: Invalid line format in settings file, format "
                       "for each line should be A=x, where A = M, N or K\n");
                valid = 0;
            }
            else if (v <= 1)
            {/* Checking that value is in correct range */
                printf("Error: Settings values must be > 1\n");
                valid = 0;
            }
            else if (v > MAX)
            {/* Checking that value is in correct range */
                printf("Error: Settings values must be <= MAX\n");
                valid = 0;
            }
            else
            {
                switch (c)
                {
                 /* We check for duplicates by seeing if value has been
                    changed from 0 already */
                    case 'M': case 'm':
                        if (width != 0)
                        {
                            printf("Error: M appears more than once\n");
                            valid = 0;
                        }
                        else
                            width = v;
                        break;
                    case 'N': case 'n':
                        if (height != 0)
                        {
                            printf("Error: N appears more than once\n");
                            valid = 0;
                        }
                        else
                            height = v;
                        break;
                    case 'K': case 'k': /* Accounting for base case -1 */
                        if (winCondition != 0 && winCondition != -1)
                        {
                            printf("Error: K appears more than once\n");
                            valid = 0;
                        }
                        else
                            winCondition = v;
                        break;
                }
            } 
            ii++;
            line = fscanf(f, "%c=%d\n", &c, &v); /* Get next line */
        } 
        
        if (ferror(f))
        {/* Catching any read errors */
            perror("Error reading from settings file");
        }
     /* Perform secondary error checking only if passed through first section in
        order to avoid multiple error messages */
        else if (valid == 1) 
        {
            if (width == 0 || height == 0 || winCondition == 0)
            {/* Checking that there are no missing settings values */
                printf("Error: File does not have all 3 required settings, "
                       "must include an M, N and K value\n");
            }
            else if (winCondition > width || winCondition > height)
            {/* Checking for invalid winCondition */
                printf("Error: K (Win Condition) must not be greater than "
                       "either M or N\n");
            }
            else
            {/* Assigning values if no errors occur */
                settings->width = width;
                settings->height = height;
                settings->winCondition = winCondition;
            }
        }
        fclose(f);
    }
}

/* PURPOSE:  */
void saveLogs(Settings* settings, LinkedList* log)
{
    #ifdef SECRET
    printf("Error: This function has been disabled\n");
    #else
    
    FILE* f;
    time_t rawTime;
    struct tm *local;
    int m, n, k, hour, min, day, month;
    char filename[26];

    time(&rawTime); /* Retrieve current system time */
    local = localtime(&rawTime); /* Create local time struct */
    m = settings->width;
    n = settings->height;
    k = settings->winCondition;
    hour = local->tm_hour;
    min = local->tm_min;
    day = local->tm_mday;
    month = local->tm_mon + 1; /* Creating logfile filename */
    sprintf(filename, "MNK_%d-%d-%d_%d-%d_%d-%d.log", m, n, k, hour, min,
            day, month);

    f = fopen(filename, "w");
    displayLogs(f, settings, log);
    fclose(f);

    #endif
}

/* PURPOSE:  */
void displayLogs(FILE* stream, Settings* settings, LinkedList* log)
{
	int gameCount, turnCount, ii, jj;
	LinkedListNode *game, *turn;
    Turn* data;
    game = log->head;
    turn = NULL;
	gameCount = turnCount = 0;

	/* Settings (most recent) */
	fprintf(stream, "SETTINGS:\n    M: %d\n    N: %d\n    K: %d\n\n",
	        settings->width, settings->height, settings->winCondition);

	while (game != NULL)
	{/* Counting how many games there were */
		gameCount++;
		game = game->next;
	}
    if (gameCount != 0)
    {
        game = log->head; /* Reinitialise game */
        turn = ((LinkedList*)game->data)->head;
        for (ii = 1; ii <= gameCount; ii++)
        {/* Iterating through each game */
            fprintf(stream, "GAME %d:\n", ii);
            while (turn != NULL)
            {/* Counting how many turns this game had */
                turnCount++;
                turn = turn->next;
            }

            turn = ((LinkedList*)game->data)->head; /* Reinitialise turn */
            for (jj = 1; jj <= turnCount; jj++)
            {/* Iterating through each turn */
                data = turn->data;
                fprintf(stream, "    Turn: %d\n    Player: %c\n    Location: "
                       "%d,%d\n\n", data->turn, data->player, data->x, data->y);
                turn = turn->next;
            }
            game = game->next;
        }
    }
}