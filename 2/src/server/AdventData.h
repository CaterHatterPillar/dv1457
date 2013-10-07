#ifndef ADVENTDATA_H
#define ADVENTDATA_H

#include <map>
#include <vector>
#include <string>

#include "Map.h"
#include "Relations.h"
#include "Letterbox.h"
#include "Vocabulary.h"
#include "Adventurer.h"

#include "Singleton.h" // Include for brevity.

class AdventData {
public:
	// Client
	int sockfd;
	std::string client;

	// Gameplay
	Map map;
	Vocabulary vocabulary;
	Adventurer adventurer;
	Letterbox letterbox;
	Relations relations;

	bool isOnSite( Object p_object ) {
		bool onSite = false;
		unsigned objectId = p_object.getId();
		if( adventurer.getInventory().carriesItem( objectId )==true ||
			adventurer.getLocation().objectAtLocation( objectId )==true ) {
			onSite = true;
		}
		return onSite;
	};
};

#endif //ADVENTDATA_H