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

    // Connect to the server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    // Send a string to the server
    char buffer[100];
    scanf("%s", buffer);
    int n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("write");
        exit(1);
    }

    // Receive the reversed string from the server
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
    {
        perror("read");
        exit(1);
    }

    // Print the reversed string
    printf("Reversed string: %s\n", buffer);

    // Close the connection
    close(sockfd);

    return 0;
}