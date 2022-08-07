#include <stdio.h>
#include <unistd.h>

void main()
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        printf("I am Child process\nMy pid is %d\n", getpid());
    }
    else
    {
        printf("I am Parent process\nMy pid is %d\n", getpid());
    }
}