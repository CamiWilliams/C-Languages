#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "allFunctions.h"

#define DASHES "------------------------------------------------------------"

/*

This program reads a sound file and displays a standard output. This program supports the passing of filenames and switches.

*/

int main(int argc, char* argv[])
{
	FILE* f;
	struct file input;
	int k = 0;
	char* name;
	
	if(argc == 1)
	{
        input = getFileInfo("(standard input)", stdin);
		printInformation(input);
        printf(DASHES);
		
		return 0;
    }
	
	else
	{
		for(k = 1; k < argc; k++)
		{
			if(strncmp(argv[k], "-h", 2) == 0)
			{
				fprintf(stderr, "This program reads a sound file and displays a standard output. The arguments for this program are sound files. If the user does not put in sound files as arguments, it will show the information for standard input. If the user types -l, they will be prompted to enter a filepath when the program runs. \n");
				return 0;
			}

			else if(strncmp(argv[k], "-1", 2) == 0)
			{
				fprintf(stderr, "Enter the pathname of a sound file: \n");
				fflush(stdout);
				scanf(" %[^\n]s", name);
				f = fopen(name, "r");
			
				if(!f) {fprintf(stderr, "Error: File does not exist \n"); printf(DASHES); printf("\n"); return 0;}
			
				else
				{
					input = getFileInfo(name, f);
					if(input.error == 0) { printInformation(input); printf("\n"); }
					if(input.error == 1) { fprintf(stderr, "Error: BitDepth is incorrect \n"); printf(DASHES); printf("\n"); return 0;}
					if(input.error == 2) { fprintf(stderr, "Error: Channels is incorrect \n"); printf(DASHES); printf("\n"); return 0;}
					if(input.error == 3) { fprintf(stderr, "Error: There is a startData number that is too low \n"); printf(DASHES); printf("\n"); return 0;}
					if(input.error == 4) { fprintf(stderr, "Error: There is a startData number that is too high \n"); printf(DASHES); printf("\n"); return 0;}
				}
			
				fclose(f);
				break;
			}

			else
			{
				f = fopen(argv[k], "r");
				name = argv[k];
				if(!f) {fprintf(stderr, "Error: File Does Not Exist"); printf(DASHES); printf("\n"); fclose(f); return 0;}
			
				else
				{
					fclose(f);
					input = getFileInfo(name, f);
					if(input.error == 0) { printInformation(input); printf("\n"); }
					if(input.error == 1) {fprintf(stderr, "Error: BitDepth is incorrect"); printf(DASHES); printf("\n"); return 0;}
					if(input.error == 2) {fprintf(stderr, "Error: Channels is incorrect"); printf(DASHES); printf("\n"); return 0;}
					if(input.error == 3) {fprintf(stderr, "Error: There is a startData number that is too low"); printf(DASHES); printf("\n"); return 0;}
					if(input.error == 4) {fprintf(stderr, "Error: There is a startData number that is too high"); printf(DASHES); printf("\n"); return 0;}
				}
			}
		}
	}
	
	printf(DASHES);
	return 0;
}