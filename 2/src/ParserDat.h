#ifndef PARSERDAT_H
#define PARSERDAT_H

#include <fstream>

#include "AdventData.h"

class ParserDat {
public:
	ParserDat( std::ifstream& p_ifs, AdventData& io_ad );
	~ParserDat();

	bool init();
protected:
	void parseDescLong(			std::istringstream& p_ss );
	void parseDescShort( 		std::istringstream& p_ss );
	void parseTravelTable( 		std::istringstream& p_ss );
	void parseVocabulary( 		std::istringstream& p_ss );
	void parseMsgs( 			std::istringstream& p_ss, std::map<unsigned, std::string>& p_target );
	void parseObjLoc( 			std::istringstream& p_ss );
	void parseObjDesc( 			std::istringstream& p_ss ); // Can only parse up to 100 objects.
	void parseActionDefaults( 	std::istringstream& p_ss );
	void parseLiquidAssets( 	std::istringstream& p_ss ); // This function is not yet used.
private:
	std::ifstream* m_ifs;
	AdventData* m_ad;
};

#endif //PARSERDAT_H