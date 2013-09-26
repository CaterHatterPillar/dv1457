# ---
all: main
	g++ -o main *.o

main: advent gui
	g++ -c main.cpp
# ---

advent: datastructures parser error util
	g++ -c Advent.h Advent.cpp

parser: datastructures util
	g++ -c ParserDat.h ParserDat.cpp

datastructures: map vocabulary
	g++ -c AdventData.h

map: 
	g++ -c Location.h Location.cpp Map.h Map.cpp

vocabulary:
	g++ -c Verb.h Verb.cpp Vocabulary.h Vocabulary.cpp

# Utilities and such
gui:
	g++ -c GUI.h GUI.cpp

error:
	g++ -c ExceptionAdventNotYetImplemented.h

util:
	g++ -c Util.h Util.cpp