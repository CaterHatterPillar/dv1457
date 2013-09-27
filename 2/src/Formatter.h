#ifndef FORMATTER_H
#define FORMATTER_H

#include <string>
#include <vector>

#include "Verb.h"
#include "AdventData.h"

static const unsigned FormatterWordLength = 5;

class Formatter {
public:
	Formatter();
	~Formatter();

	std::vector< Verb > format( std::string p_command );
protected:
private:
	std::vector< std::string >	formatWords( 		std::string p_command );
	std::vector< std::string >	formatLength( 		std::vector< std::string > p_words );
	std::vector< std::string >	formatUppercase( 	std::vector< std::string > p_words );
	std::vector< unsigned >		formatIds( 			std::vector< std::string > p_words );
	std::vector< unsigned >		formatDuplicates( 	std::vector< unsigned > p_wordIds );
	std::vector< Verb >			formatVerbs( 		std::vector< unsigned > p_wordIds );
};

#endif // FORMATTER_H