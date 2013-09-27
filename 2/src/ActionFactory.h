#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "Action.h"

class ActionFactory {
public:
	ActionFactory();
	~ActionFactory();

	static Action* actionInvalid();
	static Action* actionTravel( Verb p_target );
protected:
private:
};

#endif // ACTIONFACTORY_H