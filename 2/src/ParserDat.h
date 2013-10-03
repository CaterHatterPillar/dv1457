#ifndef PARSERDAT_H
#define PARSERDAT_H

#include <vector>
#include <fstream>

#include "AdventData.h"

class ParserDat {
public:
	ParserDat( std::ifstream& p_ifs, AdventData& io_ad );
	~ParserDat();

	void init(); // Consider adding return of bool-type to indicate successful parse.
protected:
	void compileDependantData();
	void parseDescLong(			std::istringstream& p_ss );
	void parseDescShort( 		std::istringstream& p_ss );
	void parseTravelTable( 		std::istringstream& p_ss );
	void parseVocabulary( 		std::istringstream& p_ss );
	void parseMsgsArbitrary(	std::istringstream& p_ss );
	void parseObjLoc( 			std::istringstream& p_ss );
	void parseObjDesc( 			std::istringstream& p_ss ); // Can only parse up to 100 objects.
	/*void parseActionDefaults( 	std::istringstream& p_ss );
	void parseLiquidAssets( 	std::istringstream& p_ss );*/ // This function is not yet used.
private:
	std::ifstream* m_ifs;
	AdventData* m_ad; // Result

	// Temporary data used whilst parsing:
	struct TravelDesc {
		unsigned loc;
		unsigned dest;
		std::vector<unsigned> verbIds;
	};
	struct ObjectDesc {
		std::vector< unsigned > locs;
		Object obj;
	};

	std::vector<TravelDesc> m_travelDescs;
	std::map< unsigned, ObjectDesc > m_objectDescs;
};

#endif //PARSERDAT_H