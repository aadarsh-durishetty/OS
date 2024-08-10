#include <stdio.h>

int main()
{
    int frame_count, page_count, frames[50], pages[300], temp[100], check_1, check_2, check_3, i, j, k, pos, max, faults = 0;
    // take the page count from user
    scanf("%d", &page_count);
    // take the input of page
    for (i = 0; i < page_count; i++)
    {
        scanf("%d", &pages[i]);
    }
    // take the no of frame count
    scanf("%d", &frame_count);
    // take the input of frame array
    int frame_array[10];
    for (int i = 0; i < frame_count; i++)
    {
        scanf("%d", &frame_array[i]);
    }
    int final[10];
    for (int x = 0; x < frame_count; x++)
    {
        faults = 0;
        for (i = 0; i < frame_array[x]; ++i)
        {
            frames[i] = -1;
        }
        for (i = 0; i < page_count; ++i)
        {
            check_1 = check_2 = 0;

            for (j = 0; j < frame_array[x]; ++j)
            {
                if (frames[j] == pages[i])
                {
                    check_1 = check_2 = 1;
                    break;
                }
            }
            if (check_1 == 0)
            {
                for (j = 0; j < frame_array[x]; ++j)
                {
                    if (frames[j] == -1)
                    {
                        faults++;
                        frames[j] = pages[i];
                        check_2 = 1;
                        break;
                    }
                }
            }
            if (check_2 == 0)
            {
                check_3 = 0;

                for (j = 0; j < frame_array[x]; ++j)
                {
                    temp[j] = -1;

                    for (k = i + 1; k < page_count; ++k)
                    {
                        if (frames[j] == pages[k])
                        {
                            temp[j] = k;
                            break;
                        }
                    }
                }
                for (j = 0; j < frame_array[x]; ++j)
                {
                    if (temp[j] == -1)
                    {
                        pos = j;
                        check_3 = 1;
                        break;
                    }
                }
                if (check_3 == 0)
                {
                    max = temp[0];
                    pos = 0;

                    for (j = 1; j < frame_array[x]; ++j)
                    {
                        if (temp[j] > max)
                        {
                            max = temp[j];
                            pos = j;
                        }
                    }
                }
                frames[pos] = pages[i];
                faults++;
            }
        }

        final[x] = faults;
    }
    printf("The number of page faults: [");
    for (int m = 0; m < frame_count - 1; m++)
    {
        printf("%d, ", final[m]);
    }
    printf("%d]", final[frame_count - 1]);
    return 0;
}