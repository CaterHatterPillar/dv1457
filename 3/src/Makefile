
all: asm-files
	gcc -o ../SnakeASM_Apocalypse *.o -lcurses -lc

asm-files: c-files
	gcc -c nibbles.S start.S -g

c-files:
	gcc -c helpers.c main.c -g

clean:
	rm -f *.o