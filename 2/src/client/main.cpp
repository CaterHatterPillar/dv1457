
#include <stdlib.h>

#include "Client.h"

int main( int argc, char* argv[] )
{
 	if(argc != 3)
 	{
 		printf("Usage: %s <server_ip server_port> \n", argv[0]);
 		return 1;
 	}
 	Client client(argv[1], atoi(argv[2]));
 	client.init();
 	client.run();

 	return 0;
}