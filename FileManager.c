/* Filename:           FileManager.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 16/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include <stdio.h>
#include "FileManager.h"

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
            else if (v <= 1) /*** NEGATIVES ARE CAUGHT ABOVE??? ***/
            {/* Checking that value is in correct range */
                printf("Error: Settings values must be > 1\n");
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
            /***if (ii != 3) ==== MAY BE REDUNDANT, CAUGHT AS DUPLICATE ERROR
            {/ Checking for invalid number of lines /
                printf("Error: There is an incorrect number of lines in the "
                       "settings file, there should be exactly 3\n");
            } ***/
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
void saveLogs()
{

}