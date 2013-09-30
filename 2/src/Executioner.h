#ifndef EXECUTIONER_H
#define EXECUTIONER_H

#include "Action.h"
#include "Location.h"
#include "Destination.h"

class Executioner {
public:
	Executioner();
	~Executioner();

	bool execute( Action* p_action );
protected:
private:
	bool executeTravel( 	ActionTravel* 	p_action );
	bool executeInteract( 	ActionInteract* p_action );
	bool executeGame( 		ActionGame*		p_action );
};

#endif // EXECUTIONER_H