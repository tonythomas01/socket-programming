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
	char msg[100], recvmsg[100];

	if ( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
		perror( "socket" );
	}
	
	bzero ((char*)&server, sizeof (server));
	server.sin_family = AF_INET;
	inet_aton("127.0.0.1", &server.sin_addr); 
	server.sin_port = htons(8950);
	
	if ( connect( sockfd,(struct sockaddr*)&server, sizeof(server) ) < 0  ) {
		perror( "Cannot connect to TCP" );
	}
	
	for(;;) {
		printf( "Client>> " );
		scanf( " %[^\n]", msg );
		if ( send( sockfd, msg, 100, 0  ) < 0 ) {
			perror( "client sending send" );
		}
		
		if ( recv( sockfd, recvmsg, 100, 0 ) < 0 ) {
			perror( "client recieving failed" );
		}
		printf("Server says >> %s \n", recvmsg );
	}
	close( sockfd );
	
	return 0;

}
