#include "Advent.h"

#include <string>
#include <fstream>

#include "ParserDat.h"

Advent::Advent() {
	m_running = true;
}
Advent::~Advent() {
	// Do nothing.
}

void Advent::play() {
	std::ifstream dat;
	dat.open( filepathAdventdat.c_str(), std::ios_base::in );
	if( dat.is_open()==true ) {
		ParserDat pd( dat, m_ad );
		bool success = pd.init(); // Not yet indicating success. Consider removing.
	}

	while( m_running==true ) {
		gameLoop();
	}
}

void Advent::gameLoop() {

}

// To iterate through maps.
/*typedef std::map<unsigned int, std::string>::iterator it_type;
	for(it_type iterator = ad.dataMsgsClass.begin(); iterator != ad.dataMsgsClass.end(); iterator++) {
		std::cout << std::endl;
		std::cout << iterator->first;
		std::cout << ": ";
		std::cout << iterator->second;
	}*/