#include "Common.h"
#include "Interpreter.h"
#include "ActionFactory.h"

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

	if( p_verbs.size()==0 ) {
		io_result.setSummary( s_confMessageInvalidCommand );
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
			//if( p_interpretation.vTravel.size() > 0 ) {
				action = interpretActionTravel( p_interpretation, io_result );
			//}
			break;
		case ActionTypes_INTERACT:
			//if( p_interpretation.vAction.size() > 0 ) {
				action = interpretActionInteract( p_interpretation, io_result );
			//}
			break;
		case ActionTypes_GAME:
			//if( p_interpretation.vGame.size() > 0 ) {
				action = interpretActionGame( p_interpretation, io_result );
			//}
			break;
		default:
			action = ActionFactory::actionInvalid();
			break;
	}
	return action;
}
Action* Interpreter::interpretActionTravel( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();
	if( p_interpretation.vTravel.size() > 0 ) {
		// ToDoIst: implement support for handling not-just-one verb for commands.
		if( p_interpretation.vTravel.size()==1 ) {
			delete action;
			action = ActionFactory::actionTravel( p_interpretation.vTravel.front() );
		} else {
			io_result.setSummary( s_confMessageInvalidTravel );
			/*io_result.setParams( p_interpretation.vTravel );*/
		}
	}
	
	return action;
}
Action* Interpreter::interpretActionInteract( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();
	if( p_interpretation.vAction.size() > 0 ) {
		// ToDoIst: implement support for handling not-just-one verb for commands.
		if( p_interpretation.vAction.size()==1 && p_interpretation.vObject.size()==1 ) {
			delete action;
			action = ActionFactory::actionInteract( p_interpretation.vAction.front(), p_interpretation.vObject.front() );
		} else {
			io_result.setSummary( s_confMessageInvalidInteract );
			/*io_setParams( p_interpretation.vAction );
			for( unsigned i = 0; i < p_interpretation.vObject.size(); i++ ) {
				io_result.appendParam( p_interpretation.vObject[ i ] );
			}*/
		}
	}

	return action;
}
Action* Interpreter::interpretActionGame( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();
	if( p_interpretation.vGame.size() > 0 ) {
		// ToDoIst: implement support for handling not-just-one verb for commands.
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
			io_result.setSummary( s_confMessageInvalidGame );
			/*io_result.setParams( p_interpretation.vGame );*/
		}
	}

	return action;
}