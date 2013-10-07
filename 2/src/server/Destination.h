#ifndef TRAVELDESTINATION_H
#define TRAVELDESTINATION_H

#include <vector>

#include "Verb.h"

class Destination {
public:
	Destination( unsigned p_id );
	~Destination();

	void appendVerb( Verb p_verb );
	bool canTravelToUsing( Verb p_verb );

	unsigned getId() const;
	std::vector< Verb > getVerbs() const;
protected:
private:
	unsigned m_id; // y
	std::vector<Verb> m_verbs;
};

#endif // TRAVELDESTINATION_H