#include "ParserDat.h"

#include <string>
#include <sstream>
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
			section++;
			continue;
		}

		std::istringstream ss( line );
		switch( section ) {
			case Sections_LONG_FORM_DESCRIPTIONS:
				parseDescriptionsLong( ss );
				break;
			case Sections_SHORT_FORM_DESCRIPTIONS:
				parseDescriptionsShort( ss );
				break;
			case Sections_TRAVEL_TABLE:
				break;
			case Sections_VOCABULARY:
				break;
			case Sections_OBJECT_DESCRIPTIONS:
				break;
			case Sections_ARBITRARY_MESSAGES:
				break;
			case Sections_OBJECT_LOCATIONS:
				break;
			case Sections_ACTION_DEFAULTS:
				break;
			case Sections_LIQUID_ASSETS:
				break;
			case Sections_CLASS_MESSAGES:
				break;
			case Sections_HINTS:
				break;
			case Sections_MAGIC_MESSAGES:
				break;
		}
	}

	return true; // tmep
}

void ParserDat::parseDescriptionsLong( std::istringstream& p_ss ) {
	unsigned int loc;
	std::string descLong;

	// Get location:
	p_ss >> loc;

	// Get long description (e.g. the remainder):
	std::getline( p_ss, descLong );

	m_ad->dataDescLong[ loc ] = descLong;
}
void ParserDat::parseDescriptionsShort( std::istringstream& p_ss ) {
	unsigned int loc;
	std::string descShort;

	// Get location:
	p_ss >> loc;

	// Get short description (e.g. the remainder):
	std::getline( p_ss, descShort );

	m_ad->dataDescShort[ loc ] = descShort;
}