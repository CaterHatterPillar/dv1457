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
	// Order verbs into groups indicating actions:
	Interpretation interpretation = interpretType( p_verbs );

	Action* a = ActionFactory::actionInvalid();
	for( unsigned actionType = ActionTypes_INDEX_BEGIN; actionType < ActionTypes_INDEX_END && a->isValid()==false; actionType++ ) {
		delete a;
		a = interpretAction( interpretation, io_result, (ActionTypes)actionType );
	}

	if( a->isValid()==false ) {
		io_result.setSummary( "That's not a verb I recognise." );
	}
	return a;
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
				interpretation.vObject.push_back( verb );
				break;
			case 2: // Denotes action.
				interpretation.vAction.push_back( verb );
				break;
			case 3: // Denotes special-case.
				throw ExceptionAdventNotYetImplemented( "Command - Special-case." );
				break;
			case 4: // Denotes certain game-mechanics, such as look or inventory.
				interpretation.vGame.push_back( verb );
				break;
			default:
				throw ExceptionAdventNotYetImplemented( "Unknown verb type: " + Util::toString( vType ) + " caused by Verb: " + Util::toString( vId ) + "."  );
		}
	}
	return interpretation;
}

Action* Interpreter::interpretAction( 
	Interpretation p_interpretation, 
	Result& io_result, 
	ActionTypes p_actionType ) {
	Action* action;
	switch( p_actionType ) {
		case ActionTypes_TRAVEL:
			action = interpretActionTravel( p_interpretation, io_result );
			break;
		case ActionTypes_INTERACT:
			action = interpretActionInteract( p_interpretation, io_result );
			break;
		case ActionTypes_GAME:
			action = interpretActionGame( p_interpretation, io_result );
			break;
		default:
			action = ActionFactory::actionInvalid();
			break;
	}
	return action;
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
Action* Interpreter::interpretActionInteract( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();
	if( p_interpretation.vAction.size()==1 && p_interpretation.vObject.size()==1 ) {
		delete action;
		action = ActionFactory::actionInteract( p_interpretation.vAction.front(), p_interpretation.vObject.front() );
	} else {
		io_result.setSummary( "I understand you as far as that you would like to interact with something. However, you have specified too many actions and/or objects: " );
	}

	return action;
}
Action* Interpreter::interpretActionGame( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();
	if( p_interpretation.vGame.size()==1 ) {
		delete action;
		unsigned gameCommand = p_interpretation.vGame.front().getId();
		switch( gameCommand ) {
			case 4001: // Present terrain
				action = ActionFactory::actionGame( ActionGameTypes_PRESENT_LOCATION );
				break;
			case 4002: // Present inventory
				action = ActionFactory::actionGame( ActionGameTypes_PRESENT_INVENTORY );
				break;
		}
	} else {
		io_result.setSummary( "I understand you as far as that you have specified a special game-command. However, you have specified too many game-commands: " );
	}

	return action;
}