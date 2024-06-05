udpClient2.c
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 8050
void main()
{
	char message[1024];
	int clnsock_fd;
	struct sockaddr_in svraddr;
	socklen_t svraddrlen = sizeof(struct sockaddr_in);
	clnsock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	svraddr.sin_port = htons(PORT);
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while(1)
	{
		memset(message, sizeof(message), 0);
		printf("Enter data for server : ");
		gets(message);
		sendto(clnsock_fd, message, sizeof(message), 0, &svraddr, svraddrlen);
		if(strcmp(message, "exit")==0) break;

		memset(message, sizeof(message), 0);
		recvfrom(clnsock_fd, message, sizeof(message), 0, &svraddr, &svraddrlen);
		printf("Received data from server : %s\n", message);
		if(strcmp(message,"exit")==0) break;
	}
}
