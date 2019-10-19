#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#define MAX 38 /* Max board size */

/* PURPOSE:  */
typedef struct 
{
    int width;
    int height;
    int winCondition;
} Settings;

void loadSettings(Settings* settings, char* filename);
void saveLogs();

#endif