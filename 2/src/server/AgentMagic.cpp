#include "Common.h"
#include "AgentMagic.h"
#include "AgentTravel.h"
#include "ActionFactory.h"

std::vector<bool> AgentMagic::s_feefie;

AgentMagic::AgentMagic() {

}
AgentMagic::~AgentMagic() {
	// Do nothing.
}

bool AgentMagic::execute( ActionMagic* p_action, Result& io_result ) {
	AdventData& ad = Singleton<AdventData>::get();
    
    Verb spell = p_action->getSpell();

    bool spellCast = false;
    spellCast = executeMagic( spell, io_result );

    return spellCast;
}

bool AgentMagic::executeMagic( Verb p_spell, Result& io_result ) {
	AdventData& ad = Singleton<AdventData>::get();

    Location location = ad.adventurer.getLocation();
    bool spellCast = false;
    bool canTeleport = false;

    switch( p_spell.getId() )
    {
    case MeaningfulWords_XYZZY:
        canTeleport = ad.adventurer.getMagic().getXyzzy();
        spellCast = executeMagicTeleport( p_spell, canTeleport, io_result );
        break;
    case MeaningfulWords_PLUGH:
        canTeleport = ad.adventurer.getMagic().getPlugh();
        spellCast = executeMagicTeleport( p_spell, canTeleport, io_result );
        break;
    case MeaningfulWords_PLOVE:
        canTeleport = ad.adventurer.getMagic().getPlover();
        spellCast = executeMagicTeleport( p_spell, canTeleport, io_result );
        break;
    case MeaningfulWords_FEE:
        spellCast = executeMagicFeefie( 0, io_result );
        break;
    case MeaningfulWords_FIE:
        spellCast = executeMagicFeefie( 1, io_result );
        break;
    case MeaningfulWords_FOE:
        spellCast = executeMagicFeefie( 2, io_result );
        break;
    case MeaningfulWords_FOO:
        spellCast = executeMagicFeefie( 3, io_result );
        break;
    case MeaningfulWords_FUM:
        spellCast = executeMagicFeefie( 4, io_result );
        break;
    default:
        io_result.setSummary("(to yourself) \nNothing happens.");
        break;
    }
    
    return spellCast;
}

bool AgentMagic::executeMagicTeleport(Verb p_spell, bool p_canTeleport, Result& io_result)
{
    bool success = false;

    if(p_canTeleport) {
        Action* action = ActionFactory::actionTravel( p_spell );
        success = AgentTravel::execute((ActionTravel*)action, io_result);
    }
    
    if(!success)
        io_result.setSummary("Nothing happens!");

    return success;
}
bool AgentMagic::executeMagicFeefie(unsigned p_wordIndex, Result& io_result)
{
    AdventData& ad = Singleton<AdventData>::get();

    bool success = true;
    
    if(p_wordIndex == 0)
        s_feefie.push_back(true);
    else {
        if(p_wordIndex > s_feefie.size())
            success = false;
        if(success){
            for(unsigned int i=0; i<s_feefie.size() && success; i++)
                success = s_feefie[i];
        }
        
        if(success)
            s_feefie.push_back(true);
        else
            s_feefie.resize(0, false);    
    }
    if(success && p_wordIndex == 3) {
        s_feefie.resize(0, false);
        if(ad.adventurer.getMagic().getFee()) {
            io_result.setSummary("Move eggs back to the giant room. Not yet implemented");
        }
        else {
            io_result.setSummary("Nothing happens!");
        }
    }
    else if(success)
        io_result.setSummary("Ok!");
    else
        io_result.setSummary("Get it right dummy!");

    return success;
}