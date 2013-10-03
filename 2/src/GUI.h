
#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <stdarg.h>

#include "Location.h"
#include "Inventory.h"

class GUI {
public:
	GUI();
	~GUI();

	// In
	static void GetInput( std::string& io_input );

	// Out
	static void ClearScreen();
	static void RenderLocation( Location p_location );
	static void RenderText( int numLines, ... );
	static void RenderString( std::string p_string );
	static void RenderLines( std::vector< std::string > p_lines );
	static void RenderTerminal();
	static void RenderInventory( Inventory p_inventory );
	static void RenderNewLine( unsigned p_numNewLine );
protected:
private:
	static void RenderObject( Object p_object );
};

#endif // GUI_H