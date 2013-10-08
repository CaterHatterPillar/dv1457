#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Common.h"
#include "CommonSys.h"
#include "ParserDat.h"

#include "Advent.h"
#include "Snitch.h"

Advent::Advent( int p_sockfd, std::string p_player ) {
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

bool Advent::load(Result& io_result) {
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
		io_result.setSummary(ResFormater::FormatLocation(m_ad, m_ad.map[ m_ad.adventurer.getIdLocation() ] ));
		syslog(LOG_INFO, "Loaded data file: %s", filepathAdventdat.c_str());
	}
	else {
		syslog(LOG_ERR, "Could not open data file %s", filepathAdventdat.c_str());
	}
	return sucessfulLoad;
}

void Advent::play( std::string p_in ) {
	// Format and interpret input:

	assert(m_formatter);
		syslog(LOG_INFO, "m_formatter successful");
	assert(m_interpreter);
		syslog(LOG_INFO, "m_interpreter successful");
	assert(m_executioner );
		syslog(LOG_INFO, "m_executioner successful");

	Result result;
	syslog(LOG_INFO, "Started Advent::play()");
	Action* action = m_interpreter->interpret( m_formatter->format( p_in ), result );
	syslog(LOG_INFO, "Action interpreted!");
	// Perform interpreted command:
	bool success = m_executioner->execute( action, result );
	syslog(LOG_INFO, "Action executed!");

    Snitch::SendMsg( m_ad.sockfd, result.getSummary() );

	delete action;
}