#include "Client.h"

Client::Client(char* p_ip, int p_port)
{
	m_ip = p_ip;
	m_port = p_port;

	m_sockfd = -1;
	bzero((char*)&m_addr, sizeof(m_addr));
}
Client::~Client()
{
}

void Client::init()
{
 	createAddr();
 	createSock();
 	connectToServer();
}

void Client::run()
{
	char buffer[256];
 	bzero(buffer, 256);
 	
 	printf("Enter message: ");
 	fgets(buffer, 255, stdin);

 	int n = write(m_sockfd, buffer, strlen(buffer));
 	if(n < 0)
 		printf("Error writing to socket.\n errno: %d\n", errno);

 	bzero(buffer, 256);
 	n = read(m_sockfd, buffer, 255);
 	if(n<0)
		printf("Error reading from socket.\n errno: %d\n", errno);

	printf("Answer: \n\t%s", buffer);
	printf("\n");
}

void Client::createAddr()
{
	m_addr.sin_family 	= AF_INET;
 	m_addr.sin_port 	= htons(m_port);

 	if(inet_pton(AF_INET, m_ip, &m_addr.sin_addr) <=0 )
 		printf("Error inet_pton.\n errno: %d\n", errno);
}
void Client::createSock()
{
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
 	if(m_sockfd<0)
 		printf("Error creating socket.\n errno: %d\n", errno);
}
void Client::connectToServer()
{
	if(connect(m_sockfd, (struct sockaddr*)&m_addr, sizeof(m_addr)) < 0)
 		printf("Error connecting to server.\n errno: %d\n", errno);
}