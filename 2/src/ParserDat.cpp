#include <string>
#include <sstream>

#include "Util.h"
#include "ParserDat.h"

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

void ParserDat::init() {
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
				parseDescLong( ss );
				break;
			case Sections_SHORT_FORM_DESCRIPTIONS:
				parseDescShort( ss );
				break;
			case Sections_TRAVEL_TABLE:
				parseTravelTable( ss );
				break;
			case Sections_VOCABULARY:
				parseVocabulary( ss );
				break;
			case Sections_OBJECT_DESCRIPTIONS:
				parseObjDesc( ss );
				break;
			case Sections_ARBITRARY_MESSAGES:
				parseMsgs( ss, m_ad->dataMsgsArbitrary );
				break;
			case Sections_OBJECT_LOCATIONS:
				parseObjLoc( ss );
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

	compileDependantData();
}
void ParserDat::compileDependantData() {
	for( unsigned i = 0; i < m_travelDescs.size(); i++ ) {
		TravelDesc td = m_travelDescs[ i ];

		Destination d( td.dest );
		for( unsigned j = 0; j < td.verbIds.size(); j++ ) {
			unsigned verbId = td.verbIds[ j ];
			d.appendVerb( m_ad->vocabulary[ verbId ] );
		}
		m_ad->map[ td.loc ].appendDestination( d );
	}
}

void ParserDat::parseDescLong( std::istringstream& p_ss ) {
	unsigned int key;
	std::string descLong;

	p_ss >> key;
	std::getline( p_ss, descLong );

	m_ad->map[ key ].appendDescLong( descLong ); //m_ad->dataDescLocLong[ key ].push_back( desc );
}
void ParserDat::parseDescShort( std::istringstream& p_ss ) {
	unsigned int key;
	std::string descShort;

	p_ss >> key;
	std::getline( p_ss, descShort );

	m_ad->map[ key ].setDescShort( descShort ); //m_ad->dataDescLocShort[ key ] = desc;
}
void ParserDat::parseTravelTable( std::istringstream& p_ss ) {
	unsigned x, y, v;

	// Retrieve x (loc) and y (dest), and store them in the travel table.
	p_ss >> x >> y;

	// Retrieve and store verbs causing travel (the remainder) in the travel-verb struct:
	std::string verbId;
	std::vector<unsigned> verbIds;
    while( std::getline( p_ss, verbId, '\t') ) {
    	if( verbId.size() > 0 ) {
    		v = Util::toInt( verbId.c_str() );
    		verbIds.push_back( v );
    	}
    }

    // At this point we've collected the relevant location, the destination and the verb ids that allows travel to this point.
    // This is all we need to add a Destination-object to said location. However, the verbs have not yet been loaded at this point.
    // Thus, we'd like to store some kind of temporary object which will allow us to add these destinations when all the verbs have 
    // been read.
    TravelDesc td;
    td.loc = x;
    td.dest = y;
    td.verbIds = verbIds;
    m_travelDescs.push_back( td );

    /*m_ad->dataTravelTable[ x ].loc = x;
    TravelDestination td;
    td.dest = y;
    td.verbs = verbs;
    m_ad->dataTravelTable[ x ].dests.push_back( td );*/
}
void ParserDat::parseVocabulary( std::istringstream& p_ss ) {
	unsigned id;
	std::string word;

	// Add word to Verb-structure, that is - append synonyms to a common object:
	p_ss >> id >> word;
	m_ad->vocabulary[ id ] = id; //m_ad->dataVocabulary[ verbStr ] = verbId;
	m_ad->vocabulary[ id ].appendWord( word );

	// Append unique word to vocabulary:
	m_ad->vocabulary.addWord( id, word ); // This is used to map unique words to common verbs.
}
void ParserDat::parseMsgs( std::istringstream& p_ss, std::map<unsigned, std::string>& p_map ) {
	unsigned msgId;
	std::string msgStr;

	p_ss >> msgId;
	std::getline( p_ss, msgStr );

	p_map[ msgId ] = msgStr;
}
void ParserDat::parseObjLoc( std::istringstream& p_ss ) {
	unsigned obj;
	int l;

	// Get object id in question: 
	p_ss >> obj;

	// Get locations for said object:
	std::string loc;
    while( std::getline( p_ss, loc, '\t' ) ) {
    	if( loc.size() > 0 ) { // Some weird bug caused this method to write a single zero-value at the beginning of each iteration because loc was returned as "". Strange.
    		l = Util::toInt( loc.c_str() );
    		m_ad->dataObjLoc[obj].push_back( l );
    	}
    }
}
void ParserDat::parseObjDesc( std::istringstream& p_ss ) {
	static unsigned prevObj; // hack
	std::string first, second;
	p_ss >> first;
	std::getline( p_ss, second );

	if( first.size() >= 3 ) { // Then 1st and 2nd denote a message that ought to be appended to the previously added object.
		m_ad->dataObjDesc[ prevObj ][ first ] += second;
	} else { // 1st and 2nd indicate a new object. This also means 1st may be considered an unsigned int.
		unsigned obj = Util::toInt( first.c_str() );
		m_ad->dataObj[ obj ] = second; // Name of object.

		prevObj = obj;
	}

	// "Properties which produce no message should be given the message ">$<"."
	// Considering giving objects with empty description-lists the above description? Unclear.
}
void ParserDat::parseActionDefaults( std::istringstream& p_ss ) {
	unsigned a, d;

	p_ss >> a >> d;
	m_ad->dataActionDefaults[a] = d;
}
void ParserDat::parseLiquidAssets( std::istringstream& p_ss ) {
	// Do nothing.
}