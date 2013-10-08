#ifndef SNITCH_H
#define SNITCH_H

#include <string>

static const unsigned Msg_In_Buffer_Size = 512;

class Snitch {
public:
	Snitch();
	~Snitch();

	static std::string ReadMsg( int p_sockfd );
	static bool SendMsg( int p_sockfd, std::string p_msg );
protected:
private:
};

#endif // SNITCH_H