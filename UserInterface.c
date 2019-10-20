/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 20/10/2019
   Purpose: Handles the user interface for MNK Tic Tac Toe, which includes
   			housing the main() function for the program. This means it handles
			displaying and controlling any menus and thus calling other
			fundamental parts of the program when required.                   */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "FileManager.h"
#include "UserInterface.h"
#include "Game.h"

/* PURPOSE:
The main() function for the program. It preloads the game settings and if they
are valid the rest of the program is called and run. */
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

/* PURPOSE:
The main menu for the program. Prompts the user for input to select what they
would like to do in the program and calls relevant functions based on their
selection. The majority of the program is run from calls by this menu. The game
logs are also created and controlled here. */
void menu(Settings* settings)
{			
	int cmd, upper;
	char *prompt, *str, *end;
	char temp[BUFFER];
	LinkedList *log, *game;
	log = createLinkedList();
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
					game = newGame(settings);
					insertLast(log, game);
					break;
				case 2:
					displaySettings(settings);
					break;
				case 3:
					printf("\n");
					displayLogs(stdout, settings, log);
					break;
				case 4:
					saveLogs(settings, log);
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
	
	freeLinkedList(log, &freeGameLog);
}

/* PURPOSE:
Displays game settings to the user. Made as a seperate function to keep the
structure of the menu function clear. */
void displaySettings(Settings* settings)
{
	printf("\n(M) Width         = %d tiles\n(N) Height        = %d tiles\n"
	       "(K) Win Condition = %d tiles in a row\n", settings->width,
		   settings->height, settings->winCondition);
}

/* PURPOSE:
The data type of the logs Linked List is another Linked List containing games,
so this function is imported to the first freeLinkedList() call to tell it
that to free each node, another Linked List must be free'd using the basic
free() built-in function for the node data. */
void freeGameLog(void* gameLog)
{
	LinkedList* games = (LinkedList*)gameLog;
	freeLinkedList(games, &free);
}

#ifdef EDITOR
/* PURPOSE:
Only runs when program is compiled with EDITOR defined as true. Allows the user
to choose and then change one of the game's settings values during runtime.
Changed values persist through the program via the settings struct, so the log
file will only show the most recent settings. */
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