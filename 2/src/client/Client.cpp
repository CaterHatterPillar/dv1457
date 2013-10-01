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
	bool run = true;

	answerName();
	answerLoadGame();

	while(run)
	{		
		msg = readMsg(); //Server checking connection.

 		msg = readUserInput();
	 	
	 	sendMsg(msg);

	 	msg = readMsg();
		printf("Answer: \n\t%s", msg.c_str());
		printf("\n");
	}
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
	if(numBytes == 0)
		printf("Server has closed this clients socket.\n");

	return std::string(buffer);
}

bool Client::sendMsg(std::string p_msg)
{
	bool success = true;
	int numBytes = send(m_sockfd, p_msg.c_str(), p_msg.length(), 0);
	if(numBytes <= 0)
	{
		printf("Error writing to socket.\n errno: %d\n", errno);
		success = false;
	}

	return success;
}

void Client::answerName()
{
	std::string msg;
	bool done = false;
	
	msg = readMsg();
	printf("%s\n", msg.c_str());
	while(!done)
	{
		msg = readUserInput();
		sendMsg(msg);

		msg = readMsg();
		if(msg.at(0) == 'W')
			done = true;
		printf("%s\n", msg.c_str());
	}
}

void Client::answerLoadGame()
{
	printf("answerLoadGame()\n");

	std::string input;
	std::string msg;
	msg = readMsg();

	bool done = false;

	if(strcmp(msg.c_str(), "/load_game") == 0)
	{
		printf("You have been here before, continue from last save? (yes/no)\n");
		while(!done)
		{
			input = readUserInput();
			if(strcmp(input.c_str(), "yes\n") == 0)
			{
				done = true;
				sendMsg("/load_game");
				printf("Loading game...\n");
			}
			else if(strcmp(input.c_str(), "no\n") == 0)
			{
				done = true;
				sendMsg("/new_game");
				printf("Starting new game...\n");
			}
			else
				printf("You must answer either \"yes\" or \"no\"\n");
		}
	}
	else
	{
		sendMsg("/new_game");
		printf("Starting new game...\n");
	}
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