#include "Util.h"
#include "Action.h"

// Action
Action::Action( ActionTypes p_type ) {
	m_type = p_type;
}
Action::~Action() {
	// Do nothing.
}

std::string Action::toString() {
	return "Action: " + std::string( ActionTypesString[ m_type ] );
}

ActionTypes Action::getType() const {
	return m_type;
}

// ActionTravel
ActionTravel::ActionTravel( ActionTypes p_type, Verb p_target ) : Action( p_type ) {
	m_target = p_target;
}
ActionTravel::~ActionTravel() {
	// Do nothing.
}

std::string ActionTravel::toString() {
	return Action::toString() + " - Travel to target: " + Util::toString( m_target.getId() );
}

Verb ActionTravel::getTarget() const {
	return m_target;
}