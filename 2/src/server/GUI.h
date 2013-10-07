
#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <stdarg.h>

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
	static void RenderLocation( Location p_location );
	static void RenderText( int numLines, ... );
	static void RenderString( std::string p_string );
	static void RenderLines( std::vector< std::string > p_lines );
	static void RenderInventory( Inventory p_inventory );
protected:
private:
};

#endif // GUI_H