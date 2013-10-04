#ifndef AGENTTRAVEL_H
#define AGENTTRAVEL_H

#include "Executioner.h"

class AgentTravel {
public:
	AgentTravel();
	~AgentTravel();

	static bool execute( ActionTravel* p_action, Result& io_result );
protected:
private:
	static bool executeLook();
	static bool executeTravel( ActionTravel* p_action, Result& io_result );
};

#endif // AGENTTRAVEL_H