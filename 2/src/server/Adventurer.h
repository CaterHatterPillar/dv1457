#ifndef ADVENTURER_H
#define ADVENTURER_H

#include "Magic.h"
#include "Inventory.h"

class Adventurer {
public:
	Adventurer();
	Adventurer( unsigned p_idLocation );
	~Adventurer();

	void adventTravelTo( unsigned p_idLocation );
	bool isIlluminated();

	unsigned getIdLocation() const;
	Inventory& getInventory();
protected:
private:
	unsigned m_idLocation;
	Inventory m_inventory;
};

#endif // ADVENTURER_H