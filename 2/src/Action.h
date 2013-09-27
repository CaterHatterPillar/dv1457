#ifndef ACTION_H
#define ACTION_H

#include "Verb.h"

enum ActionTypes {
	ActionTypes_INVALID,
	ActionTypes_TRAVEL/*,
	ActionTypes_INTERACTION,
	ActionTypes_SPECIAL*/
};
static const char* ActionTypesString[] = { 
	"ActionTypes_INVALID", 
	"ActionTypes_TRAVEL"
};

class Action {
public:
	Action( ActionTypes p_type );
	virtual ~Action();

	virtual std::string toString();

	ActionTypes getType() const;
protected:
private:
	ActionTypes m_type;
};

class ActionTravel : public Action {
public:
	ActionTravel( ActionTypes p_type, Verb p_target );
	~ActionTravel();

	std::string toString();

	Verb getTarget() const;
protected:
private:
	Verb m_target;
};

#endif // ACTION_H