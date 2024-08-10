#include <stdio.h>
int main()
{
    int i, j, page_count, pages[200], frame[50], frame_count, k, avail, count = 0;
    // take the page count
    scanf("%d", &page_count);
    // take the input of pages
    for (i = 1; i <= page_count; i++)
    {
        scanf("%d", &pages[i]);
    }
    // take frame count as input
    scanf("%d", &frame_count);
    int ctr1[10];
    int ctr2[10];
    for (int z = 0; z < frame_count; z++)
    {
        scanf("%d", &ctr1[z]);
        for (i = 0; i < ctr1[z]; i++)
            frame[i] = -1;
        j = 0;
        for (i = 1; i <= page_count; i++)
        {
            avail = 0;
            for (k = 0; k < ctr1[z]; k++)
                if (frame[k] == pages[i])
                    avail = 1;
            if (avail == 0)
            {
                frame[j] = pages[i];
                j = (j + 1) % ctr1[z];
                count++;
            }
        }
        ctr2[z] = count;
        count = 0;
    }
    printf("The number of page faults: [");
    for (int q = 0; q < frame_count - 1; q++)
    {
        printf("%d, ", ctr2[q]);
    }
    printf("%d]", ctr2[frame_count - 1]);
    return 0;
}