#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>

class GUI {
public:
	GUI();
	~GUI();

	// In
	static void GetInput( std::string& io_input );

	// Out
	static void ClearScreen();
	static void RenderDescription( std::string& p_short, std::vector<std::string>& p_long );
protected:
private:
};

#endif // GUI_H