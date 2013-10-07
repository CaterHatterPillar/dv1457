#ifndef AGENTINTERACT_H
#define AGENTINTERACT_H

#include "Executioner.h"

/*
executeInteracts and executeInteractGeneral has a bunch of
duplicate code. Fix that please.
*/

class AgentInteract {
public:
	AgentInteract();
	~AgentInteract();

	static bool execute( ActionInteract* p_action, Result& io_result );
protected:
	static bool executeAction( 		ActionInteract* p_action, Result& io_result );
	static bool executeInteract( 	ActionInteract* p_action, Result& io_result );
	static bool executeInteracts( 	ActionInteract* p_action, Result& io_result );
private:
	static bool executeInteractGeneral( ActionInteract* p_action, Result& io_result );
	// Special case interactions:
	static bool executeTake( Verb p_target, Result& io_result );
	static void takeObject(Object p_object);
	static bool takeBird(Object p_object, Result& io_result);
	static bool executeDrop( Verb p_target, Result& io_result );
};

#endif // AGENTINTERACT_H