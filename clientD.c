#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
 
int main (int argc,char *argv[])
{

	int sock;
	struct sockaddr_in server;
	char message[1000], server_reply[2000];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	{
		if (sock == -1)
		 {
			printf("Could not create socket");
		 }
		 printf("socket created");

		server.sin_addr.s_addr = inet_addr("127.0.0.1");
		server.sin_family = AF_INET;
		server.sin_port = htons (8888);

		if(connect(sock,(struct sockaddr *)&server, sizeof(server))<0)
		{
			perror("connect failed.Error");
			return 1;
		}
		
		printf("Connect\n");

		while(1)
		{
			printf("Enter command: ");
			scanf("%s", message);
			if(send(sock, message, strlen(message),0)<0)
			{
				printf("send failed");
				return 1;
			}
			if(recv(sock, server_reply, 2000, 0)<0)
			{
				printf("recv Failed");
				break;
			}
			printf("server reply : ", server_reply);
			printf("server_reply");
		}
		close(sock);
		
	}
	return 0;
}