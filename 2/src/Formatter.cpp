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
		formatUppercase( 
			formatLength( 
				formatWords( p_command ) ) ) );
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
std::vector< Verb > Formatter::formatVerbs( std::vector< std::string > p_words ) {
	std::vector< Verb > verbs;
	unsigned verbId;
	std::string word;
	for( unsigned i = 0; i < p_words.size(); i++ ) {
		word = p_words[ i ];
		bool isVerb = Singleton<AdventData>::get().vocabulary.isVerb( word, verbId );
		if( isVerb==true ) {
			verbs.push_back( Singleton<AdventData>::get().vocabulary[ verbId ] ); 
		}	
	}
	return verbs;
}