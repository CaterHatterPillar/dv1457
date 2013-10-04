#include "Common.h"
#include "AgentInteract.h"

AgentInteract::AgentInteract() {

}
AgentInteract::~AgentInteract() {
	// Do nothing.
}

bool AgentInteract::execute( ActionInteract* p_action, Result& io_result ) {
	AdventData& ad = Singleton<AdventData>::get();

    bool interact = false;
    
    Verb action = p_action->getAction();
    Verb target = p_action->getTargets().front();
   
    switch( action.getId() )
    {
    case VerbIds_TAKE:
        interact = AgentInteract::executeTake( target, io_result );
        break;
    case VerbIds_DROP:
        interact = AgentInteract::executeDrop( target, io_result );
        break;
    case VerbIds_OPEN:
        interact = AgentInteract::executeOpen( target, io_result );
        break;
    case VerbIds_ON:
        interact = AgentInteract::executeOn( target, io_result );
        break;
    default:
        break;
    }

    return interact;
}
bool AgentInteract::executeTake( Verb p_target, Result& io_result ) {
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
bool AgentInteract::executeDrop( Verb p_target, Result& io_result ) {
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
bool AgentInteract::executeOpen( Verb p_target, Result& io_result ) {
/*
This method is broken.
* Property value always being set to '1'.
* Only grate can be opened atm.
*/

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
bool AgentInteract::executeOn( Verb p_target, Result& io_result ) {
	/*
    This method is broken in several ways, be sure to fix.
    * Any carried object may be activated, even though that may not be possible.
    * Only carried objects may be activated.
    * 'Activated' meaning property value set to '1'. 
    */

    AdventData& ad = Singleton<AdventData>::get();
    bool on = false;

    unsigned int targetId = p_target.getId();
    unsigned int objectId = targetId % 1000;

	Inventory& inventory = ad.adventurer.getInventory();
    if( inventory.carriesItem( objectId ) ) {
        inventory[ objectId ].setPropertyValue( 1 ); // Very sketchy. Be sure to find out a way to set property value of objects better.
        on = true;

        GUI::RenderString( s_confMessageObjectOn );
    } else {
        io_result.setSummary( s_confMessageObjectNotFound );
    }

	return on;
}