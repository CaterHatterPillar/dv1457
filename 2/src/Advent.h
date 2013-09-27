#ifndef ADVENT_H
#define ADVENT_H

#include "Adventurer.h"
#include "AdventData.h"

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
	void commandFormat( std::string p_command, std::vector<Verb>& io_verbs );
	bool commandInterpret( std::vector<Verb> p_verbs  );
	
	bool commandTravel( Verb& p_verb );
	bool commandTravelToDestination( Destination p_destination, Location p_location );
	bool commandObject( std::string p_word );
private:
	// Game data:
	AdventData m_ad;
	bool m_running;

	// Adventure data:
	Adventurer m_adventurer;
};

#endif // ADVENT_H