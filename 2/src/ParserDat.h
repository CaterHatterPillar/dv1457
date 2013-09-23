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
	void parseDescriptionsLong( std::istringstream& p_ss );
	void parseDescriptionsShort( std::istringstream& p_ss );
private:
	std::ifstream* m_ifs;
	AdventData* m_ad;
};

#endif //PARSERDAT_H