#include "Game.h"
#include "Advent.h"
#include "Common.h"
#include "Result.h"

Game::Game(int p_sockfd, std::string p_name)
{
	m_sockfd = p_sockfd;
	m_name 	 = p_name;

	AdventData& ad = Singleton<AdventData>::get();
	ad.sockfd = p_sockfd;
	ad.client = p_name;
}
Game::~Game()
{
}

void Game::run()
{
	Result result;
	Advent ure;
	((Advent)ure).load(result);

	createFileName();
	
	GameStatus status = queryLoadGame();
	if(status == GameStatus_LOAD_GAME)
		loadGame();
	else if(status == GameStatus_NEW_GAME)
		newGame();

	std::string msg;
	bool run = true;
	while(run)
	{
		run = checkConnection();

		msg = readMsg();
		if(msg.length() > 0)
		{
			if(msg.at(0) == '/')
				run = sysMsg(msg);
			else
				ure.play( msg ); // haha
		}
	}

	saveGame();
}

Game::GameStatus Game::queryLoadGame()
{
	GameStatus status = GameStatus_UNKNOWN;
	bool fileExists = caveFileExists();
	if(fileExists)
	{
		sendMsg("/load_game");
		std::string msg = readMsg();
		if(strcmp(msg.c_str(), "/load_game") == 0)
			status = GameStatus_LOAD_GAME;
		else if(strcmp(msg.c_str(), "/new_game") == 0)
			status = GameStatus_NEW_GAME;
	}
	else
	{
		sendMsg("/new_game");
		std::string msg = readMsg();
		status = GameStatus_NEW_GAME;
	}
	return status;
}

void Game::loadGame()
{
	printf("Loading game\n");
	std::fstream file(m_filename.c_str());

	//Load shit!s

	file.close();
}
void Game::newGame()
{
	//Set up for new game.
}

void Game::saveGame()
{
	std::fstream file;
	file.open(m_filename.c_str(),
		std::ios_base::in |
		std::ios_base::out |
		std::ios_base::trunc);

	//Save shit!
	file << m_name << "\n";

	file.close();
}

bool Game::checkConnection()
{
	bool connected = true;
	connected = sendMsg("/con");
	return connected;
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

bool Game::sendMsg(std::string p_msg)
{
	bool success = true;
	int numBytes = send(m_sockfd, p_msg.c_str(), p_msg.length(), 0);
 	if(numBytes<0)
 	{
 		printf("Error writing message.\n errno: %d\n", errno);
 		success = false;
 	}
  	return success;
}

bool Game::gameMsg(std::string p_msg)
{
	/*
	NOTE. All incoming messges must be answered by the server.
	The client runs on a single thread and will therefore be blocked
	on next call to recieve until the server answers.
	*/
	bool success = true;

	success = sendMsg(p_msg);

	return success;
}

bool Game::sysMsg(std::string p_msg)
{
	/*
	NOTE. All incoming messges must be answered by the server.
	The client runs on a single thread and will therefore be blocked
	on next call to recieve until the server answers.
	*/

	bool success = true;

	if(strcmp(p_msg.c_str(), "/exit\n") == 0)
	{
		success = sendMsg("Client disconnecting");
		shutdown(m_sockfd, SHUT_RDWR);
	}
 	else if(strcmp(p_msg.c_str(), "/save\n") == 0)
 	{
 		saveGame();
 		success = sendMsg("Game saved!");
 	}
 	else
 		success = sendMsg("Unknown command");

 	return success;
}

void Game::createFileName()
{
	std::string filename = m_name;
	filename.erase(filename.end()-1);

	std::string dir = "/var/cave/";
	struct stat st={0};
	if( stat(dir.c_str(), &st) == -1)
		mkdir(dir.c_str(), 0700);

	m_filename = dir + filename + ".cave";
}

bool Game::caveFileExists()
{
	bool success = false;
	std::fstream file(m_filename.c_str());
	if(file.is_open())
	{
		success = true;
		file.close();
	}
	return success;
}