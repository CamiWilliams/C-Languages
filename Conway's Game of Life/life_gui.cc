#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QtCore>

#include <string.h>
#include "functions.hh"

using namespace std;


/**

	Creates the GUI based upon the file
	@author Camryn Williams

*/
int main(int argc, char* argv[])
{
    char* filename;
	bool tx = false;
	bool ty = false;
	bool wx = false;
	bool wy = false; 
	bool controls = false;
	string txr, tyr, wxr, wyr;
	int gen = 0;
	int size = 10;
	lifeFile life;
	bool file = false;
	
	for(int i = 0; i < argc; i++)
	{
		if(strncmp(argv[i], "-h", 2) == 0)
		{
			cout << "This program reads a single input .life file, either from a pathname passed as an argument, or from standard input if no file names are given as arguments. The following are the accepted switches: \n";
			cout << "-g n		Specify the desired generation number. If omitted, the default should be n = 0.\n";
			cout << "-tx l::h	Set the x range of the terrain; overrides values specified in the input file.\n";
			cout << "-ty l::h 	Set the y range of the terrain; overrides values specified in the input file.\n";
			cout << "-s n 		Specify the size, in pixels, of each square in the grid (default is 10). Grid lines omitted when size is less than 4.";
			cout << "-wx l::h 	Set the x range of the output window; otherwise this defaults to the x range of the terrain.\n";
			cout << "-wy l::h 	Set the y range of the output window; otherwise this defaults to the y range of the terrain.\n";
			//cout << "***NOTE: The visual representation takes the pixels and scales them by 5 to be more pleasing to the eye ;)*** \n";
			return 0;
		}
		
		else if(strncmp(argv[i], "-g", 2) == 0) { i++; gen = atoi(argv[i]);}
		
		else if(strncmp(argv[i], "-tx", 3) == 0) { tx = true; i++; txr = argv[i]; }
		
		else if(strncmp(argv[i], "-ty", 3) == 0) { ty = true; i++; tyr = argv[i]; }
		
		else if(strncmp(argv[i], "-s", 2) == 0) { i++; size = atoi(argv[i]); }
		
		else if(strncmp(argv[i], "-c", 2) == 0) { controls = true; }
		
		else if(strncmp(argv[i], "-wx", 3) == 0) { wx = true; i++; wxr = argv[i]; }
		
		else if(strncmp(argv[i], "-wy", 3) == 0) { wy = true; i++; wyr = argv[i]; }
		
		else { file = true; filename = argv[i]; }
	}
	
	if(!file)
	{
		cin >> filename;
	}
	
	string type = life.parseFile(filename);
	
	if(wx == true) { life.set_WxRange(wxr); }
	if(wy == true) { life.set_WyRange(wyr); }
	if(tx == true) { life.set_TxRange(txr); }
	if(ty == true) { life.set_TyRange(tyr); }

	int lowXT = getLowerBound(life.get_TxRange());
	int highXT = getUpperBound(life.get_TxRange());
	int lowYT = getLowerBound(life.get_TyRange());
	int highYT = getUpperBound(life.get_TyRange());
	int lowXW = getLowerBound(life.get_WxRange());
	int highXW = getUpperBound(life.get_WxRange());
	int lowYW = getLowerBound(life.get_TyRange());
	int highYW = getUpperBound(life.get_TyRange());
	
	int next[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	int curr[abs(lowXT) + abs(highXT)][abs(lowYT) + abs(highYT)];
	
	int x = (1+ abs(lowXW) + abs(highXW));
	int y = (1+ abs(lowYW) + abs(highYW));
	
	for(int x = 0; x < abs(lowXT) + abs(highXT); x++)
	{
		for(int y = 0; y < abs(lowYT) + abs(highYT); y++)
		{
			curr[x][y] =0;
			next[x][y] =0;
		}
	}
	
	//Setting up life grid (same implementation as printLifeVisual without printing)
	if(type == "Life")
	{
		coordinates* corrs = life.getLifeCorrArray();
		for(int k = 0; k <= gen; k++)
		{
			for(int j = highYT; j >= lowYT; j--)
			{
				for(int i = lowXT; i <= highXT; i++)
				{
					int surroundings = 0;
		
					if(k == 0)
					{	
						for(int a = 0; a < life.get_lifeCount(); a++)
						{
							if(corrs[a].x == i && corrs[a].y == j) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
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
							if(surroundings == 2) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
							else if(surroundings == 3) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
							else if(surroundings > 3) { next[i+abs(lowXT)][j+ abs(lowYT)] = 0; }
							else if(surroundings < 2) { next[i+abs(lowXT)][j+ abs(lowYT)] = 0; }
							else { next[i+abs(lowXT)][j+ abs(lowYT)] = 0; }
						}
		 
						else
						{
							if(surroundings == 3) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
							else { next[i+abs(lowXT)][j+ abs(lowYT)] = 0; }
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
	}
	
	//Setting up wireworld grid (same implementation as printWireWorld without printing)
	else if (type == "WireWorld")
	{
		coordinates* headCorr = life.getHeadCorrArray();
		coordinates* tailCorr = life.getTailCorrArray();
		coordinates* wireCorr = life.getWireCorrArray();
			
		for(int k = 0; k <= gen; k++)
		{
			for(int j = highYT; j >= lowYT; j--)
			{
				for(int i = lowXT; i <= highXT; i++)
				{		
					if(k == 0)
					{	
						for(int a = 0; a < life.get_headCount(); a++)
						{
							if(headCorr[a].x == i && headCorr[a].y == j) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
						}
			
						for(int b = 0; b < life.get_tailCount(); b++)
						{
							if(tailCorr[b].x == i && tailCorr[b].y == j) { next[i+abs(lowXT)][j+ abs(lowYT)] = 2; }
						}
			
						for(int c = 0; c < life.get_wireCount(); c++)
						{
							if(wireCorr[c].x == i && wireCorr[c].y == j) { next[i+abs(lowXT)][j+ abs(lowYT)] = 3; }
						}
					}
				
					else
					{
						if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 0) { next[i+abs(lowXT)][j+ abs(lowYT)] = 0; }
						else if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1) { next[i+abs(lowXT)][j+ abs(lowYT)] = 2; }
						else if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 2) { next[i+abs(lowXT)][j+ abs(lowYT)] = 3; }
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
	}
	
	//Setting up elementary grid (same implementation as printElementary without printing)
	else if(type == "Elementary")
	{
		coordinates* corrs = life.getOneCorrArray();
		int rule = life.get_rule();
		string binary = DecToBin(rule);
		while(binary.length() != 8) { binary = "0" + binary; }
	
		for(int k = 0; k <= gen; k++)
		{
			for(int j = highYT; j >= lowYT; j--)
			{
				for(int i = lowXT; i <= highXT; i++)
				{
					int surroundings = 0;
		
					if(k == 0)
					{	
						for(int a = 0; a < life.get_oneCount(); a++)
						{
							if(corrs[a].x == i && corrs[a].y == j) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
						}
					}
		
					else
					{
						if(curr[i+abs(lowXT)][j+ abs(lowYT)] == 1) { next[i+abs(lowXT)][j+ abs(lowYT)] = 1; }
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
								else { next[i+abs(lowXT)][j+ abs(lowYT)] = 0; }
							}
						
							else { next[i+abs(lowXT)][j+ abs(lowYT)] = 0; }
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
	}
	
	else
	{
		cerr << "Error, unable to open file \n";
		return 0;
	}
	

	//If no controls, just set up grid and exit program
	if(!controls)
	{
		QApplication app(argc,argv);
		QGraphicsScene scene;
		QGraphicsView view(&scene);
		view.setFixedSize(x*size + x, y*size + y);

		for(int j = 0; j <= abs(lowYT) + abs(highYT); j++)
		{
			for(int i = 0; i <= abs(lowXT) + abs(highXT); i++)
			{
				QGraphicsRectItem* cell = new QGraphicsRectItem(i*size,-1*j*size,size,size);
				if(type == "WireWorld")
				{
					if(curr[i][j] == 0)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cEmpty()), life.get_RGB2(life.get_cEmpty()), life.get_RGB3(life.get_cEmpty())))); //change these to your variables for colors of alive and dead
					}
					else if(curr[i][j] == 1)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cHead()), life.get_RGB2(life.get_cHead()), life.get_RGB3(life.get_cHead()))));
					}
					else if(curr[i][j] == 2)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cTail()), life.get_RGB2(life.get_cTail()), life.get_RGB3(life.get_cTail())))); //change these to your variables for colors of alive and dead
					}
					else
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cWire()), life.get_RGB2(life.get_cWire()), life.get_RGB3(life.get_cWire()))));
					}
				}
				else if(type == "Elementary")
				{
					if(curr[i][j] == 1)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cOne()), life.get_RGB2(life.get_cOne()), life.get_RGB3(life.get_cOne())))); //change these to your variables for colors of alive and dead
					}
					else
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cZero()), life.get_RGB2(life.get_cZero()), life.get_RGB3(life.get_cZero()))));
					}
				}
				else
				{
					if(curr[i][j] == 1)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cAlive()), life.get_RGB2(life.get_cAlive()), life.get_RGB3(life.get_cAlive())))); //change these to your variables for colors of alive and dead
					}
					else
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cDead()), life.get_RGB2(life.get_cDead()), life.get_RGB3(life.get_cDead()))));
					}
				}
			
				scene.addItem(cell);
			}
		}
    
		view.setWindowTitle(life.get_name().c_str());
		view.show();
	}
	
	//If there are controls...
	else
	{
		QApplication app(argc,argv);
		QGraphicsScene scene;
		QGraphicsView view(&scene);
	
		view.setFixedSize(x*size + x, y*size + y);

		for(int j = 0; j <= abs(lowYT) + abs(highYT); j++)
		{
			for(int i = 0; i <= abs(lowXT) + abs(highXT); i++)
			{
				QGraphicsRectItem* cell = new QGraphicsRectItem(i*size,-1*j*size,size,size);
				if(type == "WireWorld")
				{
					if(curr[i][j] == 0)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cEmpty()), life.get_RGB2(life.get_cEmpty()), life.get_RGB3(life.get_cEmpty())))); //change these to your variables for colors of alive and dead
					}
					else if(curr[i][j] == 1)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cHead()), life.get_RGB2(life.get_cHead()), life.get_RGB3(life.get_cHead()))));
					}
					else if(curr[i][j] == 2)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cTail()), life.get_RGB2(life.get_cTail()), life.get_RGB3(life.get_cTail())))); //change these to your variables for colors of alive and dead
					}
					else
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cWire()), life.get_RGB2(life.get_cWire()), life.get_RGB3(life.get_cWire()))));
					}
				}
				else if(type == "Elementary")
				{
					if(curr[i][j] == 1)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cOne()), life.get_RGB2(life.get_cOne()), life.get_RGB3(life.get_cOne())))); //change these to your variables for colors of alive and dead
					}
					else
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cZero()), life.get_RGB2(life.get_cZero()), life.get_RGB3(life.get_cZero()))));
					}
				}
				else
				{
					if(curr[i][j] == 1)
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cAlive()), life.get_RGB2(life.get_cAlive()), life.get_RGB3(life.get_cAlive())))); //change these to your variables for colors of alive and dead
					}
					else
					{
						cell -> setBrush(QBrush(QColor::fromRgb(life.get_RGB1(life.get_cDead()), life.get_RGB2(life.get_cDead()), life.get_RGB3(life.get_cDead()))));
					}
				}
			
				scene.addItem(cell);
			}
		}
    
		view.setWindowTitle(life.get_name().c_str());
	
		view.show();
	
		QWidget *window = new QWidget;
		window -> setWindowTitle("Controls");

		QVBoxLayout *layout = new QVBoxLayout;
		QHBoxLayout *gridLayout = new QHBoxLayout;
		QHBoxLayout *delayLayout = new QHBoxLayout;
		QHBoxLayout *genLayout = new QHBoxLayout;
		QHBoxLayout *buttonsLayout = new QHBoxLayout;

		QLabel *space = new QLabel(" ");

		QLabel *gridLabel = new QLabel("Grid size: ");
		QSpinBox *gridSizeSpinBox = new QSpinBox;
		QSlider *gridSizeSlider = new QSlider(Qt::Horizontal);
		gridSizeSpinBox->setRange(0, 50);
		gridSizeSlider->setRange(0, 50);
		QObject::connect(gridSizeSpinBox, SIGNAL(valueChanged(int)), gridSizeSlider, SLOT(setValue(int)));
		QObject::connect(gridSizeSlider, SIGNAL(valueChanged(int)), gridSizeSpinBox, SLOT(setValue(int)));
		gridSizeSpinBox->setValue(10);

		QLabel *delayLabel = new QLabel("Delay size: ");
		QSpinBox *delaySpinBox = new QSpinBox;
		QSlider *delaySlider = new QSlider(Qt::Horizontal);
		delaySpinBox->setRange(0, 1000);
		delaySlider->setRange(0, 1000);		
		QObject::connect(delaySpinBox, SIGNAL(valueChanged(int)), delaySlider, SLOT(setValue(int)));
		QObject::connect(delaySlider, SIGNAL(valueChanged(int)), delaySpinBox, SLOT(setValue(int)));
		delaySpinBox->setValue(0);

		QLabel *genLabel = new QLabel("Generation      ");
		QLabel *genNum = new QLabel(" ");
		genNum->setText(QString("%1").arg(gen, 2, 10, QChar('0')));
	
		QPushButton *quitButton = new QPushButton("Quit");
		QObject::connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));
		QPushButton *restartButton = new QPushButton("Restart");
		QObject::connect(restartButton, SIGNAL(clicked()), &app, SLOT(quit()));
		QPushButton *playButton = new QPushButton("Play");
		QObject::connect(playButton, SIGNAL(clicked()), &app, SLOT(quit()));
		QPushButton *stepButton = new QPushButton("Step");
		QObject::connect(stepButton, SIGNAL(clicked()), &app, SLOT(quit()));

		gridLayout->addWidget(gridLabel);
		gridLayout->addWidget(gridSizeSpinBox);
		gridLayout->addWidget(gridSizeSlider);
		gridLayout->addWidget(space);

		delayLayout->addWidget(delayLabel);
		delayLayout->addWidget(delaySpinBox);
		delayLayout->addWidget(delaySlider);
		delayLayout->addWidget(space);

		genLayout->addWidget(genLabel);
		genLayout->addWidget(genNum);
		genLayout->addWidget(space);

		buttonsLayout->addWidget(quitButton);
		buttonsLayout->addWidget(restartButton);
		buttonsLayout->addWidget(playButton);
		buttonsLayout->addWidget(stepButton);
		buttonsLayout->addWidget(space);

		layout->addLayout(gridLayout);
		layout->addLayout(delayLayout);
		layout->addLayout(genLayout);
		layout->addLayout(buttonsLayout);

		window -> setLayout(layout);
		window -> show();
		
		
		
		
		return app.exec();
	}
	return 0;
}


