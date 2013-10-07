#include "Common.h"
#include "Letterbox.h"

Letterbox::Letterbox() {

}
Letterbox::~Letterbox() {
	// Do nothing.
}

void Letterbox::appendActionDefault( unsigned p_idAction, unsigned p_idMsg ) {
	m_actionDefaults[ p_idAction ] = p_idMsg;
}
Letter Letterbox::getActionDefaults( unsigned p_idAction ) {
	unsigned idMsg = m_actionDefaults[ p_idAction ];
	return m_arbitrary[ idMsg ];
}

// []-operator maps to arbitrary messages, since they are the ones most used.
Letter& Letterbox::operator[]( unsigned p_idArbitrary ) {
	return m_arbitrary[ p_idArbitrary ];
}