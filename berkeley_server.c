#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    // Listen for connections
    listen(sockfd, 5);

    // Accept a connection
    int clientfd = accept(sockfd, NULL, NULL);
    if (clientfd < 0)
    {
        perror("accept");
        exit(1);
    }

    // Read data from the client
    char buffer[1024];
    int nread = read(clientfd, buffer, sizeof(buffer));
    if (nread < 0)
    {
        perror("read");
        exit(1);
    }

    // Write data back to the client
    write(clientfd, buffer, nread);

    // Close the sockets
    close(sockfd);
    close(clientfd);

    return 0;
}
