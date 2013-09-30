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

	void setId( unsigned p_id );
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
	std::string m_name;

	// itsprop ???

	bool m_immovable;
	std::map< std::string, ObjectDescription > m_descriptions;
};

#endif // OBJECT_H