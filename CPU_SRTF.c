// SRTF-Shortest Response Time First
#include <stdio.h>
#include <limits.h>
#define N 6

struct table
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int flag;
} p[N];

void readInput()
{
    for (int i = 0; i < N; i++)
    {
        printf("\n Enter AT and BT for process %d : ", i);
        p[i].pid = i;
        p[i].flag = 0;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
}

void print()
{
    printf("\n PID \t AT \t BT \t CT \t TAT \t WT");
    printf("\n----------------------------------------");
    for (int i = 0; i < N; i++)
    {
        printf("\n %d \t %d \t %d \t %d \t %d \t %d", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

void computeCT(int pid, int ct)
{
    p[pid].ct = ct;
}

void computeTAT()
{
    for (int i = 0; i < N; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
    }
}

void computeWT()
{
    for (int i = 0; i < N; i++)
        p[i].wt = p[i].tat - p[i].bt;
}

int findMinP(int ct)
{
    int min = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < N; i++)
    {
        if ((p[i].at <= ct) && (!p[i].flag) && (p[i].rt != 0))
        {
            if (min > p[i].rt)
            {
                min = p[i].rt;
                minIndex = i;
            }
        }
    }
    return minIndex;
}

int main()
{
    readInput();
    int total = 0;
    int ct = 0;
    for (int i = 0; i < N; i++)
    {
        total = total + p[i].bt;
    }
    while (ct != total)
    {
        int pid = findMinP(ct);
        // printf("\n %d ",pid);
        ct = ct + 1;
        // printf("\n %d",ct);
        p[pid].rt = p[pid].rt - 1;
        if (p[pid].rt == 0)
        {
            computeCT(pid, ct);
            p[pid].flag = 1;
        }
    }
    computeTAT();
    computeWT();
    float awt = 0;
    float atat = 0;
    for (int i = 0; i < N; i++)
    {
        awt += p[i].wt;
        atat += p[i].tat;
    }
    awt /= N;
    atat /= N;
    print();
    printf("\nThe avg. Waiting Time and avg. Turn Around Time are : %f ms and %f ms\n", awt, atat);
}