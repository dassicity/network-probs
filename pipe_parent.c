#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pipefd[2], n, pid;
    char buff[100];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        close(pipefd[1]);
        n = read(pipefd[0], buff, sizeof(buff));
        printf("Size of the data: %d\n", n);
        printf("Data: %.*s\n", n, buff);
    }
    else
    {
        printf("Parent Process\n");
        close(pipefd[0]);
        write(pipefd[1], "Data from parent", 16);
    }

    return 0;
}
