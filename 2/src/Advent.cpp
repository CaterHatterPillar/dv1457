#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Common.h"
#include "ParserDat.h"

#include "Advent.h"

Advent::Advent() {
	m_running = false;
}
Advent::~Advent() {
	// Do nothing.
}

void Advent::play() {
	AdventData& ad = Singleton<AdventData>::get();

	// Load the game's .dat-file:
	load();

	GUI::ClearScreen();
#ifdef ADVENT_DEBUG
	GUI::RenderString( "Starting adventure in DEBUG-mode.\n" );
#endif // ADVENT_DEBUG

	// Render the starting location, then start the game-loop.
	GUI::RenderLocation( ad.adventurer.getLocation() );
	while( m_running==true ) {
		gameLoop();
	}
}

void Advent::load() {
	AdventData& ad = Singleton<AdventData>::get();

	std::ifstream dat;
	dat.open( filepathAdventdat.c_str(), std::ios_base::in );
	if( dat.is_open()==true ) {
		ParserDat pd( dat, ad );
		pd.init();

		// Initialize player starting position:
		ad.adventurer.setLocation( ad.map[ adventurerStartingLocation ] );

		m_running = true; // Hack to avoid starting the game if the level hasn't yet been loaded.
	}
}

void Advent::gameLoop() {
	AdventData& ad = Singleton<AdventData>::get();

	// Render objects here.
	GUI::RenderNewLine( s_confTerminalLineSpacing );
	GUI::RenderTerminal();

	// Aqcuire input:
	std::string input;
	GUI::GetInput( input );

	// Interpret input:
	Result result;
	Action* action = m_interpreter.interpret( m_formatter.format( input ), result );
	bool success = m_executioner.execute( action, result ); // ToDoIst: make executioner recieve an inout result-argument, so that executioner may also report errors or inconsistensies in the command.

	// Print response if the command was not executed correctly.
	if( success==false ) {
        GUI::RenderString( result.getSummary() );
        // Be sure to print the stored parameters as well.
	}
}