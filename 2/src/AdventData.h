#ifndef ADVENTDATA_H
#define ADVENTDATA_H

#include <map>
#include <vector>
#include <string>

struct TravelDestination {
	unsigned dest; // y
	std::vector<unsigned> verbs;
};
struct TravelLocation {
	unsigned loc; // x
	std::vector<TravelDestination> dests;
};

struct AdventData {
	// Description
	std::map< unsigned, std::vector<std::string> > dataDescLocLong;
	std::map< unsigned, std::string > dataDescLocShort;
	
	//std::map< unsigned, std::string > dataDescObj; 
	// ^ This structure is erronous. 
	// The key-value cannot be an unsigned, as it can be '0000' and other values. 
	// Also, the data structure cannot be a map - as we must know the order of certain objects.

	// Travel
	std::map< unsigned, TravelLocation > dataTravelTable;
	//std::map< unsigned, unsigned >				dataTravelTable;
	//std::map< unsigned, std::vector<unsigned> >	dataTravelVerbs;

	std::map< std::string, unsigned > dataVocabulary;

	// Messages
	std::map< unsigned, std::string > dataMsgsArbitrary;
	std::map< unsigned, std::string > dataMsgsClass;

	std::map< unsigned, std::vector<int> > dataLocObj; // Vector contains locations for key-object. If vector contains '-1', then the object is immovable. If the object has several locatons - it can be assumed to be immovable.

	std::map< unsigned, unsigned > dataActionDefaults;

	// std::map< unsigned, std::vector<unsigned> > dataLiquidAssets;
	// ^ We're not parsing this yet.
};

#endif //ADVENTDATA_H