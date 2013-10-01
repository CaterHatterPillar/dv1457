#include "AdventData.h"
#include "Adventurer.h"

Adventurer::Adventurer() {

}
Adventurer::Adventurer( Location p_startingLocation ) {
	m_location = p_startingLocation;
}
Adventurer::~Adventurer() {
	// Do nothing.
}

void Adventurer::adventTravelTo( Location p_location ) {
	m_location = p_location;
}

Location Adventurer::getLocation() {
	return Singleton<AdventData>::get().map[ m_location.getId() ];
}
Inventory& Adventurer::getInventory() {
	return m_inventory;
}
void Adventurer::setLocation( Location p_location ) {
	m_location = p_location;
}