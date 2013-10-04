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
	return new ActionTravel( p_target );
}
Action* ActionFactory::actionInteract( Verb p_action, std::vector< Verb > p_targets ) {
	return new ActionInteract( p_action, p_targets );
}