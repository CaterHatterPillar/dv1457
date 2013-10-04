#include "Common.h"
#include "AgentGame.h"

AgentGame::AgentGame() {

}
AgentGame::~AgentGame() {
	// Do nothing.
}

bool AgentGame::execute( ActionGame* p_action, Result& io_result ) {
	AdventData& ad = Singleton<AdventData>::get();

    bool recognizedGameCommand = true;
    ActionGameTypes agt = p_action->getActionGameType();
    switch( agt ) {
        case ActionGameTypes_PRESENT_LOCATION:
            GUI::RenderLocation( ad.adventurer.getLocation() );
            ad.adventurer.getMagic().discoverMagicWords();
            break;
        case ActionGameTypes_PRESENT_INVENTORY:
            GUI::RenderInventory( ad.adventurer.getInventory() );
            break;
        default:
            recognizedGameCommand = false;
            throw ExceptionAdventNotYetImplemented( "Encountered unknown ActionGameTypes: " + std::string( ActionGameTypesString[ agt ] ) + "." );
            break;
    }

    return recognizedGameCommand;
}