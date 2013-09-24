#ifndef SERVER_H
#define SERVER_H

#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string>
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

	static void* 		handleClient(void* p_threadId);
	static int   		acceptConnection();
	static void  		disconnectClient(int p_sockfd);
	static std::string 	readMsg(int p_sockfd);
	static void 		sendMsg(int p_sockfd, std::string p_msg);
	static void	 		chatMsg(std::string p_msg, int p_sockfd);
	static int 	 		sysMsg(std::string p_msg);
	static std::string	login(int p_sockfd);
	static std::string 	askName(int p_sockfd);
	static bool 		openPrevGame(std::string p_name);

	void createSock();
	void createAddr();
	void bindAddrToSock(); 

	pthread_t 			m_threads[MAX_CLIENT_CNT];
	static unsigned int s_clientCnt;

	sockaddr_in m_addr;
	int 		m_port;
	static int 	s_sockfd;

};

#endif //SERVER_H