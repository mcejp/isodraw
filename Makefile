MEMMODEL=-mc

all: isodraw ISODRAW.EXE

clean:
	rm -f isodraw ISODRAW.EXE *.o

isodraw: *.c *.h
	gcc -O3 -ansi -pedantic -Wall -o $@ *.c

ISODRAW.EXE: *.c *.h
	wcl -q -0 -bcl=dos $(MEMMODEL) -fe=$@ *.c
