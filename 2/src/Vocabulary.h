#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <map>
#include <string>

#include "Verb.h"

class Vocabulary {
public:
	Vocabulary();
	~Vocabulary();

	void addWord( unsigned p_id, std::string p_word );
	bool isVerb( std::string p_word, unsigned& io_verbId );

	Verb& operator[]( unsigned p_id );
protected:
private:
	std::map< unsigned, Verb > m_verbs;
	std::map< std::string, unsigned > m_wordToVerb; // Used to establish legit words.
};

#endif // VOCABULARY_H