#include "Server.h"
#include "Game.h"
#include "Daemon.h"

int 				Server::s_sockfd;
sigset_t 			Server::s_mask;
unsigned int 		Server::s_clientCnt;
pthread_mutex_t 	Server::s_vecSockMutex;
std::vector<int> 	Server::s_sockfds;

pthread_mutex_t 		 Server::s_vecNameMutex;
std::vector<std::string> Server::s_names;

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
 	Daemon::daemonize("cave_server");

 	if(Daemon::alreadyRunning())
 	{
 		syslog(LOG_ERR, "Daemon already running");
 		exit(1);
 	}

 	blockSignals();

 	pthread_mutex_init(&s_vecSockMutex, NULL);

 	int err = pthread_create(&m_signalThread, NULL, signalProcessing, NULL);
 	if(err != 0)
 	{
 		syslog(LOG_INFO, "Could not create singal thread");
 		exit(1);
 	}
 
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
			pthread_t tid;
			pthread_create(&tid, NULL, handleClient, NULL);
			s_clientCnt++;
		}	

	}

	pthread_exit(NULL);
}

void Server::blockSignals()
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0)
	{
		printf("can't restore SIGHUP default");
		exit(1);
	}
	sigfillset(&s_mask);
	int err;
	if((err = pthread_sigmask(SIG_BLOCK, &s_mask, NULL)) != 0)
	{
		printf("SIG_BLOCK error");
		exit(1);
	}
}

void* Server::signalProcessing(void* p_threadId)
{
	int err, signo;

	while(true)
	{
		err = sigwait(&s_mask, &signo);
		if(err != 0)
		{
			syslog(LOG_ERR, "sigwait failed");
			exit(1);
		}
		switch(signo)
		{
		case SIGHUP:
			syslog(LOG_INFO, "Terminating all connections");
			sleep(30);
			closeAllSockfds();
			break;
		case SIGTERM:
			syslog(LOG_INFO, "got Sigterm; exiting");
			exit(0);
			break;
		default:
			syslog(LOG_INFO, "unexpected signal %d\n", signo);
			break;
		}
	}
}
void Server::closeAllSockfds()
{
	pthread_mutex_lock(&s_vecSockMutex);
	for(unsigned int i=0; i<s_sockfds.size(); i++)
	{
		sendMsg(s_sockfds[i], "Server closing connection\n");
		shutdown(s_sockfds[i], SHUT_RDWR);
	}
	pthread_mutex_unlock(&s_vecSockMutex);
}

void* Server::handleClient(void* p_threadId)
{
	int sockfd = acceptConnection();
	addSockfd(sockfd);

	std::string name = queryName(sockfd);

	syslog(LOG_INFO, "Client connected at socket: %d", sockfd);

	if(name.length() > 0)
	{
		Game game(sockfd, name);
		game.run();
	}

	syslog(LOG_INFO, "Client disconnected from socket: %d", sockfd);

	removeName(name);
	removeSockfd(sockfd);
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

void Server::addSockfd(int p_sockfd)
{
	pthread_mutex_lock(&s_vecSockMutex);
	s_sockfds.push_back(p_sockfd);
	pthread_mutex_unlock(&s_vecSockMutex);
}
void Server::removeSockfd(int p_sockfd)
{
	pthread_mutex_lock(&s_vecSockMutex);
	for(unsigned int i=0; i<s_sockfds.size(); i++)
	{
		if(p_sockfd == s_sockfds[i])
			s_sockfds.erase(s_sockfds.begin()+i);
	}
	pthread_mutex_unlock(&s_vecSockMutex);
}

std::string Server::queryName(int p_sockfd)
{
	std::string msg = "What is your name adventurer?";
	std::string name = "Unknown";
	
	bool nameAdded = false;
	bool run = sendMsg(p_sockfd, msg);
	while(run)
	{
		name = readMsg(p_sockfd);
		nameAdded = addName(name);
		if(nameAdded)
		{
			msg = "Welcome " + name;
			run = false;
		}
		else
			msg = "An adventurer with that name already exists. New name: ";

		sendMsg(p_sockfd, msg); 
	}
	return name;
}
bool Server::addName(std::string p_name)
{
	pthread_mutex_lock(&s_vecNameMutex);

	bool nameFound = false;
	bool success = false;

	for(unsigned int i=0; i<s_names.size(); i++)
	{
		if(strcmp(s_names[i].c_str(), p_name.c_str()) == 0)
			nameFound = true;
	}
	if(nameFound == false)
	{
		s_names.push_back(p_name);
		success = true;
	}
	pthread_mutex_unlock(&s_vecNameMutex);

	return success;
}
bool Server::removeName(std::string p_name)
{
	pthread_mutex_lock(&s_vecNameMutex);
	bool success = false;
	for(unsigned int i=0; i<s_names.size(); i++)
	{
		if(strcmp(s_names[i].c_str(), p_name.c_str()) == 0)
		{
			s_names.erase(s_names.begin()+i);
			success = true;
		}
	}
	pthread_mutex_unlock(&s_vecNameMutex);

	return success;
}


std::string Server::readMsg(int p_sockfd)
{
	char buffer[256];
	bzero((char*)buffer, 256);
 	int numBytes = recv(p_sockfd, buffer, 255, 0);
 	if(numBytes<0)
 		syslog(LOG_INFO, "Error reading message.");

 	return std::string(buffer);
}

bool Server::sendMsg(int p_sockfd, std::string p_msg)
{
	bool success = true;
	int numBytes = send(p_sockfd, p_msg.c_str(), p_msg.length(), 0);
 	if(numBytes<0)
 	{
 		syslog(LOG_INFO, "Error sending message.");
 		success = false;
 	}

 	return success;
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