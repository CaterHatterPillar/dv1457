#include "Common.h"
#include "Inventory.h"

Inventory::Inventory() {
	m_size = s_confInventorySize;
}
Inventory::~Inventory() {
	// Do nothing.
}

bool Inventory::carriesItem( unsigned p_objectId ) {
	bool carriesItem = false;
	for( unsigned i = 0; i < m_items.size(); i++ ) {
		if( p_objectId==m_items[ i ].getId() ) {
			carriesItem = true;
			break;
		}
	}
	return carriesItem;
}
bool Inventory::appendItem( Object p_object ) {
	bool addedItem = true;
	if( getNumItems() >= m_size ) {
		addedItem = false;
	} else {
		m_items.push_back( p_object );
	}
	return addedItem;
}
bool Inventory::removeItem( Object p_object ) {
	bool removed = false;
	for(unsigned int i=0; i<m_items.size() && !removed; i++) {
		if(m_items[i].getId() == p_object.getId())
		{
			m_items.erase(m_items.begin()+i);
			removed = true;
		}
	}

	//throw ExceptionAdventNotYetImplemented( "Non-implemented method Inventory::removeItem called." );
	return removed; // tmp
}
bool Inventory::isFull() {
	bool isFull = false;
	if( m_items.size() >= m_size ) {
		isFull = true;
	}
	return isFull;
}
unsigned Inventory::getNumItems() const {
	return m_items.size();
}

Object& Inventory::operator[]( unsigned p_index ) {
	return m_items[ p_index ];
}