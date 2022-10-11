#include <stdio.h>

int lru(int t[], int n)
{
    int min = t[0], pos = 0;
    for (int i = 0; i < n; i++)
    {
        if (t[i] < min)
        {
            pos = i;
            min = t[i];
        }
    }
    return pos;
}

void main()
{
    int i, j, f, p, counter = 0, pages[20], frames[10], time[10], flag1 = 0, flag2 = 0, x, pf = 0;
    printf("No of pages :");
    scanf("%d", &p);
    printf("No of frames :");
    scanf("%d", &f);
    printf("Enter page seq :");
    for (i = 0; i < p; i++)
        scanf("%d", &pages[i]);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    for (i = 0; i < p; i++)
    {
        flag1 = flag2 = 0;
        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }
        if (flag1 == 0)
        {
            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    frames[j] = pages[i];
                    counter++;
                    time[j] = counter;
                    pf++;
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0)
        {
            x = lru(time, f);
            counter++;
            pf++;
            time[x] = counter;
            frames[x] = pages[i];
        }
        for (j = 0; j < f; j++)
            printf("%d\t", frames[j]);
        printf("\n");
    }
    printf("No of page faults :%d", pf);
}