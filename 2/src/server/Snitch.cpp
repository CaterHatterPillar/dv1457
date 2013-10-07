#include "Common.h"
#include "Snitch.h"
#include "CommonSys.h"

Snitch::Snitch() {

}
Snitch::~Snitch() {
	// Do nothing.
}

std::string Snitch::ReadMsg( int p_sockfd ) {
	char buffer[Msg_In_Buffer_Size];
	bzero((char*)buffer, Msg_In_Buffer_Size);
 	int numBytes = recv(p_sockfd, buffer, Msg_In_Buffer_Size-1, 0);
 	if(numBytes<0)
 		printf("Error reading client message.\n errno: %d\n", errno);

 	return std::string(buffer);
}
bool Snitch::SendMsg( int p_sockfd, std::string p_msg ) {
	bool success = true;
	int numBytes = send(p_sockfd, p_msg.c_str(), p_msg.length(), 0);
 	if(numBytes<0)
 	{
 		printf("Error writing message.\n errno: %d\n", errno);
 		success = false;
 	}
  	return success;
}