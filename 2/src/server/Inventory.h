#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

class Inventory {
public:
	Inventory();
	~Inventory();

	bool removeItem( int p_objectId );
	bool carriesItem( unsigned p_idObject );
	bool appendItem( unsigned p_idObject );

	bool isFull();
	unsigned getNumItems() const;
	unsigned getItemId( unsigned p_index );
protected:
private:
	unsigned m_size;
	std::vector< unsigned > m_itemIds;
};

#endif // INVENTORY_H