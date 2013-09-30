# ---
all: main
	g++ -o main *.o

main: advent gui
	g++ -c main.cpp
# ---

advent: datastructures parser error util formatter interpreter executioner
	g++ -c Advent.h Advent.cpp

formatter: error
	g++ -c Formatter.h Formatter.cpp

interpreter: actions result vocabulary util error
	g++ -c Interpreter.h Interpreter.cpp

executioner: actions map error
	g++ -c GameLogic.h GameLogic.cpp Executioner.h Executioner.cpp

result:
	g++ -c Result.h Result.cpp

actions: vocabulary
	g++ -c Action.h Action.cpp ActionFactory.h ActionFactory.cpp

parser: datastructures util
	g++ -c ParserDat.h ParserDat.cpp

datastructures: map vocabulary
	g++ -c Singleton.h AdventData.h Adventurer.h Adventurer.cpp

map: vocabulary
	g++ -c Object.h Object.cpp Destination.h Destination.cpp Location.h Location.cpp Map.h Map.cpp

vocabulary: util
	g++ -c Verb.h Verb.cpp Vocabulary.h Vocabulary.cpp

# Utilities and such
gui:
	g++ -c GUI.h GUI.cpp

error:
	g++ -c ExceptionAdventNotYetImplemented.h

util:
	g++ -c Util.h Util.cpp