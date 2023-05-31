#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    // Bind the socket to a port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    // Listen for connections
    listen(sockfd, 5);

    // Accept a connection
    int connfd = accept(sockfd, NULL, NULL);
    if (connfd < 0)
    {
        perror("accept");
        exit(1);
    }

    // Receive a string from the client
    char buffer[100];
    int n = read(connfd, buffer, sizeof(buffer));
    if (n < 0)
    {
        perror("read");
        exit(1);
    }

    // Reverse the string
    for (int i = 0, j = n - 1; i < j; i++, j--)
    {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    // Send the reversed string back to the client
    n = write(connfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("write");
        exit(1);
    }

    // Close the connection
    close(connfd);

    return 0;
}