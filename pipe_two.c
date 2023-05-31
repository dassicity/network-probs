#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int pipe1[2], pipe2[2], n;
    char buffer[100];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);

        n = read(pipe1[0], buffer, sizeof(buffer));
        printf("Child Process received: %.*s\n", n, buffer);
        write(pipe2[1], "Message from Child", 18);

        close(pipe1[0]);
        close(pipe2[1]);
    }
    else
    {
        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1], "Message from Parent", 19);
        n = read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent Process received: %.*s\n", n, buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}
