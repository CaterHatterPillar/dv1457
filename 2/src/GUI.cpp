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
}

void GUI::ClearScreen() {
	std::cout << std::string( 100, '\n' );
}
void GUI::RenderLocation( Location p_location ) {
	// Render the terrain:
	std::cout << "---" << std::endl
		<< p_location.getDescShort() << std::endl
		<< "---" << std::endl;
	std::cout << p_location.getDescLong() << std::endl;

	// Render objects:
	std::vector< Object > objects = p_location.getObjects();
	for( unsigned i = 0; i < objects.size(); i++ ) {
		Object object = objects[ i ];
		RenderObject( object );
	}
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

void GUI::RenderObject( Object p_object ) {
	std::cout << p_object.getName() << std::endl;
}
void GUI::RenderInventory( Inventory p_inventory ) {
	if( p_inventory.getNumItems() > 0 ) {
		std::cout << "Inventory:";
		for( unsigned i = 0; i < p_inventory.getNumItems(); i++ ) {
			std::cout << std::endl << " *\t" << p_inventory[i].getName();
		}
	} else {
		std::cout << "You are carrying nothing.";
	}
}