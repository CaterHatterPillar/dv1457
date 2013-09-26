all: main
	g++ -o main *.o

main: advent gui
	g++ -c main.cpp

advent: parser error util
	g++ -c Advent.h Advent.cpp

parser: util
	g++ -c ParserDat.h ParserDat.cpp

gui:
	g++ -c GUI.h GUI.cpp

error:
	g++ -c ExceptionAdventNotYetImplemented.h

util:
	g++ -c Util.h Util.cpp