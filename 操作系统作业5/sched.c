#include "sched.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define INF (0x7fffffff)

void FCFS(
        int number_of_jobs,
        const int job_submitted_time[],
        const int job_required_time[],
        int job_sched_start[]) {
    int time = 0;
    for (int i = 0; i < number_of_jobs; i++) {
        job_sched_start[i] = MAX(time, job_submitted_time[i]);
        time = job_sched_start[i] + job_required_time[i];
    }
}

void SJF(
        int number_of_jobs,
        const int job_submitted_time[],
        const int job_required_time[],
        int job_sched_start[]) {
    int time = 0;
    int used[number_of_jobs];
    int left = number_of_jobs;
    for (int i = 0; i < number_of_jobs; i++)
        used[i] = 0;
    while (left) {
        int min_index = -1;
        int min_value = INF;
        int next_time = INF;
        for (int i = 0; i < number_of_jobs; i++)
            if (job_submitted_time[i] <= time && !used[i] && job_required_time[i] < min_value) {
                min_index = i;
                min_value = job_required_time[i];
            } else if (job_submitted_time[i] > time && !used[i] && job_submitted_time[i] < next_time) {
                next_time = job_submitted_time[i];
            }
        if (min_index == -1) {
            time = next_time;
            continue;
        }
        job_sched_start[min_index] = MAX(time, job_submitted_time[min_index]);
        time = job_sched_start[min_index] + job_required_time[min_index];
        used[min_index] = 1;
        left--;
    }
}