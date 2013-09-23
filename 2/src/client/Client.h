#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


class Client
{
public:
	Client(char* p_ip, int p_port);
	~Client();

	void init();
	void run();
private:

	void createAddr();
	void createSock();
	void connectToServer();

	char* 		m_ip;
	sockaddr_in m_addr;
	int 		m_sockfd;
	int 		m_port;
};

#endif //CLIENT_H