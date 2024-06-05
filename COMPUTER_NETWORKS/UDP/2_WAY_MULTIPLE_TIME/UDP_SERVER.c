#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000
#define MAXLINE 1000

// Driver code
int main()
{
    char buffer[MAXLINE];
    char message[MAXLINE];
    int listenfd, len, n;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (listenfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // bind server address to socket descriptor
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);

    while(1) {
        // receive message from client
        n = recvfrom(listenfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&cliaddr, &len);
        if (n < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[n] = '\0';
        printf("Client: %s", buffer); // Note the usage of printf to maintain the newline

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client initiated exit...\n");
            break;
        }

        printf("Enter message to send to client: ");
        fgets(message, MAXLINE, stdin);

        // send response to client
        int sent_len = sendto(listenfd, message, strlen(message), 0, (struct sockaddr*)&cliaddr, len);
        if (sent_len < 0) {
            perror("sendto failed");
            break;
        }
    }

    // close the descriptor
    close(listenfd);
    return 0;
}
