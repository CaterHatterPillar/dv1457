#include "Object.h"

Object::Object() {
	m_id = 0;
	m_name = "";
	
	m_immovable = false;
}
Object::~Object() {
	// Do nothing.
}

void Object::appendDescription( std::string p_condition, std::string p_description ) {
	m_descriptions[ p_condition ].condition = p_condition;
	m_descriptions[ p_condition ].description.push_back( p_description );
}

void Object::setId( unsigned p_id ) {
	m_id = p_id;
}
void Object::setName( std::string p_name ) {
	m_name = p_name;
}
void Object::setImmovable( bool p_isImmovable ) {
	m_immovable = p_isImmovable;
}

unsigned Object::getId() const {
	return m_id;
}
std::string Object::getName() const {
	return m_name;
}
bool Object::isImmovable() const {
	return m_immovable;
}