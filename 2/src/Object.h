#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <string>
#include <vector>

#include "Verb.h"

class Object {
public:
	Object();
	~Object();

	void appendDescription( std::string p_condition, std::string p_description );
	std::string toString();

	std::vector< std::string > getDescription();

	void setId( unsigned p_id );
	void setPropertyValue( unsigned p_propertyValue );
	void setName( std::string p_name );
	void setImmovable( bool p_isImmovable );

	unsigned getId() const;
	std::string getName() const;
	bool isImmovable() const;

	bool operator==( const Object& p_obj ) const;
	bool operator==( const Verb& p_verb ) const;
protected:
private:
	struct ObjectDescription {
		std::string condition;
		std::vector< std::string > description;
	};

	unsigned m_id;
	unsigned m_propertyValue;
	std::string m_name;

	bool m_immovable;
	std::map< std::string, ObjectDescription > m_descriptions;
};

#endif // OBJECT_H