#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream> // temp, be sure to have me removed.

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
	//GUI::ClearScreen();
	GUI::RenderDescription( 
		m_ad.dataDescLocShort[m_playerLoc], 
		m_ad.dataDescLocLong[m_playerLoc] );

	// Aqcuire input:
	std::string input;
	GUI::GetInput( input );

	// Format input:
	std::vector<std::string> words(5);
	commandFormat( input, words );

	// Interpret input:
	commandInterpret( words );
}

void Advent::commandFormat( std::string p_command, std::vector<std::string>& io_words ) {
	// Start by splitting up the command into words:
	std::istringstream ss( p_command );
	while( std::getline( ss, p_command, ' ') ) {
		// Shorten each word to a length of five maximum, as the verbs are stored in that way:
		std::string word = p_command.substr(0, 5); 

		// Filter any words that are not contained within the application vocabulary:
		if( m_ad.dataVocabulary.find( word )!=m_ad.dataVocabulary.end() ) {
			io_words.push_back( word ); 
		}	
    }
}
void Advent::commandInterpret( std::vector<std::string>& p_words ) {
    bool executed = false; // To make sure that one, and only one, modification is made to the game world per command.
    for( unsigned wordIx = 0; wordIx < p_words.size() && executed==false; wordIx++ ) {
    	std::string word = p_words[ wordIx ];

    	// Get value of verb, which signifies what type of action is to be performed:
    	unsigned verbVal = m_ad.dataVocabulary[ word ];
    	unsigned verbAction = verbVal / 1000;
    	switch( verbAction ) {
    		case 0: // Denotes travel.
    			executed = commandTravel( word );
    			break;
    		case 1: // Denotes object.
    			break;
    		case 2: // Denotes action.
    			break;
    		case 3: // Denotes special-case.
    			break;
    	}
    }

    if( executed==false ) {
    	// Interpreter did not understand.
    }
}
bool Advent::commandTravel( std::string p_word ) {
	bool travel = false;
	unsigned int playerLoc = m_playerLoc;

	TravelLocation tl = m_ad.dataTravelTable[ playerLoc ];
	for( unsigned i = 0; i < tl.dests.size() && travel==false; i++ ) {
		TravelDestination td = tl.dests[i];

		// If the word does not correspond to any word used for travel at the current location - skip to the next destination:
		unsigned wordId = m_ad.dataVocabulary[ p_word ];
		if( std::find( td.verbs.begin(), td.verbs.end(), wordId ) == td.verbs.end() ) {
			continue;
		}

		unsigned x = tl.loc;	// Current location.
    	unsigned y = td.dest;	// Possible location to which one might travel.
	    unsigned m = y / 1000; 	// How to travel (might actually not be travel, could even be a goto (!)).
    	unsigned n = y % 1000;	// Conditions of travel.

    	if( n<=300 ) { // if n<=300 It is the location to go to.
    	} else if( (n > 300) && (n<= 500) ) { // if 300<n<=500 n-300 is used in a computed goto to a section of special code.
    	} else if( n > 500 ) { // if n>500 Message n-500 from section 6 is printed, and he stays wherever he is.
    	}

    	if( m == 0 ) { // if m=0 It's unconditional.
    		travel = true;
    	} else if( (m > 0) && (m < 100) ) { // if 0<m<100 It is done with m% probability.
    	} else if( m == 100 ) { // if m=100 Unconditional, but forbidden to dwarves.
    	} else if( (m > 100) && (m <= 200) ) { // if 100<m<=200	He must be carrying object m-100.
    	} else if( (m > 200) && (m <= 300) ) { // if 200<m<=300	Must be carrying or in same room as m-200.
    	} else if( (m > 300) && (m <= 400) ) { // if 300<m<=400	prop(m mod 100) must *not* be 0.
    	} else if( (m > 400) && (m <= 500) ) { // if 400<m<=500	prop(m mod 100) must *not* be 1.
    	} else if( (m > 500) && (m <= 600) ) { // if 500<m<=600	prop(m mod 100) must *not* be 2, etc.
    	}

    	if( travel==true ) {
    		m_playerLoc = y;
    	}
	}

	return travel;
}

/*
std::cout << std::endl << "Current location is: " << playerLoc << std::endl
		<< "The following verbs: ";
		for(unsigned k = 0; k < td.verbs.size(); k++) {
			std::cout << std::endl << td.verbs[k];
		}
		std::cout << std::endl << "will take you to location: " << td.dest;
*/