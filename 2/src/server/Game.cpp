#include "Game.h"

Game::Game(int p_sockfd)
{
	m_sockfd = p_sockfd;
	m_name = "Unknown";
}
Game::~Game()
{
}

void Game::run()
{
	queryName();
	FileStatus fileStatus = openGame();
	GameStatus gameStatus = GameStatus_NEW_GAME;
	if(fileStatus == FileStatus_LOADED)
		gameStatus = queryContinue();

	if(gameStatus == GameStatus_LOAD_GAME)
		loadGameData();

	runGame();
	
	saveGame();
}


void Game::queryName()
{
	std::string msg = "What is your name adventurer?";
	sendMsg(msg);

  	std::string name = readMsg();
  	msg = "Welcome " + name;
  	sendMsg(msg);

  	m_name = name;
}

Game::FileStatus Game::openGame()
{
	printf("Open game\n");
	std::string msg = "";
	FileStatus status = openCaveFile();
	if(status == FileStatus_MISSING)
	{
		msg = "/new_game";
		sendMsg(msg);
	}
	else
	{
		msg = "/prev_game";
		sendMsg(msg);
	}

	return status;
}	

Game::GameStatus Game::queryContinue()
{
	GameStatus status;
	std::string msg ="";
	bool done = false;
	while(!done)
	{
		msg = readMsg();
		if(strcmp(msg.c_str(), "yes\n") == 0)
		{
			done = true;
			msg = "/load_game";
			sendMsg(msg);
			status = GameStatus_LOAD_GAME;
		}
		else if(strcmp(msg.c_str(), "no\n") == 0)
		{
			done = true;
			std::string msg = "/new_game";
			sendMsg(msg);
			status = GameStatus_NEW_GAME;
		}
		else
		{
			msg = "/unknown";
			sendMsg(msg);
		}
	}
	return status;
}

Game::FileStatus Game::openCaveFile()
{
	FileStatus status = FileStatus_UNKNOWN;

	std::string filename = getFileName();
	std::fstream file(filename.c_str());

	std::string msg = "";

	printf("%s\n", filename.c_str());
	if(file.is_open())
		status = FileStatus_LOADED;
	else
		status = FileStatus_MISSING;

	file.close();
	return status;
}

void Game::loadGameData()
{
	printf("Loading game\n");

	std::string filename = getFileName();
	std::fstream file(filename.c_str());

	//Load shit!s

	file.close();
}

void Game::runGame()
{
	std::string msg;
 	int sysCode = 1;
 	while(sysCode > 0)
 	{
 		msg = readMsg();
 		if(msg.length() > 0)
 		{
 			if(msg.at(0) == '/')
 				sysCode = sysMsg(msg);
 			else
 				chatMsg(msg);
 		}
	}
}

void Game::saveGame()
{
	printf("Saving game....\n");

	std::string filename = getFileName();
	std::fstream file;
	file.open(filename.c_str(),
		std::ios_base::in |
		std::ios_base::out |
		std::ios_base::trunc);

	//Save shit!
	file << m_name << "\n";

	file.close();

	printf("Game saved\n");
}


std::string Game::readMsg()
{
	char buffer[256];
	bzero((char*)buffer, 256);
 	int numBytes = recv(m_sockfd, buffer, 255, 0);
 	if(numBytes<0)
 		printf("Error reading client message.\n errno: %d\n", errno);

 	return std::string(buffer);
}

void Game::sendMsg(std::string p_msg)
{
	int numBytes = send(m_sockfd, p_msg.c_str(), p_msg.length(), 0);
 	if(numBytes<0)
  		printf("Error writing message.\n errno: %d\n", errno);
}

void Game::chatMsg(std::string p_msg)
{
	/*
	NOTE. All incoming messges must be answered by the server.
	The client runs on a single thread and will therefore be blocked
	on next call to recieve until the server answers.
	*/

	printf("Message at socket %d: \n\t%s", m_sockfd, p_msg.c_str());
	sendMsg(p_msg);
}

int Game::sysMsg(std::string p_msg)
{
	/*
	NOTE. All incoming messges must be answered by the server.
	The client runs on a single thread and will therefore be blocked
	on next call to recieve until the server answers.
	*/

	int sysCode = 1;
	if(strcmp(p_msg.c_str(), "/exit\n") == 0)
	{
		sysCode = 0;
		shutdown(m_sockfd, SHUT_RDWR);
	}
 	else if(strcmp(p_msg.c_str(), "/save\n") == 0)
 	{
 		saveGame();
 		sendMsg("Game saved!");
 	}

 	return sysCode;
}

std::string Game::getFileName()
{
	std::string filename = m_name;
	filename.erase(filename.end()-1);
	filename = filename + ".cave";

	return filename;
}