#include <cassert>

#include "AdventData.h"
#include "Executioner.h"
#include "ExceptionAdventNotYetImplemented.h"

Executioner::Executioner() {

}
Executioner::~Executioner() {
	// Do nothing.
}

bool Executioner::execute( Action* p_action ) {
	assert( p_action );

	bool executed = false;
	ActionTypes actionType = p_action->getType(); 
	switch( actionType ) {
		case ActionTypes_INVALID:
			break; // Print debug info
		case ActionTypes_TRAVEL:
			executeTravel( (ActionTravel*)p_action );
			break;
		default:
			throw ExceptionAdventNotYetImplemented( "Encountered unknown ActionTypes: " + std::string( ActionTypesString[ actionType ] ) + "." );
			break;
	}
	// Don't forget to clean up:
	delete p_action;

	return executed;
}

bool Executioner::executeTravel( ActionTravel* p_action ) {
	bool travel = false;
	AdventData& ad = Singleton<AdventData>::get();

	Verb target = p_action->getTarget();
	Location location = ad.adventurer.getLocation();
	for( unsigned i = 0; i < location.getNumDestinations(); i++ ) {
		Destination destination = location[ i ];

		// If the word does not correspond to any word used for travel at the current location - skip to the next destination:
		if( destination.canTravelToUsing( target )==false ) {
			continue;
		}

		travel = conditionsTravel( destination, location );
    	if( travel==true ) {
    		ad.adventurer.setLocation( ad.map[ destination.getId() ] );
    		break;
    	}
	}
	return travel;
}

bool Executioner::conditionsTravel( Destination p_destination, Location p_location ) {
	bool satisfiesConditions = false;

	unsigned x = p_location.getId();		// Current location.
    unsigned y = p_destination.getId();		// Possible location to which one might travel.
    unsigned m = y / 1000; 					// How to travel (might actually not be travel, could even be a goto (!)).
    unsigned n = y % 1000;					// Conditions of travel.

    if( n<=300 ) { // if n<=300 It is the location to go to.
    } else if( (n > 300) && (n<= 500) ) { // if 300<n<=500 n-300 is used in a computed goto to a section of special code.
    	throw ExceptionAdventNotYetImplemented( "Travel - GOTO." );
    } else if( n > 500 ) { // if n>500 Message n-500 from section 6 is printed, and he stays wherever he is.
    	throw ExceptionAdventNotYetImplemented( "Travel - Special-case message." );
    }

    if( m == 0 ) { // if m=0 It's unconditional.
    	satisfiesConditions = true;
    } else if( (m > 0) && (m < 100) ) { // if 0<m<100 It is done with m% probability.
    	throw ExceptionAdventNotYetImplemented( "Travel - Probability." );
    } else if( m == 100 ) { // if m=100 Unconditional, but forbidden to dwarves.
    	throw ExceptionAdventNotYetImplemented( " Travel - Restrictions to dwarves apply." );
    } else if( (m > 100) && (m <= 200) ) { // if 100<m<=200	He must be carrying object m-100.
    	throw ExceptionAdventNotYetImplemented( "Travel - Must carry certain object." );
    } else if( (m > 200) && (m <= 300) ) { // if 200<m<=300	Must be carrying or in same room as m-200.
    	throw ExceptionAdventNotYetImplemented( "Travel - Must be in same room as..." );
    } else if( (m > 300) && (m <= 400) ) { // if 300<m<=400	prop(m mod 100) must *not* be 0.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 0." );
    } else if( (m > 400) && (m <= 500) ) { // if 400<m<=500	prop(m mod 100) must *not* be 1.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 1." );
    } else if( (m > 500) && (m <= 600) ) { // if 500<m<=600	prop(m mod 100) must *not* be 2, etc.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 2, etc." );
    }

    return satisfiesConditions;
}

/*
bool travel = false;

	unsigned x = p_location.getId();		// Current location.
    unsigned y = p_destination.getId();		// Possible location to which one might travel.
    unsigned m = y / 1000; 					// How to travel (might actually not be travel, could even be a goto (!)).
    unsigned n = y % 1000;					// Conditions of travel.

    if( n<=300 ) { // if n<=300 It is the location to go to.
    } else if( (n > 300) && (n<= 500) ) { // if 300<n<=500 n-300 is used in a computed goto to a section of special code.
    	throw ExceptionAdventNotYetImplemented( "Travel - GOTO." );
    } else if( n > 500 ) { // if n>500 Message n-500 from section 6 is printed, and he stays wherever he is.
    	throw ExceptionAdventNotYetImplemented( "Travel - Special-case message." );
    }

    if( m == 0 ) { // if m=0 It's unconditional.
    	travel = true;
    } else if( (m > 0) && (m < 100) ) { // if 0<m<100 It is done with m% probability.
    	throw ExceptionAdventNotYetImplemented( "Travel - Probability." );
    } else if( m == 100 ) { // if m=100 Unconditional, but forbidden to dwarves.
    	throw ExceptionAdventNotYetImplemented( " Travel - Restrictions to dwarves apply." );
    } else if( (m > 100) && (m <= 200) ) { // if 100<m<=200	He must be carrying object m-100.
    	throw ExceptionAdventNotYetImplemented( "Travel - Must carry certain object." );
    } else if( (m > 200) && (m <= 300) ) { // if 200<m<=300	Must be carrying or in same room as m-200.
    	throw ExceptionAdventNotYetImplemented( "Travel - Must be in same room as..." );
    } else if( (m > 300) && (m <= 400) ) { // if 300<m<=400	prop(m mod 100) must *not* be 0.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 0." );
    } else if( (m > 400) && (m <= 500) ) { // if 400<m<=500	prop(m mod 100) must *not* be 1.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 1." );
    } else if( (m > 500) && (m <= 600) ) { // if 500<m<=600	prop(m mod 100) must *not* be 2, etc.
    	throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 2, etc." );
    }

    return travel;
*/

/*
bool travel = false;
	AdventData& ad = Singleton<AdventData>::get();

	Location location = m_adventurer.getLocation();
	for( unsigned i = 0; i < location.getNumDestinations() && travel==false; i++ ) {
		Destination destination = location[i];
	
		// If the word does not correspond to any word used for travel at the current location - skip to the next destination:
		if( destination.canTravelToUsing( p_verb )==false ) {
			continue;
		}

#ifdef ADVENT_DEBUG
		GUI::RenderString( "DEBUG TRAVEL: \nAttempting travel to: " + Util::toString( destination.getId() ) + "\nTravel would require one of the following verbs:\n" );
		for( unsigned j = 0; j < destination.getVerbs().size(); j++ ) {
			Verb verb = destination.getVerbs()[j];
			GUI::RenderString( "\t" + Util::toString( verb.getId() ) + "\n" );
		}
#endif // ADVENT_DEBUG

		travel = commandTravelToDestination( destination, location );
    	if( travel==true ) {
    		m_adventurer.setLocation( ad.map[ destination.getId() ] );
#ifdef ADVENT_DEBUG
    		GUI::RenderString( "Travelled to: " + Util::toString( m_adventurer.getLocation().getId() ) + "\n" );
#endif // ADVENT_DEBUG
    	}
	}

	return travel;
*/