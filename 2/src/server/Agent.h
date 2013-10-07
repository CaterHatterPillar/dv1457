#ifndef AGENT_H
#define AGENT_H

class AgentMagic;
class AgentTravel;
class AgentInteract;

#include "Action.h"
#include "Result.h"
#include "AdventData.h"

enum AgentTypes {
	AgentTypes_TRAVEL,
	AgentTypes_INTERACT,
	AgentTypes_MAGIC
};

class Agent {
public:
	Agent( AdventData& p_ad );
	~Agent();

	bool execute( Action* p_action, Result& io_result, AgentTypes p_target );
protected:
private:
	AgentTravel*	m_travel;
	AgentInteract*	m_interact;
	AgentMagic*		m_magic;
};

#endif // AGENT_H