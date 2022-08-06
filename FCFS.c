#include <stdio.h>

typedef struct
{
    int no, bt, ct, at, tat, wt;
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

void main()
{
    int n, i;
    printf("Enter no of processes :");
    scanf("%d", &n);
    printf("Enter No AT Bt\n");
    for (i = 0; i < n; i++)
    {

        scanf("%d%d%d", &p[i].no, &p[i].at, &p[i].bt);
    }
    sort(n);
    ct(n);
    tat(n);
    wt(n);
    printf("No\tAT\tBt\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
}
