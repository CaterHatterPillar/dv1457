#include "ParserDat.h"

#include <string>
#include <sstream>
#include <cstdlib> // atoi
#include <iostream>

enum Sections {
	Sections_LONG_FORM_DESCRIPTIONS 	= 1,
	Sections_SHORT_FORM_DESCRIPTIONS 	= 2,
	Sections_TRAVEL_TABLE 				= 3,
	Sections_VOCABULARY 				= 4,
	Sections_OBJECT_DESCRIPTIONS 		= 5,
	Sections_ARBITRARY_MESSAGES 		= 6,
	Sections_OBJECT_LOCATIONS 			= 7,
	Sections_ACTION_DEFAULTS 			= 8,
	Sections_LIQUID_ASSETS 				= 9,
	Sections_CLASS_MESSAGES 			= 10,
	Sections_HINTS 						= 11,
	Sections_MAGIC_MESSAGES 			= 12
};

ParserDat::ParserDat( std::ifstream& p_ifs, AdventData& io_ad ) {
	m_ifs = &p_ifs;
	m_ad = &io_ad;
}
ParserDat::~ParserDat() {
	// Do nothing.
}

bool ParserDat::init() {
	unsigned int section = Sections_LONG_FORM_DESCRIPTIONS; // Section start.

	std::string line;
	while( std::getline( *m_ifs, line ) ) {
		// Peek first line:
		if( line[0]=='-' ) { // -1 indicates new section.
			std::getline( *m_ifs, line ); // Each '-1' is followed by the coming section. We don't use this number, so get rid of it.
			section++;
			continue;
		}

		std::istringstream ss( line );
		switch( section ) {
			case Sections_LONG_FORM_DESCRIPTIONS:
				parseDesc( ss, m_ad->dataDescLocLong );
				break;
			case Sections_SHORT_FORM_DESCRIPTIONS:
				parseDesc( ss, m_ad->dataDescLocShort );
				break;
			case Sections_TRAVEL_TABLE:
				parseTravelTable( ss );
				break;
			case Sections_VOCABULARY:
				parseVocabulary( ss );
				break;
			case Sections_OBJECT_DESCRIPTIONS:
				//parseDesc( ss, m_ad->dataDescObj );
				// We do not parse objects yet.
				break;
			case Sections_ARBITRARY_MESSAGES:
				parseMsgs( ss, m_ad->dataMsgsArbitrary );
				break;
			case Sections_OBJECT_LOCATIONS:
				parseLocObj( ss );
				break;
			case Sections_ACTION_DEFAULTS:
				parseActionDefaults( ss );
				break;
			case Sections_LIQUID_ASSETS:
				// We're not parsing liquid assets yet.
				// parseLiquidAssets( ss );
				break;
			case Sections_CLASS_MESSAGES:
				parseMsgs( ss, m_ad->dataMsgsClass );
				break;
			case Sections_HINTS:
				break;
			case Sections_MAGIC_MESSAGES:
				break;
		}
	}

	return true; // tmep
}

void ParserDat::parseDesc( std::istringstream& p_ss, std::map<unsigned, std::string>& p_target ) {
	unsigned int key;
	std::string desc;

	p_ss >> key;
	std::getline( p_ss, desc );

	p_target[ key ] = desc;
}
void ParserDat::parseTravelTable( std::istringstream& p_ss ) {
	unsigned x, y, v;

	// Retrieve x (loc) and y (dest), and store them in the travel table.
	p_ss >> x >> y;
	m_ad->dataTravelTable[ x ] = y;

	// Retrieve and store verbs causing travel (the remainder) in the travel-verb struct:
	std::string verb;
    while( std::getline( p_ss, verb, ' ') ) {
    	v = atoi( verb.c_str() );
    	m_ad->dataTravelVerbs[x].push_back( v );
    }
}
void ParserDat::parseVocabulary( std::istringstream& p_ss ) {
	unsigned verbId;
	std::string verbStr;

	// Retrieve and store the verbID - identifying and describing the function of said verb - and it's string representation:
	p_ss >> verbId >> verbStr;
	m_ad->dataVocabulary[ verbId ] = verbStr;
}
void ParserDat::parseMsgs( std::istringstream& p_ss, std::map<unsigned, std::string>& p_map ) {
	unsigned msgId;
	std::string msgStr;

	p_ss >> msgId;
	std::getline( p_ss, msgStr );

	p_map[ msgId ] = msgStr;
}
void ParserDat::parseLocObj( std::istringstream& p_ss ) {
	unsigned obj;
	int l;

	// Get object id in question: 
	p_ss >> obj;

	// Get locations for said object:
	std::string loc;
    while( std::getline( p_ss, loc, '\t' ) ) {
    	if( loc.size() > 0 ) { // Some weird bug caused this method to write a single zero-value at the beginning of each iteration because loc was returned as "". Strange.
    		l = atoi( loc.c_str() );
    		m_ad->dataLocObj[obj].push_back( l );
    	}
    }
}
void ParserDat::parseActionDefaults( std::istringstream& p_ss ) {
	unsigned a, d;

	p_ss >> a >> d;
	m_ad->dataActionDefaults[a] = d;
}
void ParserDat::parseLiquidAssets( std::istringstream& p_ss ) {
	// Do nothing.
}