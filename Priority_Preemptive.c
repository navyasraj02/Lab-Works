#include <stdio.h>
typedef struct
{
    int no, bt, at, tat, wt, pt;
} process;
process p[10];

void main()
{
    int n, temp[10], sp, count = 0;
    printf("Enter no of processes :");
    scanf("%d", &n);
    printf("Enter AT Bt PT\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pt);
        p[i].no = i + 1;
        temp[i] = p[i].bt;
    }
    p[9].pt = 100000;
    for (int t = 0; count != n; t++)
    {
        sp = 9;
        for (int i = 0; i < n; i++)
        {
            if (p[i].pt < p[sp].pt && p[i].at <= t && p[i].bt > 0)
            {
                sp = i;
            }
        }
        p[sp].bt -= 1;
        if (p[sp].bt == 0)
        {
            count++;
            p[sp].tat = (t + 1) - p[sp].at;
            p[sp].wt = p[sp].tat - temp[sp];
        }
    }
    printf("No\tAT\tBt\tPT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, temp[i], p[i].pt, p[i].wt, p[i].tat);
    }
}

/*#include <stdio.h>
typedef struct
{
    int no, bt, at, tat, tbt, wt, pt;
} process;
process p[10];

void main()
{
    int n, temp[10], sp, count = 0;
    printf("Enter no of processes :");
    scanf("%d", &n);
    printf("Enter AT Bt PT\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pt);
        p[i].no = i + 1;
        temp[i] = p[i].bt;
    }
    p[9].pt = 100000;
    for (int t = 0; count != n; t++)
    {
        sp = 9;
        for (int i = 0; i < n; i++)
        {
            if (p[i].pt < p[sp].pt && p[i].at <= t && p[i].bt > 0)
            {
                sp = i;
            }
        }
        p[sp].bt -= 1;
        if (p[sp].bt == 0)
        {
            count++;
            p[sp].tat = (t + 1) - p[sp].at;
            p[sp].wt = p[sp].tat - temp[sp];
        }
    }
    printf("No\tAT\tBt\tPT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, temp[i], p[i].pt, p[i].wt, p[i].tat);
    }
}*/