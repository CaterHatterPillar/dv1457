#include <cassert>

#include "ActionFactory.h"
#include "Common.h"
#include "Object.h"
#include "GameLogic.h"
#include "Executioner.h"

Executioner::Executioner() {
    m_feefie.resize(0, false);
    m_xyzzy  = false;
    m_plugh  = false;
    m_plover = false;
    m_fee    = false;
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
    if(travel) {
        GUI::RenderLocation( ad.adventurer.getLocation() );
        discoverMagicWords( ad.adventurer.getLocation().getId() );
    }
    else
        io_result.setSummary("You can't go that way");

    return travel;
}
bool Executioner::executeInteract( ActionInteract* p_action, Result& io_result ) {
    AdventData& ad = Singleton<AdventData>::get();

    bool interact = false;
    
    Verb action = p_action->getAction();
    Verb target = p_action->getTarget();

    switch( action.getId() )
    {
    case VerbIds_TAKE:
        interact = interactTake(target, io_result);
        break;
    case VerbIds_DROP:
        interact = interactDrop(target, io_result);
        break;
    case VerbIds_OPEN:
        break;
    case VerbIds_SAY:
        interact = interactSay(target, io_result);
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

bool Executioner::interactTake(Verb p_target, Result& io_result) {
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
    if( interact==false ) {
        io_result.setSummary( s_confMessageObjectNotFound );
    }
    return interact;
}

bool Executioner::interactDrop(Verb p_target, Result& io_result) {
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
    if( interact==false ) {
        io_result.setSummary( s_confMessageObjectNotFound );
    }
    return interact;
}

bool Executioner::interactSay(Verb p_target, Result& io_result) {
    AdventData& ad = Singleton<AdventData>::get();
    Location location = ad.adventurer.getLocation();
    bool interact = false;

    switch(p_target.getId())
    {
    case MeaningfulWords_XYZZY:
        teleport(p_target, m_xyzzy, io_result);
        break;
    case MeaningfulWords_PLUGH:
        teleport(p_target, m_plugh, io_result);
        break;
    case MeaningfulWords_PLOVE:
        teleport(p_target, m_plover, io_result);
        break;
    case MeaningfulWords_FEE:
        feefie(0, io_result);
        break;
    case MeaningfulWords_FIE:
        feefie(1, io_result);
        break;
    case MeaningfulWords_FOE:
        feefie(2, io_result);
        break;
    case MeaningfulWords_FOO:
        feefie(3, io_result);
        break;
    case MeaningfulWords_FUM:
        feefie(4, io_result);
        break;
    default:
        io_result.setSummary("(to yourself) \nNothing happens.");
        break;
    }
    
    return interact;
}

bool Executioner::teleport(Verb p_target, bool p_canTeleport, Result& io_result)
{
    bool success = false;

    if(p_canTeleport) {
        Action* action = ActionFactory::actionTravel( p_target );
        success = executeTravel((ActionTravel*)action, io_result);
    }
    
    if(!success)
        io_result.setSummary("Nothinh happens!");

    return success;
}

void Executioner::discoverMagicWords(int p_locationId)
{
    switch(p_locationId)
    {
    case MagicWordLocations_XYZZY:
        m_xyzzy = true;
        break;
    case MagicWordLocations_PLUGH:
        m_plugh = true;
        break;
    case MagicWordLocations_PLOVER:
        m_plover = true;
        break;
    case MagicWordLocations_FEE:
        m_fee = true;
        break;
    }

}

bool Executioner::feefie(unsigned p_wordIndex, Result& io_result)
{
    bool success = true;
    
    if(p_wordIndex == 0)
        m_feefie.push_back(true);
    else {
        if(p_wordIndex > m_feefie.size())
            success = false;
        if(success){
            for(unsigned int i=0; i<m_feefie.size() && success; i++)
                success = m_feefie[i];
        }
        
        if(success)
            m_feefie.push_back(true);
        else
            m_feefie.resize(0, false);    
    }
    if(success && p_wordIndex == 3) {
        GUI::RenderString("Correct sequence!");
        m_feefie.resize(0, false);
        if(m_fee) {
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
}
