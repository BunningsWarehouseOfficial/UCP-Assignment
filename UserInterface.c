/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 16/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include <stdio.h>
#include "UserInterface.h"
#include "FileManager.h"
#include "LinkedList.h" /*** Is this needed? ***/
#include "Game.h"

/* PURPOSE:  */
int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		Settings* settings = (Settings*)malloc(sizeof(Settings));
		char* settingsFile = argv[1];
		loadSettings(settings, settingsFile);
		if (settings->winCondition != -1)
		{/* Program only continues if the settings file is valid */
			menu(settings);
		}

		free(settings);	
	}
	else
	{/* Error for running incorrectly on command line */
		printf("Error: Program must be run as: mnk [<filename>.txt]\n");
	}
	
	return 0;
}

void menu(Settings* settings)
{			
	int cmd, scan;
	char* prompt;
	prompt = "\n[1] New Game \n[2] View Settings \n[3] View Logs \n"
	         "[4] Save Logs \n[5] Exit\n\n";

	do
	{
		printf("%s", prompt);
		scan = scanf("%d", &cmd);
		if (scan != 1)
		{
			printf("Error: Invalid input, please enter a single digit "
			       "number\n\n")
		}
	} while (cmd != 5);
}