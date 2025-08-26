#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int started;
} Process;

int main() {
    int n, i, completed = 0, current_time = 0, prev = -1;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = 0;
    }

    int completed_count = 0;
    int total_burst_time = 0;
    for (i = 0; i < n; i++) {
        total_burst_time += processes[i].burst_time;
    }

    // Gantt chart arrays to store which process runs and at what time
    int gantt_processes[1000];
    int gantt_times[1000];
    int gantt_index = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_remaining = 1e9;

        // Find process with minimum remaining time which has arrived
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_remaining) {
                    min_remaining = processes[i].remaining_time;
                    idx = i;
                }
                else if (processes[i].remaining_time == min_remaining) {
                    // If tie, pick process with earlier arrival time
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // CPU is idle
            if (prev != -1 && gantt_processes[gantt_index-1] != 0) {
                gantt_processes[gantt_index++] = 0;
                gantt_times[gantt_index] = current_time;
            }
            current_time++;
            continue;
        }

        // If process changed, record time
        if (prev != idx) {
            gantt_processes[gantt_index++] = idx + 1;  // store process id (1-based)
            gantt_times[gantt_index - 1] = current_time;
            prev = idx;
        }

        processes[idx].remaining_time--;
        current_time++;

        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed_count++;
        }
    }
    // Close the last Gantt interval end time
    gantt_times[gantt_index] = current_time;

    // Print Gantt chart
    printf("\nGantt Chart:\n ");
    for (i = 0; i < gantt_index; i++) {
        printf("-------");
    }
    printf("\n|");

    for (i = 0; i < gantt_index; i++) {
        if (gantt_processes[i] == 0)
            printf("  IDLE |");
        else
            printf("  P%d   |", gantt_processes[i]);
    }
    printf("\n ");

    for (i = 0; i < gantt_index; i++) {
        printf("-------");
    }
    printf("\n");

    printf("%d", gantt_times[0]);
    for (i = 1; i <= gantt_index; i++) {
        printf("      %d", gantt_times[i]);
    }
    printf("\n");

    // Print process details
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
