#ifndef ACTION_H
#define ACTION_H

#include "Verb.h"

enum ActionTypes {
	ActionTypes_INDEX_BEGIN	= 0,
	
	ActionTypes_INVALID		= 1,
	ActionTypes_TRAVEL		= 2,
	ActionTypes_INTERACT	= 3,/*,
	ActionTypes_SPECIAL*/

	ActionTypes_INDEX_END	= 4
};
	
static const char* ActionTypesString[] = { 
	"ActionTypes_INDEX_BEGIN", // hack

	"ActionTypes_INVALID", 
	"ActionTypes_TRAVEL",
	"ActionTypes_INTERACT",/*,
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
	ActionInteract( Verb p_action, Verb p_target );
	~ActionInteract();

	std::string toString();

	Verb getAction() const;
	Verb getTarget() const;
protected:
private:
	Verb m_action;
	Verb m_target;
};

#endif // ACTION_H