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

	static bool executeSay(Verb p_target, Result& io_result);

	static bool sayXyzzy(Verb p_target, Result& io_result);
	static bool sayPlugh(Verb p_target, Result& io_result);
	static bool sayPlover(Verb p_target, Result& io_result);

	static bool teleport(Verb p_target, bool p_canTeleport, Result& io_result);
	static bool feefie(unsigned p_wordIndex, Result& io_result);
	static std::vector<bool> s_feefie;
};

#endif // AGENTINTERACT_H