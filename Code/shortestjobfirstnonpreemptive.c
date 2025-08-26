#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int completed;
} Process;

int main() {
    int n, i, completed_count = 0, current_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].completed = 0;
    }

    int total_burst_time = 0;
    for (i = 0; i < n; i++) total_burst_time += processes[i].burst_time;

    Process gantt[n];
    int gantt_index = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_burst = 1e9;

        // Find process with shortest burst time among those arrived and not completed
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
                // If tie, pick process with earlier arrival time
                else if (processes[i].burst_time == min_burst) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // No process arrived yet, CPU idle
            current_time++;
        } else {
            processes[idx].start_time = current_time;
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].start_time - processes[idx].arrival_time;
            processes[idx].completed = 1;

            // Add to gantt chart
            gantt[gantt_index++] = processes[idx];

            current_time = processes[idx].completion_time;
            completed_count++;
        }
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");
    for (i = 0; i < gantt_index; i++) {
        printf("--------");
    }
    printf("\n|");

    for (i = 0; i < gantt_index; i++) {
        printf("  P%d   |", gantt[i].pid);
    }
    printf("\n ");

    for (i = 0; i < gantt_index; i++) {
        printf("--------");
    }
    printf("\n");

    // Print timeline
    printf("%d", gantt[0].start_time);
    for (i = 0; i < gantt_index; i++) {
        printf("       %d", gantt[i].completion_time);
    }
    printf("\n");

    // Print details
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
