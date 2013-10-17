
all: asm-files
	gcc -o ../SnakeASM_Apocalypse *.o -lcurses -lc

asm-files: c-files
	gcc -c nibbles.S start.S

c-files:
	gcc -c helpers.c main.c

clean:
	rm -f *.o