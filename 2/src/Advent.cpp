#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "GUI.h"
#include "Util.h"
#include "ParserDat.h"
#include "AdventData.h"
#include "ExceptionAdventNotYetImplemented.h"

#include "Advent.h"

Advent::Advent() {
	m_running = false;
}
Advent::~Advent() {
	// Do nothing.
}

void Advent::play() {
	load();

	GUI::ClearScreen();
#ifdef ADVENT_DEBUG
	GUI::RenderString( "Starting adventure in DEBUG-mode.\n" );
#endif // ADVENT_DEBUG
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

	GUI::RenderLocation( ad.adventurer.getLocation() );
	// Render objects here.
	GUI::RenderTerminal();

	// Aqcuire input:
	std::string input;
	GUI::GetInput( input );

	// Interpret input:
	Result result;
	Action* action = m_interpreter.interpret( m_formatter.format( input ), result );
	bool success = m_executioner.execute( action );
	if( success==true ) {
#ifndef ADVENT_DEBUG
		GUI::ClearScreen(); // Do not clear screen if in debug-mode.
#endif // ADVENT_DEBUG
	} else {
		GUI::RenderString( result.getSummary() );
	}
}