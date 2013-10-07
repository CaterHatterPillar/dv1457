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

void GUI::RenderLocation( AdventData& p_ad, Location p_location ) {
	std::string descShort, descLong, descObjects = "";

	bool canSee = p_ad.locationIsIlluminated();
	if( canSee ) {
		p_ad.discoverMagicWords();
		
		descShort = p_location.getDescShort();
		descLong = p_location.getDescLong();

		std::vector< unsigned > objectIds = p_location.getObjectIds();
		for( unsigned i = 0; i < objectIds.size(); i++ ) {
			Object object = p_ad.map.getObject( objectIds[ i ] );
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
	Snitch::SendMsg( p_ad.sockfd, locationDesc );
}
void GUI::RenderText( AdventData& p_ad, int numLines, ... ) {
	std::string text = "";

	va_list list;
	va_start(list, numLines); 
	for(unsigned i = 0; i < numLines; i++) { 
		text += std::string( va_arg(list, char*) ) + "\n";
	}
	va_end(list);

	Snitch::SendMsg( p_ad.sockfd, text );
}
void GUI::RenderString( AdventData& p_ad, std::string p_string ) {
	Snitch::SendMsg( p_ad.sockfd, p_string );
}
void GUI::RenderLines( AdventData& p_ad, std::vector< std::string > p_lines ) {
	std::string lines = "";
	for( unsigned i = 0; i < p_lines.size(); i++ ) {
		lines += "\n" + p_lines[ i ];
	}
	Snitch::SendMsg( p_ad.sockfd, lines );
}
void GUI::RenderInventory( AdventData& p_ad, Inventory p_inventory ) {
	std::string inventory = "";
	if( p_inventory.getNumItems() > 0 ) {
		std::cout << s_confMessageInventoryHeader;
		for( unsigned i = 0; i < p_inventory.getNumItems(); i++ ) {
			unsigned itemId = p_inventory.getItemId( i );
			Object object = p_ad.map.getObject( itemId );
			inventory += std::string("\n") + std::string(" * ") + object.getName();
		}
	} else {
		inventory = s_confMessageInventoryEmpty;
	}
	Snitch::SendMsg( p_ad.sockfd, inventory );
}