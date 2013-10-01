#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

#include "Object.h"

class Inventory {
public:
	Inventory();
	~Inventory();

	bool appendItem( Object p_object );
	bool removeItem( Object p_object );
	bool isFull();
	unsigned getNumItems() const;

	Object& operator[]( unsigned p_index );
protected:
private:
	unsigned m_size;
	std::vector< Object > m_items;
};

#endif // INVENTORY_H