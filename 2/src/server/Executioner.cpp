#include "ActionFactory.h"

#include "Common.h"
#include "AgentMagic.h"
#include "Executioner.h"
#include "AgentTravel.h"
#include "AgentInteract.h"

Executioner::Executioner( AdventData& p_ad ) {
	m_agent = new Agent( p_ad );
}
Executioner::~Executioner() {
	assert( m_agent );
	delete m_agent;
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
			executed = m_agent->execute( p_action, io_result, AgentTypes_TRAVEL );
			break;
        case ActionTypes_INTERACT:
            executed = m_agent->execute( p_action, io_result, AgentTypes_INTERACT );
            break;
		case ActionTypes_MAGIC:
			executed = m_agent->execute( p_action, io_result, AgentTypes_MAGIC );
			break;
		default:
			throw ExceptionAdventNotYetImplemented( "Encountered unknown ActionTypes: " + std::string( ActionTypesString[ actionType ] ) + "." );
			break;
	}

	return executed;
}