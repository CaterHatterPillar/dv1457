
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

class ResFormater {
public:
	ResFormater();
	~ResFormater();

	// Out
	static std::string FormatLocation( Location p_location );
	static std::string FormatText( int numLines, ... );
	static std::string FormatLines( std::vector< std::string > p_lines );
	static std::string FormatInventory( Inventory p_inventory );
protected:
private:
};

#endif // GUI_H