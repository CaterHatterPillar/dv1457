# ---
all: main
	g++ -o main *.o

main: advent
	g++ -c main.cpp
# ---

advent: common datastructures parser formatter interpreter executioner
	g++ -c Advent.h Advent.cpp

formatter: common
	g++ -c Formatter.h Formatter.cpp

interpreter: common actions result vocabulary
	g++ -c Interpreter.h Interpreter.cpp

executioner: common actions map
	g++ -c GameLogic.h GameLogic.cpp Executioner.h Executioner.cpp

result: common
	g++ -c Result.h Result.cpp

actions: common vocabulary
	g++ -c Action.h Action.cpp ActionFactory.h ActionFactory.cpp

parser: common datastructures
	g++ -c ParserDat.h ParserDat.cpp

datastructures: common map vocabulary player
	g++ -c Singleton.h AdventData.h

player: common map
	g++ -c Inventory.h Inventory.cpp Adventurer.h Adventurer.cpp

map: common vocabulary
	g++ -c Object.h Object.cpp Destination.h Destination.cpp Location.h Location.cpp Map.h Map.cpp

vocabulary: common
	g++ -c Verb.h Verb.cpp Vocabulary.h Vocabulary.cpp

common: clean
	g++ -c GUI.h GUI.cpp Common.h AdventConf.h Util.h Util.cpp ExceptionAdventNotYetImplemented.h

# Clean solution first of all:
clean:
	rm -f *.gch *.o