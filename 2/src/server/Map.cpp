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