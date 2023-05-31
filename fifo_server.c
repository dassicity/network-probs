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
    int fd1, fd2;
    char buffer[100];

    mkfifo(FIFO_PATH1, 0666);
    mkfifo(FIFO_PATH2, 0666);

    fd1 = open(FIFO_PATH1, O_RDONLY);
    fd2 = open(FIFO_PATH2, O_WRONLY);

    read(fd1, buffer, sizeof(buffer));
    printf("Server received: %s\n", buffer);

    strcpy(buffer, "Greetings from server!");
    write(fd2, buffer, sizeof(buffer));

    close(fd1);
    close(fd2);

    unlink(FIFO_PATH1);
    unlink(FIFO_PATH2);

    return 0;
}
