/* Struct */
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


/*Variables*/
char* file;
char duration[10];

int offset_i;
int blockSize_i;


/*Functions*/
struct file getFileInfo(char* filepath, FILE* f);

/* Reads a .cs229 file line by line */
struct file get229Info(struct file input);

/* Prints the proper information for sndinfo */
void printInformation(struct file input);

/*Reads a .aiff file and appends values to variables accordingly */
struct file getASCIIInfo(struct file input);

/*Gets the duration of a file for sndinfo */
int getDuration(struct file input);

/*Finds the index of an element (taken from stack overflow example)*/
int find_index(int* a, int num_elements, int value);

/*Converts filetypes for sndconv*/
void convert(struct file input, FILE* f, int type);

/*Prints the ASCII art for sndshow*/
void getASCIIArt(int width, int zoom, int c, struct file input);

/*Merges the input files*/
struct file concatenate(struct file input[], int count);

/*Removes the range set*/
struct file removeRange(int lows[], int highs[], int numRanges, struct file input);

/*Compares the sets of highs and lows*/
int inRange(int position, int *lows, int *highs, int numRanges);

/*Gets max data from startData*/
int findMaxData(int* startData, int size);

/*Saves changes of the file*/
void saveFile(struct file input);

/*Gets min data from startData*/
int findMinData(int* startData, int size);

/* Function found at (http://aifftools.sourceforge.net/libaiff/)  */
void ieee754_write_extended(double in, uint8_t* out);

/* Function found at (http://aifftools.sourceforge.net/libaiff/)  */
double ieee754_read_extended(uint8_t* in);