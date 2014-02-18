#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <string.h>

#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

using namespace std;

/**

	Holds the classes and functions for life and life_gui
	@author Camryn Williams

*/




/** Takes in a string that contains a range and returns the lower number*/
int getLowerBound(string bounds);

/** Takes in a string that contains a range and returns the higher number*/
int getUpperBound(string bounds);

/** Takes in a number and converts it to a binary string. TAKEN FROM STACK OVERFLOW */
string DecToBin(int number);

/** Holds the properties of the terrain taken from the file */
struct terrain {
	string xRange;
	string yRange;
};

/** Holds the integer values of the ASCII symbols for each input file. */
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

/** Holds the string containing the rgb colors for each input file. */
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

/** Holds the property of the coordinates (specifically the starting coordinates from the input file).*/
struct coordinates {
	int x;
	int y;
};

/** Holds the strings containing the range of the x and y window from the input file. */
struct window {
	string xRange;
	string yRange;
};

/** File class (for all files, not just lifeFile) */
class lifeFile {
	private:
		string name;
		terrain terr;
		symbols codes;
		colors rgbcolor;
		coordinates* lifeCorr;
		coordinates* headCorr;
		coordinates* tailCorr;
		coordinates* wireCorr;
		coordinates* oneCorr;
		window win;
		int corrCount;
		int lifeCount;
		int headCount;
		int tailCount;
		int wireCount;
		int oneCount;
		int rule;
		string corrLifeString; //string taken from life file that contains the coordinate information
		string corrHeadString;
		string corrTailString;
		string corrWireString;
		string corrOneString;
		bool error;
		
	public:
		/** Constructor.
          @param  fname  		Name
          @param  fterr 		Terrain
          @param  fcodes 		ASCII Chars
		  @param  frgbcolor		Colors
		  @param  fcorr			Coordinates
		  @param  fwin          Window
		*/
		lifeFile() //ERROR FILE
		{
			name = "";
			/*terrain terr = NULL;
			symbols codes = NULL;
			colors rgbcolor = NULL;
			coordinates* corr = NULL;
			window win = NULL;*/
			error = true;
		}
		lifeFile(string fname, terrain fterr, symbols fcodes, colors frgbcolor, coordinates* fcorr, window fwin)
		{
			name = fname;
			terr = fterr;
			codes = fcodes;
			rgbcolor = frgbcolor;
			lifeCorr = fcorr;
			win = fwin;
		}

	public:
		/**
			Returns the name specified by the file
				@return name
		*/
		inline string get_name() const { return name; }
		/**
			Returns the rule specified by the elementary file
				@return rule
		*/
		inline int get_rule() const { return rule; }
		/**
			Returns an array of initial coordinates specified by the life file
				@return lifeCorr
		*/
		inline coordinates* getLifeCorrArray() const { return lifeCorr; }
		/**
			Returns an array of head coordinates specified by the wireworld file
				@return headCorr
		*/
		inline coordinates* getHeadCorrArray() const { return headCorr; }
		/**
			Returns an array of tail coordinates specified by the wireworld file
				@return tailCorr
		*/
		inline coordinates* getTailCorrArray() const { return tailCorr; }
		/**
			Returns an array of wire coordinates specified by the wireworld file
				@return wireCorr
		*/
		inline coordinates* getWireCorrArray() const { return wireCorr; }
		/**
			Returns an array of one coordinates specified by the elementary file
				@return oneCorr
		*/
		inline coordinates* getOneCorrArray() const { return oneCorr; }
		/**
			Returns the number of initial coordinates specified by the life file
				@return lifeCount
		*/
		inline int get_lifeCount() const { return lifeCount; }
		/**
			Returns the number of wire coordinates specified by the wireworld file
				@return wireCount
		*/
		inline int get_wireCount() const { return wireCount; }
		/**
			Returns the number of tail coordinates specified by the wireworld file
				@return tailCount
		*/
		inline int get_tailCount() const { return tailCount; }
		/**
			Returns the number of head coordinates specified by the wireworld file
				@return headCount
		*/
		inline int get_headCount() const { return headCount; }
		/**
			Returns the number of one coordinates specified by the elementary file
				@return oneCount
		*/
		inline int get_oneCount() const { return oneCount; }
		/**
			Returns the string of initial coordinates from the life file
				@return corrLifeString
		*/
		inline string getLifeCorrString() const { return corrLifeString; }
		/**
			Returns the string of head coordinates from the wireworld file
				@return corrHeadString
		*/
		inline string getHeadCorrString() const { return corrHeadString; }
		/**
			Returns the string of tail coordinates from the wireworld file
				@return corrTailString
		*/
		inline string getTailCorrString() const { return corrTailString; }
		/**
			Returns the string of wire coordinates from the wireworld file
				@return corrWireString
		*/
		inline string getWireCorrString() const { return corrWireString; }
		/**
			Returns the string of one coordinates from the wireworld file
				@return corrOneString
		*/
		inline string getOneCorrString() const { return corrOneString; }
		/**
			Returns the ASCII number for alive from the life file
				@return codes.sAlive
		*/
		inline int get_sAlive() const { return codes.sAlive; }
		/**
			Returns the ASCII number for dead from the life file
				@return codes.sDead
		*/
		inline int get_sDead() const { return codes.sDead; }
		/**
			Returns the ASCII number for empty from the wireworld file
				@return codes.sEmpty
		*/
		inline int get_sEmpty() const { return codes.sEmpty; }
		/**
			Returns the ASCII number for head from the wireworld file
				@return codes.sHead
		*/
		inline int get_sHead() const { return codes.sHead; }
		/**
			Returns the ASCII number for tail from the wireworld file
				@return codes.sTail
		*/
		inline int get_sTail() const { return codes.sTail; }
		/**
			Returns the ASCII number for wire from the wireworld file
				@return codes.sWire
		*/
		inline int get_sWire() const { return codes.sWire; }
		/**
			Returns the ASCII number for zero from the elementary file
				@return codes.sZero
		*/
		inline int get_sZero() const { return codes.sZero; }
		/**
			Returns the ASCII number for one from the elementary file
				@return codes.sOne
		*/
		inline int get_sOne() const { return codes.sOne; }
		/**
			Returns the string that holds the RGB value for alive from the life file
				@return rgbcolor.cAlive
		*/
		inline string get_cAlive() const { return rgbcolor.cAlive; }
		/**
			Returns the string that holds the RGB value for dead from the life file
				@return rgbcolor.cDead
		*/
		inline string get_cDead() const	{ return rgbcolor.cDead; }
		/**
			Returns the string that holds the RGB value for empty from the wireworld file
				@return rgbcolor.cEmpty
		*/
		inline string get_cEmpty() const { return rgbcolor.cEmpty; }
		/**
			Returns the string that holds the RGB value for head from the wireworld file
				@return rgbcolor.cHead
		*/
		inline string get_cHead() const { return rgbcolor.cHead; }
		/**
			Returns the string that holds the RGB value for tail from the wireworld file
				@return rgbcolor.cTail
		*/
		inline string get_cTail() const { return rgbcolor.cTail; }
		/**
			Returns the string that holds the RGB value for wire from the wireworld file
				@return rgbcolor.cWire
		*/
		inline string get_cWire() const { return rgbcolor.cWire; }
		/**
			Returns the string that holds the RGB value for zero from the elementary file
				@return rgbcolor.cZero
		*/
		inline string get_cZero() const { return rgbcolor.cZero; }
		/**
			Returns the string that holds the RGB value for one from the elementary file
				@return rgbcolor.cOne
		*/
		inline string get_cOne() const { return rgbcolor.cOne; }
		/**
			Sets error to the boolean value
			@param e 
				true if error, false if not
		*/
		inline void setError(bool e) { error = e; }
		/**
			Gets the string representation of the x-range for the terrain
			@return terr.xRange
		*/
		inline string get_TxRange() const { return terr.xRange; }
		/**
			Gets the string representation of the y-range for the terrain
			@return terr.yRange
		*/
		inline string get_TyRange() const { return terr.yRange; }
		/**
			Gets the string representation of the x-range for the window
			@return win.xRange
		*/
		inline string get_WxRange() const { return win.xRange; }
		/**
			Gets the string representation of the y-range for the window
			@return win.yRange
		*/
		inline string get_WyRange() const { return win.yRange; }
		/**
			Sets the string representation of the x-range for the terrain
			@param x
				x is written in the proper format and terr.xRange is set to x
		*/
		inline void set_TxRange(string x) { terr.xRange = x; }
		/**
			Sets the string representation of the y-range for the terrain
			@param y
				y is written in the proper format and terr.yRange is set to y
		*/
		inline void set_TyRange(string y) { terr.yRange = y; }
		/**
			Sets the string representation of the x-range for the window
			@param x
				x is written in the proper format and win.xRange is set to x
		*/
		inline void set_WxRange(string x) { win.xRange = x; }
		/**
			Sets the string representation of the y-range for the window
			@param y
				y is written in the proper format and win.yRange is set to y
		*/
		inline void set_WyRange(string y) { win.yRange = y; }
		
		/**
			Returns the 1st rgb number
			@param bounds
				the string in the format (***, ***, ***) taken from the file
			@return the first number
		*/
		inline int get_RGB1(string bounds) const
		{
			int first = 0;
			char* num = (char*) malloc(sizeof(char*) * 100);
			int i = 0;
			int j = 0;
			char p = bounds.at(i);
			while(p != '(')
			{
				i++;
				p = bounds.at(i);
			}
			i++;
			p = bounds.at(i);
			while(p != ',')
			{
				num[j] = p;
				j++;
				i++;
				p = bounds.at(i);
			}
			first = atoi(num);
			return first;
		}
		/**
			Returns the 12nd rgb number
			@param bounds
				the string in the format (***, ***, ***) taken from the file
			@return the second number
		*/
		inline int get_RGB2(string bounds) const
		{
			int second = 0;
			char* num = (char*) malloc(sizeof(char*) * 100);
			int i = 0;
			int j = 0;
			char p = bounds.at(i);
			while(p != '(')
			{
				i++;
				p = bounds.at(i);
			}
			while(p != ',')
			{
				i++;
				p = bounds.at(i);
			}
			i++;
			p = bounds.at(i);
			while(p != ',')
			{
				num[j] = p;
				j++;
				i++;
				p = bounds.at(i);
			}
			num[j] = '\0';
			second = atoi(num);
			
			return second;
		}
		/**
			Returns the 3rd rgb number
			@param bounds
				the string in the format (***, ***, ***) taken from the file
			@return the third number
		*/
		inline int get_RGB3(string bounds) const
		{
			int last = 0;
			char* num = (char*) malloc(sizeof(char*) * 100);
			int i = 0;
			int j = 0;
			char p = bounds.at(i);
			while(p != '(')
			{
				i++;
				p = bounds.at(i);
			}
			while(p != ',')
			{
				i++;
				p = bounds.at(i);
			}
			while(p != ',')
			{
				i++;
				p = bounds.at(i);
			}
			i++;
			p = bounds.at(i);
			while(p != ')')
			{
				num[j] = p;
				j++;
				i++;
				p = bounds.at(i);
			}
			num[j] = p;
			last = atoi(num);
			return last;
		}
		/**
			Takes the string representation of the coordinates from the file and converts it to an
			array of coordinates
			@param corrs
				the string of coors taken from the file
			@return an array of coordinates
		*/
		coordinates* getListCoordinates(string corrs)
		{
			int count = 0;
			int j = 0;
			int k = 0;
			int i = 0;
			int x = 0;
			for(int y = 0; y < corrs.length(); y++)
			{
				if(corrs.at(y) == '(') { count++; }
			}
			this -> corrCount = count;
			coordinates* cArray = (coordinates*)malloc(count * sizeof(coordinates));
			coordinates c;
			char p = corrs.at(i);
			while(x != count)
			{
				p = corrs.at(i);
				if(p == '(')
				{
					char* sY = (char*) malloc(sizeof(char*) * 100);
					char* sX = (char*) malloc(sizeof(char*) * 100);
					i++;
					p = corrs.at(i);
					while(p != ',')
					{
						sX[j] = p;
						i++;
						p = corrs.at(i);
						j++;
					}
					j = 0;
					i++;
					p = corrs.at(i);
					while(p != ')')
					{
						sY[k] = p;
						p = corrs.at(i);
						i++; k++;
					}
					k = 0;
					c.x = atoi(sX);
					c.y = atoi(sY);
					cArray[x] = c;
					x++;
					memset(sX, 0, 100);
					memset(sY, 0, 100);
				}
				i++;
			}
			return cArray;
		}
		/**
			Steps through the file and sets the values of the variables accordingly
			@param filename
				The filepath of the file we want information from
			@return the string "Life", "WireWorld", "Elementary" to indicate the type of file
		*/
		string parseFile(char* filename)
		{
			bool isWin = false;
			string n, r, wXrange, wYrange, tXrange, tYrange, aASCII, dASCII, eASCII, hASCII, tASCII, wASCII, zASCII, oASCII, aColors, dColors, eColors, hColors, tColors, wColors, zColors, oColors, lifeCorrs, oneCorrs, headCorrs, tailCorrs, wireCorrs;
			char point;
			FILE* myfile = fopen(filename, "r");
			if(myfile)
			{	
				point = fgetc(myfile);
				while(point != EOF)
				{
					//------------------Comment--------------------//
					if(point == '#')
					{
						while(point != '\n') { point = fgetc(myfile); }
						point = fgetc(myfile);
					}
					
					//------------------Life------------------------//
					if(point == 'L') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'f') { point = fgetc(myfile); if(point == 'e')
					{
						while(point != EOF)
						{
							//-------------------Name----------------------//
							if(point == 'N') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'm') { point = fgetc(myfile); if(point == 'e')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									if(point == '\"')
									{
										point = fgetc(myfile);
										while(point != '\"')
										{
											n += point;
											point = fgetc(myfile);
										}		
										break;
									}
									point = fgetc(myfile);
								}
							}}}}
			
							//-------------------Terrain-------------------//
							if(point == 'T') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'n')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Xrange
									if(point == 'X') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { tXrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									//Yrange
									if(point == 'Y') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{	 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Yrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { tYrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									point = fgetc(myfile);
								}
							}}}}}}}
			
							//-------------------Window-------------------//
							if(point == 'W') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'd') { point = fgetc(myfile); if(point == 'o') { point = fgetc(myfile); if(point == 'w')
							{
								isWin = true;
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Xrange
									if(point == 'X') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { wXrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									//Yrange
									if(point == 'Y') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{	 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Yrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { wYrange += point; point = fgetc(myfile); }
										}
									}}}}}}
									point = fgetc(myfile);
								}
							}}}}}}
	
							if(point == 'C') 
							{ 
								point = fgetc(myfile); 
								//-------------------Colors--------------------//
								if(point == 'o') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'o') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 's')
								{
									point = fgetc(myfile);
									while(point != ';')
									{
										//Comment
										if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
										//Alive
										if(point == 'A') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'v') { point = fgetc(myfile); if(point == 'e') 
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { aColors += point; point = fgetc(myfile); }
											}
										}}}}}
					
										//Dead
										if(point == 'D') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'd') 
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { dColors += point; point = fgetc(myfile); }
											}
										}}}}
										point = fgetc(myfile);
									}
								}}}}}
					
								//--------------------ASCII--------------------//
								if(point == 'h') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 's')
								{
									point = fgetc(myfile);
									while(point != ';')
									{
										//Comment
										if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
										//Alive
										if(point == 'A') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'v') { point = fgetc(myfile); if(point == 'e') 
										{	 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Xrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { aASCII += point; point = fgetc(myfile); }
											}
										}}}}}
					
										//Dead
										if(point == 'D') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'd') 
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Yrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { dASCII += point;	point = fgetc(myfile); }
											}
										}}}}
										point = fgetc(myfile);
									}
								}}}}
							}
					
							//-----------------Coordinates-----------------//
							if(point == 'I') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 't') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'l')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Alive
									if(point == 'A') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'v') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { lifeCorrs += point; point = fgetc(myfile); }
										}
									}}}}}
					
									point = fgetc(myfile);
								}
							}}}}}}}
			
							point = fgetc(myfile);
						}
						corrLifeString = lifeCorrs;
						lifeCorr = this -> getListCoordinates(lifeCorrs);
						lifeCount = corrCount;
						rgbcolor.cAlive = aColors;
						rgbcolor.cDead = dColors;
						codes.sAlive = atoi(aASCII.c_str());
						codes.sDead = atoi(dASCII.c_str());
						name = n;
						terr.xRange = tXrange;
						terr.yRange = tYrange;

						if(isWin)
						{
							win.xRange = wXrange;
							win.yRange = wYrange;
						}
						else 
						{
							win.xRange = tXrange;
							win.yRange = tYrange;
						}
						return "Life";
					}}}}
					
					//------------------Elementary------------------------//
					if(point == 'E') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'm'){ point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 't') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'y')
					{
						while(point != EOF)
						{
							//-------------------Name----------------------//
							if(point == 'N') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'm') { point = fgetc(myfile); if(point == 'e')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									if(point == '\"')
									{
										point = fgetc(myfile);
										while(point != '\"')
										{
											n += point;
											point = fgetc(myfile);
										}		
										break;
									}
									point = fgetc(myfile);
								}
							}}}}
							
							//-------------------Rule----------------------//
							if(point == 'R') { point = fgetc(myfile); if(point == 'u') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'e')
							{
								point = fgetc(myfile);
								while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
								point = fgetc(myfile); //move to char after equals sign
								while(point != ';')
								{
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
									else { r += point; point = fgetc(myfile); }
								}
							}}}}
			
							//-------------------Terrain-------------------//
							if(point == 'T') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'n')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Xrange
									if(point == 'X') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { tXrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									//Yrange
									if(point == 'Y') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{	 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Yrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { tYrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									point = fgetc(myfile);
								}
							}}}}}}}
			
							//-------------------Window-------------------//
							if(point == 'W') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'd') { point = fgetc(myfile); if(point == 'o') { point = fgetc(myfile); if(point == 'w')
							{
								isWin = true;
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Xrange
									if(point == 'X') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { wXrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									//Yrange
									if(point == 'Y') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{	 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Yrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { wYrange += point; point = fgetc(myfile); }
										}
									}}}}}}
									point = fgetc(myfile);
								}
							}}}}}}
							
							if(point == 'C') 
							{ 
								point = fgetc(myfile); 
								//-------------------Colors--------------------//
								if(point == 'o') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'o') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 's')
								{
									point = fgetc(myfile);
									while(point != ';')
									{
										//Comment
										if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
										//Zero
										if(point == 'Z') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'o')
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { zColors += point; point = fgetc(myfile); }
											}
										}}}}
					
										//One
										if(point == 'O') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'e') 
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { oColors += point; point = fgetc(myfile); }
											}
										}}}
										point = fgetc(myfile);
									}
								}}}}}
					
								//--------------------ASCII--------------------//
								if(point == 'h') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 's')
								{
									point = fgetc(myfile);
									while(point != ';')
									{
										//Comment
										if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
										//Zero
										if(point == 'Z') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'o')
										{	 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Xrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { zASCII += point; point = fgetc(myfile); }
											}
										}}}}
					
										//One
										if(point == 'O') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'e') 
										{
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Yrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { oASCII += point;	point = fgetc(myfile); }
											}
										}}}
										point = fgetc(myfile);
									}
								}}}}
							}
							
							//-----------------Coordinates-----------------//
							if(point == 'I') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 't') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'l')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Alive
									if(point == 'O') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { oneCorrs += point; point = fgetc(myfile); }
										}
									}}}
					
									point = fgetc(myfile);
								}
							}}}}}}}
			
							point = fgetc(myfile);
						}
						//Set values
						corrOneString = oneCorrs;
						rule = atoi(r.c_str());
						codes.sZero = atoi(zASCII.c_str());
						codes.sOne = atoi(oASCII.c_str());
						rgbcolor.cZero = zColors;
						rgbcolor.cOne = oColors;
						oneCorr = this -> getListCoordinates(oneCorrs);
						oneCount = corrCount;
						name = n;
						terr.xRange = tXrange;
						terr.yRange = tYrange;

						if(isWin)
						{
							win.xRange = wXrange;
							win.yRange = wYrange;
						}
						else 
						{
							win.xRange = tXrange;
							win.yRange = tYrange;
						}
						return "Elementary";
					}}}}}}}}}}
					
					//------------------WireWorld------------------------//
					if(point == 'W') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'e'){ point = fgetc(myfile); if(point == 'W') { point = fgetc(myfile); if(point == 'o') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'd')
					{
						while(point != EOF)
						{
							//-------------------Name----------------------//
							if(point == 'N') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'm') { point = fgetc(myfile); if(point == 'e')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									if(point == '\"')
									{
										point = fgetc(myfile);
										while(point != '\"')
										{
											n += point;
											point = fgetc(myfile);
										}		
										break;
									}
									point = fgetc(myfile);
								}
							}}}}
			
							//-------------------Terrain-------------------//
							if(point == 'T') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'n')
							{
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Xrange
									if(point == 'X') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { tXrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									//Yrange
									if(point == 'Y') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{	 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Yrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { tYrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									point = fgetc(myfile);
								}
							}}}}}}}
			
							//-------------------Window-------------------//
							if(point == 'W') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'd') { point = fgetc(myfile); if(point == 'o') { point = fgetc(myfile); if(point == 'w')
							{
								isWin = true;
								point = fgetc(myfile);
								while(point != ';')
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Xrange
									if(point == 'X') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { wXrange += point; point = fgetc(myfile); }
										}
									}}}}}}
					
									//Yrange
									if(point == 'Y') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'g') { point = fgetc(myfile); if(point == 'e') 
									{	 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Yrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { wYrange += point; point = fgetc(myfile); }
										}
									}}}}}}
									point = fgetc(myfile);
								}
							}}}}}}
						
							//-----------------Coordinates-----------------//
							if(point == 'I') { point = fgetc(myfile); if(point == 'n') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 't') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'l')
							{
								point = fgetc(myfile);
								while(point != '}') //NOTE THIS .........................................................................................
								{
									//Comment
									if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
									//Head
									if(point == 'H') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'd')
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { headCorrs += point; point = fgetc(myfile); }
										}
									}}}}
									
									//Tail
									if(point == 'T') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'l')
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { tailCorrs += point; point = fgetc(myfile); }
										}
									}}}}
									
									//Wire
									if(point == 'W') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'e')
									{ 
										point = fgetc(myfile);
										while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
										point = fgetc(myfile); //move to char after equals sign
										while(point != ';') //add chars after equals sign to Xrange
										{
											if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
											else { wireCorrs += point; point = fgetc(myfile); }
										}
									}}}}
									
									point = fgetc(myfile);
								}
							}}}}}}}
							
							if(point == 'C') 
							{ 
								point = fgetc(myfile); 
								//-------------------Colors--------------------//
								if(point == 'o') { point = fgetc(myfile); if(point == 'l') { point = fgetc(myfile); if(point == 'o') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 's')
								{
									point = fgetc(myfile);
									while(point != ';')
									{
										//Comment
										if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
										//Empty
										if(point == 'E') { point = fgetc(myfile); if(point == 'm') { point = fgetc(myfile); if(point == 'p') { point = fgetc(myfile); if(point == 't') { point = fgetc(myfile); if(point == 'y')
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { eColors += point; point = fgetc(myfile); }
											}
										}}}}}
					
										//Head
										if(point == 'H') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'd') 
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { hColors += point; point = fgetc(myfile); }
											}
										}}}}
										
										//Tail
										if(point == 'T') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'l') 
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { tColors += point; point = fgetc(myfile); }
											}
										}}}}
										
										//Wire
										if(point == 'W') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'e') 
										{ 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';')
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { wColors += point; point = fgetc(myfile); }
											}
										}}}}
										
										point = fgetc(myfile);
									}
								}}}}}
					
								//--------------------ASCII--------------------//
								if(point == 'h') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 's')
								{
									point = fgetc(myfile);
									while(point != ';')
									{
										//Comment
										if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
					
										//Empty
										if(point == 'E') { point = fgetc(myfile); if(point == 'm') { point = fgetc(myfile); if(point == 'p') { point = fgetc(myfile); if(point == 't') { point = fgetc(myfile); if(point == 'y')
										{	 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Xrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { eASCII += point; point = fgetc(myfile); }
											}
										}}}}}
										
										//Head
										if(point == 'H') { point = fgetc(myfile); if(point == 'e') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'd')
										{	 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Xrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { hASCII += point; point = fgetc(myfile); }
											}
										}}}}
										
										//Tail
										if(point == 'T') { point = fgetc(myfile); if(point == 'a') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'l')
										{	 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Xrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { tASCII += point; point = fgetc(myfile); }
											}
										}}}}
										
										//Wire
										if(point == 'W') { point = fgetc(myfile); if(point == 'i') { point = fgetc(myfile); if(point == 'r') { point = fgetc(myfile); if(point == 'e')
										{	 
											point = fgetc(myfile);
											while(point != '=') { point = fgetc(myfile); } //move to equals sign
						
											point = fgetc(myfile); //move to char after equals sign
											while(point != ';') //add chars after equals sign to Xrange
											{
												if(point == '#') { while(point != '\n') { point = fgetc(myfile); } }
												else { wASCII += point; point = fgetc(myfile); }
											}
										}}}}
										point = fgetc(myfile);
									}
								}}}}
							}
							point = fgetc(myfile);
						}
						//Set values
						codes.sHead = atoi(hASCII.c_str());
						codes.sTail = atoi(tASCII.c_str());
						codes.sEmpty = atoi(eASCII.c_str());
						codes.sWire = atoi(wASCII.c_str());
						rgbcolor.cHead = hColors;
						rgbcolor.cTail = tColors;
						rgbcolor.cEmpty = eColors;
						rgbcolor.cWire = wColors;
						corrHeadString = headCorrs;
						corrTailString = tailCorrs;
						corrWireString = wireCorrs;
						headCorr = this -> getListCoordinates(headCorrs);
						headCount = corrCount;
						wireCorr = this -> getListCoordinates(wireCorrs);
						wireCount = corrCount;
						tailCorr = this -> getListCoordinates(tailCorrs);
						tailCount = corrCount;
						name = n;
						terr.xRange = tXrange;
						terr.yRange = tYrange;
	
						if(isWin)
						{
							win.xRange = wXrange;
							win.yRange = wYrange;
						}
						else 
						{
							win.xRange = tXrange;
							win.yRange = tYrange;
						}
						return "WireWorld";
					}}}}}}}}}
					
					point = fgetc(myfile);
				}
			}
	
			else
			{
				cerr << "Error, file does not exist. \n";
				error = true;
				return "error";
			}
			
			return "done";
		}
};

/** Individual Cell Class */
class cell {
	private:
		int xCorr;
		int yCorr;
		bool alive_in_prev;
	
	public:
		/** Constructor
          @param  x 			X coordinate
          @param  y 			Y coordinate
		*/
		cell(int x, int y)
		{
			xCorr = x;
			yCorr = y;
			alive_in_prev = false;
		}
	
	public:
		inline int getX() const { return xCorr; }
		inline int getY() const { return yCorr; }
		inline bool aliveInPrev() const { return alive_in_prev; }
		inline void set_alive(bool isAlive) { alive_in_prev = isAlive; }
};

/** Prints life file visual to console */
void printLifeVisual(int gen, lifeFile lf);
/** Prints wire world file visual to console */
void printWireWorldVisual(int gen, lifeFile lf);
/** Prints elementary file visual to console */
void printElementaryVisual(int gen, lifeFile lf);

#endif