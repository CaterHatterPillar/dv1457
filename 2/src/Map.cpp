#include "Map.h"

Map::Map() {

}
Map::~Map() {
	// Do nothing.
}

Location& Map::operator[]( unsigned p_id ) { 
	return m_locs[ p_id ];
}