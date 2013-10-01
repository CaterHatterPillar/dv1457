#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

#include "Object.h"

// This class needs some refactoring.
// Consider storing only object ids instead of objects!
class Inventory {
public:
	Inventory();
	~Inventory();

	bool carriesItem( unsigned p_objectId );
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