#include "Common.h"
#include "Inventory.h"

Inventory::Inventory() {
	m_size = s_confInventorySize;
}
Inventory::~Inventory() {
	// Do nothing.
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
	throw ExceptionAdventNotYetImplemented( "Non-implemented method Inventory::removeItem called." );
	return false; // tmp
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