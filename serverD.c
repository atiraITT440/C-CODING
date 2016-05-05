#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>

int main (int argc, char *argv[])
{
	int socket_fd,client_sock, c , read_size,value, len;
    struct sockaddr_in server, client;
    char client_message[2000];
	
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket_fd == -1)
	{
		printf("Could not create socket");
	}
	printf("Socket created");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(8888);

	if(bind(socket_fd, (struct sockaddr*) &server, sizeof(server))<0)
	{
		perror("bind failed. Error");
		return 1;
	}
	printf("bind done");

	listen(socket_fd,3);
	
	printf ("waiting for incoming connections..");
	c = sizeof(struct sockaddr_in);

	client_sock = accept (socket_fd,(struct sockaddr *) &client, (socklen_t*)&c);
		
	if(client_sock<0)
	{	
		perror("accept failed");
		return 1;
	}
	printf("connection accepted");
	
	getsockopt(socket_fd,SOL_SOCKET, SO_SNDBUF, &value, &len);
	
	if(value == 0)
		printf("Unable Get \n");
	else
		printf("Can Get %d\n",value);

	value = 32768;
	setsockopt (socket_fd,SOL_SOCKET, SO_SNDBUF, &value, sizeof(value));
	printf("Set !! \n ");
	
	getsockopt(socket_fd,SOL_SOCKET, SO_SNDBUF, &value, &len);
	
	if(value == 0)
		printf("Unable Get NEW\n");
	else
		printf("Can Get NEW %d\n",value);
	
	return 0;

}