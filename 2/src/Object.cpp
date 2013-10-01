#include "Object.h"
#include "Common.h"

Object::Object() {
	m_id = 0;
	m_propertyValue = 0;
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
std::string Object::toString() {
	std::string object = m_id + ": " + m_name;
	return object;
}

std::vector< std::string > Object::getDescription() {
	// the message should be the description of the preceding object when itsprop value is n/100.
	std::string descVal = Util::toString( m_propertyValue ) + '0' + '0';

	std::vector< std::string > description;
	if( m_descriptions.find( descVal )!=m_descriptions.end() ) {
		description = m_descriptions[ descVal ].description;
	} else {
		// Properties which produce no message should be given the message ">$<".
		description.push_back( s_confMessageObjectNoDescription );
	}

	return description;
}

void Object::setId( unsigned p_id ) {
	m_id = p_id;
}
void Object::setPropertyValue( unsigned p_propertyValue ) {
	m_propertyValue = p_propertyValue;
}
void Object::setName( std::string p_name ) {
	m_name = p_name;
}
void Object::setImmovable( bool p_isImmovable ) {
	m_immovable = p_isImmovable;
}

bool Object::operator==( const Object& p_obj ) const {
	bool isEqual = false;
	if( m_id==p_obj.getId() ) {
		isEqual = true;
	}
	return isEqual;
}
bool Object::operator==( const Verb& p_verb ) const {
	bool isEqual = false;
	if( m_id==p_verb.getId() ) {
		isEqual = true;
	}
	return isEqual;
}

unsigned Object::getId() const {
	return m_id;
}
unsigned Object::getPropertyValue() const {
	return m_propertyValue;
}
std::string Object::getName() const {
	return m_name;
}
bool Object::isImmovable() const {
	return m_immovable;
}