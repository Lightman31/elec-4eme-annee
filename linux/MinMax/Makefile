all: main

minmax: minmax.c
	gcc -c minmax.c -o minmax.o

main: minmax main.c
	gcc minmax.o main.c -o main.bin

clean: rm -rf *.o
