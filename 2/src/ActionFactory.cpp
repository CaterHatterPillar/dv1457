#include "ActionFactory.h"

ActionFactory::ActionFactory() {

}
ActionFactory::~ActionFactory() {
	// Do nothing.
}

Action* ActionFactory::actionInvalid() {
	return new Action( ActionTypes_INVALID );
}
Action* ActionFactory::actionTravel( Verb p_target ) {
	return new ActionTravel( ActionTypes_TRAVEL, p_target );
}