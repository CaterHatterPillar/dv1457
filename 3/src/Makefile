
all: source
	gcc -o ../SnakeASM_Apocalypse *.o -lcurses -lc

source:
	gcc -c nibbles.S start.S helpers.c main.c -Os

clean:
	rm -f *.o