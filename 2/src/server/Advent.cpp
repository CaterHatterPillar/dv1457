#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Common.h"
#include "ParserDat.h"

#include "Advent.h"

Advent::Advent( int p_sockfd, std::string p_player ) {
	m_running = false;

	m_ad.sockfd = p_sockfd;
	m_ad.player = p_player;

	m_formatter		= NULL;
	m_interpreter	= NULL;
	m_executioner	= NULL;
}
Advent::~Advent() {
	assert( m_formatter		);
	assert( m_interpreter 	);
	assert( m_executioner 	);

	delete m_formatter;
	delete m_interpreter;
	delete m_executioner;
}

bool Advent::load() {
	bool sucessfulLoad = false;

	std::ifstream dat;
	dat.open( filepathAdventdat.c_str(), std::ios_base::in );
	if( dat.is_open()==true ) {
		ParserDat pd( dat, m_ad );
		pd.init();
		sucessfulLoad = true;
	}
	if( sucessfulLoad==true ) {
		m_formatter		= new Formatter( m_ad );
		m_interpreter 	= new Interpreter();
		m_executioner 	= new Executioner( m_ad );

		// Initialize player starting position:
		m_ad.adventurer.adventTravelTo( adventurerStartingLocation );
		// Render the starting location, then start the game-loop.
		GUI::RenderLocation( m_ad, m_ad.map[ m_ad.adventurer.getIdLocation() ] );
		m_running = true;
	}
	return sucessfulLoad;
}

bool Advent::play( std::string p_in ) {
	// Format and interpret input:
	Result result;
	Action* action = m_interpreter->interpret( m_formatter->format( p_in ), result );
	// Perform interpreted command:
	bool success = m_executioner->execute( action, result );

	// Print response if the command was not executed correctly.
	if( success==false ) {
        GUI::RenderString( m_ad, result.getSummary() ); 
        // Also consider printing: Parameters in result, action->toString
	}
	delete action; // Don't forget to clean up.

	return m_running;
}