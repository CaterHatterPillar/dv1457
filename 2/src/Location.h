#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

#include "Verb.h"
#include "Destination.h"

class Location {
public:
	Location();
	Location( unsigned p_id, std::string p_descShort, std::vector< std::string > p_descLongs );
	~Location();

	void appendDestination( Destination p_destination );

	void setId( unsigned p_id );
	void setDescShort( std::string p_descShort );
	void appendDescLong( std::string p_descLong );

	unsigned getId();
	std::string getDescShort();
	std::string getDescLong();
	std::vector< std::string > getDescLongs();
	unsigned getNumDestinations();

	Destination& operator[]( unsigned p_id );
protected:
private:
	unsigned m_id; // x - the location

	// Desc
	std::string m_descShort;
	std::vector< std::string > m_descLongs;

	// Travel
	// Consider implementing the Location/Destination paradigm as a linked graph.
	std::vector<Destination> m_destinations;
};

#endif // LOCATION_H