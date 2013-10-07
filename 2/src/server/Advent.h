#ifndef ADVENT_H
#define ADVENT_H

#include "Formatter.h"
#include "Adventurer.h"
#include "Interpreter.h"
#include "Executioner.h"

#define ADVENT_DEBUG 1

const static std::string filepathAdventdat = "../advent/advent.dat";
const static unsigned adventurerStartingLocation = 1;

class Advent {
public:
	Advent();
	~Advent();

	void load();
	bool play( std::string p_in );
protected:
private:
	Formatter	m_formatter;
	Interpreter m_interpreter;
	Executioner m_executioner;

	bool m_running;
};

#endif // ADVENT_H