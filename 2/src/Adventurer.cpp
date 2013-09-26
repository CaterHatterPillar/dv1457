#include "Adventurer.h"

Adventurer::Adventurer() {

}
Adventurer::Adventurer( Location p_startingLocation ) {
	m_location = p_startingLocation;
}
Adventurer::~Adventurer() {
	// Do nothing.
}

Location Adventurer::getLocation() {
	return m_location;
}
void Adventurer::setLocation( Location p_location ) {
	m_location = p_location;
}