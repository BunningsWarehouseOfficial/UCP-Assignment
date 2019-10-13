/* Filename:           UserInterface.c
   Author:             Kristian Rados (19764285)
   Date Created:       13/10/2019
   Date Last Modified: 13/10/2019
   Purpose: __________________________________________________________________*/
#include <stdlib.h>
#include "UserInterface.h"
#include "FileManager.h"
#include "LinkedList.h" /*** Is this needed? ***/
#include "Game.h"

/* PURPOSE:  */
int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		Settings settings; /* Declaring settings struct */
		char* settingsFile = argv[1];
		loadSettings(&settings, settingsFile);
		if (settings.winCondition != -1)
		{/* Program only continues if the settings file is valid */

		}		
		
	}
	else
	{/* Error for running incorrectly on command line */
		printf("Error: Must be run as TTT [<filename>.txt]\n");
	}
	
	
	return 0;
}