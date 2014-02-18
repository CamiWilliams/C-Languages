#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>

#include "allFunctions.h"

/*
	Updates the ASCII part of the screen
	
	input - struct containing info about file
	nums - sample nums to be displayed
	start - what index to start the screen
	stop - what index to stop the screen
	width - width the diagram should be
	max - max data value in startData
	line - if highlight, which lines to highlight
*/
void updateScreen(struct file input, int start, int stop, int width, int max, int* lines)
{
	int y, i, z, dAmount, b, x, t, h, trigger;
	char snum[100];
	int* nums;
	char* spaces;
	char* dashes;
	char* spacesNum;
	y = 2; //rows
	i = 0; //cols
	b = 0, x = 0;
	dashes = (char*) malloc((width)* sizeof(char));
	spaces = "         ";
	
	nums = (int*) malloc((input.samples)* sizeof(int));
	for(i = 0; i < input.samples; i++) { nums[i] = i; }
	i = 0;
	
	while(start < stop)
	{
		t = 0;
		x = 0;
		while (lines[x] != '\0') 
		{
			if(start == lines[x])
			{
				t = 1;
				break;
			}
			x++;
		}
		
		if(t == 1) { attron(A_REVERSE); }
		else { attroff(A_REVERSE); }
		
		i = 0;
		sprintf(snum, "%d", nums[start]);
		b = strlen(snum);
		while(i < (9 - b))
		{
			mvprintw(y, i, " ");
			i++;
		}
		mvprintw(y, i, "%d|", nums[start]); 
		
		trigger = 1; b = 0; h = 0;
		
		while(h < input.channels)
		{
			if(trigger == 0)
			{
				mvprintw(y, i, "%s|", spaces);
			}
			i = 10;
			if(input.startData[start+h] < 0)
			{
				dAmount = abs((int)round(((double)input.startData[start+h]/max) * width));
				while(b < (width - dAmount)) { mvprintw(y, i, " "); b++; i++;} b = 0;
				while(b < dAmount) { mvprintw(y, i,  "-"); b++; i++;} b = 0;
				mvprintw(y, i, "|");
				i++;
				while(b < width) { mvprintw(y, i,  " "); b++; i++;} b = 0;
				mvprintw(y, i, "|");
			}                        
			else
			{
				dAmount = abs((int)round(((double)input.startData[start+h]/max) * width));
				while(b < width) { mvprintw(y, i,  " "); b++; i++;} b = 0;
				mvprintw(y, i,  "|");
				i++;
				while(b < dAmount) { mvprintw(y, i,  "-"); b++; i++;} b = 0;
				while(b < (width - dAmount)) { mvprintw(y, i,  " "); b++; i++;} b = 0;
				mvprintw(y, i, "|");
			}
			trigger = 0;
			y++; i = 0; h++;
		}
		start++;
	}

}


/*

This is the audio file editor based onn the ncurses library. The executable takes in a single argument, which is the filepath of the audio file.

*/

int main(int argc, char* argv[])
{
	char border[100];
	struct file input;
	int i, j, width, end, sdSize, max, min, n, start, markedLength, marker, clearer, changes, copiedLength;
	int* lines;
	int* copied;
	int* lows;
    int* highs;
	char* spaces;
	char* spacesNum;
	char* dashes;
	char* go;
	int* combo;

	initscr();
	noecho();           /* don't print input */
	cbreak();           /* don't buffer input */
	keypad(stdscr, 1);  /* Get arrows */
	
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	
	markedLength = 0; marker = 0, changes = 0, copiedLength = 0;
	
	/*Create boarder big enough for screen*/
	for(i = 0; i < cols; i++) { border[i] = '='; }
	i = 0;
	
	/*Reasons to close the program*/
	if(argc != 2) { fprintf(stderr, "Error: Incorrect arguments. \n"); return 0; }
	if(cols < 40) { fprintf(stderr, "Error: terminal window too small. \n"); return 0; }
	if(rows < 24) { fprintf(stderr, "Error: terminal window too small. \n"); return 0; }
	
	/*Get file information*/
	input.filepath = argv[1];
	input.file = fopen(argv[1], "r");
	if(!input.file) { fprintf(stderr, "Error: Cannot open file. \n"); }
	fclose(input.file);
	input = getFileInfo(input.filepath, input.file);
	
	/*Print filepath in the center of the screen*/
	i = (int) ((cols - (sizeof(argv[1]) + sizeof(input.format) + 4))/2);
	mvprintw(0, i, "%s (%s)", argv[1], input.format);
	mvprintw(1, 0, "%s", border);
	i = 0;
	
	/*Print file information*/
	i = getDuration(input);
	mvprintw(2, cols - 20, "  Sample Rate: %ld ", input.sampleRate);
	mvprintw(3, cols - 20, "    Bit Depth: %d ", input.bitDepth);
	mvprintw(4, cols - 20, "     Channels: %d ", input.channels);
	mvprintw(5, cols - 20, "     Samples: %d ", input.samples);
	mvprintw(6, cols - 20, " Length: %s ", duration);
	mvprintw(7, cols - 20, "====================");
	mvprintw(14, cols - 20, "   q: quit");
	/*blank 15*/
	mvprintw(16, cols - 20, " Movement:");
	mvprintw(17, cols - 20, "   up/dn");
	mvprintw(18, cols - 20, "   pgup/pgdn");
	mvprintw(19, cols - 20, "   g: goto sample");
	/*blank 19*/
	mvprintw(20, cols - 20, "====================");
	
	width = (cols - 32) * .5; /*Width for ASCII art*/
	i = 0, sdSize = 0;
	
	/*Array containing sample numbers*/
	sdSize = (input.channels * input.samples);
	
	max = findMaxData(input.startData, sdSize);
	start = 0, n = 0;
	lines = (int*) malloc((input.samples)* sizeof(int));
	markedLength = 0, marker = 0;
	while (lines[clearer] != '\0') 
	{
		lines[clearer] = '\0';
		clearer++;
	}
	clearer = 0;
	lows = (int*) malloc((input.samples)* sizeof(int));
	highs = (int*) malloc((input.samples)* sizeof(int));
	
	int cx = 10+width;
	int cy = 2;
	
	clearer = 0, markedLength = 0;
	
	/*Show screen, if the screen size is bigger than the diagram, set the end of the art accordingly*/
	if(sdSize < (rows - 2)){ updateScreen(input, 0, sdSize, width, max, lines); end = sdSize;}
	else { updateScreen(input, 0, (rows - 2), width, max, lines); end = rows - 2;}
	
	/*Begin switches*/
	for (;;) 
	{
		/*Initialize menu*/
		if(changes == 1) mvprintw(13, cols - 20, "   s: save");
		else mvprintw(13, cols - 20, "                    ");
		
		if(markedLength == 0) mvprintw(8, cols - 20, "   m: mark      ");
		else mvprintw(8, cols - 20, "   m: unmark     ");
		
		if(copiedLength > 0)
		{
			mvprintw(11, cols - 20, "   ^: insert before");
			mvprintw(12, cols - 20, "   v: insert after");
		}
		else
		{
			mvprintw(11, cols - 20, "                    ");
			mvprintw(12, cols - 20, "                    ");
		}
		move(cy, cx);
		
		refresh();
		int c = getch();
		switch (c)
		{
			case 'q': 
				break;
			
			case 's': 
				if(changes == 1)
				{
					mvprintw(0, cols - 20, "File saved!");
					mvprintw(13, cols - 20, "                    ");
					changes = 0;
					saveFile(input);
				}
				
				else
				{
					mvprintw(0, cols - 20, "No changes made.");
				}
				break;
			
			case 'm': 
				if(marker == 1) /*Unmark*/
				{
					markedLength = 0;
					marker = 0;
					while (lines[clearer] != '\0') 
					{
						lines[clearer] = '\0';
						clearer++;
					}
					clearer = 0;
					mvprintw(8, cols - 20, "   m: mark      ");
					mvprintw(9, cols - 20, "          ");
					mvprintw(10, cols - 20, "          ");
					updateScreen(input, start, end, width, max, lines);
					mvprintw(21, cols - 20, "                    ");
				}
				else /*Mark*/
				{
					mvprintw(21, cols - 20, "   Marked: %d", (start + j));
					marker = 1;
					lines[markedLength] = start + j;
					markedLength++;
					mvprintw(8, cols - 20, "   m: unmark     ");
					mvprintw(9, cols - 20, "   c: copy");
					mvprintw(10, cols - 20, "   x: cut");
					updateScreen(input, start, end, width, max, lines);
				}
				break;

			case 'c':
				if(marker == 1)
				{
					/*Record copied*/
					copied = (int*) malloc((markedLength)* sizeof(int));
					copied = lines;
					copiedLength = markedLength;
					mvprintw(22, cols - 20, " Buffered: %d", markedLength);
					/*Clear marked*/
					markedLength = 0, marker = 0;
					while (lines[clearer] != '\0') 
					{
						lines[clearer] = '\0';
						clearer++;
					}
					clearer = 0;
					updateScreen(input, start, end, width, max, lines);
					mvprintw(0, cols - 20, "Segment copied.    ");
					mvprintw(8, cols - 20, "   m: mark      ");
					mvprintw(21, cols - 9, "         ");
				}
				else
				{
					mvprintw(0, cols - 20, "Nothing marked. ");
				}
				break;
			
			case 'x':
				if(marker == 1)
				{
					/*Record copied*/
					lines = (int*) realloc(lines, sizeof(char)* markedLength);
					copied = (int*) malloc((markedLength)* sizeof(int));
					copied = lines;
					copiedLength = markedLength;
					/*Remove range of copied*/
					lows[0] = findMinData(copied, markedLength);
					highs[0] = findMaxData(copied, markedLength);
					max = highs[0];
					removeRange(lows, highs, 1, input);
					mvprintw(22, cols - 9, "%d", markedLength);
					/*Clear marked data*/
					markedLength = 0, marker = 0;
					while (lines[clearer] != '\0') 
					{
						lines[clearer] = '\0';
						clearer++;
					}
					clearer = 0;
					mvprintw(8, cols - 20, "   m: mark      ");
					mvprintw(21, cols - 9, "         ");
					updateScreen(input, start, end, width, max, lines);
					mvprintw(0, cols - 20, "Segment cut.     ");
					changes = 1;
				}
				else
				{
					mvprintw(0, cols - 20, "Nothing marked.   ");
				}
				break;
			
			case '^':
				if(copiedLength > 0)
				{
					changes = 1;
					combo = (int*) malloc(((input.samples*input.channels) + copiedLength)*sizeof(int));
					int y = 0;
					int m = 0;
					int f = 0;
					int g = 0;
					int h = 0;
					
					markedLength = 0;
					marker = 0;
					while (lines[clearer] != '\0') 
					{
						lines[clearer] = '\0';
						clearer++;
					}
					clearer = 0;
					mvprintw(8, cols - 20, "   m: mark      ");
					mvprintw(21, cols - 9, "         ");
					
					/*Split before cursor*/
					for(y = 0; y <= (start + j - 1)*input.channels; y++)
					{
						combo[y] = input.startData[y];
					}
					f = y;
					/*Add copied*/
					for(m = 0; m < copiedLength; m++) 
					{
						g = copied[m] * input.channels;
						while(h < input.channels)
						{
							combo[y] = input.startData[h + g];
							h++;
						}
						y++;
					}
					/*Add remaining*/
					for(f = f; f < sdSize; f++)
					{
						combo[y] = input.startData[f];
						y++;
					}
					input.startData = combo;
					input.samples += copiedLength;
					
					updateScreen(input, start, end, width, max, lines);
					mvprintw(0, cols - 20, "Segment pasted.   ");
					
					i = getDuration(input);
					mvprintw(5, cols - 20, "      Samples: %d ", input.samples);
					mvprintw(6, cols - 20, " Length: %s ", duration);
				}
				
				else
				{
					mvprintw(0, cols - 20, "Nothing copied.   ");
				}
				break;
			
			case 'v':
				if(copiedLength > 0)
				{					
					changes = 1;
					combo = (int*) malloc(((input.samples*input.channels) + copiedLength)*sizeof(int));
					int y = 0;
					int m = 0;
					int f = 0;
					int g = 0;
					int h = 0;
					
					markedLength = 0;
					marker = 0;
					while (lines[clearer] != '\0') 
					{
						lines[clearer] = '\0';
						clearer++;
					}
					clearer = 0;
					mvprintw(8, cols - 20, "   m: mark      ");
					mvprintw(21, cols - 9, "         ");
					
					/*Split after cursor*/
					for(y = 0; y <= (start + j)*input.channels; y++)
					{
						combo[y] = input.startData[y];
					}
					f = y;
					/*Add copied*/
					for(m = 0; m < copiedLength; m++) 
					{
						g = copied[m] * input.channels;
						while(h < input.channels)
						{
							combo[y] = input.startData[h + g];
							h++;
						}
						y++;
					}
					/*Add remaining*/
					for(f = f; f < sdSize; f++)
					{
						combo[y] = input.startData[f];
						y++;
					}
					input.startData = combo;
					input.samples += copiedLength;
					
					updateScreen(input, start, end, width, max, lines);
					mvprintw(0, cols - 20, "Segment pasted.   ");
					
					i = getDuration(input);
					mvprintw(5, cols - 20, "     Samples: %d ", input.samples);
					mvprintw(6, cols - 20, " Length: %s ", duration);
				}
				
				else
				{
					mvprintw(0, cols - 20, "Nothing copied.  ");
				}
				break;
			
			case 'g':
				/*Clear the marked data*/
				markedLength = 0; marker = 0;
				while (lines[clearer] != '\0') 
				{
					lines[clearer] = '\0';
					clearer++;
				}
				clearer = 0;
				mvprintw(8, cols - 20, "   m: mark      ");
				mvprintw(0, cols - 20, "Goto:               ");
				mvprintw(21, cols - 9, "         ");
				move(0, cols - 14);
				go = (char*) malloc(100 * sizeof(char));
				
				/*Get user input number*/
				for(;;)
				{
					c = getch();
					switch(c)
					{
						case '\n': break;
						
						default:
							if((cols-14) + n == cols - 1)
							{
								mvaddch(0, (cols-1), c);
								go[n] = c;
							}
							else 
							{ 
								mvaddch(0, (cols-14) + n, c);
								go[n] = c; n++;
								move(0, (cols-14) + n);
							}
							break;
					}
					if ('\n' == c) break;
				}
				
				n = atoi(go);
				if(n > sdSize) mvprintw(0, cols - 20, "Invalid number.     ");
				/*Goto number*/
				else 
				{
					if(n+(rows-2) < sdSize)
					{
						start = n;
						end = n + (rows - 2);
						updateScreen(input, start, end, width, max, lines);
					}
					else 
					{
						start = (sdSize - 1) - (rows - 2);
						end = sdSize - 1;
						updateScreen(input, start, end, width, max, lines);
					}
					mvprintw(0, cols - 20, "                    ");
					
					n = 0;
				}
				cy = 2;
				move(cy, cx);
				break;
			
			case KEY_UP:
				if (cy > 2)
				{
					j--;
					if(marker == 1)
					{
						lines[markedLength] = start + j;
						markedLength++;
					}
					updateScreen(input, start, end, width, max, lines);
					cy -= input.channels;
				}
				/*At top of screen*/
				else if(cy == (2) && start > 0)
				{
					j = 0;
					if(marker == 1)
					{
						lines[markedLength] = start + j;
						markedLength++;
					}
					cy = 2;
					end--;
					start--;
					updateScreen(input, start, end, width, max, lines);
				}

				break;

			case KEY_DOWN:
				
				if ((cy < rows - 1) && cy <= sdSize) 
				{
					cy += input.channels;
					j++;
					if(marker == 1)
					{
						lines[markedLength] = start + j;
						markedLength++;
					}
					
					updateScreen(input, start, end, width, max, lines);
				}
				/*At bottom of screen*/
				else if(cy >= (rows - input.channels - 1) && end <= (input.samples - 1))
				{
					cy = rows - input.channels;
					end++;
					start++;
					j = (rows - input.channels - 2) / input.channels;
					if(marker == 1 )
					{
						lines[markedLength] = start + j;
						markedLength++;
					}
					updateScreen(input, start, end, width, max, lines);
				}

				break;
				
			/*Page Up*/
			case KEY_PPAGE:
				
				markedLength = 0; marker = 0;
				while (lines[clearer] != '\0') 
				{
					lines[clearer] = '\0';
					clearer++;
				}
				clearer = 0;
				/*If you page up and you are not at the top*/
				if(end == sdSize)
				{
				
				}
				
				if((start - (rows - 2)) >= 0)
				{
					end = start;
					start = end - (rows - 2);
				}
				/*If the top of the startData is in view*/
				else
				{
					start = 0;
					if(sdSize < (rows - 2)) end = sdSize;
					else end = rows - 2;
				}
				updateScreen(input, start, end, width, max, lines);
				
				cy = 2;
				break;
			
			/*Page Down*/
			case KEY_NPAGE:
				
				markedLength = 0; marker = 0;
				while (lines[clearer] != '\0') 
				{
					lines[clearer] = '\0';
					clearer++;
				}
				clearer = 0;
				
				if(end == sdSize)
				{
				
				}
				
				/*If you page down and you are not at the bottom of the startData*/
				else if((end + rows - 2) <= (sdSize - 1))
				{
					start = end;
					end = start + (rows - 2);
					updateScreen(input, start, end, width, max, lines);
				}
				/*If you page down and you are at the bottom of the startData or if the bottom of the startData is in view*/
				else
				{
					end = sdSize - 1;
					start = (sdSize - 1) - (rows - 2);
					updateScreen(input, start, end, width, max, lines);
				}
				
				cy = 2;
				break;
			
			default:
				mvprintw(0, cols - 20, "Key not valid.      ");
				break;
				
		}

	if ('q' == c) break;
  }

  endwin();
  return 0;
}
