#ifndef EXECUTIONER_H
#define EXECUTIONER_H

#include "Action.h"
#include "Result.h"
#include "Location.h"
#include "Destination.h"

class Executioner {
public:
	Executioner();
	~Executioner();

	bool execute( Action* p_action, Result& io_result );
protected:
private:
	bool executeTravel( 	ActionTravel* 	p_action, Result& io_result );
	// Currently we assume that all interactions are either picking up, or dropping movable objects:
	bool executeInteract( 	ActionInteract* p_action, Result& io_result );
	bool executeGame( 		ActionGame*		p_action, Result& io_result );

	bool interactTake(Verb p_target, Result& io_result);
	bool interactDrop(Verb p_target, Result& io_result);
	bool interactSay(Verb p_target, Result& io_result);
};

#endif // EXECUTIONER_H