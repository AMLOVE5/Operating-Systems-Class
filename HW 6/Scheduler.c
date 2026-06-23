#include <stdio.h>
#include <stdlib.h>
#define MAX 1024
typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;
} Process;
/* Read pid,arrival,burst,priority lines into procs[]. */
int read_processes(const char *filename, Process procs[]) {
    FILE *file = fopen(filename, "r");
    int n = 0;
    while (n < MAX && fscanf(file, "%d,%d,%d,%d",
           &procs[n].pid, &procs[n].arrival,
           &procs[n].burst, &procs[n].priority) == 4) {
        n++;
    }
    fclose(file);
    return n;
}

/* FCFS non-preemptive run in arrival order */
void fcfs(Process orig[], int n) {
    Process p[MAX];
    for (int i = 0; i < n; i++) p[i] = orig[i];

    // sort copy by arrival
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[j].arrival < p[i].arrival) {
                Process tmp = p[i]; p[i] = p[j]; p[j] = tmp;
            }

    int t = 0;
    double total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        if (t < p[i].arrival) t = p[i].arrival;  // CPU idle until arrival
        int completion = t + p[i].burst;
        int tat = completion - p[i].arrival;
        int wt = tat - p[i].burst;
        total_tat += tat;
        total_wt += wt;
        t = completion;
    }

    printf("FCFS\n");
    printf("  Average Turnaround Time: %.2f\n", total_tat / n);
    printf("  Average Waiting Time:    %.2f\n", total_wt / n);
    printf("  Throughput:              %.4f\n\n", (double)n / t);
}

/* SJF preemptive tick-by-tick simulation. */
void sjf(Process p[], int n) {
    int remaining[MAX], completion[MAX];
    for (int i = 0; i < n; i++) remaining[i] = p[i].burst;

    int completed = 0, t = 0;
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (p[i].arrival <= t && remaining[i] > 0)
                if (idx == -1 || remaining[i] < remaining[idx])
                    idx = i;

        if (idx == -1) { t++; continue; }  // nothing ready, CPU idle
        remaining[idx]--;
        t++;
        if (remaining[idx] == 0) { completion[idx] = t; completed++; }
    }

    double total_tat = 0, total_wt = 0;
    int makespan = 0;
    for (int i = 0; i < n; i++) {
        int tat = completion[i] - p[i].arrival;
        total_tat += tat;
        total_wt += tat - p[i].burst;
        if (completion[i] > makespan) makespan = completion[i];
    }

    printf("SJF (preemptive)\n");
    printf("  Average Turnaround Time: %.2f\n", total_tat / n);
    printf("  Average Waiting Time:    %.2f\n", total_wt / n);
    printf("  Throughput:              %.4f\n\n", (double)n / makespan);
}

/* Priority preemptive lower priority # = higher priority. */
void priority_sched(Process p[], int n) {
    int remaining[MAX], completion[MAX];
    for (int i = 0; i < n; i++) remaining[i] = p[i].burst;

    int completed = 0, t = 0;
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (p[i].arrival <= t && remaining[i] > 0)
                if (idx == -1 || p[i].priority < p[idx].priority)
                    idx = i;

        if (idx == -1) { t++; continue; }
        remaining[idx]--;
        t++;
        if (remaining[idx] == 0) { completion[idx] = t; completed++; }
    }

    double total_tat = 0, total_wt = 0;
    int makespan = 0;
    for (int i = 0; i < n; i++) {
        int tat = completion[i] - p[i].arrival;
        total_tat += tat;
        total_wt += tat - p[i].burst;
        if (completion[i] > makespan) makespan = completion[i];
    }

    printf("Priority (preemptive)\n");
    printf("  Average Turnaround Time: %.2f\n", total_tat / n);
    printf("  Average Waiting Time:    %.2f\n", total_wt / n);
    printf("  Throughput:              %.4f\n\n", (double)n / makespan);
}

int main(int argc, char *argv[]) {
    Process procs[MAX];
    int n = read_processes(argv[1], procs);

    fcfs(procs, n);
    sjf(procs, n);
    priority_sched(procs, n);

    return 0;
}