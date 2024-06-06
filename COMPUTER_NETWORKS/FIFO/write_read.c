#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void main(){
int fd;
char *myfifo="abc";
char message[1024],buffer[1024];
mkfifo(myfifo,0666);
while(1)
{
memset(message,0,sizeof(message));
fd=open(myfifo, O_WRONLY);
printf("Enter Input string:");
gets(message);
write(fd, message, 1024);
if(strcmp(message,"exit")==0) break;
close(fd);
memset(buffer,0,sizeof(buffer));
fd=open(myfifo, O_RDONLY);
read(fd, buffer,1024);
printf("Received data: %s\n",buffer);
if(strcmp(buffer,"exit")==0) break;
close(fd);
}
}