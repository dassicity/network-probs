#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>

bool isArmstrong(int number)
{
    int originalNumber = number;
    int sum = 0;
    int numDigits = floor(log10(abs(number))) + 1;
    bool result;

    while (number != 0)
    {
        int digit = number % 10;
        sum += pow(digit, 3);
        number /= 10;
    }

    printf("%d\n", sum);

    result = (originalNumber == sum);
    printf("%d\n", result);

    return result;
}

int main()
{
    int pipefd[2];
    int number;
    bool result;

    if (pipe(pipefd) == -1)
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
        // close(pipefd[1]);
        read(pipefd[0], &number, sizeof(number));

        result = isArmstrong(number);

        printf("%d\n", result);

        write(pipefd[1], &result, sizeof(result));

        close(pipefd[0]);
    }
    else
    {
        // close(pipefd[0]);

        printf("Enter a number: ");
        scanf("%d", &number);

        write(pipefd[1], &number, sizeof(number));

        close(pipefd[1]);

        wait(NULL);

        read(pipefd[0], &result, sizeof(result));
        printf("%d\n", result);

        if (result)
            printf("%d is an Armstrong number.\n", number);
        else
            printf("%d is not an Armstrong number.\n", number);

        close(pipefd[0]);
    }

    return 0;
}
