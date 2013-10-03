#ifndef AGENTINTERACT_H
#define AGENTINTERACT_H

#include "Executioner.h"

class AgentInteract {
public:
	AgentInteract();
	~AgentInteract();

	static bool execute( ActionInteract* p_action, Result& io_result );
protected:
private:
	static bool executeTake( Verb p_target, Result& io_result );
	static bool executeDrop( Verb p_target, Result& io_result );
	static bool executeOpen( Verb p_target, Result& io_result );
	static bool executeOn( Verb p_target, Result& io_result );
};

#endif // AGENTINTERACT_H