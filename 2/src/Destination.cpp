#include "Destination.h"

Destination::Destination( unsigned p_id ) {
	m_id = p_id;
}
Destination::~Destination() {
	// Do nothing.
}

void Destination::appendVerb( Verb p_verb ) {
	m_verbs.push_back( p_verb );
}

bool Destination::canTravelToUsing( Verb p_verb ) {
	bool canTravel = false;
	for( unsigned i = 0; i < m_verbs.size(); i++ ) {
		if( m_verbs[i]==p_verb ) {
			canTravel = true;
			break;
		}
	}
	return canTravel;
}

unsigned Destination::getId() const {
	return m_id;
}