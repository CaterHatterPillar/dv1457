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
		m_adventurer = Adventurer( ad.map[ adventurerStartingLocation ] );

		m_running = true; // Hack to avoid starting the game if the level hasn't yet been loaded.
	}
}

void Advent::gameLoop() {
	GUI::RenderLocation( m_adventurer.getLocation() );
	// Render objects here.
#ifdef ADVENT_DEBUG
	GUI::RenderString( "DEBUG INFO: \nCurrent location: " + Util::toString( m_adventurer.getLocation().getId() ) + "\n");
#endif // ADVENT_DEBUG
	GUI::RenderTerminal();

	// Aqcuire input:
	std::string input;
	GUI::GetInput( input );

	// Interpret input:
	bool success = commandInterpret( m_formatter.format( input ) );
	if( success==true ) {
#ifndef ADVENT_DEBUG
		GUI::ClearScreen(); // Do not clear screen if in debug-mode.
#endif // ADVENT_DEBUG
	}
}

bool Advent::commandInterpret( std::vector<Verb> p_verbs  ) {
    bool executed = false; // To make sure that one, and only one, modification is made to the game world per command.
    for( unsigned i = 0; i < p_verbs.size() && executed==false; i++ ) {
    	Verb verb = p_verbs[ i ];

    	// Get verb id, which signifies what type of action is to be performed:
    	unsigned verbVal = verb.getId();
    	unsigned verbAction = verbVal / 1000;
    	switch( verbAction ) {
    		case 0: // Denotes travel.
    			executed = commandTravel( verb );
    			break;
    		case 1: // Denotes object.
    			throw ExceptionAdventNotYetImplemented( "Command - Object." );
    			//executed = commandObject( word );
    			break;
    		case 2: // Denotes action.
    			throw ExceptionAdventNotYetImplemented( "Command - Action." );
    			break;
    		case 3: // Denotes special-case.
    			throw ExceptionAdventNotYetImplemented( "Command - Special-case." );
    			break;
    	}
    }

    if( executed==false ) {
    	GUI::RenderText( 2, "Sorry, I could not understand You.", "Use HELP to recieve instructions." );
    }
    return executed;
}
bool Advent::commandTravel( Verb& p_verb ) {
	bool travel = false;
	AdventData& ad = Singleton<AdventData>::get();

	Location location = m_adventurer.getLocation();
	for( unsigned i = 0; i < location.getNumDestinations() && travel==false; i++ ) {
		Destination destination = location[i];
	
		// If the word does not correspond to any word used for travel at the current location - skip to the next destination:
		if( destination.canTravelToUsing( p_verb )==false ) {
			continue;
		}

#ifdef ADVENT_DEBUG
		GUI::RenderString( "DEBUG TRAVEL: \nAttempting travel to: " + Util::toString( destination.getId() ) + "\nTravel would require one of the following verbs:\n" );
		for( unsigned j = 0; j < destination.getVerbs().size(); j++ ) {
			Verb verb = destination.getVerbs()[j];
			GUI::RenderString( "\t" + Util::toString( verb.getId() ) + "\n" );
		}
#endif // ADVENT_DEBUG

		travel = commandTravelToDestination( destination, location );
    	if( travel==true ) {
    		m_adventurer.setLocation( ad.map[ destination.getId() ] );
#ifdef ADVENT_DEBUG
    		GUI::RenderString( "Travelled to: " + Util::toString( m_adventurer.getLocation().getId() ) + "\n" );
#endif // ADVENT_DEBUG
    	}
	}

	return travel;
}
bool Advent::commandTravelToDestination( Destination p_destination, Location p_location ) {
	bool travel = false;

	unsigned x = p_location.getId();		// Current location.
    unsigned y = p_destination.getId();		// Possible location to which one might travel.
    unsigned m = y / 1000; 					// How to travel (might actually not be travel, could even be a goto (!)).
    unsigned n = y % 1000;					// Conditions of travel.

    if( n<=300 ) { // if n<=300 It is the location to go to.
    } else if( (n > 300) && (n<= 500) ) { // if 300<n<=500 n-300 is used in a computed goto to a section of special code.
    	throw ExceptionAdventNotYetImplemented( "Travel - GOTO." );
    } else if( n > 500 ) { // if n>500 Message n-500 from section 6 is printed, and he stays wherever he is.
    	throw ExceptionAdventNotYetImplemented( "Travel - Special-case message." );
    }

    if( m == 0 ) { // if m=0 It's unconditional.
    	travel = true;
    } else if( (m > 0) && (m < 100) ) { // if 0<m<100 It is done with m% probability.
    	throw ExceptionAdventNotYetImplemented( "Travel - Probability." );
    } else if( m == 100 ) { // if m=100 Unconditional, but forbidden to dwarves.
    	throw ExceptionAdventNotYetImplemented( " Travel - Restrictions to dwarves apply." );
    } else if( (m > 100) && (m <= 200) ) { // if 100<m<=200	He must be carrying object m-100.
    	throw ExceptionAdventNotYetImplemented( "Travel - Must carry certain object." );
    } else if( (m > 200) && (m <= 300) ) { // if 200<m<=300	Must be carrying or in same room as m-200.
    	throw ExceptionAdventNotYetImplemented( "Travel - Must be in same room as..." );
    } else if( (m > 300) && (m <= 400) ) { // if 300<m<=400	prop(m mod 100) must *not* be 0.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 0." );
    } else if( (m > 400) && (m <= 500) ) { // if 400<m<=500	prop(m mod 100) must *not* be 1.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 1." );
    } else if( (m > 500) && (m <= 600) ) { // if 500<m<=600	prop(m mod 100) must *not* be 2, etc.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 2, etc." );
    }

    return travel;
}
bool Advent::commandObject( std::string p_word ) {
	std::cout << "Picked up object.";
	return false;
}