#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "Action.h"

class ActionFactory {
public:
	ActionFactory();
	~ActionFactory();

	static Action* actionInvalid();
	static Action* actionTravel(Verb p_target );
	static Action* actionInteract( Verb p_action, std::vector< Verb > p_targets );
	static Action* actionMagic( Verb p_spell );
protected:
private:
};

#endif // ACTIONFACTORY_H