#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void main(){
    int fd1[2], fd2[2], pid=0;
    char message[1024], buffer[1024];
    if(pipe(fd1)==-1){
        perror("PIPE CREATION FAILED\n");
        exit(0);
    }
    if(pipe(fd2)==-1){
        perror("PIPE CREATION FAILED\n");
        exit(0);
    }
    pid=fork();
    if(pid>0){
        close(fd1[0]);
        close(fd2[1]);
        while(1){
            memset(message, sizeof(message), 0);
            printf("Enter data for child: ");
            gets(message);
            write(fd1[1], message, 1024);
            if(strcmp(message,"exit")==0) break;
            memset(buffer, sizeof(buffer), 0);
            read(fd2[0],buffer,1024);
            printf("Received data from child: %s\n",buffer);
            if(strcmp(buffer, "exit")==0) break;
        }
    }
    else{
        close(fd1[1]);
        close(fd2[0]);
        while(1){
            memset(buffer, sizeof(buffer), 0);
            read(fd1[0],buffer,1024);
            printf("Received data from parent: %s\n",buffer);
            if(strcmp(buffer, "exit")==0) break;
            memset(message, sizeof(message), 0);
            printf("Enter data for parent: ");
            gets(message);
            write(fd2[1], message, 1024);
            if(strcmp(message,"exit")==0) break;
        }
    }
}
