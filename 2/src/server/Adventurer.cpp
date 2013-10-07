#include "Common.h"
#include "Adventurer.h"

Adventurer::Adventurer() {

}
Adventurer::Adventurer( unsigned p_idLocation ) {
	m_idLocation = p_idLocation;
}
Adventurer::~Adventurer() {
	// Do nothing.
}

void Adventurer::adventTravelTo( unsigned p_idLocation ) {
	m_idLocation = p_idLocation;
}


unsigned Adventurer::getIdLocation() const {
	return m_idLocation;
}
Inventory& Adventurer::getInventory() {
	return m_inventory;
}