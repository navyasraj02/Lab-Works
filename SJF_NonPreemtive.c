#include <stdio.h>
typedef struct
{
    int no, bt, at, tat, ct, wt;
} process;
process p[10];

void sort(int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                temp = p[j].at;
                p[j].at = p[j + 1].at;
                p[j + 1].at = temp;
            }
        }
    }
}

void sjf(int n)
{
    int ready, flag = 0;
    process temp;
    p[0].ct = p[0].at + p[0].bt;
    ready = p[0].ct;
    for (int i = 1; i < n; i++)
    {
        if (p[i].at <= ready)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (p[j].at <= ready && p[j].bt < p[i].bt)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
            flag = 1; // To indicate that there are processes that arrived till current ct(ready var)
        }
        if (flag == 1)
        {
            p[i].ct = p[i - 1].ct + p[i].bt;
            ready = p[i].ct;
            flag = 0;
        }
        else
        {
            p[i].ct = p[i].at + p[i].bt;
            ready = p[i].ct;
        }
    }
}

void tat(int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
    }
}

void wt(int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void main()
{
    int n, i, j;
    printf("Enter no of processes :");
    scanf("%d", &n);
    printf("Enter AT Bt\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].no = i + 1;
    }
    sort(n);
    sjf(n);
    tat(n);
    wt(n);
    printf("No\tAT\tBt\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    printf("\n");
}