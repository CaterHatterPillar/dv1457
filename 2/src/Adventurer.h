#ifndef ADVENTURER_H
#define ADVENTURER_H

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
};

#endif // ADVENTURER_H