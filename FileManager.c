/* Filename:           FileManager.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 13/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FileManager.h"

/* PURPOSE:  */
void loadSettings(Settings* settings, char* filename)
{
    char *file;
    char c; /* c for character */
    int width, height, winCondition, line, v; /* v for value */
    int valid = 1; /* "boolean"
    FILE *f;
    
    /* Base case: settings file is either invalid or not read properly */
    settings->winCondition = -1; /* -1 represents base case */
    f = fopen(file, "r");

    if (f == NULL)
    {/* Checking for initial open error */
        perror("Error opening settings file");
    }
    else
    {
        int ii = 0; /* Counting number of lines read with ii */
        while (valid == 1 && line != EOF)
        {
            line = fscanf(f, "%c=%1d", c, v);
            if (line != 2 || (c != 'M' && c != 'N' && c != 'K') || v <= 0)
            {/* Catching any formatting errors */
                printf("Error: Invalid line format in settings file. Format "
                       "for each line should be A=x, where A = M, N or K and "
                       "x > 0\n");
                valid = 0;
            }
            else
            {
                /* switch or 3 if's to assign values to struct if no more error checking is required */
            }
            ii++;
        }
        
        if (ferror(f))
        {/* Catching any read errors */
            perror("Error reading from settings file")
        }
        else if (ii != 3)
        {/* Checking for invalid number of lines */
            printf("Error: There is an incorrect number of lines in the "
                   "settings file, there should be exactly 3\n");
        }
        else
        {/* Assigning values if no errors occur */
            
        }
    }
}

/* PURPOSE:  */
void saveLogs()
{

}