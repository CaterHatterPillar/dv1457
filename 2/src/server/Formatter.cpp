#include "Common.h"
#include "Formatter.h"

Formatter::Formatter( AdventData& p_ad ) {
	m_ad = &p_ad;
}
Formatter::~Formatter() {
	// Do nothing.
}

std::vector< Verb > Formatter::format( std::string p_command ) {
	// All aboard the format-train!
	return formatOrder(
		formatVerbs( 
			formatDuplicates( 
				formatIds( 
					formatUppercase( 
						formatLength( 
							formatWords( p_command ) ) ) ) ) ) );
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
	std::string word;
	unsigned wordId;
	std::vector< unsigned > wordIds;
	for( unsigned i = 0; i < p_words.size(); i++ ) {
		word = p_words[ i ];
		
		bool isVerb = m_ad->vocabulary.isVerb( word, wordId );
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
	std::vector< Verb > verbs;
	for( unsigned i = 0; i < p_wordIds.size(); i++ ) {
		unsigned wordId = p_wordIds[ i ];
		verbs.push_back( m_ad->vocabulary[ wordId ] );
	}
	return verbs;
}
std::vector< Verb >	Formatter::formatOrder( std::vector< Verb > p_verbs ) {
	std::vector< Verb > verbs = p_verbs;
	std::reverse( verbs.begin(), verbs.end() );
	return verbs;
}