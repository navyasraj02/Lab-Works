#include <stdio.h>

typedef struct
{
    int no, bt, ct, at, tat, wt, tbt, pt;
} process;
process p[10];

void sort(int n)
{
    int temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
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

void ct(int n)
{
    p[0].ct = p[0].at + p[0].bt;
    int i;
    for (i = 1; i < n; i++)
    {
        if (p[i].at > p[i - 1].ct)
            p[i].ct = p[i].at + p[i].bt;
        else
            p[i].ct = p[i - 1].ct + p[i].bt;
    }
}

void tat(int n)
{
    int i;
    for (i = 0; i < n; i++)
        p[i].tat = p[i].ct - p[i].at;
}

void wt(int n)
{
    int i;
    for (i = 0; i < n; i++)
        p[i].wt = p[i].tat - p[i].bt;
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

void priority(int n)
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
                if (p[j].at <= ready && p[j].pt < p[i].pt)
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

void main()
{
    int n, i, x;
    char op;
    printf("Enter no of processes :");
    scanf("%d", &n);
    // for priority give separately
    printf("Enter No AT Bt\n");
    for (i = 0; i < n; i++)
    {

        scanf("%d%d%d", &p[i].no, &p[i].at, &p[i].bt);
        p[i].tbt = p[i].bt;
    }
    printf("CPU Scheduling Algos\n1.FCFS\n2.SJF\n3.Priority\n4.RR\n");
    do
    {
        printf("Enter-1/2/3/4 : ");
        scanf("%d", &x);
        switch (x)
        {
        case 1:
            // FCFS
            sort(n);
            ct(n);
            tat(n);
            wt(n);
            break;
        case 2:
            // SJF Non preemptive
            sort(n);
            sjf(n);
            tat(n);
            wt(n);
            break;
        case 3:
            // Priority Non preemptive
            printf("Enter priority for %d processes\n:", n);
            for (i = 0; i < n; i++)
                scanf("%d", &p[i].pt);
            priority(n);
            tat(n);
            wt(n);
            break;
        case 4:
            // RR
            break;
        default:
            break;
        }
    } while (op == 'y');

    printf("No\tAT\tBt\tPT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].tbt, p[i].pt, p[i].wt, p[i].tat);
    }
}