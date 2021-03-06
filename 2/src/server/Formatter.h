#ifndef FORMATTER_H
#define FORMATTER_H

#include <string>
#include <vector>

#include "Verb.h"
#include "AdventData.h"

static const unsigned FormatterWordLength = 5;

class Formatter {
public:
	Formatter( AdventData& p_ad );
	~Formatter();

	std::vector< Verb > format( std::string p_command );
protected:
private:
	AdventData* m_ad;

	std::vector< std::string >	formatWords( 		std::string p_command );
	std::vector< std::string >	formatLength( 		std::vector< std::string > 	p_words 	);
	std::vector< std::string >	formatUppercase( 	std::vector< std::string > 	p_words 	);
	std::vector< unsigned >		formatIds( 			std::vector< std::string > 	p_words 	);
	std::vector< unsigned >		formatDuplicates( 	std::vector< unsigned > 	p_wordIds	);
	std::vector< Verb >			formatVerbs( 		std::vector< unsigned > 	p_wordIds	);
	std::vector< Verb >			formatOrder( 		std::vector< Verb >			p_verbs		);
};

#endif // FORMATTER_H