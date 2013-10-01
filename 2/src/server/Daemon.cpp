
#include "Daemon.h"

void Daemon::daemonize(const char* p_cmd)
{
	umask(0);

	struct rlimit rl;
	rl = getMaxNumFDs();
	closeControlingTTY();
	ceepTTYClosed();
	switchToRootDir();
	closeAllFDs(p_cmd, rl);
}

struct rlimit Daemon::getMaxNumFDs()
{
	struct rlimit rl;
	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
	{
		printf("Can't get file limit\n");
		exit(1);
	}

	return rl;
}

void Daemon::closeControlingTTY()
{
	pid_t pid;
	if((pid = fork()) < 0)
	{
		printf("Can't fork\n");
		exit(1);
	}
	else if(pid != 0)
		exit(0);

	setsid();
}

void Daemon::ceepTTYClosed()
{
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGHUP, &sa, NULL) < 0)
	{
		printf("Can't ignore SIGHUP\n");
		exit(1);
	}
	pid_t pid;
	if((pid = fork()) < 0)
	{
		printf("Can't fork");
		exit(1);
	}
	else if(pid != 0)
		exit(0);
}

void Daemon::switchToRootDir()
{
	if(chdir("/") < 0)
	{
		printf("Can't change directory to /\n");
		exit(1);
	}
}

void Daemon::closeAllFDs(const char* p_cmd, struct rlimit p_rl)
{
	if(p_rl.rlim_max == RLIM_INFINITY)
		p_rl.rlim_max = 1024;
	for(int i=0; i<p_rl.rlim_max; i++)
		close(i);

	//Attach file descriptors 0, 1 and 2 to /dev/null.
	int fd0 = open("/dev/null", O_RDWR);
	int fd1 = dup(0);
	int fd2 = dup(0);

	//Initiate log file.
	openlog(p_cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "unexpected file descriptors %d, %d, %d", fd0, fd1, fd2);
		exit(1);
	}
}

int Daemon::alreadyRunning()
{
	int fd;
	char buf[16];

	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if(fd < 0)
	{
		syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
		exit(1);
	}
	if(lockfile(fd) < 0)
	{
		if(errno == EACCES || errno == EAGAIN)
		{
			close(fd);
			return 1;
		}
		syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
		exit(1);
	}
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf)+1);
	return 0;
}

int Daemon::lockfile(int p_fd)
{
	struct flock fl;
	fl.l_type 	= F_WRLCK;
	fl.l_start 	= 0;
	fl.l_whence = SEEK_SET;
	fl.l_len 	= 0;
	return(fcntl(p_fd, F_SETLK, &fl));
}