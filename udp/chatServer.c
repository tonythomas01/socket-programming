//Text Chat application Server
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main() {
	struct sockaddr_in server;
	struct sockaddr_in client;
	unsigned int sockfd, clientlen;
	char rmsg[100], serverMsg[100], exitMsg[10] ="exit";
	
	/*---- Create the socket. The three arguments are: ----*/
	sockfd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP); 	/* 1) Internet domain 2) Stream socket 3) Default protocol */	  
	bzero ((char*) &server, sizeof (server));     /* Set all bits of the padding field to 0 */
	server.sin_family = AF_INET;        /* Address family = Internet */
	inet_aton ("127.0.0.1", &server.sin_addr);  /* Set IP address to localhost */
	server.sin_port = htons (4069);   /* Set port number, using htons function to use proper byte order */
	/*---- Bind the address struct to the socket ----*/
	bind (sockfd, (struct sockaddr*)&server, sizeof (server));   
	/*---- Recive  message from the socket  ----*/
	while( 1 ) {
		recvfrom (sockfd, rmsg, 100, 0, (struct sockaddr*)&client, &clientlen); 
		printf("Client says >> %s \n", rmsg );
		
		//Send a message back to server
		printf( "Server >> ");
		scanf("%s", serverMsg );
		if ( strcmp( serverMsg, exitMsg ) == 0 ) {
			printf( "Exiting. \n" );
			return 0;
		}
		sendto (sockfd, serverMsg, 100, 0, (struct sockaddr*)&client, sizeof(client));
	}
	
	return 1;

}
