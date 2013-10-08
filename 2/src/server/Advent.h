#ifndef ADVENT_H
#define ADVENT_H

#include <string>

#include "Formatter.h"
#include "AdventData.h"
#include "Interpreter.h"
#include "Executioner.h"

#define ADVENT_DEBUG 1

const static std::string filepathAdventdat = "/var/cave/advent.dat";
const static unsigned adventurerStartingLocation = 1;

class Advent {
public:
	Advent( int p_sockfd, std::string p_player );
	~Advent();


	bool load(Result& io_result);

	void play( std::string p_in );
	bool isRunning() const;
protected:
private:
	AdventData m_ad;

	Formatter*		m_formatter;
	Interpreter* 	m_interpreter;
	Executioner* 	m_executioner;
};

#endif // ADVENT_H