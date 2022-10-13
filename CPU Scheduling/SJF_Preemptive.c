#include <stdio.h>
typedef struct
{
    int no, at, bt, tat, wt, tbt;
} process;
process p[10];

void main()
{
    int n, i, count = 0, shortp;
    printf("Enter no of processes :");
    scanf("%d", &n);
    printf("Enter AT Bt\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].no = i + 1;
        p[i].tbt = p[i].bt;
    }
    p[9].bt = 100000;
    // SJF

    for (int t = 0; count != n; t++)
    {
        shortp = 9;
        for (int i = 0; i < n; i++)
        {
            if (p[i].bt < p[shortp].bt && (p[i].at <= t && p[i].bt > 0))
            {
                shortp = i;
            }
        }
        p[shortp].bt -= 1;
        if (p[shortp].bt == 0)
        {
            count++;
            p[shortp].tat = (t + 1) - p[shortp].at;
            p[shortp].wt = (t + 1) - p[shortp].tat;
        }
    }
    printf("No\tAT\tBt\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].tbt, p[i].wt, p[i].tat);
    }
}
