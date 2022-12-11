#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void main()
{
    int fd[2], n, status;
    char buffer[100];
    pid_t p;
    pipe(fd);
    p = fork();
    if (p > 0)
    {
        // Parent process
        close(fd[0]);
        printf("Passing value to child\n");
        write(fd[1], "Hello world\n", 15);
        wait(&status);
    }
    else
    {
        // Child process
        close(fd[1]);
        n = read(fd[0], buffer, 100);
        write(1, buffer, n);
        exit(1);
    }
}
