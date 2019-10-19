/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 17/10/2019
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

/* PURPOSE:  */
void menu(Settings* settings)
{			
	int cmd, upper;
	char *prompt, *str, *end;
	char temp[BUFFER];
	str = NULL;
	#ifdef EDITOR
	prompt = "\n================= \n[1] New Game \n[2] View Settings \n"
	         "[3] View Logs \n[4] Save Logs \n[5] Edit Settings \n[0] Exit \n"
			 "=================\n\n";
	upper = 5;
	#else
	prompt = "\n================= \n[1] New Game \n[2] View Settings \n"
	         "[3] View Logs \n[4] Save Logs \n[0] Exit \n=================\n\n";
	upper = 4;
	#endif

	printf("\nM-N-K Tic Tac Toe\nby Kristian Rados\n%s", prompt);
	do
	{
		printf("> ");
		str = fgets(temp, BUFFER, stdin); /* Retreiving the user's input */
		cmd = strtol(temp, &end, 10); /* Parsing cmd from the user's input */
		if (str == NULL || strcmp(str, end) == 0 || strcmp(end, "\n") != 0)
		{/* Checking for 'dirty' and/or otherwise invalid input */
			printf("Error: Please enter a single digit number\n");
		}
		else if (cmd < 0 || cmd > upper)
		{/* Checking that input is in valid range */
			printf("Error: Input out of valid range, please enter a number "
				   "between 1 and %d (inclusive)\n", upper);
		}
		else
		{
			switch (cmd)
			{
				case 1:
					newGame(settings);
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
				#ifdef EDITOR
				case 5:
					editSettings(settings);
					break;
				#endif
			}
			if (cmd != 0)
				printf("%s", prompt);
		}
	} while (cmd != 0);
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

#ifdef EDITOR
/* PURPOSE:  */
void editSettings(Settings* settings)
{
    int valid, input, value;
    char temp[BUFFER]; /* Used for input */
	char s;
	char *prompt, *str, *end;
	str = NULL;
	prompt = "\nWhich setting would you like to edit? \n[M] Width \n"
			 "[N] Height \n[K] Win Condition\n\n";	
    
	printf("%s", prompt);
    do
    {    
        valid = 1;
		printf("> ");
		fgets(temp, BUFFER, stdin); /* Retrieving user input */
        input = sscanf(temp, "%c\n", &s); /* Parsing value from user input */
        if (input != 1)
        {/* Checking that user's input is a letter */
            printf("Error: Invalid selection, please enter a letter\n");
            valid = 0;
        }
        else if (s!='M' && s!='N' && s!='K' && s!='m' && s!='n' && s!='k')
        {/* Checking for correct letter */
            printf("Error: Invalid selection, please enter either M, N or K\n");
            valid = 0;
        }
		else
		{
			printf("\nWhat value are you changing {%c} to?\n\n", s);
			printf("> ");
			str = fgets(temp, BUFFER, stdin); /* Retrieving user input */
			value = strtol(temp, &end, 10); /* Parsing value from user input */
			if (str == NULL || strcmp(str, end) == 0 || strcmp(end, "\n") != 0)
			{/* Checking for 'dirty' and/or otherwise invalid input */
				printf("Error: Value must be a single digit number\n");
			}
			else if (value <= 1)
			{/* Checking that input is in valid range */
				printf("Error: Settings values must be > 1\n");
			}
			else if (value > MAX)
			{/* Checking that input is in valid range */
				printf("Error: Settings values must be <= MAX\n");
			}
			else
			{
				switch (s)
				{/* Changing the chosen setting if value is valid */
					case 'M': case 'm':
						settings->width = value;
						break;
					case 'N': case 'n':
						settings->height = value;
						break;
					case 'K': case 'k':
						settings->winCondition = value;
						break;
				}
			}
			
		}
    } while (valid == 0);
}
#endif