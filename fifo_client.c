#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO_PATH1 "/tmp/myfifo1"
#define FIFO_PATH2 "/tmp/myfifo2"

int main()
{
    int fd1, fd2, n;
    char buffer[100], line[100];

    mkfifo(FIFO_PATH1, 0666);
    mkfifo(FIFO_PATH2, 0666);

    fd1 = open(FIFO_PATH1, O_RDONLY);
    fd2 = open(FIFO_PATH2, O_WRONLY);

    // strcpy(buffer, "Hello, my name is Soumyanil!");
    printf("Enter a line of text - ");
    fgets(line, sizeof(line), stdin);
    write(fd2, line, sizeof(line));

    n = read(fd1, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("Client received: %s\n", buffer);

    close(fd1);
    close(fd2);

    unlink(FIFO_PATH1);
    unlink(FIFO_PATH2);

    return 0;
}
