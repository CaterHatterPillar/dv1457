#include <string>
#include <algorithm>

#include "GUI.h"
#include "Common.h"

ResFormater::ResFormater() {

}
ResFormater::~ResFormater() {
	// Do nothing.
}


std::string ResFormater::FormatLocation(AdventData& p_ad, Location p_location ) {

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
	return locationDesc;
}
std::string ResFormater::FormatText(AdventData& p_ad, int numLines, ... ) {
	std::string text = "";

	va_list list;
	va_start(list, numLines); 
	for(unsigned i = 0; i < numLines; i++) { 
		text += std::string( va_arg(list, char*) ) + "\n";
	}
	va_end(list);

	return text;
}
std::string ResFormater::FormatLines(AdventData& p_ad, std::vector< std::string > p_lines ) {
	std::string lines = "";
	for( unsigned i = 0; i < p_lines.size(); i++ ) {
		lines += "\n" + p_lines[ i ];
	}
	return lines;
}
std::string ResFormater::FormatInventory(AdventData& p_ad, Inventory p_inventory ) {
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
	return inventory;
}