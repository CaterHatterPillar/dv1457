#include <string>
#include <iostream>
#include <algorithm>

#include "GUI.h"

GUI::GUI() {

}
GUI::~GUI() {
	// Do nothing.
}

void GUI::GetInput( std::string& io_input ) {
	getline( std::cin, io_input );

	// Make line uppercase:
	std::transform( io_input.begin(), io_input.end(), io_input.begin(), ::toupper );
}

void GUI::ClearScreen() {
	std::cout << std::string( 100, '\n' );
}
void GUI::RenderLocation( Location p_location ) {
	std::cout << "---" << std::endl
		<< p_location.getDescShort() << std::endl
		<< "---" << std::endl;
	std::cout << p_location.getDescLong() << std::endl;
}
void GUI::RenderText( int numLines, ... ) {
	va_list list;
	va_start(list, numLines); 
	for(unsigned i = 0; i < numLines; i++) { 
		std::cout << va_arg(list, char*) << std::endl;
	}
	va_end(list);
}
void GUI::RenderString( std::string p_string ) {
	std::cout << p_string;
}
void GUI::RenderTerminal() {
	std::cout << "> ";
}