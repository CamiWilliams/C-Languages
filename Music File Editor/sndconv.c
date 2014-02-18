#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "allFunctions.h"

/*

This program converts from one file format to another.

*/

int main(int argc, char* argv[])
{
	FILE* f_in;
	FILE* f_out;
	struct file input;
	struct file output;
	char* name1;
	char* name2;
	int k;
	
	if(argc == 1)
	{
		input = getFileInfo("(standard input)", stdin);
		if(input.error == 0) 
		{
			convert(input, stdout, input.type);
		}
		if(input.error == 1) {fprintf(stderr, "Error: BitDepth is incorrect. \n"); return 0;}
		if(input.error == 2) {fprintf(stderr, "Error: Channels is incorrect. \n"); return 0;}
		if(input.error == 3) {fprintf(stderr, "Error: There is a startData number that is too low"); printf("\n"); return 0;}
		if(input.error == 4) {fprintf(stderr, "Error: There is a startData number that is too high"); printf("\n"); return 0;}
	}
	
	for(k = 1; k < argc; k++)
	{
		if(strncmp(argv[k], "-h", 2) == 0)
		{
			fprintf(stderr, "This program reads from the standard input and writes to the standard output. -1 means to behave as part 1, -a means that the output will always be AIFF, and -c means the output will always be CS229. \n");
			return 0;
		}

		else if(strncmp(argv[k], "-1", 2) == 0)
		{
			fprintf(stderr, "Enter the pathname of the input file: \n");
			scanf(" %[^\n]s", name1);
			f_in = fopen(name1, "r");
			
			fprintf(stderr, "Enter the pathname of the output file: \n");
			scanf(" %[^\n]s", name2);
			f_out = fopen(name2, "w");
			
			if(!f_in) {fprintf(stderr, "Error: Input file does not exist. \n"); return 0;}
			
			else
			{
				input = getFileInfo(name1, f_in);
				fclose(f_in);
				output.filepath = name2;
				if(input.error == 0) 
				{ 
					/* input file is of type CS229 */
					if(input.type == 1) { convert(input, f_out, 1); }
					
					/* input file is of type AIFF */
					else if(input.type == 2) { convert(input, f_out, 2); }
					
					else {fprintf(stderr, "Error: File is not of type .cs229 or .aiff . \n"); fclose(f_out); return 0;}
					
					fclose(f_out);
				}
				if(input.error == 1) {fprintf(stderr, "Error: BitDepth is incorrect. \n");}
				if(input.error == 2) {fprintf(stderr, "Error: Channels is incorrect. \n");}
				if(input.error == 3) {fprintf(stderr, "Error: There is a startData number that is too low"); printf("\n"); return 0;}
				if(input.error == 4) {fprintf(stderr, "Error: There is a startData number that is too high"); printf("\n"); return 0;}
		
			}
			fclose(f_in);
			fclose(f_out);
		}

		else if(strncmp(argv[k], "-a", 2) == 0)
		{
			input = getFileInfo("(standard input)", stdin);
			if(input.error == 0) 
			{
				convert(input, stdout, 1);
			}
			if(input.error == 1) {fprintf(stderr, "Error: BitDepth is incorrect. \n"); return 0;}
			if(input.error == 2) {fprintf(stderr, "Error: Channels is incorrect. \n"); return 0;}
			if(input.error == 3) {fprintf(stderr, "Error: There is a startData number that is too low"); printf("\n"); return 0;}
			if(input.error == 4) {fprintf(stderr, "Error: There is a startData number that is too high"); printf("\n"); return 0;}
		}

		else if(strncmp(argv[k], "-c", 2) == 0)
		{
			input = getFileInfo("(standard input)", stdin);
			if(input.error == 0) 
			{
				convert(input, stdout, 2);
			}
			if(input.error == 1) {fprintf(stderr, "Error: BitDepth is incorrect. \n"); return 0;}
			if(input.error == 2) {fprintf(stderr, "Error: Channels is incorrect. \n"); return 0;}
			if(input.error == 3) {fprintf(stderr, "Error: There is a startData number that is too low"); printf("\n"); return 0;}
			if(input.error == 4) {fprintf(stderr, "Error: There is a startData number that is too high"); printf("\n"); return 0;}
		}
	}

	return 0;
}