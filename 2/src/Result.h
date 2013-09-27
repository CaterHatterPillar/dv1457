#ifndef RESULT_H
#define RESULT_H

#include <string>
#include <vector>

class Result {
public:
	Result();
	~Result();

	void appendParam( std::string p_param );

	void setSummary( std::string p_summary );
	void setParams( std::vector< std::string > p_params );

	std::string getSummary() const;
	unsigned getParamsSize() const;

	std::string& operator[]( unsigned p_i );
protected:
private:
	std::string m_summary;
	std::vector< std::string > m_params;
};

#endif // RESULT_H