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
	static void takeObject(Object p_object, Result& io_result );
	static bool takeBird(Object p_object, Result& io_result);
	static bool executeDrop( Verb p_target, Result& io_result );

	static bool executeOpen( Verb p_target, Result& io_result );
	static bool executeOn( Verb p_target, Result& io_result );
	
	static bool executeEat(Verb p_target, Result& io_result);;
	static bool eatObject(int p_objId, Result& io_result);

	static bool executeFill(Verb p_target, Result& io_result);
	static bool fillBottle(Result& io_result);

	static bool executeDrink(Verb p_target, Result& io_result);
	static bool drinkFromInventory(Result& io_result);

	static bool executeWave(Result& io_result);
	static bool executeWave(Verb p_target, Result& io_result);

	static int searchInventory(int p_objId);
	static int searchLocation(int p_objId);
};

#endif // AGENTINTERACT_H