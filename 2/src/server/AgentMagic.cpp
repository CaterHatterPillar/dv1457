#include "Agent.h"
#include "Common.h"
#include "AgentMagic.h"
#include "AgentTravel.h"
#include "ActionFactory.h"

AgentMagic::AgentMagic( AdventData& p_ad, Agent* p_agent ) {
    m_ad = &p_ad;
    m_agent = p_agent;

    assert(m_ad);
    syslog(LOG_INFO, "AgentMagic::AgentMagic() m_ad");
    assert( m_agent );
    syslog(LOG_INFO, "AgentMagic::AgentMagic() m_agent");
}
AgentMagic::~AgentMagic() {
	// Do nothing.
}

bool AgentMagic::execute( ActionMagic* p_action, Result& io_result ) {
    Verb spell = p_action->getSpell();

    bool spellCast = false;
    spellCast = executeMagic( spell, io_result );

    return spellCast;
}

bool AgentMagic::executeMagic( Verb p_spell, Result& io_result ) {
    Location location = m_ad->map[ m_ad->adventurer.getIdLocation() ];
    bool spellCast = false;
    bool canTeleport = false;

    switch( p_spell.getId() )
    {
    case MeaningfulWords_XYZZY:
        canTeleport = m_ad->magic.getXyzzy();
        spellCast = executeMagicTeleport( p_spell, canTeleport, io_result );
        break;
    case MeaningfulWords_PLUGH:
        canTeleport = m_ad->magic.getPlugh();
        spellCast = executeMagicTeleport( p_spell, canTeleport, io_result );
        break;
    case MeaningfulWords_PLOVE:
        canTeleport = m_ad->magic.getPlover();
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
        success = m_agent->execute( action, io_result, AgentTypes_TRAVEL );
    }
    
    if(!success)
        io_result.setSummary("Nothing happens!");

    return success;
}
bool AgentMagic::executeMagicFeefie(unsigned p_wordIndex, Result& io_result)
{
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
        if(m_ad->magic.getFee()) {
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