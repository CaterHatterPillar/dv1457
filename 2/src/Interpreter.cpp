#include "Util.h"
#include "Singleton.h"
#include "AdventData.h"
#include "Interpreter.h"
#include "ActionFactory.h"
#include "ExceptionAdventNotYetImplemented.h"

Interpreter::Interpreter() {

}
Interpreter::~Interpreter() {
	// Do nothing.
}

Action* Interpreter::interpret( std::vector< Verb > p_verbs, Result& io_result ) {
	Interpretation interpretation = interpretType( p_verbs );

	Action* actions[4];
	actions[ 0 ] = interpretActionTravel( interpretation, io_result );
	//actions[ 1 ] = interpretActionObject( interpretation );
	//actions[ 2 ] = interpretActionAction( interpretation );
	//actions[ 3 ] = interpretActionSpecial( interpretation );

	return actions[ 0 ]; // temp
}

Interpreter::Interpretation Interpreter::interpretType( std::vector< Verb > p_verbs ) {
	Interpretation interpretation;
	for( unsigned i = 0; i < p_verbs.size(); i++ ) {
		Verb verb = p_verbs[ i ];

		unsigned vId = verb.getId();
		unsigned vType = vId / 1000;
		switch( vType ) {
			case 0: // Denotes travel.
				interpretation.vTravel.push_back( verb );
				break;
			case 1: // Denotes object.
				throw ExceptionAdventNotYetImplemented( "Command - Object." );
				break;
			case 2: // Denotes action.
				throw ExceptionAdventNotYetImplemented( "Command - Action." );
				break;
			case 3: // Denotes special-case.
				throw ExceptionAdventNotYetImplemented( "Command - Special-case." );
				break;
			default:
				throw ExceptionAdventNotYetImplemented( "Unknown verb type: " + Util::toString( vType ) + " caused by Verb: " + Util::toString( vId ) + "."  );
		}
	}
	return interpretation;
}

Action* Interpreter::interpretActionTravel( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();
	if( p_interpretation.vTravel.size()==1 ) {
		delete action;
		action = ActionFactory::actionTravel( p_interpretation.vTravel.front() );
	} else {
		io_result.setSummary( "I understand you as far as that you would like to travel. However, you have specified too many destinations: " );
	}
	return action;
}