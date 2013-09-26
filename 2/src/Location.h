#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

class Location {
public:
	Location();
	Location( unsigned p_id, std::string p_descShort, std::vector< std::string > p_descLongs );
	~Location();

	void setId( unsigned p_id );
	void setDescShort( std::string p_descShort );
	void appendDescLong( std::string p_descLong );

	unsigned getId();
	std::string getDescShort();
	std::string getDescLong();
	std::vector< std::string > getDescLongs();
protected:
private:
	unsigned m_id;
	std::string m_descShort;
	std::vector< std::string > m_descLongs;
};

#endif // LOCATION_H