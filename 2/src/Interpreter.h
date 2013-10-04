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
protected:
private:
	Interpretation interpretType( std::vector< Verb > p_verbs );

	// These methods all need their result-writebacks to be re-written. They are currently faulty.
	Action* interpretAction( 			Interpretation p_interpretation, Result& io_result, ActionTypes p_actionType );
	Action* interpretActionTravel( 		Interpretation p_interpretation, Result& io_result );
	Action* interpretActionInteract( 	Interpretation p_interpretation, Result& io_result );
};

#endif // INTERPRETER_H