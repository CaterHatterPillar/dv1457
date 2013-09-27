#include "Server.h"
#include "Game.h"

int Server::s_sockfd;
unsigned int Server::s_clientCnt;
sigset_t Server::s_mask;

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
 	daemonize("cave_server");
 	syslog(LOG_INFO, "Server demonized");
 	blockSignals();
 	syslog(LOG_INFO, "Server blocking signals");

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
	syslog(LOG_INFO, "server running");
	while(true)
	{
		syslog(LOG_INFO, "Listening for connections");
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

void Server::daemonize(const char* cmd)
{
	//clear file creation mask.
	umask(0);
	
	//Get the maximum number of file descriptors.
	struct rlimit rl;
	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
	{
		printf("Can't get file limit\n");
		exit(1);
	}

	//Become session leader to close controlling TTY.
	pid_t pid;
	if((pid = fork()) < 0)
	{
		printf("Can't fork\n");
		exit(1);
	}
	else if(pid != 0)
		exit(0);

	setsid();

	//Ensure futire opens won't allocate controlling TTYs
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGHUP, &sa, NULL) < 0)
	{
		printf("Can't ignore SIGHUP\n");
		exit(1);
	}
	if((pid = fork()) < 0)
	{
		printf("Can't fork");
		exit(1);
	}
	else if(pid != 0)
		exit(0);

	//Chanfe directory to root
	if(chdir("/") < 0)
	{
		printf("Can't change directory to /\n");
		exit(1);
	}

	//close all file descriptors.
	if(rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for(int i=0; i<rl.rlim_max; i++)
		close(i);

	//Attach file descriptors 0, 1 and 2 to /dev/null.
	int fd0 = open("/dev/null", O_RDWR);
	int fd1 = dup(0);
	int fd2 = dup(0);

	//Initiate log file.
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "unexpected file descriptors %d, %d, %d", fd0, fd1, fd2);
		exit(1);
	}
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
		printf("singal recived\n");
		switch(signo)
		{
		case SIGHUP:
			syslog(LOG_INFO, "Terminating all connections");
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