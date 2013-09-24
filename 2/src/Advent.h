#ifndef ADVENT_H
#define ADVENT_H

#include "AdventData.h"

const static std::string filepathAdventdat = "../advent/advent.dat";

class Advent {
public:
	Advent();
	~Advent();

	void play();
protected:
	void gameLoop();
	void interpretCommand( std::string& p_command );
private:
	// Game data:
	AdventData m_ad;
	bool m_running;

	// Adventure data:
	unsigned int m_playerLoc;
};

#endif // ADVENT_H