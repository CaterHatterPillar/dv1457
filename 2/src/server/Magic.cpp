
#include "Magic.h"
#include "AdventConf.h"
#include "AdventData.h"

Magic::Magic()
{
	m_xyzzy  = false;
	m_plugh  = false;
	m_plover = false;
	m_fee 	 = false;
}
Magic::~Magic()
{
}

void Magic::setXyzzy(	bool p_xyzzy ) {
	m_xyzzy = p_xyzzy;
}
void Magic::setPlugh(	bool p_plugh ) {
	m_plugh = p_plugh;
}
void Magic::setPlover(	bool p_plover ) {
	m_plover = p_plover;
}
void Magic::setFee(		bool p_fee ) {
	m_fee = p_fee;
}

bool Magic::getXyzzy() {
	return m_xyzzy;
}
bool Magic::getPlugh() {
	return m_plugh;
}
bool Magic::getPlover() {
	return m_plover;
}
bool Magic::getFee() {
	return m_fee;
}

void Magic::discoverMagicWords()
{
    AdventData& ad = Singleton<AdventData>::get();
    int locationId = ad.adventurer.getLocation().getId();
    switch(locationId)
    {
    case MagicWordLocations_XYZZY:
        if(ad.adventurer.isIlluminated())
            m_xyzzy = true;
        break;
    case MagicWordLocations_PLUGH:
        if(ad.adventurer.isIlluminated())
            m_plugh = true;
        break;
    case MagicWordLocations_PLOVER:
        if(ad.adventurer.isIlluminated())
            m_plover = true;
        break;
    case MagicWordLocations_FEE:
        if(ad.adventurer.isIlluminated())
            m_fee = true;
        break;
    }
}