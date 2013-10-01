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

    bool travel = false;

    Verb target = p_action->getTarget();
    Location location = ad.adventurer.getLocation();
    for( unsigned i = 0; i < location.getNumDestinations() && travel==false; i++ ) {
        Destination destination = location[ i ];

        // If the word does not correspond to any word used for travel at the current location - skip to the next destination:
        if( destination.canTravelToUsing( target )==false ) {
            continue;
        }

        travel = GameLogic::canTravel( destination, location );
        if( travel==true ) {
            ad.adventurer.adventTravelTo( ad.map[ destination.getId() ] );
        }
    }

    // The location is printing whether or not the travel was successful.
    GUI::RenderLocation( ad.adventurer.getLocation() );

    return travel;
}
bool Executioner::executeInteract( ActionInteract* p_action, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();

    bool interact = false;
    
    Verb action = p_action->getAction();
    Verb target = p_action->getTarget();
   
    switch(action.getId())
    {
    case Verb::VerbIds_TAKE:
        interact = interactTake(target);
        break;
    case Verb::VerbIds_DROP:
        interact = interactDrop(target);
        break;
    default:
        break;
    }

    if( interact==false ) {
        io_result.setSummary( s_confMessageObjectNotFound );
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

bool Executioner::interactTake(Verb p_target) {
    AdventData& ad = Singleton<AdventData>::get();
    bool interact = false;

    Location location = ad.adventurer.getLocation();
    std::vector< unsigned > locationObjectIds = location.getObjectIds();
    for( unsigned i = 0; i < locationObjectIds.size() && interact==false; i++ ) {
        unsigned objectId = locationObjectIds[ i ];
        Object object = ad.map.getObject( objectId );

        interact = GameLogic::canTakeObject( p_target, object );
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

bool Executioner::interactDrop(Verb p_target) {
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