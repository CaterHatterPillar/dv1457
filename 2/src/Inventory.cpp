#include "Common.h"
#include "Inventory.h"

Inventory::Inventory() {
	m_size = s_confInventorySize;
}
Inventory::~Inventory() {
	// Do nothing.
}

bool Inventory::carriesItem( unsigned p_idObject ) {
	bool carriesItem = false;
	for( unsigned i = 0; i<m_itemIds.size(); i++ ) {
		if( p_idObject==m_itemIds[ i ] ) {
			carriesItem = true;
			break;
		}
	}
	return carriesItem;
}
bool Inventory::appendItem( unsigned p_idObject ) {
	bool addedItem = true;
	if( getNumItems()>=m_size ) {
		addedItem = false;
	} else {
		m_itemIds.push_back( p_idObject );
	}
	return addedItem;
}
bool Inventory::removeItem( int p_objectId ) {
	bool removed = false;
	for(unsigned int i=0; i<m_itemIds.size() && !removed; i++) {
		if(m_itemIds[i] == p_objectId) {
			m_itemIds.erase(m_itemIds.begin()+i);
			removed = true;
		}
	}
	return removed;
}
bool Inventory::isFull() {
	bool isFull = false;
	if( m_itemIds.size() >= m_size ) {
		isFull = true;
	}
	return isFull;
}
unsigned Inventory::getNumItems() const {
	return m_itemIds.size();
}
unsigned Inventory::getItemId( unsigned p_index ) {
	return m_itemIds[ p_index ];
}