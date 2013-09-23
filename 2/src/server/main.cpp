#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#include <stdlib.h>

#include "Server.h"

#define SERVER_PORT 17000
#define MAX_CONNECTION_COUNT 5 

int main( int argc, char* argv[] )
 {
 	if(argc != 2)
 	{
 		printf("Usage: %s <server port nr> \n", argv[0]);
 		return 1;
 	}

 	Server server(atoi(argv[1]));
 	server.init();
 	server.run();

 	return 0;
 }