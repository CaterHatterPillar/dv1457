#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Common.h"
#include "CommonSys.h"
#include "ParserDat.h"

#include "Advent.h"
#include "Snitch.h"

Advent::Advent() {
	m_running = false;
}
Advent::~Advent() {
	// Do nothing.
}

void Advent::load(Result& io_result) {
	AdventData& ad = Singleton<AdventData>::get();

	std::ifstream dat;
	dat.open( filepathAdventdat.c_str(), std::ios_base::in );
	if( dat.is_open()==true ) {
		ParserDat pd( dat, ad );
		pd.init();

		// Initialize player starting position:
		ad.adventurer.adventTravelTo( ad.map[ adventurerStartingLocation ] );

		m_running = true; // Hack to avoid starting the game if the level hasn't yet been loaded.
		syslog(LOG_INFO, "Loaded data file: %s", filepathAdventdat.c_str());
	}
	else {
		syslog(LOG_ERR, "Could not open data file %s", filepathAdventdat.c_str());
	}

// 	GUI::ClearScreen();
// #ifdef ADVENT_DEBUG
// 	GUI::RenderString( "Starting adventure in DEBUG-mode.\n" );
// #endif // ADVENT_DEBUG

	// Render the starting location, then start the game-loop.
	io_result.setSummary(ResFormater::FormatLocation( ad.adventurer.getLocation() ));
}

bool Advent::play( std::string p_in ) {
	AdventData& ad = Singleton<AdventData>::get();

	// Render objects here.
	// GUI::RenderNewLine( s_confTerminalLineSpacing );
	// GUI::RenderTerminal();

	// Interpret input:
	Result result;
	Action* action = m_interpreter.interpret( m_formatter.format( p_in ), result );
	bool success = m_executioner.execute( action, result ); // ToDoIst: make executioner recieve an inout result-argument, so that executioner may also report errors or inconsistensies in the command.

	// Print response if the command was not executed correctly.
//	if( success==false ) {
        Snitch::SendMsg( ad.sockfd, p_in );
// #ifdef ADVENT_DEBUG
//         GUI::RenderString( action->toString() );
// #endif // ADVENT_DEBUG
        // Be sure to print the stored parameters as well.
//	}
	// Don't forget to clean up.
	delete action;

	return m_running;
}

bool Advent::isRunning() const {
	return m_running;
}