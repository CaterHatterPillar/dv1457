#include <string>
#include <algorithm>

#include "GUI.h"
#include "Common.h"

ResFormater::ResFormater() {

}
ResFormater::~ResFormater() {
	// Do nothing.
}

std::string ResFormater::FormatLocation( Location p_location ) {
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
	return locationDesc;
}
std::string ResFormater::FormatText( int numLines, ... ) {
	AdventData& ad = Singleton<AdventData>::get();
	std::string text = "";

	va_list list;
	va_start(list, numLines); 
	for(unsigned i = 0; i < numLines; i++) { 
		text += std::string( va_arg(list, char*) ) + "\n";
	}
	va_end(list);

	return text;
}
std::string ResFormater::FormatLines( std::vector< std::string > p_lines ) {
	AdventData& ad = Singleton<AdventData>::get();

	std::string lines = "";
	for( unsigned i = 0; i < p_lines.size(); i++ ) {
		lines += "\n" + p_lines[ i ];
	}
	return lines;
}
std::string ResFormater::FormatInventory( Inventory p_inventory ) {
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
	return inventory;
}