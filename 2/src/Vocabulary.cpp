#include "Vocabulary.h"

Vocabulary::Vocabulary() {

}
Vocabulary::~Vocabulary() {
	// Do nothing.
}

void Vocabulary::addWord( unsigned p_id, std::string p_word ) {
	m_wordToVerb[ p_word ].push_back( p_id );
}
bool Vocabulary::isVerb( std::string p_word, unsigned& io_verbId ) {
	bool isVerb = false;
	
	std::map< std::string, std::vector< unsigned > >::iterator it;
	it = m_wordToVerb.find( p_word );
	if( it!=m_wordToVerb.end() ) {
		io_verbId = it->second.front();
		isVerb = true;
	}
	
	return isVerb;
}

Verb& Vocabulary::operator[]( unsigned p_id ) {
	return m_verbs[ p_id ];
}