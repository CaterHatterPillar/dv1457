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
	bool executeTravel( ActionTravel* p_action );

	// Game logic-ish:
	bool conditionsTravel( Destination p_destination, Location p_location );
};

#endif // EXECUTIONER_H