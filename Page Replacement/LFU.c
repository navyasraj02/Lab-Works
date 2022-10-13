#include <stdio.h>

void main()
{
    int x = 0, i, j, pages[30], frames[10], counter[100], temp, flag, pf = 0, least, p, f, hit = 0;
    printf("No of pages :");
    scanf("%d", &p);
    printf("No of frames :");
    scanf("%d", &f);

    printf("Enter page seq :");
    for (i = 0; i < p; i++)
        scanf("%d", &pages[i]);

    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
        counter[pages[i]] = 0;
    }

    for (i = 0; i < p; i++)
    {
        counter[pages[i]]++;
        least = frames[0];
        temp = 0;
        flag = 1;
        for (j = 0; j < f; j++)
        {
            if (frames[j] == -1 || frames[j] == pages[i])
            {
                if (frames[j] != -1)
                    hit++;
                if (frames[j] == -1)
                {
                    frames[j] = pages[i];
                    pf++;
                }
                flag = 0;
                break;
            }
            if (counter[least] > counter[frames[j]])
            {
                least = frames[j];
                temp = j;
            }
        }
        if (flag)
        {
            pf++;
            frames[temp] = pages[i];
            counter[least] = 1;
        }
        for (j = 0; j < f; j++)
            printf("%d\t", frames[j]);
        printf("\n");
    }
    printf("No of page faults :%d\n", pf);
    printf("No of page hits :%d\n", hit);
    printf("No of page hits :%d", p - pf);
}