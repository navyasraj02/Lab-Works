#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
void main()
{
    pid_t pid;
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