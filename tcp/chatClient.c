//Text Chat application
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <netdb.h>

int main() {
	struct sockaddr_in server, client;
	unsigned int sockfd,serverlen;

	if ( ( sockfd = socket( PF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
		perror( "socket" );
	}
	
	bzero ((char*)&server, sizeof (server));
	server.sin_family = PF_INET;
	inet_aton("127.0.0.1", &server.sin_addr); 
	server.sin_port = htons (8698); 
	
	bzero((char*) &client, sizeof(client));
	client.sin_family = AF_INET;
	inet_aton ("127.0.0.1", &client.sin_addr);
	client.sin_port = htons (0);
	
	if ( connect( sockfd,(struct sockaddr*)&server, sizeof(server) ) < 0  ) {
		perror( "Cannot connect to TCP" );
	}
	
	char msg[100], recvmsg[100];
	bind (sockfd, (struct sockaddr*)&client, sizeof (client));
	for(;;) {
		printf( "Client>> " );
		scanf( "%s", msg );
		if ( send( sockfd, msg, 100, 0  ) < 0 ) {
			perror( "client sending send" );
		}
		if ( recv( sockfd, recvmsg, 100, 0 ) < 0 ) {
			perror( "client recieving failed" );
		}
	}
	close( sockfd );
	
	return 0;

}