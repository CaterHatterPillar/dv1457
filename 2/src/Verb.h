#ifndef VERB_H
#define VERB_H

#include <string>
#include <vector>

class Object;

class Verb {
public:
	Verb();
	~Verb();

	enum VerbIds {
		VerbIds_TAKE 	= 2001,
		VerbIds_DROP 	= 2002,
		VerbIds_SAY		= 2003,
		VerbIds_OPEN 	= 2004,
		VerbIds_NOTHING = 2005,
		VerbIds_CLOSE 	= 2006,
		VerbIds_ON 		= 2007,
		VerbIds_OFF 	= 2008,
		VerbIds_WAVE 	= 2009,
		VerbIds_CALM 	= 2010,
		VerbIds_WALK 	= 2011,
		VerbIds_FIGHT 	= 2012,
		VerbIds_POUR 	= 2013,
		VerbIds_EAT 	= 2014,
		VerbIds_DRINK 	= 2015,
		VerbIds_RUB 	= 2016,
		VerbIds_THROW 	= 2017,
		VerbIds_QUIT 	= 2018,
		VerbIds_FIND	= 2019,	
		VerbIds_INVEN	= 2020,
		VerbIds_FEED	= 2021,
		VerbIds_FILL	= 2022,
		VerbIds_BLAST	= 2023,
		VerbIds_SCORE	= 2024,
		VerbIds_FEE		= 2025,
		VerbIds_FIE		= 2025,
		VerbIds_BRIEF	= 2026,
		VerbIds_READ	= 2027,
		VerbIds_BREAK	= 2028,
		VerbIds_WAKE	= 2029,
		VerbIds_SUSPE	= 2030,
		VerbIds_HOURS	= 2031,
	};

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