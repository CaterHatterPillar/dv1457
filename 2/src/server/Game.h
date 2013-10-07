#ifndef GAME_H
#define GAME_H

#include "CommonSys.h"

class Game
{
public:
	Game(int p_sockfd, std::string p_name);
	~Game();

	enum GameStatus
	{
		GameStatus_UNKNOWN,
		GameStatus_LOAD_GAME,
		GameStatus_NEW_GAME
	};

	void run();
private:

	GameStatus queryLoadGame();

	void loadGame();
	void newGame();
	void saveGame();

	bool checkConnection();

	std::string readMsg();
	bool 		sendMsg(std::string p_msg);
	bool	 	gameMsg(std::string p_msg);
	bool 	 	sysMsg(std::string p_msg);

	void createFileName();
	bool caveFileExists();

	int m_sockfd;
	std::string m_name;
	std::string m_filename;

};

#endif //GAME_H