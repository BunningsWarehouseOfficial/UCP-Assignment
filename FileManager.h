#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/* PURPOSE:
Defining a struct that stores the settings values that determines the
parameters for how the game is run. It is passed through to functions so that
they can access all the game settings from a single import. */
typedef struct 
{
    int width;
    int height;
    int winCondition;
} Settings;

void loadSettings(Settings* settings, char* filename);
void saveLogs(Settings* settings, LinkedList* log);
void displayLogs(FILE* stream, Settings* settings, LinkedList* log);

#endif