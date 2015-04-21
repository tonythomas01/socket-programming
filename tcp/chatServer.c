//Text Chat application Server
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<ctype.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
int main() {
	struct sockaddr_in server, client;
	unsigned int sockfd, clientlen, clientfd;
	char rmsg[100], serverMessage[100];
	
	if ( ( sockfd = socket (AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
		perror( "socket" );
	}
	
	bzero ((char*) &server, sizeof (server)); 
	server.sin_family = AF_INET;
	inet_aton ("127.0.0.1", &server.sin_addr); 
	server.sin_port = htons(8950);
	
	if ( bind ( sockfd, (struct sockaddr*)&server, sizeof (server) ) < 0 ) {
		perror( "bind error " );
	}
	if ( listen( sockfd, SOMAXCONN ) < 0 ) {
		perror( "listen" );
	}
	
	clientlen = sizeof( client );
	clientfd = accept( sockfd, ( struct sockaddr * )&client, &clientlen );
	
	if ( clientfd <  0 ) {
		perror( "accept" );
	}
	
	for (;;) {
		if ( recv( clientfd, rmsg, 100, 0 )  < 0 ){
			perror( "receive" );
		}
		printf("Client says >> %s \n", rmsg );
		printf( "Server >> ");
		scanf( " %[^\n]", serverMessage );
		if ( send( clientfd, serverMessage, 100, 0  ) < 0 ) { 
			perror( "serever sending fail" );
		}
	}
	
	close(clientfd);
	close(sockfd);
	return 1;

}
