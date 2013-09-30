#ifndef ACTION_H
#define ACTION_H

#include "Verb.h"

enum ActionTypes {
	ActionTypes_INDEX_BEGIN	= 0,
	
	ActionTypes_INVALID		= 1,
	ActionTypes_TRAVEL		= 2,
	ActionTypes_INTERACT	= 3,/*,
	ActionTypes_SPECIAL*/
	ActionTypes_GAME		= 4,

	ActionTypes_INDEX_END	= 5
};
	
static const char* ActionTypesString[] = { 
	"ActionTypes_INDEX_BEGIN", // hack

	"ActionTypes_INVALID", 
	"ActionTypes_TRAVEL",
	"ActionTypes_INTERACT",/*,
	"ActionTypes_SPECIAL"*/
	"ActionTypes_GAME",

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

enum ActionGameTypes {
	ActionGameTypes_PRESENT_LOCATION 	= 0,
	ActionGameTypes_PRESENT_INVENTORY	= 1
};
static const char* ActionGameTypesString[] = { 
	"ActionGameTypes_PRESENT_LOCATION", 
	"ActionGameTYpes_PRESENT_INVENTORY"
};
class ActionGame : public Action {
public:
	ActionGame( ActionGameTypes p_actionGameType );
	~ActionGame();

	std::string toString();

	ActionGameTypes getActionGameType() const;
protected:
private:
	ActionGameTypes m_actionGameType;
};

#endif // ACTION_H