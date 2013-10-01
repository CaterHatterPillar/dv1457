#ifndef SERVER_H
#define SERVER_H

#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>


#define MAX_CLIENT_CNT 128

class Server
{
public:
	Server(int p_port);
	~Server();

	void init();
	void run();
private:

	void blockSignals();

	static void* signalProcessing(void* p_threadId);
	static void	 closeAllSockfds();
	static void* handleClient(void* p_threadId);
	static int   acceptConnection();
	static void  addSockfd(int p_sockfd);
	static void  removeSockfd(int p_sockfd);
	
	static std::string queryName(int p_sockfd);
	static bool addName(std::string p_name);
	static bool removeName(std::string p_name);

	static std::string 	readMsg(int p_sockfd);
	static bool 		sendMsg(int p_sockfd, std::string p_msg);

	void createSock();
	void createAddr();
	void bindAddrToSock(); 

	static sigset_t 	s_mask;

	pthread_t			m_signalThread;
	static unsigned int s_clientCnt;

	static pthread_mutex_t 	s_vecSockMutex;
	static std::vector<int> s_sockfds;

	static pthread_mutex_t s_vecNameMutex;
	static std::vector<std::string> s_names;

	pthread_t threads[MAX_CLIENT_CNT];

	sockaddr_in m_addr;
	int 		m_port;
	static int 	s_sockfd;

};

#endif //SERVER_H