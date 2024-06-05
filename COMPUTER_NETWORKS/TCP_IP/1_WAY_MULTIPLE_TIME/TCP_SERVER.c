#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8090
void main()
{
  int opt=1;
  int svrsock_fd,new_conn;
  char buffer[1024];
  struct sockaddr_in address;
  socklen_t addrlen=sizeof(struct sockaddr_in);
  svrsock_fd=socket(AF_INET,SOCK_STREAM,0);
  setsockopt(svrsock_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
  address.sin_family=AF_INET;
  address.sin_addr.s_addr=INADDR_ANY;
  address.sin_port=htons(PORT);
  bind(svrsock_fd,(struct sockaddr *)&address,addrlen);
  printf("WAITING FOR CLIENT\n");
  listen(svrsock_fd,3);
  new_conn=accept(svrsock_fd,(struct sockaddr *)&address,&addrlen);
  while(1)
  {
    memset(buffer,0,sizeof(buffer));
    read(new_conn,buffer,1024);
    printf("Received data from TCP/IP client:%s\n",buffer);
    if(strcmp(buffer,"exit")==0) break;
  }
}
