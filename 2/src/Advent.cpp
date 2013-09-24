#include <string>
#include <fstream>
#include <sstream>
#include <iostream> // tmpe

#include "ParserDat.h"
#include "GUI.h"

#include "Advent.h"

Advent::Advent() {
	m_running = true;

	m_playerLoc = 1; // Player starts at position 1.
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
	GUI::ClearScreen();
	GUI::RenderDescription( 
		m_ad.dataDescLocShort[m_playerLoc], 
		m_ad.dataDescLocLong[m_playerLoc] );

	// Aqcuire input:
	std::string input;
	GUI::GetInput( input );

	// Interpret input:
	interpretCommand( input );
}

void Advent::interpretCommand( std::string& p_command ) {
	// Start by splitting up the command into words:
	std::vector<std::string> words(5);
	std::istringstream ss( p_command );
	while( std::getline( ss, p_command, ' ') ) {
    	words.push_back( p_command );
    }

    // Loop through possible verbs for the current location:
}

// To iterate through maps.
/*typedef std::map<unsigned int, std::string>::iterator it_type;
	for(it_type iterator = ad.dataMsgsClass.begin(); iterator != ad.dataMsgsClass.end(); iterator++) {
		std::cout << std::endl;
		std::cout << iterator->first;
		std::cout << ": ";
		std::cout << iterator->second;
	}*/