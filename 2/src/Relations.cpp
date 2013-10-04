#include "Common.h"
#include "Relations.h"

Relations::Relations() {

}
Relations::~Relations() {
	// Do nothing.
}

void Relations::appendRelation( Relation p_ro ) {
	m_relations[ p_ro.getIdSubject() ].push_back( p_ro );
}
bool Relations::hasRelation( 
	unsigned p_idSubject, 
	unsigned p_idSubjector, 
	unsigned p_idAction, 
	Relation& io_relation ) {
	bool hasRelation = false;
	std::vector< Relation > relations = getRelations( p_idSubject, p_idSubjector, p_idAction );
	if( relations.size() > 0 ) {
		hasRelation = true;
		io_relation = relations.front();
	}
	return hasRelation;
}

std::vector< Relation > Relations::getRelations( unsigned p_idSubject ) {
	return m_relations[ p_idSubject ];
}
std::vector< Relation > Relations::getRelations( unsigned p_idSubject, unsigned p_idSubjector ) {
	std::vector< Relation > relations = getRelations( p_idSubject );
	std::vector< Relation > relationsFiltered;
	for( unsigned i = 0; i < relations.size(); i++ ) {
		Relation r = relations[ i ];
		if( r.getIdSubjector()==p_idSubjector ) {
			relationsFiltered.push_back( r );
		}
	}
	return relationsFiltered;
}
std::vector< Relation > Relations::getRelations( unsigned p_idSubject, unsigned p_idSubjector, unsigned p_idAction ) {
	std::vector< Relation > relations = getRelations( p_idSubject, p_idSubjector );
	std::vector< Relation > relationsFiltered;
	for( unsigned i = 0; i < relations.size(); i++ ) {
		Relation r = relations[ i ];
		if( r.getIdAction()==p_idAction ) {
			relationsFiltered.push_back( r );
		}
	}
	return relationsFiltered;
}