#include <cassert>

#include "Common.h"
#include "Object.h"
#include "GameLogic.h"
#include "Executioner.h"

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
			executed = executeTravel( (ActionTravel*)p_action );
			break;
        case ActionTypes_INTERACT:
            executed = executeInteract( (ActionInteract*)p_action );
            break;
        case ActionTypes_GAME:
            executed = executeGame( (ActionGame*)p_action );
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
	AdventData& ad = Singleton<AdventData>::get();

    bool canTravel = false;

    Verb target = p_action->getTarget();
    Location location = ad.adventurer.getLocation();
    for( unsigned i = 0; i < location.getNumDestinations() && canTravel==false; i++ ) {
        Destination destination = location[ i ];

        // If the word does not correspond to any word used for travel at the current location - skip to the next destination:
        if( destination.canTravelToUsing( target )==false ) {
            continue;
        }

        canTravel = GameLogic::canTravel( destination, location );
        if( canTravel==true ) {
            ad.adventurer.adventTravelTo( ad.map[ destination.getId() ] );
            GUI::RenderLocation( ad.adventurer.getLocation() );
        }
    }

    return canTravel;
}
bool Executioner::executeInteract( ActionInteract* p_action ) {
    AdventData& ad = Singleton<AdventData>::get();

    bool canInteract = false;
    // Establish what kind of object to perform here.
    // ...then call the correct function.
    
    // Currently, we assume it's picking up objects.
    Verb action = p_action->getAction();
    Verb target = p_action->getTarget();
    Location location = ad.adventurer.getLocation();
    std::vector< Object > locationObjects = location.getObjects();
    for( unsigned i = 0; i < locationObjects.size() && canInteract==false; i++ ) {
        Object object = locationObjects[ i ];

        canInteract = GameLogic::canTakeObject( target, object );
        if( canInteract==true && ad.adventurer.getInventory().isFull()==false ) {
            // Loot object:
            ad.adventurer.getInventory().appendItem( object );
            // Remove object from location:
            ad.map[ location.getId() ].objectRemove( object );

            GUI::RenderString( s_confMessageObjectTaken );

            canInteract = true;
        }
    }

    return canInteract;
}
bool Executioner::executeGame( ActionGame* p_action ) {
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
}