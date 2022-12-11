#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

void reverseString(char *str)
{
    int i;
    int l = strlen(str);
    char *begin_ptr, *end_ptr, ch;
    begin_ptr = str;
    end_ptr = str;
    for (i = 0; i < l - 1; i++)
        end_ptr++;
    for (i = 0; i < l / 2; i++)
    {
        ch = *end_ptr;
        *end_ptr = *begin_ptr;
        *begin_ptr = ch;

        begin_ptr++;
        end_ptr--;
    }
}
void main()
{
    void *sharedmem;
    char buff[100];
    int i, shmid, key;
    shmid = shmget((key_t)1122, 1024, 0666 | IPC_CREAT);
    printf("Block ID of shared memory :%d", shmid);
    sharedmem = shmat(shmid, NULL, 0);
    printf("Shared memory located at %p", sharedmem);
    printf("Enter data to be written :");
    read(0, buff, 100);
    strcpy(sharedmem, buff);
    printf("Data entered :%s", (char *)sharedmem);
    int n = strlen(sharedmem);
    reverseString((char *)sharedmem);
    printf("%s", (char *)sharedmem);
    shmdt(buff);
    shmctl(shmid, IPC_RMID, NULL);
}