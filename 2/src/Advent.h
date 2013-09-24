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
private:
	AdventData m_ad;
	bool m_running;
};

#endif // ADVENT_H