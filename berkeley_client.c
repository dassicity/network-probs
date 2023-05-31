#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

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
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    // Send data to the server
    char buffer[1024];
    scanf("%s", buffer);
    int nwrite = write(sockfd, buffer, strlen(buffer));
    if (nwrite < 0)
    {
        perror("write");
        exit(1);
    }

    // Read data from the server
    int nread = read(sockfd, buffer, sizeof(buffer));
    if (nread < 0)
    {
        perror("read");
        exit(1);
    }

    // Print the data from the server
    printf("Received from server: %s\n", buffer);

    // Close the socket
    close(sockfd);

    return 0;
}