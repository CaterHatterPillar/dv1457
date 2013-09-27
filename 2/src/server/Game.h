#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstring>

#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <syslog.h>
#include <stdio.h>
#include <pwd.h>

class Game
{
public:
	Game(int p_sockfd);
	~Game();

	enum FileStatus
	{
		FileStatus_UNKNOWN,
		FileStatus_LOADED,
		FileStatus_MISSING
	};
	enum GameStatus
	{
		GameStatus_UNKNOWN,
		GameStatus_LOAD_GAME,
		GameStatus_NEW_GAME
	};

	void run();
private:

	void	 	queryName();
	FileStatus 	openGame();
	FileStatus 	openCaveFile();
	GameStatus 	queryContinue();
	void 		loadGameData();
	void 		runGame();
	void 		saveGame();

	std::string readMsg();
	void 		sendMsg(std::string p_msg);
	void	 	chatMsg(std::string p_msg);
	void 	 	sysMsg(std::string p_msg);

	void createFileName();

	int m_sockfd;
	std::string m_name;
	std::string m_filename;

};

#endif //GAME_H