#include "Common.h"
#include "Relation.h"

Relation::Relation() {
	m_idSubject 	= 0;
	m_idSubjector 	= 0;
	m_idAction 		= 0;
	m_influence 	= 0;
	m_output		= "";
}
Relation::Relation( 
	unsigned p_idSubject, 
	unsigned p_idSubjector,
	unsigned p_idAction,
	unsigned p_influence,
	std::string p_output ) {
	m_idSubject 	= p_idSubject;
	m_idSubjector	= p_idSubjector;
	m_idAction		= p_idAction;
	m_influence 	= p_influence;
	m_output		= p_output;
}
Relation::~Relation() {
	// Do nothing.
}

unsigned Relation::getIdSubject() const {
	return m_idSubject;
}
unsigned Relation::getIdSubjector() const {
	return m_idSubjector;
}
unsigned Relation::getIdAction() const {
	return m_idAction;
}
unsigned Relation::getInfluence() const {
	return m_influence;
}
std::string Relation::getOutput() const {
	return m_output;
}