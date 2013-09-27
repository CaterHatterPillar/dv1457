#ifndef ADVENTURER_H
#define ADVENTURER_H

#include "Object.h"
#include "Location.h"

class Adventurer {
public:
	Adventurer();
	Adventurer( Location p_startingLocation );
	~Adventurer();

	Location getLocation();
	void setLocation( Location p_location );
protected:
private:
	Location m_location;
	//std::vector< Object > m_inventory;
};

#endif // ADVENTURER_H