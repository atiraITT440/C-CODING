#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, newSock, portno, clientlen;
	char buffer[256];
	struct sockaddr_in serv_addr, client_addr;
	int n;
	if (argc < 3)
	{
		fprintf(stderr, "Error, no port provided\n");
		exit(0);
	}
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd < 0)
		error ("Error opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)error("Error on binding");

	listen(sockfd,5);
	clientlen = sizeof(client_addr);
	newSock = accept(sockfd, (struct sockaddr *) &client_addr, &clientlen);
	if(newSock < 0)
		error("Error on accept");

	bzero (buffer,256);
	n = read(newSock, buffer, 255);

	if(n<0) 
		error ("Error reading from socket");

	printf("Here is the message : %s\n",buffer );
	n= write(newSock,"I got your message ", 18);

	if(n<0) 
		error ("Error writing to socket");

	return 0;

}
