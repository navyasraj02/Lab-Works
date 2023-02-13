#include <stdio.h>

typedef struct
{
    int no, bt, ct, at, tat, wt, tbt, pt;
} process;
process p[10];
int q[15], front = -1, rear = -1;
void insert(int p)
{
    if (front == -1)
    {
        front = 0;
    }
    rear += 1;
    q[rear] = p;
}

int delete()
{
    int p;
    p = q[front];
    front += 1;
    return p;
}
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
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
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

void rr(int n)
{
    int t, time = 0, temp[10], exist[10] = {0}, a;
    printf("Enter time quantum :");
    scanf("%d", &t);

    insert(0);
    exist[0] = 1;
    while (front <= rear)
    {
        a = delete ();
        if (p[a].bt >= t)
        {
            p[a].bt -= t;
            time += t;
        }
        else
        {
            time += p[a].bt;
            p[a].bt = 0;
        }
        for (int i = 0; i < n; i++)
        {
            if (exist[i] == 0 && p[i].at <= time)
            {
                insert(i);
                exist[i] = 1;
            }
        }
        if (p[a].bt == 0)
        {
            p[a].tat = time - p[a].at;
            p[a].wt = p[a].tat - p[a].tbt;
        }
        else
        {
            insert(a);
        }
    }
}
void display(int n)
{
    float sum_wt = 0, sum_tat = 0, avg_wt = 0, avg_tat = 0;
    printf("No\tAT\tBt\tPT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].tbt, p[i].pt, p[i].wt, p[i].tat);
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
    }
    printf("Average waiting time : %f\n", sum_wt / n);
    printf("Average turnaround time : %f\n", sum_tat / n);
}
void main()
{
    int n, i, x;
    char op;
    printf("Enter no of processes :");
    scanf("%d", &n);
    // for priority give separately
    printf("Enter AT Bt\n");
    for (i = 0; i < n; i++)
    {

        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].tbt = p[i].bt;
        p[i].no = i + 1;
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
            display(n);
            break;
        case 2:
            // SJF Non preemptive
            sort(n);
            sjf(n);
            tat(n);
            wt(n);
            display(n);
            break;
        case 3:
            // Priority Non preemptive
            printf("Enter priority for %d processes\n:", n);
            for (i = 0; i < n; i++)
                scanf("%d", &p[i].pt);
            priority(n);
            tat(n);
            wt(n);
            display(n);
            break;
        case 4:
            rr(n);
            display(n);
            break;
        default:
            break;
        }
        printf("Do you want to enter more options(y/n)? :");
        scanf(" %c", &op);
    } while (op == 'y');
}