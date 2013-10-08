#include "Common.h"
#include "CommonSys.h"
#include "Interpreter.h"
#include "ActionFactory.h"

Interpreter::Interpreter() {

}
Interpreter::~Interpreter() {
	// Do nothing.
}

Action* Interpreter::interpret( std::vector< Verb > p_verbs, Result& io_result ) {
	Action* a;

	syslog(LOG_INFO, "Interpreter::interpret()");

	// Order verbs into groups indicating actions:
	Interpretation interpretation = interpretVerbs( p_verbs );
	// Attempt to predict intent based off Action-verbs:
	ActionIntents intent = interpretIntent( interpretation );
	// Call corresponding action if intent has been predicted...
	switch( intent ) {
		case ActionIntents_TRAVEL:
			a = interpretAction( interpretation, io_result, ActionTypes_TRAVEL );
			break;
		case ActionIntents_INTERACT:
			a = interpretAction( interpretation, io_result, ActionTypes_INTERACT );
			break;
		case ActionIntents_MAGIC:
			a = interpretAction( interpretation, io_result, ActionTypes_MAGIC );
			break;
		// ...or attempt to interpret it anyway if not successful:
		default:
			a = interpretWildcard( interpretation, io_result );
			break;
	}
	if( p_verbs.size()==0 ) {
		io_result.setSummary( s_confMessageInvalidCommand );
	}

	return a;
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
		case ActionTypes_MAGIC:
			action = interpretActionMagic( p_interpretation, io_result );
			break;
		default:
			action = ActionFactory::actionInvalid();
			break;
	}
	return action;
}
Action* Interpreter::interpretWildcard( Interpretation p_interpretation, Result& io_result ) {
	Action* a = ActionFactory::actionInvalid();
	for( unsigned actionType = ActionTypes_INDEX_BEGIN; actionType < ActionTypes_INDEX_END && a->isValid()==false; actionType++ ) {
		delete a;
		a = interpretAction( p_interpretation, io_result, (ActionTypes)actionType );
	}
	return a;
}

Action* Interpreter::interpretActionTravel( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();

	syslog(LOG_INFO, "Interpreter::interpretActionTravel()");

	bool validTarget = false;
	switch( p_interpretation.vTravel.size() ) {
		case 0:
			io_result.setSummary( "No target specified. Where-to do you wish to travel?" );
			break;
		case 1:
			validTarget = true;
			break;
		default:
			io_result.setSummary( "Too many targets specified. Please specify only one destination." );
			break;
	}

	if( validTarget==true ) {
		delete action;
		action = ActionFactory::actionTravel( p_interpretation.vTravel.front() );
	}
	
	return action;
}
Action* Interpreter::interpretActionInteract( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();

	syslog(LOG_INFO, "Interpreter::interpretActionInteract()");

	bool validAction = false;
	if( p_interpretation.vAction.size()==1 ) {
		validAction = true;
	} else {
		// Temp output. Be sure to refine the comment and put it into AdventConf.h:
		io_result.setSummary( "You have specified too many actions. Please limit your command to a single action." );
	}
	bool validTargets = false;
	if( p_interpretation.vObject.size()>=0 &&
		p_interpretation.vObject.size()<=2 ) {
		validTargets = true;
	} else {
		// Temp output. Be sure to refine the comment and put it into AdventConf.h:
		io_result.setSummary( "You have specified too many targets. Please limit the number of objects in your command to two or less." );
	}

	if( validAction==true && 
		validTargets==true ) {
		delete action;
		action = ActionFactory::actionInteract( p_interpretation.vAction.front(), p_interpretation.vObject );
	}

	return action;
}
Action* Interpreter::interpretActionMagic( Interpretation p_interpretation, Result& io_result ) {
	Action* action = ActionFactory::actionInvalid();

	syslog(LOG_INFO, "Interpreter::interpretActionMagic");

	std::vector< Verb > spellsTravel = p_interpretation.vTravel;	// Some spells are motion-verbs, such as XYZZY.
	std::vector< Verb > spellsSpecial = p_interpretation.vSpecial;	// Others are special, such as fee fie fum - yadda yadda.

	std::vector< Verb > spells = spellsTravel;
	spells.insert( spells.end(), spellsSpecial.begin(), spellsSpecial.end() );

	Verb spell;
	bool validSpell = false;
	if( spells.size()==0 ) {
		io_result.setSummary( "Those are not magic words." );
	} else if( spells.size()>1 ) {
		io_result.setSummary( "That spell is too long. Limit your spell to single words." );
	} else { // ==1
		spell = spells.front();
		validSpell = true;
	}

	if( validSpell==true ) {
		delete action;
		action = ActionFactory::actionMagic( spell );
	}

	return action;
}

Interpreter::Interpretation Interpreter::interpretVerbs( std::vector< Verb > p_verbs ) {
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
				interpretation.vSpecial.push_back( verb );
				//throw ExceptionAdventNotYetImplemented( "Command - Special-case." );
				break;
			default:
				throw ExceptionAdventNotYetImplemented( "Unknown verb type: " + Util::toString( vType ) + " caused by Verb: " + Util::toString( vId ) + "."  );
		}
	}
	return interpretation;
}
Interpreter::ActionIntents Interpreter::interpretIntent( Interpreter::Interpretation p_interpretation ) {
	ActionIntents intent = ActionIntents_UNKNOWN;
	if( p_interpretation.vAction.size() > 0 ) {
		Verb action = p_interpretation.vAction.front();
		
		unsigned actionId = action.getId();
		if( actionId==VerbIdsAction_WALK ) {
			intent = ActionIntents_TRAVEL;
		} else if( actionId==VerbIdsAction_SAY ) {
			intent = ActionIntents_MAGIC;
		} else {
			intent = ActionIntents_INTERACT;
		}
	}

	return intent;
}