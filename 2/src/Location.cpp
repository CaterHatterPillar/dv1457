#include <algorithm>

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
void Location::objectAppend( Object p_object ) {
	m_objects.push_back( p_object );
}
void Location::objectRemove( Object p_object ) {
	std::vector< Object >::iterator it;
	it = std::find( m_objects.begin(), m_objects.end(), p_object );
	m_objects.erase( it );
	//bool removed = false;
	//for( unsigned i = 0; i < m_objects.size() && removed==false; i++ ) {
	//	if( p_object==m_objects[i] ) {
	//		m_objects.erase( i );
	//		removed = true;
	//	}
	//}
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
std::vector< Object > Location::getObjects() const {
	return m_objects;
}

unsigned Location::getNumDestinations() const {
	return m_destinations.size();
}

Destination& Location::operator[]( unsigned p_id ) {
	return m_destinations[ p_id ];
}