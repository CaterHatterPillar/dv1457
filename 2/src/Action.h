#ifndef ACTION_H
#define ACTION_H

#include "Verb.h"

enum ActionTypes {
	ActionTypes_INDEX_BEGIN	= 0,
	
	ActionTypes_INVALID		= 1,
	ActionTypes_TRAVEL		= 2,
	ActionTypes_INTERACT	= 3,
	ActionTypes_MAGIC		= 4,/*,
	ActionTypes_SPECIAL*/

	ActionTypes_INDEX_END	= 5
};
	
static const char* ActionTypesString[] = { 
	"ActionTypes_INDEX_BEGIN", // hack

	"ActionTypes_INVALID", 
	"ActionTypes_TRAVEL",
	"ActionTypes_INTERACT",
	"ActionTypes_MAGIC",/*,
	"ActionTypes_SPECIAL"*/

	"ActionTypes_INDEX_END" // hack
};
static std::string ActionTypesAsString( ActionTypes p_actionType ) {
	return std::string( ActionTypesString[ p_actionType ] );
}

class Action {
public:
	Action( ActionTypes p_type );
	virtual ~Action();

	virtual std::string toString();
	bool isValid() const;

	ActionTypes getType() const;
protected:
private:
	ActionTypes m_type;
};

class ActionTravel : public Action {
public:
	ActionTravel( Verb p_target );
	~ActionTravel();

	std::string toString();

	Verb getTarget() const;
protected:
private:
	Verb m_target;
};

class ActionInteract : public Action {
public:
	ActionInteract( Verb p_action, std::vector< Verb > p_targets );
	~ActionInteract();

	enum ActionInteractTypes {
		ActionInteractTypes_ACTION,
		ActionInteractTypes_INTERACT,
		ActionInteractTypes_INTERACTS
	};

	std::string toString();
	ActionInteractTypes getTypeActionInteract();

	Verb getAction() const;
	std::vector< Verb > getTargets() const;
	unsigned getNumTargets() const;
protected:
private:
	Verb m_action;
	std::vector< Verb > m_targets;
};

class ActionMagic : public Action {
public:
	ActionMagic( Verb p_spell );
	~ActionMagic();

	std::string toString();

	Verb getSpell() const;
protected:
private:
	Verb m_spell;
};

#endif // ACTION_H