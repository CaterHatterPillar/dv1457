#include <algorithm>

#include "Common.h"
#include "Location.h"

Location::Location() {
	m_id = 0;
	m_descShort = "";
}
Location::Location( unsigned p_id, std::string p_descShort, std::vector< std::string > p_descLongs ) {
	m_id = p_id;
	m_descShort = p_descShort;
	m_descLongs = p_descLongs;
}
Location::~Location() {
	// Do nothing.
}

void Location::setId( unsigned p_id ) {
	m_id = p_id;
}
void Location::setDescShort( std::string p_descShort ) {
	m_descShort = p_descShort;
}
void Location::appendDescLong( std::string p_descLong ) {
	m_descLongs.push_back( p_descLong );
}

void Location::appendDestination( Destination p_destination ) {
	m_destinations.push_back( p_destination );
}
void Location::objectIdAppend( unsigned p_objectId ) {
	m_objectIds.push_back( p_objectId );
}
void Location::objectIdRemove( unsigned p_objectId ) {
	std::vector< unsigned >::iterator it;
	it = std::find( m_objectIds.begin(), m_objectIds.end(), p_objectId );
	if( it!=m_objectIds.end() ) {
		m_objectIds.erase( it );
	} else {
		throw ExceptionAdvent( "Object ID " + Util::toString( p_objectId ) + " not found in m_objectIds (see Location::objectIdRemove)." );
	}
}

unsigned Location::getId() const {
	return m_id;
}
std::string Location::getDescShort() const {
	return m_descShort;
}
std::string Location::getDescLong() const {
	std::string descLong = "";
	for( unsigned i = 0; i < m_descLongs.size(); i++ ) {
		descLong += m_descLongs[i];
		descLong += '\n';
	}
	return descLong;
}
std::vector< std::string > Location::getDescLongs() const {
	return m_descLongs;
}
std::vector< unsigned > Location::getObjectIds() const {
	return m_objectIds;
}

unsigned Location::getNumDestinations() const {
	return m_destinations.size();
}

Destination& Location::operator[]( unsigned p_id ) {
	return m_destinations[ p_id ];
}