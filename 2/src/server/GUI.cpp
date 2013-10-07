#include <string>
#include <iostream>
#include <algorithm>

#include "GUI.h"
#include "Snitch.h"
#include "Common.h"

GUI::GUI() {

}
GUI::~GUI() {
	// Do nothing.
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

	std::string locationDesc = descShort + "\n" + descLong + descObjects;
	Snitch::SendMsg( ad.sockfd, locationDesc );
}
void GUI::RenderText( int numLines, ... ) {
	AdventData& ad = Singleton<AdventData>::get();
	std::string text = "";

	va_list list;
	va_start(list, numLines); 
	for(unsigned i = 0; i < numLines; i++) { 
		text += std::string( va_arg(list, char*) ) + "\n";
	}
	va_end(list);

	Snitch::SendMsg( ad.sockfd, text );
}
void GUI::RenderString( std::string p_string ) {
	AdventData& ad = Singleton<AdventData>::get();

	Snitch::SendMsg( ad.sockfd, p_string );
}
void GUI::RenderLines( std::vector< std::string > p_lines ) {
	AdventData& ad = Singleton<AdventData>::get();

	std::string lines = "";
	for( unsigned i = 0; i < p_lines.size(); i++ ) {
		lines += "\n" + p_lines[ i ];
	}
	Snitch::SendMsg( ad.sockfd, lines );
}
void GUI::RenderInventory( Inventory p_inventory ) {
	AdventData& ad = Singleton<AdventData>::get();

	std::string inventory = "";
	if( p_inventory.getNumItems() > 0 ) {
		std::cout << s_confMessageInventoryHeader;
		for( unsigned i = 0; i < p_inventory.getNumItems(); i++ ) {
			unsigned itemId = p_inventory.getItemId( i );
			Object object = ad.map.getObject( itemId );
			inventory += std::string("\n") + std::string(" * ") + object.getName();
		}
	} else {
		inventory = s_confMessageInventoryEmpty;
	}
	Snitch::SendMsg( ad.sockfd, inventory );
}