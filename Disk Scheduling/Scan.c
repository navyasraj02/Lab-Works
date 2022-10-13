#include <stdio.h>
#include <stdlib.h>

void main()
{
    int head, queue[25], q1[10], q2[10], temp, temp1 = 0, temp2 = 0, i, j, n, maxrange, diff, seek = 0;
    printf("Enter maxrange of disk :");
    scanf("%d", &maxrange);
    printf("Enter head position :");
    scanf("%d", &head);
    printf("Enter no of requests :");
    scanf("%d", &n);
    printf("Enter request sequence :");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &temp);
        if (temp > head)
        {
            q1[temp1] = temp;
            temp1++;
        }
        else
        {
            q2[temp2] = temp;
            temp2++;
        }
    }
    for (i = 0; i < temp1 - 1; i++)
    {
        for (j = i + 1; j < temp1; j++)
        {
            if (q1[i] > q1[j])
            {
                temp = q1[i];
                q1[i] = q1[j];
                q1[j] = temp;
            }
        }
    }

    for (i = 0; i < temp2 - 1; i++)
    {
        for (j = i + 1; j < temp2; j++)
        {
            if (q2[i] < q2[j])
            {
                temp = q2[i];
                q2[i] = q2[j];
                q2[j] = temp;
            }
        }
    }

    for (i = 1, j = 0; j < temp1; i++, j++)
        queue[i] = q1[j];
    queue[i] = maxrange;

    for (i = temp1 + 2, j = 0; j < temp2; i++, j++)
        queue[i] = q2[j];

    queue[0] = head;
    queue[i] = 0;

    for (j = 0; j <= n; j++)
    {
        diff = abs(queue[j + 1] - queue[j]);
        seek += diff;
    }
    printf("Total seek time is %d sec", seek);
}