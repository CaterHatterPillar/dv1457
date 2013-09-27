#ifndef ADVENT_H
#define ADVENT_H

#include "Formatter.h"
#include "Adventurer.h"

#define ADVENT_DEBUG 1

const static std::string filepathAdventdat = "../advent/advent.dat";
const static unsigned adventurerStartingLocation = 1;

class Advent {
public:
	Advent();
	~Advent();

	void play();
protected:
	void load();
	void gameLoop();
	bool commandInterpret( std::vector<Verb> p_verbs  );
	
	bool commandTravel( Verb& p_verb );
	bool commandTravelToDestination( Destination p_destination, Location p_location );
	bool commandObject( std::string p_word );
private:
	bool m_running;
	Formatter m_formatter;

	Adventurer m_adventurer; // Game data, considering storing in seperate class.
};

#endif // ADVENT_H