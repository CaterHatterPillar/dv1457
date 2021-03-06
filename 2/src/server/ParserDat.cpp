#include "Common.h"
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
	Sections_MAGIC_MESSAGES 			= 12,
	Sections_RELATIONS					= 13
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
				parseMsgsArbitrary( ss );
				break;
			case Sections_OBJECT_LOCATIONS:
				parseObjLoc( ss );
				break;
			case Sections_ACTION_DEFAULTS:
				parseActionDefaults( ss );
				break;
			case Sections_LIQUID_ASSETS:
				parseLiquidAssets( ss );
				break;
			case Sections_CLASS_MESSAGES:
				// throw ExceptionAdventNotYetImplemented( "Not yet implemented: Parsing Class Messages." );
				break;
			case Sections_HINTS:
				// throw ExceptionAdventNotYetImplemented( "Not yet implemented: Parsing Sections_HINTS." );
				break;
			case Sections_MAGIC_MESSAGES:
				// throw ExceptionAdventNotYetImplemented( "Not yet implemented: Parsing Magic Messages." );
				break;
			case Sections_RELATIONS:
				parseRelations( ss );
				break;
		}
	}

	compileDependantData();
}
void ParserDat::compileDependantData() {
	// Compile travel-descriptions:
	for( unsigned i = 0; i < m_travelDescs.size(); i++ ) {
		TravelDesc td = m_travelDescs[ i ];

		Destination d( td.dest );
		for( unsigned j = 0; j < td.verbIds.size(); j++ ) {
			unsigned verbId = td.verbIds[ j ];
			d.appendVerb( m_ad->vocabulary[ verbId ] );
		}
		m_ad->map[ td.loc ].appendDestination( d );
	}

	// Compile object-descriptions:
	typedef std::map< unsigned, ObjectDesc >::iterator uoIt;
	for( uoIt it = m_objectDescs.begin(); it!=m_objectDescs.end(); it++ ) {
		Object object = it->second.obj;
		std::vector< unsigned > locations = it->second.locs;

		// Add object to list of objects present in the game world:
		m_ad->map.appendObject( object );

		// Add object ID to location where that object is located:
		for( unsigned i = 0; i < locations.size(); i++ ) {
			unsigned location = locations[ i ];
			m_ad->map[ location ].objectIdAppend( object.getId() );
		}
	}

	// Compile liquid assets:
	typedef std::map< unsigned, std::vector< unsigned > >::iterator uvIt;
	for( uvIt it = m_liquidAssets.begin(); it!=m_liquidAssets.end(); it++ ) {
		unsigned loc = it->first;
		std::vector< unsigned > assets = it->second;
		for( unsigned i = 0; i < assets.size(); i++ ) {
			unsigned asset = assets[ i ];
			// Currently only supports LIT-attribute:
			switch( asset ) {
				case LiquidAssets_LIT:
					m_ad->map[ loc ].setLit( true );
					break;
				case LiquidAssets_LIQUID_TYPE:
					m_ad->map[loc].setWater( false );
					m_ad->map[loc].setOil( true );
					break;
				case LiquidAssets_LIQUID:
					m_ad->map[loc].setWater(true);
					break;
				default:
					// Do nothing.
					break;
			}
		}
	}
}

void ParserDat::parseDescLong( std::istringstream& p_ss ) {
	unsigned int key;
	std::string descLong;

	p_ss >> key;
	std::getline( p_ss, descLong );

	m_ad->map[ key ].setId( key ); // This is likewize set in parseDescShort.
	m_ad->map[ key ].appendDescLong( descLong );
}
void ParserDat::parseDescShort( std::istringstream& p_ss ) {
	unsigned int key;
	std::string descShort;

	p_ss >> key;
	std::getline( p_ss, descShort );

	m_ad->map[ key ].setId( key ); // This is likewize set in parseDescLong.
	m_ad->map[ key ].setDescShort( descShort );
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
void ParserDat::parseMsgsArbitrary( std::istringstream& p_ss ) {
	unsigned msgId;
	std::string msgLine;

	p_ss >> msgId;
	std::getline( p_ss, msgLine );

	m_ad->letterbox[ msgId ].id = msgId;
	m_ad->letterbox[ msgId ].lines.push_back( msgLine );
}
void ParserDat::parseObjLoc( std::istringstream& p_ss ) {
	unsigned objId;

	// Get object id in question: 
	p_ss >> objId;

	// Get locations for said object:
	std::string locationString;
	unsigned location;
	std::vector< unsigned > locations;
    while( std::getline( p_ss, locationString, '\t' ) ) {
    	if( locationString.size() > 0 ) { // Some weird bug caused this method to write a single zero-value at the beginning of each iteration because loc was returned as "". Strange.
    		location = Util::toInt( locationString.c_str() );
    		locations.push_back( location );
    	}
    }

    m_objectDescs[ objId ].obj.setId( objId );
    for( unsigned i = 0; i < locations.size(); i++ ) {
    	unsigned location = locations[ i ];
    	if( location!=-1 ) {
    		m_objectDescs[ objId ].locs.push_back( location );
    	} else {
    		m_objectDescs[ objId ].obj.setImmovable( true );
    	} // m_objectDescs[ objId ].obj.insert( m_objectDescs[ objId ].obj.end(), locations.begin(), locations.end() ); 
    }
    // If more than one locations, assume immovable status:
    if( locations.size() > 1 ) {
    	m_objectDescs[ objId ].obj.setImmovable( true );
    }
}
void ParserDat::parseObjDesc( std::istringstream& p_ss ) {
	static unsigned prevObjId; // hack
	std::string first, second;
	p_ss >> first;
	std::getline( p_ss, second );

	if( first.size() >= 3 ) { // Then 1st and 2nd denote a message that ought to be appended to the previously added object.
		m_objectDescs[ prevObjId ].obj.appendDescription( first, second );
	} else { // 1st and 2nd indicate a new object. This also means 1st may be considered an unsigned int.
		unsigned objId = Util::toInt( first.c_str() );
		m_objectDescs[ objId ].obj.setName( second ); // Name of object.

		prevObjId = objId;
	}

	// "Properties which produce no message should be given the message ">$<"."
	// Considering giving objects with empty description-lists the above description? Unclear.
}
void ParserDat::parseLiquidAssets( std::istringstream& p_ss ) {
	// Get asset num:
	unsigned n;
	p_ss >> n;

	// Get relevant locations:
	std::string loc;
	std::vector< unsigned > locs;
    while( std::getline( p_ss, loc, '\t') ) {
    	if( loc.size() > 0 ) { // Necessary?
    		unsigned l = Util::toInt( loc.c_str() );
    		locs.push_back( l );
    	}
    }

    // Add liquid asset to location:
    for( unsigned i = 0; i < locs.size(); i++ ) {
    	m_liquidAssets[ locs[ i ] ].push_back( n );
    }
}
void ParserDat::parseActionDefaults( std::istringstream& p_ss ) {
	unsigned a, d;
	p_ss >> a >> d;
	m_ad->letterbox.appendActionDefault( a, d );
}
void ParserDat::parseRelations( std::istringstream& p_ss ) {
	unsigned subject, subjector, action, influence;
	std::string output;
	p_ss >> subject >> subjector >> action >> influence >> output;

	Relation r( subject, subjector, action, influence, output );
	m_ad->relations.appendRelation( r );
}