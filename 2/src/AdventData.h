#ifndef ADVENTDATA_H
#define ADVENTDATA_H

#include <map>
#include <vector>
#include <string>

#include "Map.h"
#include "Singleton.h" // Include for brevity.
#include "Vocabulary.h"

class AdventData {
public:
	AdventData()	{}
	~AdventData()	{}

	Map map;
	Vocabulary vocabulary;

	// Messages
	std::map< unsigned, std::string > dataMsgsArbitrary;
	std::map< unsigned, std::string > dataMsgsClass;

	std::map< unsigned, unsigned > dataActionDefaults;

	// std::map< unsigned, std::vector<unsigned> > dataLiquidAssets;
	// ^ We're not parsing this yet.
protected:
private:
};

#endif //ADVENTDATA_H