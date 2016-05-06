isodraw: *.c *.h
	gcc -O3 -ansi -pedantic -Wall -o $@ *.c
