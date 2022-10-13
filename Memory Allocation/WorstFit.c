#include <stdio.h>

void main()
{
    int proc[10], alloc[10], mem[10], n, m, i, j, waste = 0, idx;
    printf("No of processes :");
    scanf("%d", &n);
    printf("Enter process size :");
    for (i = 0; i < n; i++)
        scanf("%d", &proc[i]);

    printf("No of memory blocks :");
    scanf("%d", &m);
    printf("Enter memory blocks :");
    for (i = 0; i < m; i++)
        scanf("%d", &mem[i]);
    for (i = 0; i < n; i++)
        alloc[i] = -1;
    for (i = 0; i < n; i++)
    {
        idx = -1;
        for (j = 0; j < m; j++)
        {
            if (mem[j] >= proc[i])
            {
                if (idx == -1)
                    idx = j;
                else if (mem[idx] < mem[j])
                    idx = j;
            }
        }
        if (idx != -1)
        {
            alloc[i] = idx;
            mem[idx] -= proc[i];
        }
    }
    for (i = 0; i < m; i++)
    {
        waste += mem[i];
    }
    printf("Process no\tProcess size\tBlock no\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, proc[i]);
        if (alloc[i] != -1)
        {
            printf("%d\n", alloc[i] + 1);
        }
        else
        {
            printf("Not allocated\n");
        }
    }
    printf("Memory wastage :%d", waste);
}
