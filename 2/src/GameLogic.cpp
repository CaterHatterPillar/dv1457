#include "GameLogic.h"
#include "ExceptionAdventNotYetImplemented.h"

GameLogic::GameLogic() {

}
GameLogic::~GameLogic() {
	// Do nothing.
}

bool GameLogic::canTravel( Destination p_destination, Location p_location ) {
	bool canTravel = false;
	
 	unsigned x = p_location.getId();        // Current location.
    unsigned y = p_destination.getId();     // Possible location to which one might travel.
    unsigned m = y / 1000;                  // How to travel (might actually not be travel, could even be a goto (!)).
    unsigned n = y % 1000;                  // Conditions of travel.

    if( n<=300 ) { // if n<=300 It is the location to go to.
    } else if( (n > 300) && (n<= 500) ) { // if 300<n<=500 n-300 is used in a computed goto to a section of special code.
        throw ExceptionAdventNotYetImplemented( "Travel - GOTO." );
    } else if( n > 500 ) { // if n>500 Message n-500 from section 6 is printed, and he stays wherever he is.
        throw ExceptionAdventNotYetImplemented( "Travel - Special-case message." );
    }

    if( m == 0 ) { // if m=0 It's unconditional.
        canTravel = true;
    } else if( (m > 0) && (m < 100) ) { // if 0<m<100 It is done with m% probability.
        throw ExceptionAdventNotYetImplemented( "Travel - Probability." );
    } else if( m == 100 ) { // if m=100 Unconditional, but forbidden to dwarves.
        throw ExceptionAdventNotYetImplemented( " Travel - Restrictions to dwarves apply." );
    } else if( (m > 100) && (m <= 200) ) { // if 100<m<=200 He must be carrying object m-100.
        throw ExceptionAdventNotYetImplemented( "Travel - Must carry certain object." );
    } else if( (m > 200) && (m <= 300) ) { // if 200<m<=300 Must be carrying or in same room as m-200.
        throw ExceptionAdventNotYetImplemented( "Travel - Must be in same room as..." );
    } else if( (m > 300) && (m <= 400) ) { // if 300<m<=400 prop(m mod 100) must *not* be 0.
        throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 0." );
    } else if( (m > 400) && (m <= 500) ) { // if 400<m<=500 prop(m mod 100) must *not* be 1.
        throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 1." );
    } else if( (m > 500) && (m <= 600) ) { // if 500<m<=600 prop(m mod 100) must *not* be 2, etc.
        throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 2, etc." );
    }

	return canTravel;
}

bool GameLogic::canTakeObject( Verb p_target, Object p_object ) {
	bool canTakeObject = false;

	unsigned targetId = p_target.getId();
	unsigned objectIdForTarget = targetId % 1000;

	if( objectIdForTarget==p_object.getId() && p_object.isImmovable()==false ) {
		canTakeObject = true;
	}

	return canTakeObject;
}