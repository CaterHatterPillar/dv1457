#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <vector>

#include "Location.h"
#include "Inventory.h"

class Adventurer {
public:
	Adventurer();
	Adventurer( Location p_startingLocation );
	~Adventurer();

	void adventTravelTo( Location p_location );

	Location getLocation();
	Inventory& getInventory();
	void setLocation( Location p_location ); // Consider removing.
protected:
private:
	Location m_location;
	Inventory m_inventory;
};

#endif // ADVENTURER_H