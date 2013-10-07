#ifndef MAP_H
#define MAP_H

#include<map> // haha

#include "Object.h"
#include "Location.h"

class Map {
public:
	Map();
	~Map();

	void appendObject( Object p_object );
	Object& getObject( unsigned p_idObject );

	Location& operator[]( unsigned p_idLocation );
protected:
private:
	std::map< unsigned, Object > m_objects;
	std::map< unsigned, Location > m_locations;
};

#endif // MAP_H