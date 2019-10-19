#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/* PURPOSE:  */
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