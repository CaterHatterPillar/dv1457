#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>

#include "Verb.h"
#include "Action.h"
#include "Result.h"

class Interpreter {
public:
	Interpreter();
	~Interpreter();

	Action* interpret( std::vector< Verb > p_verbs, Result& io_result );

	struct Interpretation {
		std::vector< Verb > vTravel;
		std::vector< Verb > vObject;
		std::vector< Verb > vAction;
		std::vector< Verb > vSpecial;
	};
	enum ActionIntents {
		ActionIntents_UNKNOWN,
		ActionIntents_TRAVEL,
		ActionIntents_INTERACT,
		ActionIntents_MAGIC
	};
protected:
private:
	Action* interpretAction( 			Interpretation p_interpretation, Result& io_result, ActionTypes p_actionType );
	Action* interpretWildcard( 			Interpretation p_interpretation, Result& io_result );

	Action* interpretActionTravel( 		Interpretation p_interpretation, Result& io_result );
	Action* interpretActionInteract( 	Interpretation p_interpretation, Result& io_result );
	Action* interpretActionMagic( 		Interpretation p_interpretation, Result& io_result );

	Interpretation interpretVerbs( std::vector< Verb > p_verbs );
	ActionIntents interpretIntent( Interpretation p_interpretation );
};

#endif // INTERPRETER_H