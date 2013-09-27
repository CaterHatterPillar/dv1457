#include "Result.h"

Result::Result() {

}
Result::~Result() {
	// Do nothing.
}

void Result::appendParam( std::string p_param ) {
	m_params.push_back( p_param );
}

void Result::setSummary( std::string p_summary ) {
	m_summary = p_summary;
}
void Result::setParams( std::vector< std::string > p_params ) {
	m_params = p_params;
}

std::string Result::getSummary() const {
	return m_summary;
}
unsigned Result::getParamsSize() const {
	return m_params.size();
}

std::string& Result::operator[]( unsigned p_i ) {
	return m_params[ p_i ];
}