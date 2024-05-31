#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8090
void main()
  {
  int clnsock_fd;
  char message[1024];
  struct sockaddr_in svraddr;
  socklen_t svraddrlen=sizeof(struct sockaddr_in);
  clnsock_fd=socket(AF_INET,SOCK_STREAM,0);
  svraddr.sin_family=AF_INET;
  svraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  svraddr.sin_port=htons(PORT);
  connect(clnsock_fd,(struct sockaddr*)&svraddr,svraddrlen);
  while(1)
  {
    memset(message,0,sizeof(message));
    printf("enter data for TCP/IP");
    gets(message);
    send(clnsock_fd,message,strlen(message),0);
    if(strcmp(message,"exit")==0)break;
  }
}
