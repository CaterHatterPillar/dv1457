#ifndef ADVENTDATA_H
#define ADVENTDATA_H

#include "Map.h"
#include "Magic.h"
#include "Relations.h"
#include "Letterbox.h"
#include "Vocabulary.h"
#include "Adventurer.h"

/* Clean me from comments */
class AdventData {
public:
	AdventData();
	~AdventData();

	// Client
	int sockfd;
	std::string player;

	// Gameplay
	Map map;
	Magic magic;
	Vocabulary vocabulary; 	
	Adventurer adventurer; 	
	Letterbox letterbox; 
	Relations relations;

	bool isOnSite( Object p_object );
	bool locationIsIlluminated();
	void discoverMagicWords();
protected:
private:
};

#endif // ADVENTDATA_H