#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8050
void main()
{
	int svrsock_fd;
	char buffer[1024];
	struct sockaddr_in svraddr, clnaddr;
	socklen_t svraddrlen = sizeof(struct sockaddr_in);
	socklen_t clnaddrlen = sizeof(struct sockaddr_in);
	svrsock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	svraddr.sin_port = htons(PORT);
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;

	bind(svrsock_fd, (struct sockaddr *) &svraddr, svraddrlen);
	printf("WAITING FOR CLIENT !!\n");
	
	while(1)
	{
		memset(buffer, 0, sizeof(buffer));
		recvfrom(svrsock_fd, buffer, sizeof(buffer), 0, &clnaddr, &clnaddrlen);
		printf("Received data from client : %s\n",buffer);
		if(strcmp(buffer,"exit")==0) break;

		memset(buffer, 0, sizeof(buffer));
		printf("Enter data for client : ");
		gets(buffer);
		sendto(svrsock_fd, buffer, sizeof(buffer), 0, &clnaddr, clnaddrlen);
		if(strcmp(buffer,"exit")==0) break;
	}
}