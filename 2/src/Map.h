#ifndef MAP_H
#define MAP_H

#include<map> // haha

#include "Location.h"

class Map {
public:
	Map();
	~Map();

	Location& operator[]( unsigned p_id );
protected:
private:
	std::map< unsigned, Location > m_locs;
};

#endif // MAP_H