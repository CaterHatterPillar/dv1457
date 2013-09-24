all: main
	g++ -o main *.o

main: advent gui
	g++ -c main.cpp

advent: parser
	g++ -c Advent.h Advent.cpp

parser:
	g++ -c ParserDat.h ParserDat.cpp

gui:
	g++ -c GUI.h GUI.cpp