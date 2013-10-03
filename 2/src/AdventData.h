#ifndef ADVENTDATA_H
#define ADVENTDATA_H

#include <map>
#include <vector>
#include <string>

#include "Map.h"
#include "Letterbox.h"
#include "Vocabulary.h"
#include "Adventurer.h"

#include "Singleton.h" // Include for brevity.

class AdventData {
public:
	AdventData()	{}
	~AdventData()	{}

	Map map;
	Vocabulary vocabulary;
	Adventurer adventurer;
	Letterbox letterbox;

	// Everything below is temporary. Ought not be stored in this way.
	//std::map< unsigned, std::string > dataMsgsClass;
	//std::map< unsigned, unsigned > dataActionDefaults;
	// std::map< unsigned, std::vector<unsigned> > dataLiquidAssets;
protected:
private:
};

#endif //ADVENTDATA_H