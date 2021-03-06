#ifndef VERB_H
#define VERB_H

#include <string>
#include <vector>

class Object;

class Verb {
public:
	Verb();
	~Verb();

	void appendWord( std::string p_word );

	std::string toString();

	Verb& operator=( unsigned p_id );
	bool operator==( const unsigned& p_id ) const;
	bool operator==( const Verb& p_verb ) const;

	unsigned getId() const;
protected:
private:
	unsigned m_id;
	std::vector< std::string > m_words;
};

#endif // WORD_H