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

	Location getLocation(); // Consider returning reference
	Inventory& getInventory();
	Magic& getMagic();
protected:
private:
	unsigned m_idLocation;
	Inventory m_inventory;
	Magic m_magic;
};

#endif // ADVENTURER_H