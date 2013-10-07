
#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <stdarg.h>

#include "AdventData.h"
#include "Location.h"
#include "Inventory.h"

/*
Some of these methods are not used.
Remove them.
Also, be sure to watch Pacific Rim.
*/

class GUI {
public:
	GUI();
	~GUI();

	// Out
	static void RenderLocation( 	AdventData& p_ad, Location p_location );
	static void RenderText( 		AdventData& p_ad, int numLines, ... );
	static void RenderString( 		AdventData& p_ad, std::string p_string );
	static void RenderLines( 		AdventData& p_ad, std::vector< std::string > p_lines );
	static void RenderInventory( 	AdventData& p_ad, Inventory p_inventory );
protected:
private:
};

#endif // GUI_H