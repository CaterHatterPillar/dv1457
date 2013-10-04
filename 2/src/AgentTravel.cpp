#include "Common.h"
#include "AgentTravel.h"

AgentTravel::AgentTravel() {

}
AgentTravel::~AgentTravel() {
	// Do nothing.
}

bool AgentTravel::execute( ActionTravel* p_action, Result& io_result ) {
	AdventData& ad = Singleton<AdventData>::get();
    bool satisfiesConditions = false;

    Verb target = p_action->getTarget();
    Location location = ad.adventurer.getLocation();
    for( unsigned i = 0; i < location.getNumDestinations() && satisfiesConditions==false; i++ ) {
        Destination destination = location[ i ];

        // If the word does not correspond to any word used for travel at the current location - skip to the next destination:
        if( destination.canTravelToUsing( target )==false ) {
            continue;
        }
    
        unsigned x = location.getId();      // Current location.
        unsigned y = destination.getId();   // Possible location to which one might travel.
        unsigned m = y / 1000;              // How to travel (might actually not be travel, could even be a goto (!)).
        unsigned n = y % 1000;              // Conditions of travel.

        // Note to self, developer and the world: By 'prop', the original author apperently mean object - so the property value of said object.
        if( m == 0 ) { // if m=0 It's unconditional.
            satisfiesConditions = true;
        } else if( (m>0) && (m<100) ) { // if 0<m<100 It is done with m% probability.
            throw ExceptionAdventNotYetImplemented( "Travel - Probability." );
        } else if( m==100 ) { // if m=100 Unconditional, but forbidden to dwarves.
            throw ExceptionAdventNotYetImplemented( " Travel - Restrictions to dwarves apply." );
        } else if( (m>100) && (m<=200) ) { // if 100<m<=200 He must be carrying object m-100.
            throw ExceptionAdventNotYetImplemented( "Travel - Must carry certain object." );
        } else if( (m>200) && (m<=300) ) { // if 200<m<=300 Must be carrying or in same room as m-200.
            throw ExceptionAdventNotYetImplemented( "Travel - Must be in same room as..." );
        } else if( (m>300) && (m<=400) ) { // if 300<m<=400 prop(m mod 100) must *not* be 0.
            unsigned prop = m % 100;
            unsigned propValue = ad.map.getObject( prop ).getPropertyValue();
            if( propValue!=0 ) {
                satisfiesConditions = true;
            }
        } else if( (m>400) && (m <=500) ) { // if 400<m<=500 prop(m mod 100) must *not* be 1.
            throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 1." );
        } else if( (m>500) && (m <=600) ) { // if 500<m<=600 prop(m mod 100) must *not* be 2, etc.
            throw ExceptionAdventNotYetImplemented( "Travel - prop(m mod 100) must *not* be 2, etc." );
        }

        if( satisfiesConditions==true ) {
            if( n<=300 ) { // if n<=300 It is the location to go to.
                ad.adventurer.adventTravelTo( ad.map[ n ] );
            } else if( (n>300) && (n<=500) ) { // if 300<n<=500 n-300 is used in a computed goto to a section of special code.
                throw ExceptionAdventNotYetImplemented( "Travel - GOTO." );
            } else if( n>500 ) { // if n>500 Message n-500 from section 6 is printed, and he stays wherever he is.
                GUI::RenderLines( ad.letterbox[ n ].lines );
            }
        } 
    }

    // The location is printing whether or not the travel was successful.
    GUI::RenderLocation( ad.adventurer.getLocation() );
    if(satisfiesConditions)
        ad.adventurer.getMagic().discoverMagicWords();

    return satisfiesConditions;
}



/*
std::cout << "FROM: " << Util::toString( x ) << std::endl
        << "TO: " << Util::toString( y ) << std::endl
        << "m: " << Util::toString( m ) << std::endl
        << "n: " << Util::toString( n ) << std::endl;
*/