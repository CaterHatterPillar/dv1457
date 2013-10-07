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
	AdventData& ad = Singleton< AdventData >::get();
	std::string descShort, descLong, descObjects = "";

	bool canSee = p_location.isLit();
	canSee |= ad.adventurer.isIlluminated();
	if( canSee ) {
		ad.adventurer.getMagic().discoverMagicWords();
		
		descShort = p_location.getDescShort();
		descLong = p_location.getDescLong();

		std::vector< unsigned > objectIds = p_location.getObjectIds();
		for( unsigned i = 0; i < objectIds.size(); i++ ) {
			Object object = ad.map.getObject( objectIds[ i ] );
			descObjects += '\n';

			std::vector< std::string > description = object.getDescription();
			for( unsigned i = 0; i < description.size(); i++ ) {
				descObjects += description[i];
			}
		}
	} else {
		descShort = s_confDescShortDarkness;
		descLong = s_confDescLongDarkness;
	}

	std::cout << descShort << std::endl << descLong << descObjects;
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
void GUI::RenderLines( std::vector< std::string > p_lines ) {
	for( unsigned i = 0; i < p_lines.size(); i++ ) {
		std::cout << std::endl << p_lines[ i ];
	}
}
void GUI::RenderTerminal() {
	std::cout << s_confTerminalIndicator;
}
void GUI::RenderInventory( Inventory p_inventory ) {
	AdventData& ad = Singleton< AdventData >::get();
	if( p_inventory.getNumItems() > 0 ) {
		std::cout << s_confMessageInventoryHeader;
		for( unsigned i = 0; i < p_inventory.getNumItems(); i++ ) {
			unsigned itemId = p_inventory.getItemId( i );
			Object object = ad.map.getObject( itemId );
			std::cout << std::endl << " * " << object.getName();
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