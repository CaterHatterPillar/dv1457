#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Verb.h"
#include "Object.h"
#include "Location.h"

class GameLogic {
public:
	GameLogic();
	~GameLogic();

	static bool canTravel( Destination p_destination, Location p_location );
	static bool canTakeObject( Verb p_target, Object p_object );
protected:
private:
};

#endif // GAMELOGIC_H