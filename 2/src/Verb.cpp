#include "Verb.h"

Verb::Verb() {

}
Verb::~Verb() {
	// Do nothing.
}

void Verb::appendWord( std::string p_word ) {
	m_words.push_back( p_word );
}

Verb& Verb::operator=( unsigned p_id ) {
	m_id = p_id;
	return *this;
}
bool Verb::operator==( const unsigned& p_id ) const {
	bool equals = false;
	if( m_id==p_id ) {
		equals = true;
	}
	return equals;
}
bool Verb::operator==( const Verb& p_verb ) const {
	bool equals = false;
	if( m_id==p_verb.getId() ) {
		equals = true;
	}
	return equals;
}

unsigned Verb::getId() const {
	return m_id;
}