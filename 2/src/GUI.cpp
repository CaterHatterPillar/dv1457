#include <iostream>

#include "GUI.h"

GUI::GUI() {

}
GUI::~GUI() {
	// Do nothing.
}

void GUI::GetInput( std::string& io_input ) {
	getline( std::cin, io_input );
}

void GUI::ClearScreen() {
	std::cout << std::string( 100, '\n' );
}
void GUI::RenderDescription( std::string& p_short, std::vector<std::string>& p_long ) {
	std::cout << "---" << std::endl
		<< p_short << std::endl
		<< "---" << std::endl;
	for( unsigned i = 0; i < p_long.size(); i++ ) {
		std::cout << p_long[i] << std::endl;
	}
	std::cout << std::endl;
}