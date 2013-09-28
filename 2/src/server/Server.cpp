#include "Server.h"
#include "Game.h"
#include "Daemon.h"

int Server::s_sockfd;
unsigned int Server::s_clientCnt;
sigset_t Server::s_mask;
pthread_mutex_t Server::m_vecSockMutex;
std::vector<int> Server::s_sockfds;

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
 	blockSignals();

 	pthread_mutex_init(&m_vecSockMutex, NULL);

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
	pthread_mutex_lock(&m_vecSockMutex);
	for(unsigned int i=0; i<s_sockfds.size(); i++)
	{
		sendMsg(s_sockfds[i], "Server closing connection\n");
		shutdown(s_sockfds[i], SHUT_RDWR);
	}
	pthread_mutex_unlock(&m_vecSockMutex);
}


void* Server::handleClient(void* p_threadId)
{
	int sockfd = acceptConnection();

	addSockfd(sockfd);

	Game game(sockfd);
	game.run();

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
	pthread_mutex_lock(&m_vecSockMutex);
	s_sockfds.push_back(p_sockfd);
	pthread_mutex_unlock(&m_vecSockMutex);
}
void Server::removeSockfd(int p_sockfd)
{
	pthread_mutex_lock(&m_vecSockMutex);
	for(unsigned int i=0; i<s_sockfds.size(); i++)
	{
		if(p_sockfd == s_sockfds[i])
			s_sockfds.erase(s_sockfds.begin()+i);
	}
	pthread_mutex_unlock(&m_vecSockMutex);
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