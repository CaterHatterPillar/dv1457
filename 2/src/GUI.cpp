#include <string>
#include <iostream>
#include <algorithm>

#include "GUI.h"
#include "Common.h"

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
	std::string descShort = p_location.getDescShort();
	std::cout << descShort << std::endl << p_location.getDescLong();

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
	std::cout << s_confTerminalIndicator;
}
void GUI::RenderInventory( Inventory p_inventory ) {
	if( p_inventory.getNumItems() > 0 ) {
		std::cout << s_confMessageInventoryHeader;
		for( unsigned i = 0; i < p_inventory.getNumItems(); i++ ) {
			std::cout << std::endl << " * " << p_inventory[i].getName();
		}
	} else {
		std::cout << s_confMessageInventoryEmpty;
	}
}
void GUI::RenderNewLine( unsigned p_numNewLine ) {
	for( unsigned i = 0; i < p_numNewLine; i++ ) {
		std::cout << std::endl;
	}
}

void GUI::RenderObject( Object p_object ) {
	std::cout << std::endl;

	std::vector< std::string > description = p_object.getDescription();
	for( unsigned i = 0; i < description.size(); i++ ) {
		std::cout << description[i];
	}
}