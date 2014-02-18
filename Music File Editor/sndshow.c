#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "allFunctions.h"

/*

This program reads a sound file from the standard input stream, and displays an "ASCII art" representation of the sample data.

*/

int main(int argc, char* argv[])
{
	FILE* f;
	struct file input;
	int k, c, w, n;
	c = 0, w = 80, n = 1;

	input = getFileInfo("(standard input)", stdin);
	
	for(k = 1; k < argc; k++)
	{
		if(strncmp(argv[k], "-h", 2) == 0)
		{
			fprintf(stderr, "This programs reads a sound file from the standard input stream and displays an ASCII art representation of the sample data. -w specifies the total output width, default of 80, min of 20. -c represents the bounds for which channels to show, 1 <= c <= num channles. -z is the zoom out factor.\n");
		}

		else if(strncmp(argv[k], "-c", 2) == 0)
		{
			c = atoi(argv[k+1]);
			if(c > input.channels)
			{
				fprintf(stderr, "Error: c is greater than channels. \n");
				return 0;
			}
		}

		else if(strncmp(argv[k], "-w", 2) == 0)
		{
			w = atoi(argv[k+1]);
			if(w < 20)
			{
				fprintf(stderr, "Error: w is less than 20. \n");
				return 0;
			}
			
			if(w % 2 != 0)
			{
				w -= 1;
			}
		}

		else if(strncmp(argv[k], "-z", 2) == 0)
		{
			n = atoi(argv[k+1]);
		}
	}
	
	getASCIIArt(w, n, c, input);

}