#include <stdio.h>
int queue[20];
int rear = -1, front = -1;

void enqueue(int p)
{
    if (front == -1)
        front++;
    rear++;
    queue[rear] = p;
}

int dequeue()
{
    int item;
    item = queue[front];
    if (front == rear)
        front = -1;
    else
        front++;
    return item;
}

int main()
{
    int i, j, p, f, x = 0, flag = 0, pf = 0;
    printf("No of pages :");
    scanf("%d", &p);
    printf("No of frames :");
    scanf("%d", &f);
    int pages[p], frames[f];
    printf("Enter page seq :");
    for (i = 0; i < p; i++)
        scanf("%d", &pages[i]);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    for (i = 0; i < p; i++)
    {
        flag = 0;
        for (j = 0; j < f; j++)
        {
            if (frames[j] == -1 || frames[j] == pages[i])
            {
                if (frames[j] == -1) // Case : Initially frames[] is empty
                    pf++;
                frames[j] = pages[i];
                enqueue(j);
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            // Case : Page not present in frames[]
            pf++;
            x = dequeue();
            frames[x] = pages[i];
        }

        for (j = 0; j < f; j++)
        {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }
    printf("No of page faults : %d", pf);
}