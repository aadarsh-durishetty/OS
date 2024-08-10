#include <stdio.h>
#define N 4

struct table
{
    int pid;
    int at;
    int bt;
    int wt;
    int ct;
    int tat;
} P[N];

void printTable()
{
    printf("\n  PID \t AT \t BT \t CT \t TAT \t WT \n");
    printf("-------------------------------------------\n");

    for (int i = 0; i < N; i++)
    {
        printf("\n %d \t %d \t %d \t %d \t %d \t %d ",
               P[i].pid, P[i].at, P[i].bt, P[i].ct, P[i].tat, P[i].wt);
    }
    printf("\n -----------------------------------------");
}

void calcCT()
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum = sum + P[i].bt;
        P[i].ct = sum;
    }
}

void calcTAT()
{
    for (int i = 0; i < N; i++)
    {
        P[i].tat = P[i].ct - P[i].at;
    }
}

void calcWT()
{
    for (int i = 0; i < N; i++)
    {
        P[i].wt = P[i].tat - P[i].bt;
    }
}
int main()
{
    for (int i = 0; i < N; i++)
    {
        printf("\n Enter arrival, and burst times of a process %d: ", i);
        P[i].pid = i;
        scanf("%d %d", &P[i].at, &P[i].bt);
    }
    calcCT();
    calcTAT();
    calcWT();

    printTable();

    float awt, att;
    awt = 0.0;
    att = 0.0;

    for (int i = 0; i < N; i++)
    {
        awt = awt + P[i].wt;
        att = att + P[i].tat;
    }

    awt = awt / N;
    att = att / N;

    printf("\n Avg Waiting Time and TAT : %0.2f and %0.2f ", awt, att);
}

//-----------------------------
// FCFS-First come first serve
/*
#include <stdio.h>
#define N 6

struct table{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
}p[N];

void readInput(){
    for(int i = 0;i<N;i++){
        printf("\n Enter AT and BT for process %d : ", i);
        p[i].pid = i;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
}

void print(){
    printf("\n PID \t AT \t BT \t CT \t TAT \t WT");
    printf("\n----------------------------------------");
    for(int i = 0;i<N;i++){
        printf("\n %d \t %d \t %d \t %d \t %d \t %d",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
}

void computeCT(){
    int sum = 0;
    for(int i = 0;i<N ;i++){
        sum += p[i].bt;
        p[i].ct = sum;
    }
}

void computeTAT(){
    for(int i =0;i<N;i++){
        p[i].tat = p[i].ct - p[i].at;
    }
}

void computeWT(){
    for(int i = 0;i<N;i++)
        p[i].wt = p[i].tat - p[i].bt;
}

int main(){
    readInput();
    computeCT();
    computeTAT();
    computeWT();
    float awt= 0;float atat = 0;
    for(int  i =0;i<N;i++){
        awt += p[i].wt;
        atat += p[i].tat;
    }
    awt /= N;atat /= N;
    print();
    printf("\nThe avg. Waiting Time and avg. Turn Around Time are : %f ms and %f ms",awt,atat);
}
*/

// SJF-Shortest Jump First
/*
#include<stdio.h>
#include<limits.h>
#define N 6

struct table{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int flag;
}p[N];

void readInput(){
    for(int i = 0;i<N;i++){
        printf("\n Enter AT and BT for process %d : ", i);
        p[i].pid = i;p[i].flag =0;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
}

void print(){
    printf("\n PID \t AT \t BT \t CT \t TAT \t WT");
    printf("\n----------------------------------------");
    for(int i = 0;i<N;i++){
        printf("\n %d \t %d \t %d \t %d \t %d \t %d",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
}

void computeCT(int pid,int ct){
    p[pid].ct = ct;
}

void computeTAT(){
    for(int i =0;i<N;i++){
        p[i].tat = p[i].ct - p[i].at;
    }
}

void computeWT(){
    for(int i = 0;i<N;i++)
        p[i].wt = p[i].tat - p[i].bt;
}

int findMinP(int ct){
    int min = INT_MAX;
    int minIndex = -1;
    for(int i = 0;i<N;i++){
        if((p[i].at<=ct) && (!p[i].flag)){
            if(min>p[i].bt){
                min = p[i].bt;
                minIndex = i;
            }
        }
    }
    return minIndex;
}

int main(){
    readInput();

    int ct = 0;
    for(int i =0;i<N;i++){
        int pid = findMinP(ct);
        ct += p[pid].bt;
        computeCT(pid,ct);
        p[pid].flag = 1;
    }
    computeTAT();
    computeWT();
    float awt= 0;float atat = 0;
    for(int  i =0;i<N;i++){
        awt += p[i].wt;
        atat += p[i].tat;
    }
    awt /= N;atat /= N;
    print();
    printf("\nThe avg. Waiting Time and avg. Turn Around Time are : %f ms and %f ms\n",awt,atat);
}
*/
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