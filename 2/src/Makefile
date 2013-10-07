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
	g++ -c Executioner.h Executioner.cpp AgentTravel.h AgentTravel.cpp AgentInteract.h AgentInteract.cpp AgentMagic.h AgentMagic.cpp

result: common
	g++ -c Result.h Result.cpp

actions: common vocabulary
	g++ -c Action.h Action.cpp ActionFactory.h ActionFactory.cpp

parser: common datastructures
	g++ -c ParserDat.h ParserDat.cpp

datastructures: common map vocabulary player relations
	g++ -c Singleton.h Letterbox.h Letterbox.cpp AdventData.h

relations: common
	g++ -c Relation.h Relation.cpp Relations.h Relations.cpp

player: common map magic
	g++ -c Inventory.h Inventory.cpp Adventurer.h Adventurer.cpp

magic: common
	g++ -c Magic.h Magic.cpp

map: common vocabulary
	g++ -c Object.h Object.cpp Destination.h Destination.cpp Location.h Location.cpp Map.h Map.cpp

vocabulary: common
	g++ -c Verb.h Verb.cpp Vocabulary.h Vocabulary.cpp

common: clean
	g++ -c GUI.h GUI.cpp Common.h AdventConf.h Util.h Util.cpp ExceptionAdvent.h ExceptionAdventNotYetImplemented.h

# Clean solution first of all:
clean:
	rm -f *.gch *.o