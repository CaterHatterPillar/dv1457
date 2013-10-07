#include "Agent.h"
#include "Common.h"
#include "AgentMagic.h"
#include "AgentTravel.h"
#include "AgentInteract.h"

Agent::Agent( AdventData& p_ad ) {
	m_travel 	= new AgentTravel( 		p_ad, this );
	m_interact 	= new AgentInteract( 	p_ad, this );
	m_magic 	= new AgentMagic( 		p_ad, this );
}
Agent::~Agent() {
	assert( m_travel );
	assert( m_interact );
	assert( m_magic );

	delete m_travel;
	delete m_interact;
	delete m_magic;
}

bool Agent::execute( Action* p_action, Result& io_result, AgentTypes p_target ) {
	bool success = false;
	switch( p_target ) {
		case AgentTypes_TRAVEL:
			success = m_travel->execute( (ActionTravel*)p_action, io_result );
			break;
		case AgentTypes_INTERACT:
			success = m_interact->execute( (ActionInteract*)p_action, io_result );
			break;
		case AgentTypes_MAGIC:
			success = m_magic->execute( (ActionMagic*)p_action, io_result );
			break;
		default:
			throw ExceptionAdvent( "Encountered unknown AgentType in Agent::execute." );
			break;
	};
	return success;
}