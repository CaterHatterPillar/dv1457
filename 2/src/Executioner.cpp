#include "Common.h"
#include "Object.h"
#include "Executioner.h"

Executioner::Executioner() {

}
Executioner::~Executioner() {
	// Do nothing.
}

bool Executioner::execute( Action* p_action, Result& io_result ) {
	assert( p_action );

	bool executed = false;
	ActionTypes actionType = p_action->getType(); 
	switch( actionType ) {
		case ActionTypes_INVALID:
            executed = false;
			break;
		case ActionTypes_TRAVEL:
			executed = executeTravel( (ActionTravel*)p_action, io_result );
			break;
        case ActionTypes_INTERACT:
            executed = executeInteract( (ActionInteract*)p_action, io_result );
            break;
        case ActionTypes_GAME:
            executed = executeGame( (ActionGame*)p_action, io_result );
            break;
		default:
			throw ExceptionAdventNotYetImplemented( "Encountered unknown ActionTypes: " + std::string( ActionTypesString[ actionType ] ) + "." );
			break;
	}
	// Don't forget to clean up:
	delete p_action;

	return executed;
}

bool Executioner::executeTravel( ActionTravel* p_action, Result& io_result ) {
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

        // std::cout << "FROM: " << Util::toString( x ) << std::endl
        // << "TO: " << Util::toString( y ) << std::endl
        // << "m: " << Util::toString( m ) << std::endl
        // << "n: " << Util::toString( n ) << std::endl;

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

    return satisfiesConditions;
}
bool Executioner::executeInteract( ActionInteract* p_action, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();

    bool interact = false;
    
    Verb action = p_action->getAction();
    Verb target = p_action->getTarget();
   
    switch( action.getId() )
    {
    case VerbIds_TAKE:
        interact = interactTake( target, io_result );
        break;
    case VerbIds_DROP:
        interact = interactDrop( target, io_result );
        break;
    case VerbIds_OPEN:
        interact = interactOpen( target, io_result );
        break;
    default:
        break;
    }

    return interact;
}
bool Executioner::executeGame( ActionGame* p_action, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();

    bool recognizedGameCommand = true;
    ActionGameTypes agt = p_action->getActionGameType();
    switch( agt ) {
        case ActionGameTypes_PRESENT_LOCATION:
            GUI::RenderLocation( ad.adventurer.getLocation() );
            break;
        case ActionGameTypes_PRESENT_INVENTORY:
            GUI::RenderInventory( ad.adventurer.getInventory() );
            break;
        default:
            recognizedGameCommand = false;
            throw ExceptionAdventNotYetImplemented( "Encountered unknown ActionGameTypes: " + std::string( ActionGameTypesString[ agt ] ) + "." );
            break;
    }

    return recognizedGameCommand;
}

bool Executioner::interactTake( Verb p_target, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();
    bool interact = false;

    Location location = ad.adventurer.getLocation();
    std::vector< unsigned > locationObjectIds = location.getObjectIds();
    for( unsigned i = 0; i < locationObjectIds.size() && interact==false; i++ ) {
        unsigned objectId = locationObjectIds[ i ];
        Object object = ad.map.getObject( objectId );

        unsigned targetId = p_target.getId();
        unsigned objectIdForTarget = targetId % 1000;
        if( objectIdForTarget==object.getId() && object.isImmovable()==false ) {
            interact = true;
        }

        if( interact==true && ad.adventurer.getInventory().isFull()==false ) {
            // Loot object:
            ad.adventurer.getInventory().appendItem( object );
            // Remove object from location:
            ad.map[ location.getId() ].objectIdRemove( objectId );

            GUI::RenderString( s_confMessageObjectTaken );

            interact = true;
        }
    }
    return interact;
}

bool Executioner::interactDrop( Verb p_target, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();
    Location location = ad.adventurer.getLocation();
    bool interact = false;

    unsigned int targetId = p_target.getId();
    unsigned int objectId = targetId % 1000;

    for(unsigned int i=0; i<ad.adventurer.getInventory().getNumItems(); i++)
    {
        Object obj = ad.adventurer.getInventory()[i];
        if(obj.getId() == objectId)
        {
            ad.adventurer.getInventory().removeItem(obj);
            ad.map[ location.getId() ].objectIdAppend( objectId );
            GUI::RenderString( s_confMessageObjectDropped );
            interact = true;
        }
    }

    return interact;
}
bool Executioner::interactOpen( Verb p_target, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();
    Location location = ad.adventurer.getLocation();
    unsigned objectId = p_target.getId() % 1000;

    // Check whether or not target is something one may open in the first place:
    bool satisfiesConditions = false;
    for( unsigned i = 0; i < s_objectsOpenableSize; i++ ) {
        if( objectId==ObjectsOpenable[ i ] ) {
            satisfiesConditions = true;
            break;
        }
    }

    // This case needs some refactoring.
    // Currently assumes grate being unlocked and checks whether or not the player carries keys.
    if( satisfiesConditions==true
        && ad.adventurer.getInventory().carriesItem( 1 )==true // hack
        && location.objectAtLocation( objectId )==true ) {
        Object& object = ad.map.getObject( objectId );
        object.setPropertyValue( 1 ); // This is very sketchy. Try to find out a better way to edit property values according to a certain set of standards.

        GUI::RenderString( s_confMessageObjectOpened );
    } else {
        satisfiesConditions = false;
        io_result.setSummary( s_confMessageObjectNotOpenable );
    }

    return satisfiesConditions;
}