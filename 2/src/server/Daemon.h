#ifndef DAEMON_H
#define DAEMON_H

#include "CommonSys.h"

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