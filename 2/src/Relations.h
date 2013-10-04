#ifndef RELATIONS_H
#define RELATIONS_H

#include <map>
#include <vector>

#include "Relation.h"

class Relations {
public:
	Relations();
	~Relations();

	void appendRelation( Relation p_ro );
	bool hasRelation( 
		unsigned p_idSubject, 
		unsigned p_idSubjector, 
		unsigned p_idAction, 
		Relation& io_relation ); // overload me a bunch?
protected:
	std::vector< Relation > getRelations( unsigned p_idSubject );
	std::vector< Relation > getRelations( unsigned p_idSubject, unsigned p_idSubjector );	
	std::vector< Relation > getRelations( unsigned p_idSubject, unsigned p_idSubjector, unsigned p_idAction );
private:
	std::map< unsigned, std::vector< Relation > > m_relations;
};

#endif // RELATIONS_H