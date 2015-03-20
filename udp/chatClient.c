//Text Chat application
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main() {
	struct sockaddr_in server, client;
	unsigned int sockfd,serverlen;
	
	/*---- Create the socket. The three arguments are: ----*/  
	sockfd = socket (AF_INET, SOCK_DGRAM, 0);          /* 1) Internet domain 2) Stream socket 3) Default protocol */	
	bzero ((char*)&server, sizeof (server));     /* Set all bits of the padding field to 0 */
	server.sin_family = AF_INET;                    /* Address family = Internet */
	inet_aton ("127.0.0.1", &server.sin_addr);      /* Set IP address to localhost */
	server.sin_port = htons (4069);                 /* Set port number, using htons function to use proper byte order */     
	
	bzero ((char*) &client, sizeof (client));
	client.sin_family = AF_INET;
	inet_aton ("127.0.0.1", &client.sin_addr);
	client.sin_port = htons (0);
	
	bind (sockfd, (struct sockaddr*)&client, sizeof (client)); /*---- Bind the address struct to the socket ----*/
	
	char msg[100], exitMsg[10] ="exit";
	while( 1 ) {
		printf( "Client>> " );
		scanf( "%s", msg );
		if ( strcmp( msg, exitMsg ) == 0 ) {
			printf( "Exiting. \n" );
			return 0;
		}
		sendto(sockfd, msg, 100, 0, (struct sockaddr*)&server, sizeof (server) );

		//Receive from server 
		char serverMsgReceived[100];
		recvfrom (sockfd, serverMsgReceived, 100, 0, (struct sockaddr*)&server, &serverlen ); 
		printf("Server says >> %s \n", serverMsgReceived );
	}
	return 0;

}
