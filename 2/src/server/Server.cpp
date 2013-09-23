#include "Server.h"

Server::Server(int p_port)
{
	m_port 	 = p_port;
	m_sockfd = -1;
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
	listen(m_sockfd, MAX_CONNECTION_COUNT);

	sockaddr_in clientAddress;
 	int clientSize = sizeof(clientAddress);
 	int newSockfd = accept(m_sockfd, (struct sockaddr*)&clientAddress, (socklen_t*)&clientSize);
 	if(newSockfd < 0)
 		printf("Error accepting client.\n errno: %d\n", errno);
 		
 	char buffer[256];
 	bzero(buffer, 256);
 	int n = read(newSockfd, buffer, 255);
 	if(n<0)
 		printf("Error reading client message.\n errno: %d\n", errno);

 	printf("Message: \n\t%s", buffer);

 	n = write(newSockfd, "Message recived!", 16);
 	if(n<0)
 		printf("Error writing message.\n errno: %d\n", errno);
}

void Server::createSock()
{
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
 	if(m_sockfd < 0)
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
	if(bind(m_sockfd, (struct sockaddr*)&m_addr, sizeof(m_addr))< 0)
 		printf("Error binding adress to socket.\n errno: %d\n", errno);
}