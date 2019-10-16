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
			printf("Success\n");
		}
		
		free(settings);	
	}
	else
	{/* Error for running incorrectly on command line */
		printf("Error: Program must be run as: mnk [<filename>.txt]\n");
	}
	
	return 0;
}