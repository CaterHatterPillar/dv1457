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
void Adventurer::adventTakeObject( Object p_object ) {
	m_inventory.push_back( p_object );
}

Location Adventurer::getLocation() {
	return Singleton<AdventData>::get().map[ m_location.getId() ];
}
void Adventurer::setLocation( Location p_location ) {
	m_location = p_location;
}
std::vector< Object > Adventurer::getInventory() const {
	return m_inventory;
}