#ifndef ADVENT_H
#define ADVENT_H

#include "AdventData.h"

#define ADVENT_DEBUG 1

const static std::string filepathAdventdat = "../advent/advent.dat";

class Advent {
public:
	Advent();
	~Advent();

	void play();
protected:
	void gameLoop();
	void commandFormat( std::string p_command, std::vector<Verb>& io_verbs );
	bool commandInterpret( std::vector<Verb> p_verbs  );
	
	bool commandTravel( Verb& p_verb );
	bool commandTravelToDestination( TravelDestination& p_td, unsigned p_loc );
	bool commandObject( std::string p_word );
private:
	// Game data:
	AdventData m_ad;
	bool m_running;

	// Adventure data:
	unsigned int m_playerLoc;
};

#endif // ADVENT_H