#include "Common.h"
#include "Adventurer.h"

Adventurer::Adventurer() {

}
Adventurer::Adventurer( Location p_startingLocation ) {
	m_idLocation = p_startingLocation.getId();
}
Adventurer::~Adventurer() {
	// Do nothing.
}

void Adventurer::adventTravelTo( Location p_location ) {
	m_idLocation = p_location.getId();
}
bool Adventurer::isIlluminated() {
	AdventData& ad = Singleton<AdventData>::get();
	bool illuminated = false;
	const unsigned LAMP_HACK = 2;
	if( m_inventory.carriesItem( LAMP_HACK ) ) {
		unsigned lampPropVal = ad.map.getObject( LAMP_HACK ).getPropertyValue();
		if( lampPropVal!=0 ) {
			illuminated = true;
		}
	} 

	return illuminated;
}

Location Adventurer::getLocation() {
	return Singleton<AdventData>::get().map[ m_idLocation ];
}
Inventory& Adventurer::getInventory() {
	return m_inventory;
}
Magic& Adventurer::getMagic() {
	return m_magic;
}