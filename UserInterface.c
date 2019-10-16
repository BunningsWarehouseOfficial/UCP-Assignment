/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 16/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FileManager.h"
#include "UserInterface.h"
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
	int cmd;
	char *prompt, *str, *end;
	char buffer[100];
	str = NULL;
	prompt = "\n================= \n[1] New Game \n[2] View Settings \n"
	         "[3] View Logs \n[4] Save Logs \n[5] Exit \n=================\n\n";

	printf("\nM-N-K Tic Tac Toe\nby Kristian Rados\n%s", prompt);
	do
	{
		printf("> ");
		str = fgets(buffer, 100, stdin); /* Retreiving the user's input */
		cmd = strtol(buffer, &end, 10); /* Parsing cmd from the user's input */
		if (str == NULL || strcmp(str, end) == 0 || strcmp(end, "\n") != 0)
		{/* Checking for 'dirty' and/or otherwise invalid input */
			printf("Error: Please enter a single digit number\n");
		}
		else if (cmd < 1 || cmd > 5)
		{/* Checking that input is in valid range */
			printf("Error: Input out of valid range, please enter a number "
				   "between 1 and 5 (inclusive)\n");
		}
		else
		{
			switch (cmd)
			{
				case 1:

					break;
				case 2:
					displaySettings(settings);
					break;
				case 3:
					displayLogs();
					break;
				case 4:
					saveLogs(/*** IMPORT ***/);
					break;
			}
			if (cmd != 5)
				printf("%s", prompt);
		}
	} while (cmd != 5);
}

/* PURPOSE:  */
void displaySettings(Settings* settings)
{
	printf("\n(M) Width         = %d tiles\n(N) Height        = %d tiles\n"
	       "(K) Win Condition = %d tiles in a row\n", settings->width,
		   settings->height, settings->winCondition);
}

/* PURPOSE:  */
void displayLogs()
{

}