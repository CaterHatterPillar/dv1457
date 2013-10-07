#include "Common.h"
#include "AgentInteract.h"
#include "ActionFactory.h"
#include "AgentTravel.h"

AgentInteract::AgentInteract() {

}
AgentInteract::~AgentInteract() {
	// Do nothing.
}

bool AgentInteract::execute( ActionInteract* p_action, Result& io_result ) {
	AdventData& ad = Singleton<AdventData>::get();
    bool interact = false;
    
    ActionInteract::ActionInteractTypes ait = p_action->getTypeActionInteract();
    switch( ait ) {
        case ActionInteract::ActionInteractTypes_ACTION:
            interact = executeAction( p_action, io_result );
            break;
        case ActionInteract::ActionInteractTypes_INTERACT:
            interact = executeInteract( p_action, io_result );
            break;
        case ActionInteract::ActionInteractTypes_INTERACTS:
            interact = executeInteracts( p_action, io_result );
            break;
        default:
            throw ExceptionAdvent( "Encountered unknown ActionInteract-type: " + Util::toString( ait ) );
            break;
    }

    return interact;
}

bool AgentInteract::executeAction( ActionInteract* p_action, Result& io_result ) {
    bool executedAction = false;
    AdventData& ad = Singleton<AdventData>::get();

    Verb action = p_action->getAction();
    unsigned idAction = action.getId();
    switch( idAction ) {
        case VerbIdsAction_INVEN:
            GUI::RenderInventory( ad.adventurer.getInventory() );
            executedAction = true;
            break;
        default:
            throw ExceptionAdvent( "Encountered unsupported Action ID in AgentInteract::executeAction()." );
            break;
    }

    return executedAction;
}
bool AgentInteract::executeInteract( ActionInteract* p_action, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();
    bool interact = false;

    Verb action = p_action->getAction();
    Verb target = p_action->getTargets().front();

    unsigned idAction = action.getId();
    switch( idAction )
    {
    case VerbIdsAction_TAKE:
        interact = AgentInteract::executeTake( target, io_result );
        break;
    case VerbIdsAction_DROP:
        interact = AgentInteract::executeDrop( target, io_result );
        break;
    case VerbIdsAction_OPEN:
        interact = AgentInteract::executeOpen( target, io_result );
        break;
    case VerbIdsAction_ON:
        interact = AgentInteract::executeOn( target, io_result );
        break;
    default:
        throw ExceptionAdvent( "Unrecognized action id in AgentInteract::executeInteract!" );
        break;
    }

    return interact;
}
bool AgentInteract::executeInteracts( ActionInteract* p_action, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();
    bool interaction = false;

    Verb action = p_action->getAction();
    std::vector< Verb > targets = p_action->getTargets();
    Verb subject = targets[ 0 ];
    Verb subjector = targets[ 1 ]; // eww

    unsigned idSubject      = subject.getId()   % 1000;
    unsigned idSubjector    = subjector.getId() % 1000; // Remember to convert to objet ids.
    unsigned idAction       = action.getId();

     Relation r;
    bool hasRelation = ad.relations.hasRelation( idSubject, idSubjector, idAction, r );
    Object& oSubject = ad.map.getObject( r.getIdSubject() );
    Object& oSubjector = ad.map.getObject( r.getIdSubjector() );

    bool onSiteSubject = ad.isOnSite( oSubject );
    bool onSiteSubjector = ad.isOnSite( oSubjector );
    if( hasRelation==true   &&
        onSiteSubject==true &&
        onSiteSubjector==true ) {
        oSubject.setPropertyValue( r.getInfluence() );
        GUI::RenderString( r.getOutput() );
        interaction = true;
    } else {
        io_result.setSummary( "That won't work!" );
    }

    return interaction;
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
        if( objectIdForTarget==object.getId()) {
            interact = true;
        }
        else {
            io_result.setSummary("You see no such item.");
        }

        if(interact == true && object.isImmovable()==true) {
            interact = false;
            io_result.setSummary("You cannot take that item.");
        }
        if(interact == true && ad.adventurer.getInventory().isFull()==true) {
            interact = false;
            io_result.setSummary("Your inventory is full.");
        }

        if( interact==true ) {
            if(object.getId() == ObjectIds_BIRD) {
                interact = takeBird(object, io_result);
            }
            else {
                takeObject(object);
            }
        }
    }
    return interact;
}
void AgentInteract::takeObject(Object p_object) {
    AdventData& ad = Singleton<AdventData>::get();
    //Loot object.
    ad.adventurer.getInventory().appendItem( p_object );
    // Remove object from location:
    ad.map[ad.adventurer.getLocation().getId()].objectIdRemove(p_object.getId());
    GUI::RenderString( s_confMessageObjectTaken );
}
bool AgentInteract::takeBird(Object p_object, Result& io_result) {
    AdventData& ad = Singleton<AdventData>::get();
    
    bool success = false;
    bool hasRod  = false;
    bool hasCage = false;
    
    Inventory invent = ad.adventurer.getInventory();
    for(unsigned int i=0; i<invent.getNumItems(); i++) {
        if(invent[i].getId() == ObjectIds_ROD)
            hasRod = true;
        if(invent[i].getId() == ObjectIds_CAGE)
            hasCage = true;   
    }

    if(hasRod == false && hasCage == true) {
        takeObject(p_object);
        success = true;
    }
    else if(hasCage == false)
        io_result.setSummary("You can catch the bird but you cannot carry it.");
    else if(hasRod == true)
        io_result.setSummary("The bird was unafraid when you entered but as you approach it, it becomes disturbed and you cannot catch it.");

    return success;
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