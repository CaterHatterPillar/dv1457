#ifndef DAEMON_H
#define DAEMON_H

#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)


namespace Daemon
{
	void daemonize(const char* p_cmd);
	struct rlimit getMaxNumFDs();
	void closeControlingTTY();
	void ceepTTYClosed();
	void switchToRootDir();
	void closeAllFDs(const char* p_cmd,
		struct rlimit p_rl);

	int alreadyRunning();
	int lockfile(int p_fd);
};

#endif //DAEMON_H