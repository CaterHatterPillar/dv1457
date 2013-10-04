
#include <cassert>

#include "ActionFactory.h"

#include "Common.h"
#include "Object.h"
#include "Location.h"
#include "AgentMagic.h"
#include "Destination.h"
#include "Executioner.h"
#include "AgentTravel.h"
#include "AgentInteract.h"

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
			executed = AgentTravel::execute( (ActionTravel*)p_action, io_result );
			break;
        case ActionTypes_INTERACT:
            executed = AgentInteract::execute( (ActionInteract*)p_action, io_result );
            break;
		case ActionTypes_MAGIC:
			executed = AgentMagic::execute( (ActionMagic*)p_action, io_result );
			break;
		default:
			throw ExceptionAdventNotYetImplemented( "Encountered unknown ActionTypes: " + std::string( ActionTypesString[ actionType ] ) + "." );
			break;
	}

	return executed;
}
