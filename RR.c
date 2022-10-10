#include <stdio.h>
typedef struct
{
    int no, bt, at, tat, wt;
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

int delete ()
{
    int p;
    p = q[front];
    front += 1;
    return p;
}

void main()
{
    int t, time = 0, temp[10], exist[10] = {0}, a, n;
    printf("Enter no of processes :");
    scanf("%d", &n);
    printf("Enter AT Bt\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].no = i + 1;
        temp[i] = p[i].bt;
    }
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
            p[a].wt = p[a].tat - temp[a];
        }
        else
        {
            insert(a);
        }
    }
    printf("No\tAT\tBt\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, temp[i], p[i].wt, p[i].tat);
    printf("0 | ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].bt - 1; j++)
        {
            printf("  ");
        }
        printf("P%d", p[i].no);
        for (int j = 0; j < p[i].bt - 1; j++)
        {
            printf("  ");
        }
        printf("(%d)", p[i].tat + p[i].at);
        printf("|");
    }
}

/*#include <stdio.h>
typedef struct
{
    int no, bt, at, tat, wt;
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

int delete ()
{
    int p;
    p = q[front];
    front += 1;
    return p;
}
void main()
{
    int n, temp[10], exist[10] = {0}, t, time = 0, a;
    printf("Enter no of processes :");
    scanf("%d", &n);
    printf("Enter AT Bt\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].no = i + 1;
        temp[i] = p[i].bt;
    }

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
            p[a].wt = p[a].tat - temp[a];
        }
        else
        {
            insert(a);
        }
    }
    printf("No\tAT\tBt\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, temp[i], p[i].wt, p[i].tat);
}*/