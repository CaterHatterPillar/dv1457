#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <stdarg.h>

class GUI {
public:
	GUI();
	~GUI();

	// In
	static void GetInput( std::string& io_input );

	// Out
	static void ClearScreen();
	static void RenderDescription( std::string p_short, std::vector<std::string> p_long );
	static void RenderText( int numLines, ... );
	static void RenderString( std::string p_string );
	static void RenderTerminal();
protected:
private:
};

#endif // GUI_H