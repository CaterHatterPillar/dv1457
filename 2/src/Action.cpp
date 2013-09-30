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
bool Action::isValid() const {
	bool valid = true;
	if( m_type==ActionTypes_INVALID ) {
		valid = false;
	}
	return valid;
}

ActionTypes Action::getType() const {
	return m_type;
}

// ActionTravel
ActionTravel::ActionTravel( Verb p_target ) : Action( ActionTypes_TRAVEL ) {
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

// ActionInteract
ActionInteract::ActionInteract( Verb p_action, Verb p_target ) : Action( ActionTypes_INTERACT ) {
	m_action = p_action;
	m_target = p_target;
}
ActionInteract::~ActionInteract() {
	// Do nothing.
}

std::string ActionInteract::toString() {
	return Action::toString() + " - Interact with target verb: [" + m_target.toString() + "] with verb [" + m_action.toString() + "].";
}

Verb ActionInteract::getAction() const {
	return m_action;
}
Verb ActionInteract::getTarget() const {
	return m_target;
}

// ActionGame
ActionGame::ActionGame( ActionGameTypes p_actionGameType ) : Action( ActionTypes_GAME ) {
	m_actionGameType = p_actionGameType;
}
ActionGame::~ActionGame() {
	// Do nothing.
}

std::string ActionGame::toString() {
	return Action::toString() + " - " + std::string( ActionGameTypesString[ m_actionGameType ] ) + ".";
}

ActionGameTypes ActionGame::getActionGameType() const {
	return m_actionGameType;
}