#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void main(){
    int fd[2], pid=0;
    char message[1024], buffer[1024];
    if(pipe(fd)==-1){
        perror("PIPE CREATION FAILED\n");
        exit(0);
    }
    pid=fork();
    if(pid>0){
        close(fd[0]);
        while(1){
            memset(message, sizeof(message), 0);
            gets(message);
            write(fd[1], message, 1024);
            if(strcmp(message,"exit")==0) break;
        }
    }
    else{
        close(fd[1]);
        while(1){
            memset(buffer, sizeof(buffer), 0);
            read(fd[0],buffer,1024);
            printf("%s\n",buffer);
            if(strcmp(buffer, "exit")==0) break;
        }
    }
}
