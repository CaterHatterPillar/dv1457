#include "Map.h"
#include "Common.h"

Map::Map() {

}
Map::~Map() {
	// Do nothing.
}

void Map::appendObject( Object p_object ) {
	m_objects[ p_object.getId() ] = p_object;
}
Object& Map::getObject( unsigned p_idObject ) {
	if( m_objects.find( p_idObject )!=m_objects.end() ) {
		return m_objects[ p_idObject ];
	} else {
		throw ExceptionAdvent( "Object ID " + Util::toString( p_idObject ) + " not found in m_objects (see Map::getObject())." );
	}

	//hack, fix a proper return-statement
}

Location& Map::operator[]( unsigned p_idLocation ) { 
	return m_locations[ p_idLocation ];
}

void Map::removeDuplicatesHack( unsigned p_objectId ){
	typedef std::map< unsigned, Location >::iterator it_type;
	for(it_type it = m_locations.begin(); it!=m_locations.end(); it++) {
    	unsigned locationId = it->first;
    	Location& location = it->second;

    	if( location.objectAtLocation( p_objectId )==true ) {
    		location.objectIdRemove( p_objectId );
    	}
    }
}