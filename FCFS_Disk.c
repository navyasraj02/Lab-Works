#include <stdio.h>
#include <stdlib.h>

void fcfs(int req[], int n, int head)
{
    int curr, i, distance, seek = 0;
    for (i = 0; i < n; i++)
    {
        curr = req[i];
        distance = abs(curr - head);
        seek += distance;
        head = curr;
    }
    printf("The total seek time is %d sec", seek);
}

void main()
{
    int head, n, i;
    printf("Enter no of requests :");
    scanf("%d", &n);
    int req[n];
    printf("Enter request sequence : ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);
    printf("Enter head:");
    scanf("%d", &head);
    fcfs(req, n, head);
}