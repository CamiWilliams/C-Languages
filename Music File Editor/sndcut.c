#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "allFunctions.h"

/*

This program reads a sound file from the standard input stream, and writes the sound file to the standard output stream in the same format, after removing all 
samples specified as arguments.

*/

int main(int argc, char* argv[])
{
	FILE* f;
	struct file input;
    int k;
    int lows[argc];
    int highs[argc];
    int high, low, numRanges = 0;
    
    input = getFileInfo("(standard input)", stdin);
    fclose(f);
	for(k = 1; k < argc; k++)
	{
		if(strncmp(argv[k], "-h", 2) == 0)
		{
			fprintf(stderr, "This program reads a sound file from the standard input stream and writes it to the standard output stream. It removes all samples specified as arguments. The arguments are written as low..high \n");
		} 
		else
		{
			/*Looks for range*/
            if(sscanf(argv[k], "%d..%d", &low, &high) > 0)
			{
                if( low >= 0 && high <= input.samples)
				{
                    lows[numRanges] = low;
                    highs[numRanges] = high;
                    numRanges++;
                } 
				else { fprintf(stderr, "\nYou specified ranges outside of the file sample ranges\n"); }
            }
        }	
	}
    
    if(input.error == 0)
    {
        input = removeRange(lows, highs, numRanges, input);
        if(input.error == 5) 
		{
            fprintf(stderr, "Error: Boundaries written incorrectly");
            printf("\n");
            return 0;
        }
    }
    if(input.type == 1)	{ convert(input, stdout, 2); } 
	else if(input.type == 2) { convert(input, stdout, 1); }
}