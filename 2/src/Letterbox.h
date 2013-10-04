#ifndef LETTERBOX_H
#define LETTERBOX_H

#include <map>
#include <vector>
#include <string>

struct Letter {
	unsigned id;
	std::vector< std::string > lines;
};

class Letterbox {
public:
	Letterbox();
	~Letterbox();

	void appendActionDefault( unsigned p_idAction, unsigned p_idMsg );
	Letter getActionDefaults( unsigned p_idAction );

	// []-operator maps to arbitrary messages, since they are the ones most used.
	Letter& operator[]( unsigned p_idArbitrary );
protected:
private:
	std::map< unsigned, Letter > m_arbitrary;
	std::map< unsigned, unsigned > m_actionDefaults;
};

#endif // LETTERBOX_H