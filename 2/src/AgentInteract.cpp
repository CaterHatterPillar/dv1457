#include "Common.h"
#include "AgentInteract.h"
#include "ActionFactory.h"
#include "AgentTravel.h"

std::vector<bool> AgentInteract::s_feefie;

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
    case VerbIds_SAY:
        interact = AgentInteract::executeSay( target, io_result );
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

bool AgentInteract::executeSay(Verb p_target, Result& io_result) {
    AdventData& ad = Singleton<AdventData>::get();
    Location location = ad.adventurer.getLocation();
    bool interact = false;
    bool canTeleport = false;

    switch(p_target.getId())
    {
    case MeaningfulWords_XYZZY:
        canTeleport = ad.adventurer.getMagic().getXyzzy();
        interact = teleport(p_target, canTeleport, io_result);
        break;
    case MeaningfulWords_PLUGH:
        canTeleport = ad.adventurer.getMagic().getPlugh();
        interact = teleport(p_target, canTeleport, io_result);
        break;
    case MeaningfulWords_PLOVE:
        canTeleport = ad.adventurer.getMagic().getPlover();
        interact = teleport(p_target, canTeleport, io_result);
        break;
    case MeaningfulWords_FEE:
        interact = feefie(0, io_result);
        break;
    case MeaningfulWords_FIE:
        interact = feefie(1, io_result);
        break;
    case MeaningfulWords_FOE:
        interact = feefie(2, io_result);
        break;
    case MeaningfulWords_FOO:
        interact = feefie(3, io_result);
        break;
    case MeaningfulWords_FUM:
        interact = feefie(4, io_result);
        break;
    default:
        io_result.setSummary("(to yourself) \nNothing happens.");
        break;
    }
    
    return interact;
}

bool AgentInteract::teleport(Verb p_target, bool p_canTeleport, Result& io_result)
{
    bool success = false;

    if(p_canTeleport) {
        Action* action = ActionFactory::actionTravel( p_target );
        success = AgentTravel::execute((ActionTravel*)action, io_result);
    }
    
    if(!success)
        io_result.setSummary("Nothing happens!");

    return success;
}

bool AgentInteract::feefie(unsigned p_wordIndex, Result& io_result)
{
    AdventData& ad = Singleton<AdventData>::get();

    bool success = true;
    
    if(p_wordIndex == 0)
        s_feefie.push_back(true);
    else {
        if(p_wordIndex > s_feefie.size())
            success = false;
        if(success){
            for(unsigned int i=0; i<s_feefie.size() && success; i++)
                success = s_feefie[i];
        }
        
        if(success)
            s_feefie.push_back(true);
        else
            s_feefie.resize(0, false);    
    }
    if(success && p_wordIndex == 3) {
        s_feefie.resize(0, false);
        if(ad.adventurer.getMagic().getFee()) {
            GUI::RenderString("Move eggs back to the giant room. Not yet implemented");
        }
        else {
            GUI::RenderString("Nothing happens!");
        }
    }
    else if(success)
        GUI::RenderString("Ok!");
    else
        io_result.setSummary("Get it right dummy!");

    return success;
}