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

unsigned Location::getId() {
	return m_id;
}
std::string Location::getDescShort() {
	return m_descShort;
}
std::string Location::getDescLong() {
	std::string descLong = "";
	for( unsigned i = 0; i < m_descLongs.size(); i++ ) {
		descLong += m_descLongs[i];
		descLong += '\n';
	}
	return descLong;
}
std::vector< std::string > Location::getDescLongs() {
	return m_descLongs;
}