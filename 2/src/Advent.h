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
	void commandFormat( std::string p_command, std::vector<std::string>& io_words );
	bool commandInterpret( std::vector<std::string>& p_words );
	
	bool commandTravel( std::string p_word );
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