/* Filename:           FileManager.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 13/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include <stdio.h>
#include "FileManager.h"

/* PURPOSE:  */
void loadSettings(Settings* settings, char* filename)
{
    char *file;
    int width, height, winCondition;
    FILE *f;
    
    /* Base case: settings file is either invalid or not read properly */
    settings->winCondition = -1; /* -1 represents base case */
    f = fopen(file, "r");

    if (f == NULL)
    {/* Checking for initial open error */
        perror("Error opening journal file");
    }
    else
    {
        /* code */
    }
        
}

/* PURPOSE:  */
void saveLogs()
{

}