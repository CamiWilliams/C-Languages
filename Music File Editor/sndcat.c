#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "allFunctions.h"

/*

This program reads all sound files passed as arguments, and writes a single sound file where the sample data is the concatenation of the sample data in the 
inputs. The resulting sound file is written directly to standard output. If no files are passed as arguments, then the standard input stream is treated as
the input file. 

*/
int main(int argc, char* argv[])
{
	FILE* f;
	struct file input[argc];
	struct file output;
	int k, count = 0;
	int fileVersion = 0; /* 0 if flip, 1 if AIFF, 2 if CS229*/
	char point;
	
	if (argc == 1)
	{
        fprintf(stderr, "Error: No file arguments. \n");
        return 0;
    }
	
	for(k = 1; k < argc; k++)
	{
		if(strncmp(argv[k], "-h", 2) == 0)
		{
			fprintf(stderr, "This program reads all sound files passed as arguments and writes a single sound file where the sample data is the concatenation of the sample data in the inputs. The file is written directly to standard output. If no files are passed as arguments, the standard input stream should be treated as the input file. -a means the output should be AIFF and -c means the output should be CS229.\n");
		}
        
		else if(strncmp(argv[k], "-a", 2) == 0)
		{
			fileVersion = 1;
		}
        
		else if(strncmp(argv[k], "-c", 2) == 0)
		{
			fileVersion = 2;
		}
        
		else
		{
			f = fopen(argv[k],"r");
			input[count] = getFileInfo(argv[k], f);
			if(input[count].error == 0)
			{
				fclose(f);
				if (count > 0 && (input[0].channels != input[count].channels)){ fprintf(stderr, "Error: These files are incompatible. \n"); return 0;}
				if (count > 0 && (input[0].sampleRate != input[count].sampleRate)){ fprintf(stderr, "Error: These files are incompatible. \n"); return 0;}
				if (count > 0 && (input[0].bitDepth != input[count].bitDepth)){ fprintf(stderr, "Error: These files are incompatible. \n"); return 0;}
				count++;
			}
			else if(input[count].error == 1) {fprintf(stderr, "Error: BitDepth is incorrect. \n"); return 0;}
			else if(input[count].error == 2) {fprintf(stderr, "Error: Channels is incorrect. \n"); return 0;}
			else if(input[count].error == 3) {fprintf(stderr, "Error: There is a startData number that is too low"); printf("\n"); return 0;}
			else if(input[count].error == 4) {fprintf(stderr, "Error: There is a startData number that is too high"); printf("\n"); return 0;}
            
		}
	}
	
	output = concatenate(input, count);
	convert(output, stdout, fileVersion);
    
}