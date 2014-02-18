   _________     _________   ____      ____ ___________   _________    _________   ____
  /         \   /         \ |    \    /    |    ___    \ /         \  /         \ |    | 
 /    ___    \ /    ___    \|     \  /     |   |   \    |    ___    |/    ___    \|    | 
|    /   \    |    /   \    |      \/      |   |    |   |   /   \___|    /   \    |    |
|   |     |___|   |     |   |              |   |    |   |   \______ |   |     |___|    |
|   |         |   |     |   |              |   |___/    |          \|   |         |    |
|   |      ___|   |     |   |              |     ______/\_______    |   |      ___|    |
|   |     |   |   |     |   |    |\  /|    |    |        ___    \   |   |     |   |    |
|    \___/    |    \___/    |    | \/ |    |    |       |   \___/   |    \___/    |    |
 \           / \           /|    |    |    |    |       |           |\           /|    | 
  \_________/   \_________/ |____|    |____|____|        \_________/  \_________/ |____|
README  
Author: Camryn Williams
NetID: 765387623


Project 2 Final Project
This project provides a visual representation of 3 different types of cellular automata: John Conway's "Game of Life", WireWorld, and Elementary. 
It displays a two-dimensional grid of square cells, each cell having different states based upon the filetype. It also steps through generations. The state of the cell evolved over time according
to it's eight neighboring cells, and its previous state.
For the Game of Life, there are two possible states: alive or dead. 
	1. If a cell is alive in generation i, then
		a) if there are fewer than two alive neighbors in generation i, then the cell will be dead in generation i+1
		b) if there are two or three alive neighbors in generation i, then the cell will be alive in generation i+1
		c) if there are more than three alive neighbors in generation i, then the cell will be dead in generation i+1
	2. If a cell is dead in generation i, then
		a) if there are exactly three alive neighbors in generation i, then the cell will be alive in gereation i+1
		b) otherwise the cell will be dead in generation i+1
For WireWorld, there are four possible states: empty, electron head, electron tail, and wire.
	1. If a cell is empty in generation i, it will be empty in generation i+1
	2. If a cell is an electron head in generation i, it will be an electron tail in generation i+1
	3. If a cell is an electron tail in generation i, it will be a wire in generation i+1
	4. If a cell is a wire in generation i, it will be an electron head in generation i+1 if exactly one or two neighbors are electron heads (wire otherwise)
For Elementary, there are two possible states: one or zero
	1. If a cell is in state one, then it remains in state 1
	2. If a cell is in state zero, it's next state is determined by looking at the rule pattern and comparing it to the cell pattern above it.

There are two main programs with this program: life and life_gui.  Both read a single input file passed  as  an  argument  or from
standard input. life displays it's result in the command line, life_gui opens up a Qt executable to show the result.

life accepts the following switches:
	-f	 	Output should be in the same le format as Appendix A.
	-g n 	 	Specify the desired generation number. If omitted, the default should be n = 0.
	-h 	 	Display a help screen that describes the program.
	-tx l::h 	Set the x range of the terrain; overrides values specied in the input le.
	-ty l::h 	Set the y range of the terrain; overrides values specied in the input le.
	-v 		Output should be visual: an ASCII display of the terrain with appropriate characters for the
			dead and alive cells. In Figure 4, the dead character is \~" and the alive character is \@".
	-wx l::h 	Set the x range of the output window; otherwise this defaults to the x range of the terrain.
	-wy l::h 	Set the y range of the output window; otherwise this defaults to the y range of the terrain.

life_gui accepts the following switches:
	-g n 		Specify the desired generation number. If omitted, the default should be n = 0.
	-h 		Display a help screen that describes the program, and terminate before starting the GUI.
	-s n 		Specify the size, in pixels, of each square in the grid (default should be 10). Grid lines should
			be omitted when the size is less than 4.
	-tx l::h 	Set the x range of the terrain; overrides values specied in the input le.
	-ty l::h 	Set the y range of the terrain; overrides values specied in the input le.
	-wx l::h 	Set the (initial) x range of the output window (default is terrain x range).
	-wy l::h 	Set the (initial) y range of the output window (default is terrain y range).
	-c              A dialog box that controls the simulation appears (see below for more information)	

These two programs have different main files, but share the same .hh and .cc files (functions.hh and functions.cc).
	Structs:
		(1) This is the struct that holds the strings containing the range of the x and y terrain from the input file.
		    struct terrain {
			string xRange;
			string yRange;
		    };
		(2) This is the struct that holds the integer values of the ASCII symbols for each input file.
		    struct symbols {
			int sAlive;
			int sDead;
		
			int sEmpty;
			int sHead;
			int sTail;
			int sWire;
	
			int sZero;
			int sOne;
		    };
		(3) This is the struct that holds the string containing the rgb colors for each input file.
		    struct colors {
			string cAlive;
			string cDead;
	
			string cEmpty;
			string cHead;
			string cTail;
			string cWire;	
	
			string cZero;
			string cOne;
		    };
		(4) This is a struct for coordinates (specifically the starting coordinates from the input file).
		    struct coordinates {
			int x;
			int y;
		    };
		(5) This is the struct that holds the strings containing the range of the x and y window from the input file. 
		    struct window {
			string xRange;
			string yRange;
		    };
	Classes:
		(1) This class reads and interprets data from the input file
		    class lifeFile
		    {
			/** Constructor.
         		    @param  fname  	  Name
         		    @param  fterr 	  Terrain
          		    @param  fcodes 	  ASCII Chars
		  	    @param  frgbcolor	  Colors
		 	    @param  fcorr	  Coordinates
		 	    @param  fwin          Window
			*/
			lifeFile(string fname, terrain fterr, symbols fcodes, colors frgbcolor, coordinates* fcorr, window fwin)
			...
		    };
		    For each variable there are getter and setter functions. Besides that, the functions within this class are as follows:
			public:
				int get_RGB1(string bounds) /*Returns the first rgb number*/
					-- Returns the first rgb number from the string in the format (***, ***, ***) taken from the file by stepping through the string
						(Functions RGB2 and RGB3 do the same thing for the 2nd and 3rd number respectively)
				coordinates* getListCoordinates(string corrs) /*Creates a list of coordinates based upon the string of initial coordinates taken from the file*/
					-- This function looks for when the string is not a '(', ',', ')', or ';' and assigns the properties of a struct
					   to the remaining values, assigning that coordinate struct to an array of the structs.
				void parseFile(char* filename) /*Sets all of the initial properties to variables and structs according to the input file*/
					-- This function steps through the file by individual characters, looking for the keywords of the file and then 
					   assigning preceeding characters to the proper variables.
		(2) This class holds the properties of an individual cell **Only used for life file**
		    class cell 
		    {
			/** Constructor
          		    @param  x 		X coordinate
          		    @param  y 	        Y coordinate
			*/
			cell(int x, int y)
			{
				xCorr = x;
				yCorr = y;
				alive_in_prev = false;
			}
			...
		    };
		    For each variable there are getter and setter functions. 
	Functions:
		(1) int getLowerBound(string bounds); /*Takes in a string that contains a range and returns the lower number*/
			-- Steps through the string looking for '..' and returning the number that comes before that key
		(2) int getUpperBound(string bounds); /*Takes in a string that contains a range and returns the higher number*/
			-- Steps through the string looking for '..' and returning the number that comes after that key
		(3) string DecToBin(int number); /*Takes in a number and converts it to a binary string. TAKEN FROM STACK OVERFLOW*/
		(4) void printLifeVisual(int gen, lifeFile lf); /*Prints grid to console*/
			-- Loops through grids, starting at gen = 0 until gen and then returns ASCII representation of that
			   grid at the ending generation
		(5) void printWireWorld(int gen, lifeFile lf); /*Prints grid to console*/
			-- Loops through grids, starting at gen = 0 until gen and then returns ASCII representation of that
			   grid at the ending generation
		(6) void printElementary(int gen, lifeFile lf); /*Prints grid to console*/
			-- Loops through grids, starting at gen = 0 until gen and then returns ASCII representation of that
			   grid at the ending generation

The actual gui part of this project is implemented in life_gui. It has the same approach as life, except instead of calling any of the printVisual functions, it draws to a QtWindow.

CONTROLS
When the user selects -c on the console, a window appears alongside the grid representation that controls the simulation. In this controlled box, the user has:
	1. The ability to advance to the next generation, i.e., compute and display it.
	2. The ability to continuously run the simulation, i.e., compute the next generation, display it, delay
	   for some time, and repeat.
	3. The ability to set the duration of the delay between generations.
	4. The ability to pause the simulation.
	5. The ability to restart the simulation back to generation 0.
	6. An indication of the number of the current generation.
	7. The ability to set the size of the grid squares. 
	8. The ability to quit the simulation. *done*