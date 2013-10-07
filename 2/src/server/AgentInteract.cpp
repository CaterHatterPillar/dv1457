#include "Common.h"
#include "AgentInteract.h"
#include "ActionFactory.h"
#include "AgentTravel.h"

AgentInteract::AgentInteract( AdventData& p_ad, Agent* p_agent ) {
    m_ad = &p_ad;
    m_agent = p_agent;
}
AgentInteract::~AgentInteract() {
	// Do nothing.
}

bool AgentInteract::execute( ActionInteract* p_action, Result& io_result ) {
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
    Verb action = p_action->getAction();
    unsigned idAction = action.getId();
    switch( idAction ) {
        case VerbIdsAction_INVEN:
            GUI::RenderInventory( (*m_ad), m_ad->adventurer.getInventory() );
            executedAction = true;
            break;
        case VerbIdsAction_WAVE:
            executedAction = executeWave( io_result );
            break;
        default:
            throw ExceptionAdvent( "Encountered unsupported Action ID in AgentInteract::executeAction()." );
            break;
    }

    return executedAction;
}
bool AgentInteract::executeInteract( ActionInteract* p_action, Result& io_result ) {
    bool interact = false;
    Verb action = p_action->getAction();
    Verb target = p_action->getTargets().front();

    // Perform special-case action of generic action:
    unsigned idAction = action.getId();
    switch( idAction )
    {
    case VerbIdsAction_TAKE:
        interact = AgentInteract::executeTake( target, io_result );
        break;
    case VerbIdsAction_DROP:
        interact = AgentInteract::executeDrop( target, io_result );
        break;
    case VerbIdsAction_EAT:
        interact = executeEat(target, io_result);
        break;
    case VerbIdsAction_FILL:
        interact = executeFill(target, io_result);
        break;
    case VerbIdsAction_DRINK:
        interact = executeDrink(target, io_result);
        break;
    case VerbIdsAction_WAVE:
        interact = executeWave(target, io_result);
        break;
    default:
        interact = AgentInteract::executeInteractGeneral( p_action, io_result );
        break;
    }

    return interact;
}
bool AgentInteract::executeInteracts( ActionInteract* p_action, Result& io_result ) {
    bool interaction = false;

    Verb action = p_action->getAction();
    std::vector< Verb > targets = p_action->getTargets();
    Verb subject = targets[ 0 ];
    Verb subjector = targets[ 1 ]; // eww

    unsigned idSubject      = subject.getId()   % 1000;
    unsigned idSubjector    = subjector.getId() % 1000; // Remember to convert to objet ids.
    unsigned idAction       = action.getId();

    Relation r;
    bool hasRelation = m_ad->relations.hasRelation( idSubject, idSubjector, idAction, r );
    if( hasRelation==true ) {
        Object& oSubject = m_ad->map.getObject( r.getIdSubject() );
        Object& oSubjector = m_ad->map.getObject( r.getIdSubjector() );

        bool onSiteSubject = m_ad->isOnSite( oSubject );
        bool onSiteSubjector = m_ad->isOnSite( oSubjector );
        if( onSiteSubject==true &&
            onSiteSubjector==true ) {
            oSubject.setPropertyValue( r.getInfluence() );
            GUI::RenderString( (*m_ad), r.getOutput() );
            interaction = true;
        }
    }

    if( interaction==false ) {
        io_result.setSummary( "That won't work!" );
    }
    return interaction;
}

bool AgentInteract::executeInteractGeneral( ActionInteract* p_action, Result& io_result ) {
    bool interaction = false;
    Verb action = p_action->getAction();
    Verb target = p_action->getTargets().front();
    unsigned idAction = action.getId();
    unsigned idSubject = target.getId() % 1000;

    Relation r;
    bool hasRelation = m_ad->relations.hasRelation( idSubject, idAction, r );
    if( hasRelation==true ) {
        Object& oSubject = m_ad->map.getObject( r.getIdSubject() );
        bool onSiteSubject = m_ad->isOnSite( oSubject );
        if( onSiteSubject==true ) {
            oSubject.setPropertyValue( r.getInfluence() );
            GUI::RenderString( (*m_ad), r.getOutput() );
            interaction = true;
        }
    }

    if( interaction==false ) {
        io_result.setSummary( "That won't work!" );
    }
     return interaction;
}
bool AgentInteract::executeTake( Verb p_target, Result& io_result ) {
    bool interact = false;

    Location location = m_ad->map[ m_ad->adventurer.getIdLocation() ];
    std::vector< unsigned > locationObjectIds = location.getObjectIds();
    for( unsigned i = 0; i < locationObjectIds.size() && interact==false; i++ ) {
        unsigned objectId = locationObjectIds[ i ];
        Object object = m_ad->map.getObject( objectId );

        unsigned targetId = p_target.getId();
        unsigned objectIdForTarget = targetId % 1000;
        if( objectIdForTarget==object.getId()) {
            interact = true;
        }
        else {
            io_result.setSummary(s_confMessageObjectNotFound);
        }

        if(interact == true && object.isImmovable()==true) {
            interact = false;
            io_result.setSummary("You cannot take that item.");
        }
        if(interact == true && m_ad->adventurer.getInventory().isFull()==true) {
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
    //Loot object.
    m_ad->adventurer.getInventory().appendItem( p_object.getId() );
    // Remove object from location:
    m_ad->map[ m_ad->adventurer.getIdLocation() ].objectIdRemove( p_object.getId() );
    GUI::RenderString( (*m_ad), s_confMessageObjectTaken );
}
bool AgentInteract::takeBird(Object p_object, Result& io_result) {
    bool success = false;
    bool hasRod  = false;
    bool hasCage = false;
    
    Inventory invent = m_ad->adventurer.getInventory();
    if( invent.carriesItem( ObjectIds_ROD )==true ) {
        hasRod = true;
    }
    if( invent.carriesItem( ObjectIds_CAGE )==true ) {
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
    Location location = m_ad->map[ m_ad->adventurer.getIdLocation() ];
    bool interact = false;

    unsigned int targetId = p_target.getId();
    unsigned int objectId = targetId % 1000;

    Inventory& inventory = m_ad->adventurer.getInventory();
    if( inventory.carriesItem( objectId )==true ) {
        inventory.removeItem( objectId );
        m_ad->map[ location.getId() ].objectIdAppend( objectId );
        GUI::RenderString( (*m_ad), s_confMessageObjectDropped );
        interact = true;
    }

    return interact;
}

bool AgentInteract::executeEat(Verb p_target, Result& io_result) {
    unsigned targetId = p_target.getId();
    unsigned objectId = targetId % 1000;

    bool fromInventory = false;
    bool fromLocation = false;

    int id = searchInventory(objectId);
    if( id != -1) {
        fromInventory = true;
    }
    else {
        id = searchLocation(objectId);
        if(id != -1)
            fromLocation = true;
    }

    bool success = false;
    if(id != -1) {
        success = eatObject(id, io_result);
        if(success && fromInventory) {
            m_ad->adventurer.getInventory().removeItem(id);
        }
        else if(success && fromLocation) {
            m_ad->map[ m_ad->adventurer.getIdLocation() ].objectIdRemove(id);
        }
    }
    else
        io_result.setSummary(s_confMessageObjectNotFound);
    return success;
}
bool AgentInteract::eatObject(int p_objId, Result& io_result) {
    bool success = false;

    if(p_objId == ObjectIds_FOOD) {
        GUI::RenderString( (*m_ad), "Delecious!");
        success = true;
    }
    else if(p_objId == ObjectIds_BIRD) {
        io_result.setSummary("If you take it out of the cage the bird will likely fly away from you.");
    }
    else {
        io_result.setSummary("That's plainly inedible.");
    }

    return success;
}

bool AgentInteract::executeFill(Verb p_target, Result& io_result) {
    bool success = false;
    int id = -1;
    Location location = m_ad->map[ m_ad->adventurer.getIdLocation() ];

    unsigned objId = p_target.getId() % 1000;

    id = searchInventory(objId);

    if(location.hasWater()) {
        if(id == ObjectIds_BOTTLE) {
            success = fillBottle(io_result);
        }
        else if(id == ObjectIds_NOT_FOUND) {
            success = false;
            io_result.setSummary(s_confMessageObjectNotFound);
        }
        else {
            io_result.setSummary("That item can't hold any liquids.");
        }
    }
    else {
        success = false;
        io_result.setSummary("You can't do that here.");
    }


    return success;
}
bool AgentInteract::fillBottle(Result& io_result) {
    bool success = false;
    int id = searchInventory(ObjectIds_WATER);
    if(id == -1) {
        m_ad->adventurer.getInventory().appendItem(m_ad->map.getObject(ObjectIds_WATER).getId());
        success = true;
        GUI::RenderString( (*m_ad), "The bottle is now full of water.");
    }
    else {
        success = false;
        io_result.setSummary("The bottle is already full");
    }
    return success;
}

bool AgentInteract::executeDrink(Verb p_target, Result& io_result) {
    Location location   = m_ad->map[ m_ad->adventurer.getIdLocation() ];
    bool success        = false;

    int objId = p_target.getId() % 1000;
    if(objId == ObjectIds_WATER) {
        if(location.hasWater()) {
            success = true;
            GUI::RenderString( (*m_ad), "(the stream)\nYou have taken a drink from the stream. The water tastes strongly of minerals, but is not unpleasant. It is extremely cold.");
        }
        else {
            success = drinkFromInventory(io_result);
        }
    }
    else {
        success = false;
        io_result.setSummary("You can't drink that.");
    }

    return success;
}
bool AgentInteract::drinkFromInventory(Result& io_result) {
    bool success   = false;

    int id = searchInventory(ObjectIds_WATER);
    if(id != ObjectIds_NOT_FOUND) {
        success = true;
        GUI::RenderString( (*m_ad), "You have taken a drink from yout bottle. The water tastes strongly of minerals, but is not unpleasant. It is extremely cold.");
        m_ad->adventurer.getInventory().removeItem(id);
    }
    else {
        success = false;
        io_result.setSummary(s_confMessageObjectNotFound);
    }

    return success;
}

bool AgentInteract::executeWave(Result& io_result) {
    bool success = true;
    GUI::RenderString( (*m_ad), "You wave, feeling foolish.");
    return success;
}
bool AgentInteract::executeWave(Verb p_target, Result& io_result) {
    bool success = false;

    int objId = p_target.getId() % 1000;
    int id = searchInventory(objId);
    if(id != ObjectIds_NOT_FOUND) {
        std::string name = m_ad->map.getObject(id).getNameTextFriendly();
        GUI::RenderString( (*m_ad), "You look foolish waving the " + name);
        success = true;
    }
    else {
        success = false;
        io_result.setSummary(s_confMessageObjectNotFound);
    }

    return success;
}

int AgentInteract::searchInventory(int p_objId) {
    int id = ObjectIds_NOT_FOUND;

    for(unsigned int i=0; i<m_ad->adventurer.getInventory().getNumItems(); i++) {
        if(p_objId == m_ad->adventurer.getInventory().getItemId(i)) {
            id = p_objId;
        }
    }
    return id;   
}
int AgentInteract::searchLocation(int p_objId) {
    int id = ObjectIds_NOT_FOUND;

    Location location = m_ad->map[ m_ad->adventurer.getIdLocation() ];
    std::vector< unsigned > locationObjectIds = location.getObjectIds();
    for(unsigned int i = 0; i < locationObjectIds.size(); i++) {
        if(p_objId == locationObjectIds[i]) {
            id = locationObjectIds[i];
        }
    }
    return id;
}
