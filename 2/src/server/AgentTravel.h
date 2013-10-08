#ifndef AGENTTRAVEL_H
#define AGENTTRAVEL_H

#include "Agent.h"
#include "AdventData.h"
#include "Executioner.h"

class AgentTravel {
public:
	AgentTravel( AdventData& p_ad, Agent* p_agent );
	~AgentTravel();

	bool execute( ActionTravel* p_action, Result& io_result );
protected:
	bool executeLook();
	bool executeTravel( ActionTravel* p_action, Result& io_result );

	bool condObjectCarry( unsigned int p_objectId );
	bool condObjectLocation( unsigned int p_objectId );
private:
	AdventData* m_ad;
	Agent* m_agent;
};

#endif // AGENTTRAVEL_H