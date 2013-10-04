#ifndef AGENTINTERACT_H
#define AGENTINTERACT_H

#include "Executioner.h"

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
	static bool executeTake( Verb p_target, Result& io_result );
	static void takeObject(Object p_object);
	static bool takeBird(Object p_object, Result& io_result);

	static bool executeDrop( Verb p_target, Result& io_result );
	static bool executeOpen( Verb p_target, Result& io_result );
	static bool executeOn( Verb p_target, Result& io_result );

	static bool executeSay(Verb p_target, Result& io_result);
	static bool teleport(Verb p_target, bool p_canTeleport, Result& io_result);
	static bool feefie(unsigned p_wordIndex, Result& io_result);
	
	static bool executeEat(Verb p_target, Result& io_result);;
	static bool eatObject(int p_objId, Result& io_result);

	static int searchInventory(int p_objId);
	static int searchLocation(int p_objId);

	static std::vector<bool> s_feefie;

};

#endif // AGENTINTERACT_H