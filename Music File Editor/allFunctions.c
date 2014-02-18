#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "allFunctions.h"

/*
* Infinite & NAN values
* for non-IEEE systems
*/
#ifndef HUGE_VAL
#ifdef HUGE
#define INFINITE_VALUE	HUGE
#define NAN_VALUE	HUGE
#endif
#else
#define INFINITE_VALUE	HUGE_VAL
#define NAN_VALUE	HUGE_VAL
#endif

#define DASHES "------------------------------------------------------------"

/* Gets the information from the file and applies it to the returned struct*/
struct file getFileInfo(char* filepath, FILE* f)
{
	struct file input;
	char current[1024];
	char pointer;
	int low;
	int high;
	int x;
	
	/*Sets initial data*/
	input.filepath = "0";
	input.filename = "0";
	input.format = "0";
	input.sampleRate = 0;
	input.bitDepth = 0;
	input.channels = 0;
	input.samples = 0;
	input.error = 0;
	input.type = 0;

	if(strncmp(filepath, "(standard input)", 16) == 0)
	{
		input.filename = "(standard input)";
		input.file = stdin;
	}
	else
	{
		f = fopen(filepath, "r");
		input.filepath = filepath;
		input.file = f;
		input.filename = basename(filepath);
	}

	x = 0;

	fgets(current, 6, f);
	if(strncmp(current, "CS229", 5) == 0)
	{
		input = get229Info(input);
		/*Checks to see if numbers are in range*/
		low = (int) - pow((double) 2, input.bitDepth - 1);
		high = (int) pow((double) 2, input.bitDepth - 1) - 1;

		for(x = 0; x < (input.samples * input.channels); x++)
		{
			if(input.startData[x] < low)
			{
				input.error = 3;
				return input;
			}

			else if(input.startData[x] > high)
			{
				input.error = 4;
				return input;
			}
		}
	}

	else if(strncmp(current, "FORM", 4) == 0)
	{
		input = getASCIIInfo(input);
	}

	else
	{
		input.type = 0;
		input.filename = filepath;
		input.format = "0";
		input.sampleRate = 0;
		input.bitDepth = 0;
		input.channels = 0;
		input.samples = 0;
	}

	fclose(f);
	return input;
}

/*Reads a .cs229 file line by line and appends data to the struct values accordingly*/
struct file get229Info(struct file input)
{
	char* pointer;
	long keyword;
	FILE* f;
	int data; //numValues
	int num; //value
	int* thisStartData;

	pointer = (char*) malloc(1000000* sizeof(char));
	thisStartData = (int*) malloc(2000000 * sizeof(int));
	input.format = "CS229";
	input.type = 1;
	input.error = 0;
	f = input.file;
	num = 0, data = 0;

	fgets(pointer, 6, f); /*skip CS229*/
	keyword = fscanf(f, "%s", pointer);
	
	/*Search for keywords*/
	while(keyword > 0)
	{
		if(strncmp(pointer,"Samples", 7) == 0)
		{
			fscanf(f, "%s", pointer);
			input.samples = atoi(pointer);
		}
		else if(strncmp(pointer,"Channels", 8) == 0)
		{
			fscanf(f, "%s", pointer);
			input.channels = atoi(pointer);
			if(input.channels <= 32) { }
			else { input.error = 2; return input;}
		}
		else if(strncmp(pointer,"BitDepth", 8) == 0)
		{
			fscanf(f, "%s", pointer);
			input.bitDepth = atoi(pointer);
			if(input.bitDepth == 8 || input.bitDepth == 16 || input.bitDepth == 32) { }
			else { input.error = 1; return input;}
		}
		else if(strncmp(pointer,"SampleRate", 10) == 0)
		{
			fscanf(f, "%s", pointer);
			input.sampleRate = atoi(pointer);
		}
		else if(strncmp(pointer,"StartData", 9) == 0)
		{
			break;
		}

		keyword = fscanf(f, "%s", pointer);
	}

	/*Reading startData in*/
	keyword = fscanf(f, "%s", pointer);
	num = atoi(pointer);

	while(keyword > 0)
	{
		thisStartData[data] = num;
		data++;
		keyword = fscanf(f, "%s", pointer);
		num = atoi(pointer);
	}

	input.samples = data / input.channels;
	input.startData = (int *)malloc( data * sizeof(int));

	num = 0;

	while( num < data )
	{
		input.startData[num] = thisStartData[num];
		num += 1;
	}

	return input;
}

/*Reads a .aiff file and appends data to the struct values accordingly*/
struct file getASCIIInfo(struct file input)
{
	char pointer[1024];
	char point;
	int remainingCOMM;
	int remainingSSND;
	unsigned char *sampleRate;
	FILE* f;
	int data;
	int num;

	input.format = "AIFF";
	input.type = 2;
	input.error = 0;
	f = input.file;
	point = ' ';
	sampleRate = malloc(10 * sizeof(unsigned char));

	fgets(pointer, 5, f); /* skip FORM */
	fseek(f,8,SEEK_CUR); /*skip AIFF*/
	fread(&point, 1, 1, f);

	while(point != EOF)
	{
		/*COMM*/
		if(point == 'C'){ point = fgetc(f); if(point == 'O') { point = fgetc(f); if(point == 'M') { point = fgetc(f); if(point == 'M')
						{
			fread(pointer, 4, 1, f);
			remainingCOMM = (pointer[0]<< 24) + (pointer[1]<< 16) + (pointer[2]<< 8) +  pointer[3];

			fread(pointer, 2, 1, f);
			input.channels = (pointer[0]<< 8) + pointer[1];
			if(input.channels <= 32) { }
			else { input.error = 2; return input;}

			fread(pointer, 4, 1, f);
			input.samples = (pointer[0]<< 24) + (pointer[1]<< 16) + (pointer[2]<< 8) +  pointer[3];
			fread(pointer, 2, 1, f);
			input.bitDepth = (pointer[0]<< 8) + pointer[1];
			fread(sampleRate, 10, 1, f);
			input.sampleRate = ieee754_read_extended(sampleRate);

			if(input.bitDepth == 8 || input.bitDepth == 16 || input.bitDepth == 32) { }
			else { input.error = 1; return input;}
			point = fgetc(f);
					}
				}
			}
		}

		/*SSND*/
		if(point == 'S'){ point = fgetc(f); if(point == 'S') { point = fgetc(f); if(point == 'N') { point = fgetc(f); if(point == 'D')
					{
			fread(pointer, 4, 1, f);
			remainingSSND = (pointer[0]<< 24) + (pointer[1]<< 16) + (pointer[2]<< 8) +  pointer[3];
			fread(pointer, 4, 1, f);
			offset_i = (pointer[0]<< 24) + (pointer[1]<< 16) + (pointer[2]<< 8) +  pointer[3];
			fread(pointer, 4, 1, f);
			blockSize_i = (pointer[0]<< 24) + (pointer[1]<< 16) + (pointer[2]<< 8) +  pointer[3];

			break;
					}
				}
			}
		}

		fread(&point, 1, 1, f);
	}

	fseek(f, offset_i, SEEK_CUR); /* Go to startData */
	input.startData = (int *)malloc( input.samples * input.channels * sizeof(int));
	fread(&pointer, input.bitDepth/8, 1, f);

	data = 0;
	/*Interpret startData*/
	while( data < input.samples * input.channels)
	{
		if(input.bitDepth == 32)
		{
			num = (pointer[0]<< 24) + (pointer[1]<< 16) + (pointer[2]<< 8) +  pointer[3];
		}
		else if(input.bitDepth == 16)
		{
			num = (int16_t)((pointer[0]<< 8) + pointer[1]);
		}
		else
		{
			num = (int8_t)(pointer[0]);
		}

		input.startData[data] = num;
		data++;
		fread(&pointer, input.bitDepth/8, 1, f);
	}

	fclose(f);
	return input;
}

/*Gets the duration of a file for sndinfo and sndedit*/
int getDuration(struct file input)
{
	float seconds = ((double)input.samples)/input.sampleRate;
	char* dur;
	int n;

	if(seconds == 0)
	{
		dur = "0:00:00.00";
	}
	else
	{
		int hours = 0, minutes = 0;

		while(seconds >= 60)
		{
			minutes++;
			seconds = seconds - 60;
		}

		while(minutes >= 60)
		{
			hours++;
			minutes = minutes - 60;
		}

		n = sprintf(duration, "%02d:%02d:%05.2f", hours, minutes, seconds);
	}

	return n;
}

/* Prints the proper information for sndinfo */
void printInformation(struct file input)
{
	int i;
	printf(DASHES); printf("\n");
	i = getDuration(input);
	printf("   Filename: %s \n", input.filename);
	printf("     Format: %s \n", input.format);
	printf("Sample Rate: %ld \n", input.sampleRate);
	printf("  Bit Depth: %d \n", input.bitDepth);
	printf("   Channels: %d \n", input.channels);
	printf("    Samples: %d \n", input.samples);
	printf("   Duration: %s \n", duration);

}

/*Converts filetypes*/
void convert(struct file input, FILE* f, int type)
{
	int total;
	int tempBit;
	unsigned char buffer[1024];

	int i, j, k, commSize, ssndSize;
	i = 0, j = 0, k = 0, commSize = 18, ssndSize = 8;
	tempBit = input.bitDepth;

	if(type == 1) /*convert CS229 to AIFF*/
	{
		/*Bitshifting according to specifications in part 1, printing to the file*/
		fprintf(f,"FORM");
		fprintf(f, "%c%c%c%c",((42 + (input.samples * input.channels * (input.bitDepth/8))) >> 24) & 0xFF, ((42 + (input.samples * input.channels * (input.bitDepth/8))) >> 16) & 0xFF,((42 + (input.samples * input.channels * (input.bitDepth/8))) >> 8) & 0xFF, (42 + (input.samples * input.channels * (input.bitDepth/8))) & 0xFF);
		fprintf(f,"AIFF");
		fprintf(f,"COMM");
		fprintf(f, "%c%c%c%c",(18 >> 24) & 0xFF, (18 >> 16) & 0xFF,(18 >> 8) & 0xFF, 18 & 0xFF);
		fprintf(f, "%c%c",(input.channels >> 8) & 0xFF, input.channels & 0xFF);
		fprintf(f, "%c%c%c%c",(input.samples >> 24) & 0xFF, (input.samples >> 16) & 0xFF,(input.samples >> 8) & 0xFF, input.samples & 0xFF);
		fprintf(f, "%c%c",(input.bitDepth >> 8) & 0xFF, input.bitDepth & 0xFF);

		unsigned char sampleRate[10];
		ieee754_write_extended(input.sampleRate, sampleRate);

		fprintf(f, "%c%c%c%c%c%c%c%c%c%c",sampleRate[0],sampleRate[1],sampleRate[2],sampleRate[3],sampleRate[4],sampleRate[5],sampleRate[6],sampleRate[7],sampleRate[8],sampleRate[9]);

		fprintf(f,"SSND");
		fprintf(f, "%c%c%c%c",((4+(input.samples * input.channels * (input.bitDepth/8))) >> 24) & 0xFF, ((4+(input.samples * input.channels * (input.bitDepth/8))) >> 16) & 0xFF,((4+(input.samples * input.channels * (input.bitDepth/8))) >> 8) & 0xFF, (4+(input.samples * input.channels * (input.bitDepth/8))) & 0xFF);
		fprintf(f, "%c%c%c%c",(0 >> 24) & 0xFF, (0 >> 16) & 0xFF,(0 >> 8) & 0xFF, 0 & 0xFF);

		int r = 0;
		for(k = 0; k < input.samples * input.channels; k++) 
		{
			if(input.bitDepth == 32)
			{
				fprintf(f, "%c%c%c%c",(input.startData[k] >> 24) & 0xFF, (input.startData[k] >> 16) & 0xFF,(input.startData[k] >> 8) & 0xFF, input.startData[k] & 0xFF);
			} 
			
			else if (input.bitDepth == 16)
			{
				fprintf(f, "%c%c",(input.startData[k] >> 8), input.startData[k]);
			} 
			else 
			{
				fprintf(f, "%c", input.startData[k] & 0xFF);
			}
		}


	}

	else /*Convert AIFF to CS229*/
	{
		fprintf(f,"%s","CS229 \n");
		fprintf(f, "Samples %d \n", input.samples);
		fprintf(f, "Channels %d \n", input.channels);
		fprintf(f, "BitDepth %d \n", input.bitDepth);
		fprintf(f, "SampleRate %ld \n", input.sampleRate);
		fprintf(f, "StartData\n");
		for(i = 0; i < input.samples * input.channels; i++)
		{
			if(k != 0 && input.channels != 0 && k % input.channels == 0)
			{
				fwrite("\n", sizeof(char), 1, f);
			}
			fprintf(f, "%d ", input.startData[i]);
		}
	}

}

/*Merges the input files*/
struct file concatenate(struct file input[], int count)
{
	int* values;
	long length = 0;
	unsigned int samples = 0;
	int pos = 0;
	int pos1 = 0;
	int pos2 = 0;
	struct file file = input[0];

	/*find position*/
	while(pos < count)
	{
		length = length + (input[pos].samples * input[pos].channels);
		samples = samples + input[pos].samples;
		pos++;
	}

	values = (int*) malloc(length * sizeof(int));
	pos = 0;

	/*concatenate*/
	while(pos < count)
	{
		while(pos1 < input[pos].samples * input[pos].channels)
		{
			values[pos2] = input[pos].startData[pos1];

			pos1++;
			pos2++;
		}
		pos1 = 0;
		pos++;
	}

	file.samples = samples;
	file.startData = values;

	return file;
}

/*Removes the range set*/
struct file removeRange(int lows[], int highs[], int numRanges, struct file input)
{
	int i, j;
	int first_open = 0;
	int removed = 0;
	
	/*Find remove ranges*/
	for(i =0; i < numRanges; i++)
	{
		removed += (highs[i] - lows[i]);
	}

	int length = ((input.samples * input.channels) - (removed * input.channels));


	int *startData = (int*)malloc(length * sizeof(int));
	i = 0;
	/*Remove the ranges and append to struct's startData*/
	while( i < input.samples * input.channels )
	{
		if( inRange(i / input.channels, lows, highs, numRanges) == 0)
		{
			for(j = 0; j < input.channels; j++)
			{
				startData[first_open + j] = input.startData[i];
				i++;
			}
			first_open += input.channels;
		}

		i += input.channels;
	}

	free(input.startData);
	input.samples = input.samples - removed;
	input.startData = startData;
	return input;
}

/*Compares the sets of highs and lows*/	
int inRange(int position, int *lows, int *highs, int numRanges)
{
	int i;
	for(i=0; i < numRanges; i++)
	{
		if(position > lows[i] && position < highs[i]) return 1;
	}
	return 0;
}



/*
	Prints ASCII art representation of startData
	Default for w = 80, z = 1, c = 1
*/
void getASCIIArt(int w, int zoom, int c, struct file input)
{
	int temp, number, final, isNegative, i, j, k, x, y, zlen, a, b, m;
	int width, dAmount, max;
	int* data;
	int* nums;
	int* z_nums;
	char* spaces;
	char* spacesNum;
	char* dashes;
	i = 0, j = 1, k = 0, x = 0, y = 0, zlen = 0, a = 0, b = 0, m = 0, final = 0, isNegative = 0;
	width = (int)((w - 12)/2);

	data = (int*) malloc((input.channels * input.samples)* sizeof(int));
	nums = (int*) malloc((input.samples)* sizeof(int));
	z_nums = (int*) malloc((input.samples)* sizeof(int));
	dashes = (char*) malloc((width)* sizeof(char));
	spacesNum = "        ";
	spaces = "         ";

	for(y = 0; y < input.samples; y++) { nums[y] = y; }
	y = 0;
	/*Adjust data if zoom > 1*/
	if(zoom > 1)
	{
		/*adjusts index numbers to de displayed*/
		for(zlen = 0; y < input.samples; zlen++)
		{
			z_nums[zlen] = y;
			y += zoom;
		}

		y = 0;
		/*adjusts sample data to be displayed*/
		for(i = 0; i < (input.channels * input.samples); i++)
		{
			b = i;
			while(k < input.channels)
			{
				while(j < zoom)
				{
					number = input.startData[b + (j* input.channels)];
					temp = abs(number);
					if(temp > final)
					{
						final = temp;
						if(number < 0)
						{
							isNegative = 1;
						}
					}
					j++;
				}
				if(isNegative == 1)
				{
					final *= -1;
				}
				data[x] = final;
				k++; b++; x++; j=0;
				final = 0;
				isNegative = 0;
			}
			k = 0; j = 0;
			i += (zoom) * input.channels - 1;
			y++;
		}
		data = (int*) realloc(data, sizeof(char)* x);
		z_nums = (int*) realloc(z_nums, sizeof(char) * zlen);
		input.startData = data;
		nums = z_nums;
	}

	else { x = (input.channels * input.samples); }
	b = 0; y = 0;
	max = findMaxData(input.startData, x);

	if(c > 0)
	{
		/*Print information*/
		for(a = c - 1; a < x; a += input.channels*m)
		{
			fprintf(stdout, "%s%d|", spacesNum, nums[y]); 
			y++; m++;

			if(input.startData[a] < 0)
			{
				dAmount = abs((int)round(((double)input.startData[a]/max) * width));
				while(b < (width - dAmount)) { fprintf(stdout, " "); b++; } b = 0;
				while(b < dAmount) { fprintf(stdout, "-"); b++; } b = 0;
				fprintf(stdout, "|");
				while(b < width) { fprintf(stdout, " "); b++; } b = 0;
				fprintf(stdout, "|\n");
			}
			else
			{
				dAmount = abs((int)round(((double)input.startData[a]/max) * width));
				while(b < width) { fprintf(stdout, " "); b++; } b = 0;
				fprintf(stdout, "|");
				while(b < dAmount) { fprintf(stdout, "-"); b++; } b = 0;
				while(b < (width - dAmount)) { fprintf(stdout, " "); b++; } b = 0;
				fprintf(stdout, "|\n");
			}
		}
	}

	else
	{
		/*Print information*/
		for(a = 0; a < x; a++)
		{
			if(a == 0){ fprintf(stdout, "%s0|", spacesNum); y++;}
			else if(zoom == 1 && a == input.channels*nums[y]){ fprintf(stdout, "%s%d|", spacesNum, nums[y]); y++;}
			else if(zoom != 1 && a == nums[y]){ fprintf(stdout, "%s%d|", spacesNum, nums[y]); y++; }
			else { fprintf(stdout, "%s|", spaces); }

			if(input.startData[a] < 0)
			{
				dAmount = abs((int)round(((double)input.startData[a]/max) * width));
				while(b < (width - dAmount)) { fprintf(stdout, " "); b++; } b = 0;
				while(b < dAmount) { fprintf(stdout, "-"); b++; } b = 0;
				fprintf(stdout, "|");
				while(b < width) { fprintf(stdout, " "); b++; } b = 0;
				fprintf(stdout, "|\n");
			}
			else
			{
				dAmount = abs((int)round(((double)input.startData[a]/max) * width));
				while(b < width) { fprintf(stdout, " "); b++; } b = 0;
				fprintf(stdout, "|");
				while(b < dAmount) { fprintf(stdout, "-"); b++; } b = 0;
				while(b < (width - dAmount)) { fprintf(stdout, " "); b++; } b = 0;
				fprintf(stdout, "|\n");
			}
		}
	}

}

/*Gets max data number*/
int findMaxData(int* startData, int size)
{
	int max = startData[0];
	int i;
	for(i = 0; i < (size); i++)
	{
		if(startData[i] > max) { max = startData[i]; }
	}

	return max;
}

/*Gets min data number*/
int findMinData(int* startData, int size)
{
	int min = startData[0];
	int i;
	for(i = 0; i < (size); i++)
	{
		if(startData[i] < min) { min = startData[i]; }
	}

	return min;
}

/*Saves file for sndedit*/
void saveFile(struct file input)
{
	if(input.type == 1) { convert(input, input.file, 2); }
	if(input.type == 2) { convert(input, input.file, 1); }
}

/*Finds the index of an element (taken from stack overflow example)*/
int find_index(int* a, int num_elements, int value)
{
   int i;
   for (i = 0; i < num_elements; i++)
   {
	 if (a[i] == value)
	 {
	    return(value);  /* it was found */
	 }
   }
   return(-1);  /* if it was not found */
}

void ieee754_write_extended(double in, uint8_t* out)
{
	int sgn, exp, shift;
	double fraction, t;
	unsigned int lexp, hexp;
	uint32_t low, high;

	if (in == 0.0) {
		memset(out, 0, 10);
		return;
	}
	if (in < 0.0) {
		in = fabs(in);
		sgn = 1;
	} else
		sgn = 0;

	fraction = frexp(in, &exp);

	if (exp == 0 || exp > 16384) {
		if (exp > 16384) /* infinite value */
			low = high = 0;
		else {
			low = 0x80000000;
			high = 0;
		}
		exp = 32767;
		goto done;
	}
	fraction = ldexp(fraction, 32);
	t = floor(fraction);
	low = (uint32_t) t;
	fraction -= t;
	t = floor(ldexp(fraction, 32));
	high = (uint32_t) t;

	/* Convert exponents < -16382 to -16382 (then they will be
	* stored as -16383) */
	if (exp < -16382) {
		shift = 0 - exp - 16382;
		high >>= shift;
		high |= (low << (32 - shift));
		low >>= shift;
		exp = -16382;
	}
	exp += 16383 - 1;	/* bias */

done:
	lexp = ((unsigned int) exp) >> 8;
	hexp = ((unsigned int) exp) & 0xFF;

	/* big endian */
	out[0] = ((uint8_t) sgn) << 7;
	out[0] |= (uint8_t) lexp;
	out[1] = (uint8_t) hexp;
	out[2] = (uint8_t) (low >> 24);
	out[3] = (uint8_t) ((low >> 16) & 0xFF);
	out[4] = (uint8_t) ((low >> 8) & 0xFF);
	out[5] = (uint8_t) (low & 0xFF);
	out[6] = (uint8_t) (high >> 24);
	out[7] = (uint8_t) ((high >> 16) & 0xFF);
	out[8] = (uint8_t) ((high >> 8) & 0xFF);
	out[9] = (uint8_t) (high & 0xFF);

	return;
}


/*
* Read IEEE Extended Precision Numbers
*/
double ieee754_read_extended(uint8_t* in)
{
	int sgn, exp;
	uint32_t low, high;
	double out;

	/* Extract the components from the big endian buffer */
	sgn = (int) (in[0] >> 7);
	exp = ((int) (in[0] & 0x7F) << 8) | ((int) in[1]);
	low = (((uint32_t) in[2]) << 24)
		| (((uint32_t) in[3]) << 16)
		| (((uint32_t) in[4]) << 8) | (uint32_t) in[5];
	high = (((uint32_t) in[6]) << 24)
		| (((uint32_t) in[7]) << 16)
		| (((uint32_t) in[8]) << 8) | (uint32_t) in[9];

	if (exp == 0 && low == 0 && high == 0)
		return (sgn ? -0.0 : 0.0);

	switch (exp) 
	{
	case 32767:
		if (low == 0 && high == 0)
			return (sgn ? -INFINITE_VALUE : INFINITE_VALUE);
		else
			return (sgn ? -NAN_VALUE : NAN_VALUE);
	default:
		exp -= 16383;	/* unbias exponent */

	}

	out = ldexp((double) low, -31 + exp);
	out += ldexp((double) high, -63 + exp);

	return (sgn ? -out : out);
}

