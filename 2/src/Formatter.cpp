#include <string>
#include <sstream>
#include <algorithm> // transform

#include "Formatter.h"
#include "AdventData.h"

Formatter::Formatter() {

}
Formatter::~Formatter() {
	// Do nothing.
}

std::vector< Verb > Formatter::format( std::string p_command ) {
	return formatVerbs( 
		formatDuplicates( 
			formatIds( 
				formatUppercase( 
					formatLength( 
						formatWords( p_command ) ) ) ) ) );
}

std::vector< std::string > Formatter::formatWords( std::string p_command ) {
	std::vector< std::string > words;
	std::istringstream ss( p_command );
	while( std::getline( ss, p_command, ' ') ) {
		words.push_back( p_command );
    }
    return words;
}
std::vector< std::string > Formatter::formatLength( std::vector< std::string > p_words ) {
	std::vector< std::string > words;
	for( unsigned i = 0; i < p_words.size(); i++ ) {
		std::string word = p_words[i].substr( 0, FormatterWordLength );
		words.push_back( word );
	}
	return words;
}
std::vector< std::string > Formatter::formatUppercase( std::vector< std::string > p_words ) {
	std::vector< std::string > words;
	for( unsigned i = 0; i < p_words.size(); i++ ) {
		std::string word = p_words[ i ];
		std::transform( word.begin(), word.end(), 
			word.begin(), ::toupper );
		words.push_back( word );
	}
	return words;
}
std::vector< unsigned > Formatter::formatIds( std::vector< std::string > p_words ) {
	AdventData& ad = Singleton<AdventData>::get();

	std::string word;
	unsigned wordId;
	std::vector< unsigned > wordIds;
	for( unsigned i = 0; i < p_words.size(); i++ ) {
		word = p_words[ i ];
		
		bool isVerb = ad.vocabulary.isVerb( word, wordId );
		if( isVerb==true ) {
			wordIds.push_back( wordId );
		}
	}

	return wordIds;
}
std::vector< unsigned > Formatter::formatDuplicates( std::vector< unsigned > p_wordIds ) {
	std::sort( p_wordIds.begin(), p_wordIds.end() );
	p_wordIds.erase( unique( p_wordIds.begin(), p_wordIds.end() ), p_wordIds.end() );

	return p_wordIds;
}
std::vector< Verb > Formatter::formatVerbs( std::vector< unsigned > p_wordIds ) {
	AdventData& ad = Singleton<AdventData>::get();

	std::vector< Verb > verbs;
	for( unsigned i = 0; i < p_wordIds.size(); i++ ) {
		unsigned wordId = p_wordIds[ i ];
		verbs.push_back( ad.vocabulary[ wordId ] );
	}
	return verbs;
}