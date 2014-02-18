#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include <string.h>
#include "functions.hh"

using namespace std;


/**

	Creates the console grid based upon the file
	@author Camryn Williams

*/
int main(int argc, char* argv[])
{
	char* filename;
	bool f, g, tx, ty, v, wx, wy, file; 
	string txr, tyr, wxr, wyr;
	int gen = 0;
	lifeFile life;
	
	for(int i = 0; i < argc; i++)
	{
		/* -h			Display a help screen that describes the program. */
		if(strncmp(argv[i], "-h", 2) == 0)
		{
			cout << "This program reads a single input .life file, either from a pathname passed as an argument, or from standard input if no file names are given as arguments. The following are the accepted switches: \n";
			cout << "-f		Output should be in the same file format as Appendix A. **Shows the properties of the file at generation 0\n";
			cout << "-g n		Specify the desired generation number. If omitted, the default should be n = 0.\n";
			cout << "-tx l::h	Set the x range of the terrain; overrides values specified in the input file.\n";
			cout << "-ty l::h 	Set the y range of the terrain; overrides values specified in the input file.\n";
			cout << "-v 		Output should be visual: an ASCII display of the terrain with appropriate characters for the dead and alive cells. In Figure 4, the dead character is ~ and the alive character is @.\n";
			cout << "-wx l::h 	Set the x range of the output window; otherwise this defaults to the x range of the terrain.\n";
			cout << "-wy l::h 	Set the y range of the output window; otherwise this defaults to the y range of the terrain.\n";
			return 0;
		}
		
		/* -f			Output should be in the same file format as Appendix A. */
		else if(strncmp(argv[i], "-f", 2) == 0) { f = true;	}
		
		/* -g n			Specify the desired generation number. If omitted, the default should be n = 0. */
		else if(strncmp(argv[i], "-g", 2) == 0) { g = true; i++; gen = atoi(argv[i]);}
		
		/* -tx l::h	 	 Set the x range of the terrain; overrides values specified in the input file. */
		else if(strncmp(argv[i], "-tx", 3) == 0) { tx = true; i++; txr = argv[i]; }
		
		/* -ty l::h 	 Set the y range of the terrain; overrides values specified in the input file. */
		else if(strncmp(argv[i], "-ty", 3) == 0) { ty = true; i++; tyr = argv[i]; }
		
		/* -v 			 Output should be visual: an ASCII display of the terrain with appropriate characters for the
						 dead and alive cells. In Figure 4, the dead character is \~" and the alive character is \@". */
		else if(strncmp(argv[i], "-v", 2) == 0) { v = true; }
		
		/* -wx l::h 	  Set the x range of the output window; otherwise this defaults to the x range of the terrain. */
		else if(strncmp(argv[i], "-wx", 3) == 0) { wx = true; i++; wxr = argv[i]; }
		
		/* -wy l::h 	  Set the y range of the output window; otherwise this defaults to the y range of the terrain. */
		else if(strncmp(argv[i], "-wy", 3) == 0) { wy = true; i++; wyr = argv[i]; }
		
		/* file */
		else { file = true; filename = argv[i]; }
	}
	
	if(!file)
	{
		cin >> filename;
	}
	
	string type = life.parseFile(filename);
	
	if(f && v)
	{
		cerr << "Error, cannot do -f and -v \n";
		return 0;
	}
	
	if(wx) { life.set_WxRange(wxr); }
	if(wy) { life.set_WyRange(wyr); }
	if(tx) { life.set_TxRange(txr); }
	if(ty) { life.set_TyRange(tyr); }
	
	if(f)
	{
		if(type == "Life")
		{
			cout << "Life = \n { \n   Name = \"" << life.get_name() << "\"; \n \n   Terrain = { \n     Xrange = " << life.get_TxRange() << ";\n     Yrange = " << life.get_TyRange() << ";\n   };\n \n   Chars = {\n     Alive = " << life.get_sAlive() << ";\n     Dead = " << life.get_sDead() << ";\n    };\n\n   Colors = {\n     Alive = " << life.get_cAlive() << ";\n     Dead = " << life.get_cDead() << ";\n   }; \n\n   Initial = { \n     Alive = " << life.getLifeCorrString() << ";\n   };\n};\n";
		}
		else if (type == "WireWorld")
		{
			cout << "WireWorld = \n { \n   Name = \"" << life.get_name() << "\"; \n \n   Terrain = { \n     Xrange = " << life.get_TxRange() << ";\n     Yrange = " << life.get_TyRange() << ";\n   };\n \n   Chars = {\n     Empty = " << life.get_sEmpty() << ";          Head = " << life.get_sHead() << ";\n     Tail = " << life.get_sTail() << ";          Wire = " << life.get_sWire() << ";\n    };\n\n   Colors = {\n     Empty = " << life.get_cEmpty() << ";          Head = " << life.get_cHead() << ";\n     Tail = " << life.get_cTail() << ";          Wire = " << life.get_cWire() << ";\n   }; \n\n   Initial = { \n     Head = " << life.getHeadCorrString() << ";\n     Tail = " << life.getTailCorrString() << ";\n     Wire = " << life.getWireCorrString() << ";\n   };\n};\n";
		}
		else if(type == "Elementary")
		{
			cout << "Elementary = \n { \n   Name = \"" << life.get_name() << "\"; \n \n   Terrain = { \n     Xrange = " << life.get_TxRange() << ";\n     Yrange = " << life.get_TyRange() << ";\n   };\n \n   Chars = {\n     Zero = " << life.get_sZero() << ";\n     One = " << life.get_sOne() << ";\n    };\n\n   Colors = {\n     Zero = " << life.get_cZero() << ";\n     One = " << life.get_cOne() << ";\n   }; \n\n   Initial = { \n     One = " << life.getOneCorrString() << ";\n   };\n};\n";
		}
		else
		{
			cerr << "Error, unable to open file \n";
			return 0;
		}
	}
	
	if(v)
	{
		if(type == "Life")
		{
			printLifeVisual(gen, life);
		}
		else if (type == "WireWorld")
		{
			printWireWorldVisual(gen, life);
		}
		else if(type == "Elementary")
		{
			printElementaryVisual(gen, life);
		}
		else
		{
			cerr << "Error, unable to open file \n";
			return 0;
		}
	}
	
	return 0;
}
