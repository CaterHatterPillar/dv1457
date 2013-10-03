#include "Common.h"
#include "Letterbox.h"

Letterbox::Letterbox() {

}
Letterbox::~Letterbox() {
	// Do nothing.
}

// []-operator maps to arbitrary messages, since they are the ones most used.
Letter& Letterbox::operator[]( unsigned p_idArbitrary ) {
	return m_arbitrary[ p_idArbitrary ];
}