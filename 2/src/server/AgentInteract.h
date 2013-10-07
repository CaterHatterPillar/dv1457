#ifndef AGENTINTERACT_H
#define AGENTINTERACT_H

#include "Verb.h"
#include "Agent.h"
#include "Result.h"
#include "Action.h"
#include "AdventData.h"

/*
executeInteracts and executeInteractGeneral has a bunch of
duplicate code. Fix that please.
*/

class AgentInteract {
public:
	AgentInteract( AdventData& p_ad, Agent* p_agent );
	~AgentInteract();

	bool execute( ActionInteract* p_action, Result& io_result );
protected:
	bool executeAction( 	ActionInteract* p_action, Result& io_result );
	bool executeInteract( 	ActionInteract* p_action, Result& io_result );
	bool executeInteracts( 	ActionInteract* p_action, Result& io_result );
private:
	bool executeInteractGeneral( ActionInteract* p_action, Result& io_result );
	// Special case interactions:
	bool executeTake( Verb p_target, Result& io_result );
	void takeObject(Object p_object);
	bool takeBird(Object p_object, Result& io_result);
	bool executeDrop( Verb p_target, Result& io_result );

	bool executeOpen( Verb p_target, Result& io_result );
	bool executeOn( Verb p_target, Result& io_result );
	bool executeEat(Verb p_target, Result& io_result);;
	bool eatObject(int p_objId, Result& io_result);
	bool executeFill(Verb p_target, Result& io_result);
	bool fillBottle(Result& io_result);
	bool executeDrink(Verb p_target, Result& io_result);
	bool drinkFromInventory(Result& io_result);
	bool executeWave(Result& io_result);
	bool executeWave(Verb p_target, Result& io_result);
	int searchInventory(int p_objId);
	int searchLocation(int p_objId);

	AdventData* m_ad;
	Agent* m_agent;
};

#endif // AGENTINTERACT_H