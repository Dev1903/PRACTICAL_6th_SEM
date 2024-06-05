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
    int sockfd, n;
    struct sockaddr_in servaddr;

    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // create datagram socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("Enter message to send to server: ");
        fgets(message, MAXLINE, stdin);

        if (strncmp(message, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }

        // send message to server
        int sent_len = sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)NULL, sizeof(servaddr));
        if (sent_len < 0) {
            perror("sendto failed");
            break;
        }

        // receive response from server
        n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)NULL, NULL);
        if (n < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[n] = '\0';
        printf("Server: %s", buffer); // Note the usage of printf to maintain the newline
    }

    // close the descriptor
    close(sockfd);
    return 0;
}
