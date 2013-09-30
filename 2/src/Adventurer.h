#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <vector>

#include "Object.h"
#include "Location.h"

class Adventurer {
public:
	Adventurer();
	Adventurer( Location p_startingLocation );
	~Adventurer();

	// Game methods. Try using these:
	void adventTravelTo( Location p_location );
	void adventTakeObject( Object p_object );

	Location getLocation();
	void setLocation( Location p_location ); // Consider removing.
	std::vector< Object > getInventory() const;
protected:
private:
	Location m_location;
	std::vector< Object > m_inventory;
};

#endif // ADVENTURER_H