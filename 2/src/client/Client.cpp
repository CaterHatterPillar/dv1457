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
	std::string msg;
	bool exit = false;

	login();

	while(!exit)
	{
 		msg = readUserInput();

 		if(strcmp(msg.c_str(), "/exit\n") == 0)
 			exit = true;

	 	sendMsg(msg);
		if(!exit)
		{
	 		msg = readMsg();
	
			printf("Answer: \n\t%s", msg.c_str());
			printf("\n");
		}
	}
	shutdown(m_sockfd, SHUT_RDWR);
}

std::string Client::readUserInput()
{
	char buffer[256];
	bzero(buffer, 256);
 	fgets(buffer, 255, stdin);

 	return std::string(buffer);
}
std::string Client::readMsg()
{
	char buffer[256];
	bzero(buffer, 256);
	int numBytes = recv(m_sockfd, buffer, 255, 0);
	if(numBytes<0)
		printf("Error reading from socket.\n errno: %d\n", errno);

	return std::string(buffer);
}
void Client::sendMsg(std::string p_msg)
{
	int numBytes = send(m_sockfd, p_msg.c_str(), p_msg.length(), 0);
	if(numBytes < 0)
		printf("Error writing to socket.\n errno: %d\n", errno);
}

void Client::login()
{
	std::string msg = readMsg();
	printf("%s\n", msg.c_str());

	msg = readUserInput();
	sendMsg(msg);

	msg = readMsg();
	printf("%s\n", msg.c_str());
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