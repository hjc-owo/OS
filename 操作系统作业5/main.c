#include <stdio.h>
#include "sched.h"
int job_submitted_time[] = {0, 1, 2, 3, 12, 12, 12, 12, 200, 200};
int job_required_time[] = {4, 3, 2, 1, 6, 5, 4, 3, 1, 1};
int fcfs_result[10];
int sjf_result[10];

int main()
{
    int n = 10, i;
    FCFS(n, job_submitted_time, job_required_time, fcfs_result);
    puts("FCFS results:");
    for (i = 0; i < n; ++i)
        printf("job % 2d: [% 9d]\n", i, fcfs_result[i]);
    SJF(n, job_submitted_time, job_required_time, sjf_result);
    puts("SJF results:");
    for (i = 0; i < n; ++i)
        printf("job % 2d: [% 9d]\n", i, sjf_result[i]);
}