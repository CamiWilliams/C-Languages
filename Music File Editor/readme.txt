   _________     _________   ____      ____ __________   _________    _________   ____
  /         \   /         \ |    \    /    |    ___   \ /         \  /         \ |    | 
 /    ___    \ /    ___    \|     \  /     |   |   \   |    ___    |/    ___    \|    | 
|    /   \    |    /   \    |      \/      |   |    |  |   /   \___|    /   \    |    |
|   |     |___|   |     |   |              |   |    |  |   \______ |   |     |___|    |
|   |         |   |     |   |              |   |___/   |          \|   |         |    |
|   |      ___|   |     |   |              |     _____/\_______    |   |      ___|    |
|   |     |   |   |     |   |    |\  /|    |    |       ___    \   |   |     |   |    |
|    \___/    |    \___/    |    | \/ |    |    |      |   \___/   |    \___/    |    |
 \           / \           /|    |    |    |    |      |           |\           /|    | 
  \_________/   \_________/ |____|    |____|____|       \_________/  \_________/ |____|
README  
Author: Camryn Williams
NetID: 765387623



Project 1 Part 3 Description:
For this project, we were required to utilize our programs from parts 1 and 2 to create an audio file editor based upon the ncurses library. The six programs share the same .h and .c files.





sndinfo: SAME FROM PART2
This program reads a sound file and displays a standard output. This program supports the passing of filenames and switches. The included switches are:
	-h   : Display a short help screen to standard error, and terminate cleanly without reading any files.
	-1   : Prompts for filenames and ignores any other arguments. 
The program initially starts out with reading the filepath input and creates a struct accordingly. It then utilizes functions defined in allFunctions.c 
to output the correct variables as taken from the file. If the functions from allFunctions.c do not return an error, the program prints
out the information of the file. See allFunctions.c for more information.

sndconv: SAME FROM PART2
This program converts from one file format to another. This program supports the passing of switches. The included switches are:
	-h   : Display a short help screen to standard error, and terminate cleanly without reading any files.
	-1   : Prompts for filenames of the input and output and ignores any other arguments. 
	-a   : Output should be AIFF
	-c   : Output should be CS229 
When the -1 argument is not passed, this program reads from standard input and writes to standard output.

sndcat: SAME FROM PART2
This program reads all sound files passed as arguments, and writes a single sound file where the sample data is the concatenation of the sample data in the 
inputs. The resulting sound file is written directly to standard output. If no files are passed as arguments, then the standard input stream is treated as
the input file. The included switches for this program are:
	-h   : Display a short help screen to standard error, and terminate cleanly without reading any files.
	-a   : Output should be AIFF
	-c   : Output should be CS229 

sndcut: SAME FROM PART2
This program reads a sound file from the standard input stream, and writes the sound file to the standard output stream in the same format, after removing all 
samples specified as arguments. Specifically, arguments may be passed as:
	$ sndcut [switches] [low..high] [low..high] ...
where low..high specifies that all samples numbered between low and high, inclusive, are to be removed. The included switches for this program are:
	-h   : Display a short help screen to standard error, and terminate cleanly without reading any files.

sndshow: SAME FROM PART2
This program reads a sound file from the standard input stream, and displays an "ASCII art" representation of the sample data. The included switches are:
	-h   : Display a short help screen to standard error, and terminate cleanly without reading any files.
	-c c : Show the output only for channel c, for 1 <= c <= #channels.
	-w w : Specifies the total output width, in number of characters. If not specified, the default is w = 80. w must be even so that the number of characters 
	       for representing positive values is equal to the number of characters for representing negative values. Supports values down to w = 20.
	-z n : Zoom out by a factor of n. If not specified, the default is n = 1. The value to "plot" is the largest magnitude value over n consecutive samples, and the number of lines
	       of output decreases by about a factor of n.

sndedit: NEW FROM PART 3
This is the audio file editor based onn the ncurses library. The executable takes in a single argument, which is the filepath of the audio file. The following is an example of the display

                              ../hello.cs229 (CS229)        
================================================================================
     1163|                --------|                        |  Sample Rate: 22050
     1164|                --------|                        |    Bit Depth: 16
     1165|                 -------|                        |     Channels: 1
     1166|                 -------|                        |      Samples: 13351
     1167|                --------|                        | Length: 00:00:00.61
     1168|                --------|                        |====================
     1169|                --------|                        |   m: mark
     1170|                --------|                        |   c: copy
     1171|                --------|                        |   x: cut
     1172|                 -------|                        |   ^: insert before
     1173|                  ------|                        |   v: insert after
     1174|                    ----|                        |   s: save
     1175|                        |                        |   q: quit
     1176|                        |---                     |
     1177|                        |------                  | Movement:
     1178|                        |----------              |   up/dn
     1179|                        |-----------             |   pgup/pgdn
     1180|                        |-----------             |   g: goto sample
     1181|                        |------------            |====================
     1182|                        |-----------             |   Marked: 1167
     1183|                        |---------               | Buffered: 12
     1184|                        |---------               |

	'g' (goto)  : Allows the user to input to which sample number they want to go to in a file **In my program, if anything is marked and 'g' is pressed, it is then unmarked
	'm' (mark)  : Makes the program select/hightlight whichever sample they are on. **In my program, when you move up and down, it continues to highlight (does not undo highlight)
	'c' (copy)  : Copies whatever sample numbers are marked **In my program, when 'c' is pressed, whatever is marked becomes unmarked
	'x' (cut)   : Cuts whatever sample numbers are marked
	'^' (paste) : Pastes the copied samples above the selected sample
	'v' (paste) : Pastes the copied samples below the selected sample
	's' (save)  : Saves any changes made to the program
	'q' (quit)  : Exits the program
For each command, there are specific iterations that the program goes through to accomodate the user's input. At the end of each key press command, the ASCII art screen is updated.
The function called is in sndedit:
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
	void updateScreen(struct file input, int start, int stop, int width, int max, int* lines).



allFunctions.h:
This file contains all the functions and variables of sndconv, sndinfo, and allFunctions.c. The following is the struct used in this program
	struct file
	{
		FILE* file;
		char* filepath;
		char* filename;
		char* format;
		unsigned long sampleRate;
		int bitDepth;
	        int channels;
	        unsigned int samples;
	        int* startData;
	        int error;
		int type;
	};
The filepath represents the user's input. The file is made by the filepath. The filename is extracted from that filepath. The format is either CS229 or AIFF depending on the file type. The sampleRate, bitDepth, 
channels, samples, and startData are all information taken from the file. The int error is initially set to 0, meaning that the file contains no bugs. As the program progresses,
the error is updated accordingly: 
	error is 0 : No bugs found.
	error is 1 : BitDepth is incorrect
	error is 2 : Channels is incorrect
        error is 3 : There is a startData number that is too low
	error is 4 : There is a startData number that is too high
	error is 5 : Boundaries for sndcut written incorrectly
All errors are written to standard error. The type is an integer that differentiates which filetype the user has as their input.







allFunctions.c:
The following are more detailed descriptions of the functions that I implemented in allFunctions.c.
	
	/* Gets the information from the file and applies it to the returned struct*/
	struct file getFileInfo(char* filepath, FILE* f);
		This file first opens the file and reads whether it is of type CS229 or AIFF. Based upon the data in the files, it assigns
		the struct variables accordingly with the use of get229Info and get ASCIIInfo (see for more details). This function also
		uses char* basecase() to get the filename from the filepath. This function is used in every program. Returns the resultant
		struct.

	/* Reads a .cs229 file line by line and appends data to the struct values accordingly */
	struct file get229Info(struct file input);
		Uses the fscanf function to find the keywords in the file (Samples, BitDepth, etc.) and appends the values accordingly to
		the variables in the struct. When the pointer reaches "StartData" in the file, it counts the amount, compares that to the
		samples number, and appends the values to the struct's startData int array. Returns the resultant struct.

	/*Reads a .aiff file and appends data to the struct values accordingly*/
	struct file getASCIIInfo(struct file input);
		Iterates through the .aiff file. Uses a state machine to find the appropriate chuncks. When keyword values are found, performs
		bitshifting when necessary and appends the results accordingly to the struct's variables. When the StartData is reached, it bitshifts
		the values according to the value of the BitDepth, and appends the values to the struct's startData int array. Returns the resultant
		struct.

	/*Gets the duration of a file for sndinfo and sndedit*/
	int getDuration(struct file input);
		Gets the amount of seconds from the samples/sampleRate, and converts the seconds to hours and minutes. Prints the end result in
		the format HH:MM:SS.SS. If the samples or sampleRate is equal to zero, prints all zeros to this format.

	/* Prints the proper information for sndinfo */
	void printInformation(struct file input);
		Prints the key information based upon the values in the struct parameter.

	/*Converts filetypes*/
	void convert(struct file input, FILE* f, int type);
		The struct file parameter represents the struct containing the information for the file to be converted. The FILE* parameter is the 
		file variable of the struct. The int parameter represents what the file is being converted to (if type is 1, convert to AIFF, if type
		is 2, convert to CS229). For converting to AIFF, this function writes to the output file and bitshifts values accordingly. For converting
		to CS229, the function writes the variable data from the struct directly to the output file.

	/*Saves changes to files*/
	void saveFile(struct file input);
		Calls the convert function to save the file in the proper format

	/*Gets min data number*/
	int findMinData(int* startData, int size);
		Finds the min startData number for sndedit. It takes in the int* containing the startData and the size of the startData
		int array.	

	/*Gets max data number*/
	int findMaxData(int* startData, int size);
		This function finds the max startData number for sndshow and sndedit. It takes in the int* containing the startData and the size of the startData
		int array.

	/*Prints ASCII art representation of startData*/
	void getASCIIArt(int width, int zoom, int c, struct file input);
		This function first resets the startData if zoom is > 1: first it adjusts the array containing the index numbers to be displayed, and then
		it goes through the startData and adjusts the values according to the zoom formula. The function then prints the information, of which is 
		dependent on c (whether it is > 0). 
	
	/*Merges the input files*/
	struct file concatenate(struct file input[], int count);
		Takes in the array of files entered in by the user as structs. Creates a new array the size of all the input file sizes combined, and puts
		them together.

	/*Removes the range set*/
	struct file removeRange(int lows[], int highs[], int numRanges, struct file input);
		It loops through the original startData, copying only the samples not in the ranges. Frees the memory of the old array and sets the input's 
		startData to the new array.

	/*Compares the sets of highs and lows*/	
	int inRange(int position, int *lows, int *highs, int numRanges);
		Checks to see if the int is in the range of a set of high and lows.

	/*Finds the index of an element (taken from stack overflow example)*/
	int find_index(int* a, int num_elements, int value);

	/* Function found at (http://aifftools.sourceforge.net/libaiff/)  */
	void ieee754_write_extended(double in, uint8_t* out);

	/* Function found at (http://aifftools.sourceforge.net/libaiff/)  */
	double ieee754_read_extended(uint8_t* in);

