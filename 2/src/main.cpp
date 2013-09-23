#include <string>
#include <fstream>

#include "ParserDat.h"
#include "AdventData.h"

#include <iostream> //tmep

const static std::string filepathAdventdat = "../advent/advent.dat";
int main( int argc, char* argv[] ) {
	AdventData ad; // Make me into a singleton or something.

	std::ifstream dat;
	dat.open( filepathAdventdat.c_str(), std::ios_base::in );
	if( dat.is_open()==true ) {
		ParserDat pd( dat, ad );
		bool success = pd.init();
	}

	typedef std::map<unsigned int, std::string>::iterator it_type;
	for(it_type iterator = ad.dataDescLong.begin(); iterator != ad.dataDescLong.end(); iterator++) {
		std::cout << std::endl;
		std::cout << iterator->first;
		std::cout << ": ";
		std::cout << iterator->second;
	}

	return 0;
}