#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <vector>

#include "Location.h"
#include "Inventory.h"
#include "Magic.h"

class Adventurer {
public:
	Adventurer();
	Adventurer( Location p_startingLocation );
	~Adventurer();

	void adventTravelTo( Location p_location );
	bool isIlluminated();

	Location getLocation();
	Inventory& getInventory();
	Magic& getMagic();
	void setLocation( Location p_location ); // Consider removing.
protected:
private:
	Location m_location;
	Inventory m_inventory;
	Magic m_magic;
};

#endif // ADVENTURER_H