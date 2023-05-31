#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
    int pipefd[2], n;
    char buff[100];

    pipe(pipefd);

    printf("\nReadfd = %d", pipefd[0]);
    printf("\nWritefd = %d", pipefd[1]);

    write(pipefd[1], "Hello World!", 12);
    n = read(pipefd[0], buff, sizeof(buff));

    printf("\nSize of data: %d", n);
    printf("\nData from pipe: %s\n", buff);
}