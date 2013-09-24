#ifndef SERVER_H
#define SERVER_H

#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_CLIENT_CNT 5

class Server
{
public:
	Server(int p_port);
	~Server();

	void init();
	void run();
private:

	static void* handleClient(void* threadId);
	static int acceptConnection();
	static void disconnectClient(int sockfd);

	void createSock();
	void createAddr();
	void bindAddrToSock(); 

	pthread_t m_threads[MAX_CLIENT_CNT];
	static unsigned int s_clientCnt;

	sockaddr_in m_addr;
	int m_port;
	static int s_sockfd;

};

#endif //SERVER_H