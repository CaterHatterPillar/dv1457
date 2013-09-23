#ifndef SERVER_H
#define SERVER_H

#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#define MAX_CONNECTION_COUNT 5

class Server
{
public:
	Server(int p_port);
	~Server();

	void init();
	void run();
private:

	void createSock();
	void createAddr();
	void bindAddrToSock(); 

	sockaddr_in m_addr;
	int m_port;
	int m_sockfd;

};

#endif //SERVER_H