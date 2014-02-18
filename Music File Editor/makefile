all: sndinfo sndconv sndcat sndcut sndshow sndedit

clean:
	rm -f allFunctions.o sndconv.o sndcat.o sndcut.o sndshow.o sndinfo.o sndedit.o sndedit sndinfo sndconv sndcat sndcut sndshow

tarball: CamiWilliamsP1P3.tar.gz

CamiWilliamsP1P3.tar.gz: makefile sndinfo.c sndconv.c sndcat.c sndcut.c sndshow.c sndedit.c allFunctions.h allFunctions.c readme.txt
	tar -czf CamiWilliamsP1P3.tar.gz makefile sndinfo.c sndcat.c sndcut.c sndshow.c sndconv.c sndedit.c allFunctions.h allFunctions.c readme.txt

sndinfo: sndinfo.o allFunctions.o
	gcc -lm -o sndinfo sndinfo.o allFunctions.o 

sndinfo.o:
	gcc -lm -c sndinfo.c

sndconv: sndconv.o allFunctions.o
	gcc -lm -o sndconv sndconv.o allFunctions.o

sndconv.o:
	gcc -lm -c sndconv.c

sndcat: sndcat.o allFunctions.o
	gcc -lm -o sndcat sndcat.o allFunctions.o

sndcat.o:
	gcc -lm -c sndcat.c

sndcut: sndcut.o allFunctions.o
	gcc -lm -o sndcut sndcut.o allFunctions.o

sndcut.o:
	gcc -lm -c sndcut.c

sndshow: sndshow.o allFunctions.o
	gcc -lm -o sndshow sndshow.o allFunctions.o

sndshow.o:
	gcc -lm -c sndshow.c
	
sndedit: sndedit.o allFunctions.o
	gcc -lm -o sndedit sndedit.o -lncurses allFunctions.o

sndedit.o:
	gcc -lm -c sndedit.c

allFunctions.o:
	gcc -lm -c allFunctions.c