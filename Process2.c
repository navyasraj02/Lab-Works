#include <stdio.h>
#include <unistd.h>

void main()
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0)
    {
        printf("I am child process\n My pid is %d\n", getpid());
        sleep(10);
        exit(5);
    }
    else
    {
        printf("I am parent process\n My pid is %d\n", getpid());
        wait(&status);
        printf("exit status :%d\n", WEXITSTATUS(status));
        printf("exiting parent process\n");
    }
}