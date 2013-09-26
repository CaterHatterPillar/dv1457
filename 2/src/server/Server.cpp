#include "Server.h"
#include "Game.h"

int Server::s_sockfd;
unsigned int Server::s_clientCnt;

Server::Server(int p_port)
{
	m_port 	 	= p_port;
	s_sockfd 	= -1;
	s_clientCnt = 0;
}
Server::~Server()
{
	
}

void Server::init()
{
 	createSock();
 	createAddr();
 	bindAddrToSock();	
}

void Server::run()
{
	while(true)
	{
		listen(s_sockfd, MAX_CLIENT_CNT);
		if(s_clientCnt < MAX_CLIENT_CNT)
		{
			pthread_create(&m_threads[s_clientCnt], NULL, handleClient, NULL);
			s_clientCnt++;
		}	

	}

	pthread_exit(NULL);
}

void* Server::handleClient(void* p_threadId)
{
	int sockfd = acceptConnection();

	Game game(sockfd);
	game.run();

	disconnectClient(sockfd);
 	pthread_exit(NULL);
}

int Server::acceptConnection()
{
	sockaddr_in clientAddress;
 	int clientSize = sizeof(clientAddress);
 	int newSockfd = accept(s_sockfd, (struct sockaddr*)&clientAddress, (socklen_t*)&clientSize);
 	if(newSockfd < 0)
 		printf("Error accepting client.\n errno: %d\n", errno);

 	return newSockfd;
}

void Server::disconnectClient(int p_sockfd)
{
	printf("Client at socket %d disconnecting.\n", p_sockfd);
	s_clientCnt--;
}

std::string Server::readMsg(int p_sockfd)
{
	char buffer[256];
	bzero((char*)buffer, 256);
 	int numBytes = recv(p_sockfd, buffer, 255, 0);
 	if(numBytes<0)
 		printf("Error reading client message.\n errno: %d\n", errno);

 	return std::string(buffer);
}

void Server::sendMsg(int p_sockfd, std::string p_msg)
{
	int numBytes = send(p_sockfd, p_msg.c_str(), p_msg.length(), 0);
 	if(numBytes<0)
  		printf("Error writing message.\n errno: %d\n", errno);
}

void Server::chatMsg(std::string p_msg, int p_sockfd)
{
	printf("Message at socket %d: \n\t%s", p_sockfd, p_msg.c_str());
	sendMsg(p_sockfd, p_msg);
}

int Server::sysMsg(std::string p_msg)
{
	int sysCode = 1;
	if(strcmp(p_msg.c_str(), "/exit\n") == 0)
 		sysCode = 0;

 	return sysCode;
}

void Server::createSock()
{
	s_sockfd = socket(AF_INET, SOCK_STREAM, 0);
 	if(s_sockfd < 0)
 		printf("Error creating socket.\n errno: %d\n", errno);	
}

void Server::createAddr()
{
	bzero((char*)&m_addr, sizeof(m_addr));
	
	m_addr.sin_family 	 	= AF_INET;
 	m_addr.sin_port 		= htons(m_port);
 	m_addr.sin_addr.s_addr  = INADDR_ANY;
}

void Server::bindAddrToSock()
{
	if(bind(s_sockfd, (struct sockaddr*)&m_addr, sizeof(m_addr))< 0)
 		printf("Error binding adress to socket.\n errno: %d\n", errno);
}