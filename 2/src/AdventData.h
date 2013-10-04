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

struct AdventData {
public:
	Map map;
	Vocabulary vocabulary;
	Adventurer adventurer;
	Letterbox letterbox;
	Relations relations;
};

#endif //ADVENTDATA_H