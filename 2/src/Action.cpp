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
ActionInteract::ActionInteract( Verb p_action, std::vector< Verb > p_targets ) : Action( ActionTypes_INTERACT ) {
	m_action = p_action;
	m_targets = p_targets;
}
ActionInteract::~ActionInteract() {
	// Do nothing.
}

std::string ActionInteract::toString() {
	std::string interact = Action::toString() + " - Interact with target verbs: [ ";
	for( unsigned i = 0; i < m_targets.size(); i++ ) {
		interact += m_targets[ 0 ].toString() + " ";
	}
	interact += "] with verb [" + m_action.toString() + "].";
	return interact;
}
ActionInteract::ActionInteractTypes ActionInteract::getTypeActionInteract() {
	ActionInteractTypes type;
	switch( getNumTargets() ) {
		case 0:
			type = ActionInteractTypes_ACTION;
			break;
		case 1:
			type = ActionInteractTypes_INTERACT;
			break;
		default: // More than one.
			type = ActionInteractTypes_INTERACTS;
			break;
	}
	return type;
}

Verb ActionInteract::getAction() const {
	return m_action;
}
std::vector< Verb > ActionInteract::getTargets() const {
	return m_targets;
}
unsigned ActionInteract::getNumTargets() const {
	return m_targets.size();
}

// ActionMagic
ActionMagic::ActionMagic( Verb p_spell ) : Action( ActionTypes_MAGIC ) {
	m_spell = p_spell;
}
ActionMagic::~ActionMagic() {
	// Do nothing.
}

std::string ActionMagic::toString() {
	std::string magic = Action::toString() + " - Cast spell: " + m_spell.toString() + ".";
	return magic;
}

Verb ActionMagic::getSpell() const {
	return m_spell;
}