#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <string.h>

#include "functions.hh"

using namespace std;

/*

	Holds the functions for life necessary to print the grid to the console
	@author Camryn Williams

*/




/* Prints life file visual to console */
void printLifeVisual(int gen, lifeFile lf)
{
	char alive = lf.get_sAlive();
	char dead = lf.get_sDead();
	int lowXT = getLowerBound(lf.get_TxRange());
	int highXT = getUpperBound(lf.get_TxRange());
	int lowYT = getLowerBound(lf.get_TyRange());
	int highYT = getUpperBound(lf.get_TyRange());
	
	cout << "X-Range: " << lowXT << " to " << highXT << "    Y-Range: " << lowYT << " to " << highYT << "    Generation: " << gen << "\n";
	int next[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	int curr[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	coordinates* corrs = lf.getLifeCorrArray();
	
	//Initialize grids
	for(int x = 0; x < abs(lowXT) + abs(highXT); x++)
	{
		for(int y = 0; y < abs(lowYT) + abs(highYT); y++)
		{
			curr[x][y] =0;
			next[x][y] =0;
		}
	}
	
	for(int k = 0; k <= gen; k++)
	{
		for(int j = highYT; j >= lowYT; j--)
		{
			for(int i = lowXT; i <= highXT; i++)
			{
				int surroundings = 0;
				/*
					|UL|U|UR|
					|L |X| R|
					|DL|D|DR|
				*/
					
				if(k == 0)
				{	
					for(int a = 0; a < lf.get_lifeCount(); a++)
					{
						if(corrs[a].x == i && corrs[a].y == j)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
						}
					}	
				}
				
				else
				{
					if(j+1 <= highYT) { if (curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 1) { surroundings++; } }
					if(j-1 >= lowYT) { if (curr[i+abs(lowXT)][j-1+ abs(lowYT)] == 1) { surroundings++; } }
					if(i+1 <= highXT) { if (curr[i+1+abs(lowXT)][j+ abs(lowYT)] == 1) { surroundings++; } }
					if(i-1 >= lowXT) { if (curr[i-1+abs(lowXT)][j+ abs(lowYT)] == 1) { surroundings++; } }
					if(i+1 <= highXT && j+1 <= highYT) { if (curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 1) { surroundings++; } }
					if(i-1 >= lowXT && j+1 <= highYT) { if (curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 1) { surroundings++; } }
					if(i+1 <= highXT && j-1 >= lowYT) { if (curr[i+1+abs(lowXT)][j-1+ abs(lowYT)] == 1) { surroundings++; } }
					if(i-1 >= lowXT && j-1 >= lowYT) { if (curr[i-1+abs(lowXT)][j-1+ abs(lowYT)] == 1) { surroundings++; } }
				
					if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1)
					{
						if(surroundings == 2)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
						}
						else if(surroundings == 3)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
						}
						else if(surroundings > 3)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 0;
						}
						else if(surroundings < 2)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 0;
						}
						else
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 0;
						}
					}
		 
					else
					{
						if(surroundings == 3)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
						}
						else
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 0;
						}
					}
				}
			}
		}
		
		for(int x = 0; x <= abs(lowXT) + abs(highXT); x++)
		{
			for(int y = 0; y <= abs(lowYT) + abs(highYT); y++)
			{
				curr[x][y] = next[x][y];
			}
		}
	}
	
	for(int j = highYT; j >= lowYT; j--)
	{
		for(int i = lowXT; i <= highXT; i++)
		{
			if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1) { cout << alive; }
			else { cout << dead; }
		}
		cout << "\n";
	}

}


/* Prints wire world file visual to console */
void printWireWorldVisual(int gen, lifeFile lf)
{
	char empty = lf.get_sEmpty();
	char head = lf.get_sHead();
	char wire = lf.get_sWire();
	char tail = lf.get_sTail();
	int lowXT = getLowerBound(lf.get_TxRange());
	int highXT = getUpperBound(lf.get_TxRange());
	int lowYT = getLowerBound(lf.get_TyRange());
	int highYT = getUpperBound(lf.get_TyRange());
	
	cout << "X-Range: " << lowXT << " to " << highXT << "    Y-Range: " << lowYT << " to " << highYT << "    Generation: " << gen << "\n";
	int next[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	int curr[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	coordinates* headCorr = lf.getHeadCorrArray();
	coordinates* tailCorr = lf.getTailCorrArray();
	coordinates* wireCorr = lf.getWireCorrArray();
	
	//Initialize grids
	for(int x = 0; x < abs(lowXT) + abs(highXT); x++)
	{
		for(int y = 0; y < abs(lowYT) + abs(highYT); y++)
		{
			curr[x][y] =0;
			next[x][y] =0;
		}
	}
	
	for(int k = 0; k <= gen; k++)
	{
		for(int j = highYT; j >= lowYT; j--)
		{
			for(int i = lowXT; i <= highXT; i++)
			{
				/*
					|UL|U|UR|
					|L |X| R|
					|DL|D|DR|
				*/
					
				if(k == 0)
				{	
					for(int a = 0; a < lf.get_headCount(); a++)
					{
						if(headCorr[a].x == i && headCorr[a].y == j)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
						}
					}
					
					for(int b = 0; b < lf.get_tailCount(); b++)
					{
						if(tailCorr[b].x == i && tailCorr[b].y == j)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 2;
						}
					}
					
					for(int c = 0; c < lf.get_wireCount(); c++)
					{
						if(wireCorr[c].x == i && wireCorr[c].y == j)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 3;
						}
					}
				}
				
				else
				{
					if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 0)
					{
						next[i+abs(lowXT)][j+ abs(lowYT)] = 0;
					}
					
					else if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1)
					{
						next[i+abs(lowXT)][j+ abs(lowYT)] = 2;
					}
					
					else if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 2)
					{
						next[i+abs(lowXT)][j+ abs(lowYT)] = 3;
					}
					
					else
					{
						int surroundings = 0;
						if(j+1 <= highYT) { if (curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 1) { surroundings++; } }
						if(j-1 >= lowYT) { if (curr[i+abs(lowXT)][j-1+ abs(lowYT)] == 1) { surroundings++; } }
						if(i+1 <= highXT) { if (curr[i+1+abs(lowXT)][j+ abs(lowYT)] == 1) { surroundings++; } }
						if(i-1 >= lowXT) { if (curr[i-1+abs(lowXT)][j+ abs(lowYT)] == 1) { surroundings++; } }
						if(i+1 <= highXT && j+1 <= highYT) { if (curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 1) { surroundings++; } }
						if(i-1 >= lowXT && j+1 <= highYT) { if (curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 1) { surroundings++; } }
						if(i+1 <= highXT && j-1 >= lowYT) { if (curr[i+1+abs(lowXT)][j-1+ abs(lowYT)] == 1) { surroundings++; } }
						if(i-1 >= lowXT && j-1 >= lowYT) { if (curr[i-1+abs(lowXT)][j-1+ abs(lowYT)] == 1) { surroundings++; } }
						
						if(surroundings == 2) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
						else { next[i+abs(lowXT)][j+ abs(lowYT)] = 3; }
					}
				}
			}
		}
		
		for(int x = 0; x <= abs(lowXT) + abs(highXT); x++)
		{
			for(int y = 0; y <= abs(lowYT) + abs(highYT); y++)
			{
				curr[x][y] = next[x][y];
			}
		}

	}
	
	for(int j = highYT; j >= lowYT; j--)
	{
		for(int i = lowXT; i <= highXT; i++)
		{
			if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 0) { cout << empty; }
			else if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1) { cout << head; }
			else if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 2) { cout << tail; }
			else { cout << wire; }
		}
		cout << "\n";
	}
}


/* Prints elementary file visual to console */
void printElementaryVisual(int gen, lifeFile lf)
{
	char one = lf.get_sOne();
	char zero = lf.get_sZero();
	int lowXT = getLowerBound(lf.get_TxRange());
	int highXT = getUpperBound(lf.get_TxRange());
	int lowYT = getLowerBound(lf.get_TyRange());
	int highYT = getUpperBound(lf.get_TyRange());
	
	cout << "X-Range: " << lowXT << " to " << highXT << "    Y-Range: " << lowYT << " to " << highYT << "    Generation: " << gen << "\n";
	int next[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	int curr[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	coordinates* corrs = lf.getOneCorrArray();
	int rule = lf.get_rule();
	string binary = DecToBin(rule);
	while(binary.length() != 8) { binary = "0" + binary; }
	
	//Initialize grids
	for(int x = 0; x < abs(lowXT) + abs(highXT); x++)
	{
		for(int y = 0; y < abs(lowYT) + abs(highYT); y++)
		{
			curr[x][y] =0;
			next[x][y] =0;
		}
	}
	
	for(int k = 0; k <= gen; k++)
	{
		for(int j = highYT; j >= lowYT; j--)
		{
			for(int i = lowXT; i <= highXT; i++)
			{
				int surroundings = 0;
				/*
					|UL|U|UR|
					|L |X| R|
					|DL|D|DR|
				*/
					
				if(k == 0)
				{	
					for(int a = 0; a < lf.get_oneCount(); a++)
					{
						if(corrs[a].x == i && corrs[a].y == j)
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
						}
						
					//cout << corrs[a].x << " " << corrs[a].y << "\n";
					}
					
				}
				
				else
				{
					if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1)
					{
						next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
					}
					
					else
					{
						if(j+1 <= highYT && i+1 <= highXT && i-1 >= lowXT) 
						{ 
							//000
							if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && binary.at(0) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							//001
							else if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && binary.at(1) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							//010
							else if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && binary.at(2) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							//011
							else if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && binary.at(3) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							//100
							else if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && binary.at(4) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							//101
							else if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 0 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && binary.at(5) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							//110
							else if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 0 && binary.at(6) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							//111
							else if(curr[i-1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+abs(lowXT)][j+1+ abs(lowYT)] == 1 && curr[i+1+abs(lowXT)][j+1+ abs(lowYT)] == 1 && binary.at(7) == 1) 
							{ 
								next[i+abs(lowXT)][j+ abs(lowYT)] = 1;
							}
							else
							{
								next[i+abs(lowXT)][j+ abs(lowYT)] = 0;
							}
						}
						
						else
						{
							next[i+abs(lowXT)][j+ abs(lowYT)] = 0;
						}
					}
				}
			}
		}
		
		for(int x = 0; x <= abs(lowXT) + abs(highXT); x++)
		{
			for(int y = 0; y <= abs(lowYT) + abs(highYT); y++)
			{
				curr[x][y] = next[x][y];
			}
		}
	}
	
	for(int j = highYT; j >= lowYT; j--)
	{
		for(int i = lowXT; i <= highXT; i++)
		{
			if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1) { cout << one; }
			else { cout << zero; }
		}
		cout << "\n";
	}
}


/* Takes in a number and converts it to a binary string. TAKEN FROM STACK OVERFLOW */
string DecToBin(int number)
{
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return DecToBin(number / 2) + "0";
    else
        return DecToBin(number / 2) + "1";
}

/* Takes in a string that contains a range and returns the lower number*/
int getLowerBound(string bounds)
{
	int low = 0;
	char* num = (char*) malloc(sizeof(char*) * 100);
	int i = 0;
	char p = bounds.at(i);
	while(p != '.')
	{
		num[i] = p;
		i++;
		p = bounds.at(i);
	}
	low += atoi(num);
	
	return low;
}

/* Takes in a string that contains a range and returns the higher number*/
int getUpperBound(string bounds)
{
	int high = 0;
	char* num = (char*) malloc(sizeof(char*) * 100);
	int i = 0;
	int j = 0;
	char p = bounds.at(i);
	while(p != '.')
	{
		i++;
		p = bounds.at(i);
	}
	while(p == '.')
	{
		p = bounds.at(i);
		i++;
	}
	while(i < bounds.length())
	{
		num[j] = p;
		p = bounds.at(i);
		j++;
		i++;
	}
	num[j] = p;
	high = atoi(num);
	return high;
}
