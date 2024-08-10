// FCFS-First come first serve
#include <stdio.h>
#define N 6

struct table
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
} p[N];

void readInput()
{
    for (int i = 0; i < N; i++)
    {
        printf("\n Enter AT and BT for process %d : ", i);
        p[i].pid = i;
        scanf("%d %d", &p[i].at, &p[i].bt);
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

void computeCT()
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += p[i].bt;
        p[i].ct = sum;
    }
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

int main()
{
    readInput();
    computeCT();
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
    printf("\nThe avg. Waiting Time and avg. Turn Around Time are : %f ms and %f ms", awt, atat);
}
