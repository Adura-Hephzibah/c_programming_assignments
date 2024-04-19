// Server Side (server.c)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CLIENTS 5

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main()
{
    int sockfd, newsockfd, client_count = 0;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024] = {0};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, MAX_CLIENTS) != 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    int len = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (newsockfd < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recv(newsockfd, buffer, sizeof(buffer), 0);
        printf("Received: %s\n", buffer);
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}
